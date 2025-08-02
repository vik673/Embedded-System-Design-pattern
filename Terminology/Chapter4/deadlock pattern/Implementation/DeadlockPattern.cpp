#include "DeadlockPattern.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// ================================
// SharedResource Implementation
// ================================

SharedResource::SharedResource(const std::string& name, int id)
    : name_(name), id_(id), is_locked_(false), current_owner_(std::thread::id{}) {
}

bool SharedResource::try_lock() {
    bool expected = false;
    if (is_locked_.compare_exchange_strong(expected, true)) {
        std::lock_guard<std::mutex> lock(mutex_);
        current_owner_ = std::this_thread::get_id();
        return true;
    }
    return false;
}

bool SharedResource::try_lock_for(const std::chrono::milliseconds& timeout) {
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < timeout) {
        if (try_lock()) {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return false;
}

void SharedResource::lock() {
    std::lock_guard<std::mutex> lock(mutex_);
    while (is_locked_.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    is_locked_.store(true);
    current_owner_ = std::this_thread::get_id();
}

void SharedResource::unlock() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (current_owner_ == std::this_thread::get_id()) {
        current_owner_ = std::thread::id{};
        is_locked_.store(false);
    }
}

// ================================
// DeadlockDetector Implementation
// ================================

DeadlockDetector::DeadlockDetector() : deadlock_detected_(false) {
}

void DeadlockDetector::register_resource_acquisition(std::thread::id thread_id, int resource_id) {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    thread_resources_[thread_id].push_back(resource_id);
    
    // Remove from waiting list if present
    auto& waiting = thread_waiting_[thread_id];
    waiting.erase(std::remove(waiting.begin(), waiting.end(), resource_id), waiting.end());
}

void DeadlockDetector::register_resource_release(std::thread::id thread_id, int resource_id) {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    auto& resources = thread_resources_[thread_id];
    resources.erase(std::remove(resources.begin(), resources.end(), resource_id), resources.end());
}

void DeadlockDetector::register_waiting_for_resource(std::thread::id thread_id, int resource_id) {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    thread_waiting_[thread_id].push_back(resource_id);
}

void DeadlockDetector::unregister_waiting_for_resource(std::thread::id thread_id, int resource_id) {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    auto& waiting = thread_waiting_[thread_id];
    waiting.erase(std::remove(waiting.begin(), waiting.end(), resource_id), waiting.end());
}

bool DeadlockDetector::detect_deadlock() {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    
    // Simple deadlock detection: check for circular wait
    for (const auto& [thread1, waiting1] : thread_waiting_) {
        for (int waiting_resource : waiting1) {
            // Find who owns this resource
            for (const auto& [thread2, owned2] : thread_resources_) {
                if (thread1 != thread2 && 
                    std::find(owned2.begin(), owned2.end(), waiting_resource) != owned2.end()) {
                    
                    // Check if thread2 is waiting for resources owned by thread1
                    const auto& waiting2 = thread_waiting_.find(thread2);
                    if (waiting2 != thread_waiting_.end()) {
                        const auto& owned1 = thread_resources_[thread1];
                        for (int resource : waiting2->second) {
                            if (std::find(owned1.begin(), owned1.end(), resource) != owned1.end()) {
                                deadlock_detected_.store(true);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    deadlock_detected_.store(false);
    return false;
}

void DeadlockDetector::print_deadlock_info() {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    
    std::cout << "\n=== DEADLOCK DETECTION REPORT ===\n";
    std::cout << "Deadlock Status: " << (deadlock_detected_.load() ? "DETECTED" : "NONE") << "\n\n";
    
    std::cout << "Thread Resource Ownership:\n";
    for (const auto& [thread_id, resources] : thread_resources_) {
        std::cout << "Thread " << std::hex << thread_id << " owns: ";
        for (int res : resources) {
            std::cout << "R" << res << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nThread Waiting Status:\n";
    for (const auto& [thread_id, waiting] : thread_waiting_) {
        if (!waiting.empty()) {
            std::cout << "Thread " << std::hex << thread_id << " waiting for: ";
            for (int res : waiting) {
                std::cout << "R" << res << " ";
            }
            std::cout << "\n";
        }
    }
    std::cout << "==================================\n\n";
}

void DeadlockDetector::reset() {
    std::lock_guard<std::mutex> lock(detector_mutex_);
    thread_resources_.clear();
    thread_waiting_.clear();
    deadlock_detected_.store(false);
}

// ================================
// ResourceManager Implementation
// ================================

ResourceManager::ResourceManager() {
    detector_ = std::make_unique<DeadlockDetector>();
}

int ResourceManager::create_resource(const std::string& name) {
    std::lock_guard<std::mutex> lock(manager_mutex_);
    int id = static_cast<int>(resources_.size());
    resources_.push_back(std::make_unique<SharedResource>(name, id));
    lock_order_.push_back(id);
    return id;
}

SharedResource* ResourceManager::get_resource(int id) {
    std::lock_guard<std::mutex> lock(manager_mutex_);
    if (id >= 0 && id < static_cast<int>(resources_.size())) {
        return resources_[id].get();
    }
    return nullptr;
}

bool ResourceManager::acquire_resources_ordered(const std::vector<int>& resource_ids,
                                               const std::chrono::milliseconds& timeout) {
    // Sort resource IDs to ensure consistent ordering
    std::vector<int> sorted_ids = resource_ids;
    std::sort(sorted_ids.begin(), sorted_ids.end());
    
    std::vector<SharedResource*> acquired_resources;
    auto start_time = std::chrono::steady_clock::now();
    
    for (int id : sorted_ids) {
        SharedResource* resource = get_resource(id);
        if (!resource) {
            // Release already acquired resources
            for (auto* res : acquired_resources) {
                res->unlock();
                detector_->register_resource_release(std::this_thread::get_id(), res->get_id());
            }
            return false;
        }
        
        auto remaining_time = timeout - (std::chrono::steady_clock::now() - start_time);
        if (remaining_time <= std::chrono::milliseconds(0)) {
            // Timeout exceeded
            for (auto* res : acquired_resources) {
                res->unlock();
                detector_->register_resource_release(std::this_thread::get_id(), res->get_id());
            }
            return false;
        }
        
        detector_->register_waiting_for_resource(std::this_thread::get_id(), id);
        
        if (resource->try_lock_for(std::chrono::duration_cast<std::chrono::milliseconds>(remaining_time))) {
            acquired_resources.push_back(resource);
            detector_->register_resource_acquisition(std::this_thread::get_id(), id);
            detector_->unregister_waiting_for_resource(std::this_thread::get_id(), id);
        } else {
            // Failed to acquire resource, release all previously acquired
            detector_->unregister_waiting_for_resource(std::this_thread::get_id(), id);
            for (auto* res : acquired_resources) {
                res->unlock();
                detector_->register_resource_release(std::this_thread::get_id(), res->get_id());
            }
            return false;
        }
    }
    
    return true;
}

void ResourceManager::release_resources(const std::vector<int>& resource_ids) {
    for (int id : resource_ids) {
        SharedResource* resource = get_resource(id);
        if (resource) {
            resource->unlock();
            detector_->register_resource_release(std::this_thread::get_id(), id);
        }
    }
}

bool ResourceManager::is_safe_state(const std::vector<int>& request, std::thread::id thread_id) {
    // Simplified banker's algorithm check
    // In a real implementation, this would check against available resources
    // and maximum resource needs
    return true; // Simplified for demonstration
}

void ResourceManager::print_resource_status() {
    std::lock_guard<std::mutex> lock(manager_mutex_);
    
    std::cout << "\n=== RESOURCE STATUS ===\n";
    for (const auto& resource : resources_) {
        std::cout << "Resource " << resource->get_id() << " (" << resource->get_name() << "): ";
        if (resource->is_locked()) {
            std::cout << "LOCKED by thread " << std::hex << resource->get_owner();
        } else {
            std::cout << "AVAILABLE";
        }
        std::cout << "\n";
    }
    std::cout << "=======================\n\n";
}

bool ResourceManager::check_for_deadlock() {
    return detector_->detect_deadlock();
}

// ================================
// DeadlockDemo Implementation
// ================================

DeadlockDemo::DeadlockDemo() : demo_running_(false) {
    resource_manager_ = std::make_unique<ResourceManager>();
}

DeadlockDemo::~DeadlockDemo() {
    cleanup();
}

void DeadlockDemo::run_classic_deadlock_demo() {
    std::cout << "\n========================================\n";
    std::cout << "CLASSIC DEADLOCK DEMONSTRATION\n";
    std::cout << "========================================\n";
    
    // Create two resources
    int resource1 = resource_manager_->create_resource("DatabaseConnection");
    int resource2 = resource_manager_->create_resource("FileHandle");
    
    std::cout << "Created resources: R" << resource1 << " (DatabaseConnection) and R" << resource2 << " (FileHandle)\n";
    std::cout << "Starting two threads that will acquire locks in different orders...\n\n";
    
    demo_running_.store(true);
    
    // Start two threads that will create a deadlock
    threads_.emplace_back(&DeadlockDemo::worker_thread_1, this, resource1, resource2);
    threads_.emplace_back(&DeadlockDemo::worker_thread_2, this, resource1, resource2);
    
    // Monitor for deadlock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    for (int i = 0; i < 10 && demo_running_.load(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        if (resource_manager_->check_for_deadlock()) {
            std::cout << "*** DEADLOCK DETECTED! ***\n";
            resource_manager_->get_detector()->print_deadlock_info();
            break;
        }
        
        resource_manager_->print_resource_status();
    }
    
    demo_running_.store(false);
    wait_for_threads();
    resource_manager_->get_detector()->reset();
}

void DeadlockDemo::run_prevention_demo() {
    std::cout << "\n========================================\n";
    std::cout << "DEADLOCK PREVENTION DEMONSTRATION\n";
    std::cout << "========================================\n";
    
    // Create resources
    int resource1 = resource_manager_->create_resource("NetworkSocket");
    int resource2 = resource_manager_->create_resource("MemoryBuffer");
    int resource3 = resource_manager_->create_resource("HardwareRegister");
    
    std::cout << "Created resources: R" << resource1 << ", R" << resource2 << ", R" << resource3 << "\n";
    std::cout << "Using ordered resource acquisition to prevent deadlocks...\n\n";
    
    demo_running_.store(true);
    
    // Start threads using prevention strategy
    threads_.emplace_back(&DeadlockDemo::deadlock_prevention_scenario, this);
    threads_.emplace_back(&DeadlockDemo::deadlock_prevention_scenario, this);
    threads_.emplace_back(&DeadlockDemo::deadlock_prevention_scenario, this);
    
    // Monitor system
    for (int i = 0; i < 8 && demo_running_.load(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        resource_manager_->print_resource_status();
        
        if (resource_manager_->check_for_deadlock()) {
            std::cout << "*** Unexpected deadlock detected! ***\n";
            resource_manager_->get_detector()->print_deadlock_info();
        } else {
            std::cout << "✓ No deadlock detected - prevention strategy working!\n";
        }
    }
    
    demo_running_.store(false);
    wait_for_threads();
    resource_manager_->get_detector()->reset();
}

void DeadlockDemo::run_dining_philosophers_demo() {
    std::cout << "\n========================================\n";
    std::cout << "DINING PHILOSOPHERS DEMONSTRATION\n";
    std::cout << "========================================\n";
    
    const int num_philosophers = 5;
    std::vector<int> forks;
    
    // Create forks (resources)
    for (int i = 0; i < num_philosophers; ++i) {
        forks.push_back(resource_manager_->create_resource("Fork" + std::to_string(i)));
    }
    
    std::cout << "Created " << num_philosophers << " philosophers and " << num_philosophers << " forks\n";
    std::cout << "Each philosopher needs two adjacent forks to eat...\n\n";
    
    demo_running_.store(true);
    
    // Start philosopher threads
    for (int i = 0; i < num_philosophers; ++i) {
        int left_fork = i;
        int right_fork = (i + 1) % num_philosophers;
        threads_.emplace_back(&DeadlockDemo::philosopher_thread, this, i, left_fork, right_fork);
    }
    
    // Monitor for deadlock
    for (int i = 0; i < 15 && demo_running_.load(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        if (resource_manager_->check_for_deadlock()) {
            std::cout << "*** DEADLOCK DETECTED in dining philosophers! ***\n";
            resource_manager_->get_detector()->print_deadlock_info();
            break;
        }
        
        resource_manager_->print_resource_status();
    }
    
    demo_running_.store(false);
    wait_for_threads();
    resource_manager_->get_detector()->reset();
}

void DeadlockDemo::worker_thread_1(int resource1_id, int resource2_id) {
    DeadlockUtils::print_thread_info("Worker Thread 1 starting");
    
    while (demo_running_.load()) {
        DeadlockUtils::print_thread_info("Attempting to acquire R" + std::to_string(resource1_id) + " first");
        
        auto* resource1 = resource_manager_->get_resource(resource1_id);
        if (resource1 && resource1->try_lock_for(std::chrono::milliseconds(100))) {
            resource_manager_->get_detector()->register_resource_acquisition(std::this_thread::get_id(), resource1_id);
            DeadlockUtils::print_thread_info("Acquired R" + std::to_string(resource1_id));
            
            DeadlockUtils::simulate_work(std::chrono::milliseconds(200));
            
            DeadlockUtils::print_thread_info("Attempting to acquire R" + std::to_string(resource2_id));
            auto* resource2 = resource_manager_->get_resource(resource2_id);
            resource_manager_->get_detector()->register_waiting_for_resource(std::this_thread::get_id(), resource2_id);
            
            if (resource2 && resource2->try_lock_for(std::chrono::milliseconds(1000))) {
                resource_manager_->get_detector()->register_resource_acquisition(std::this_thread::get_id(), resource2_id);
                resource_manager_->get_detector()->unregister_waiting_for_resource(std::this_thread::get_id(), resource2_id);
                DeadlockUtils::print_thread_info("Acquired R" + std::to_string(resource2_id));
                
                DeadlockUtils::simulate_work(std::chrono::milliseconds(300));
                
                resource2->unlock();
                resource_manager_->get_detector()->register_resource_release(std::this_thread::get_id(), resource2_id);
                DeadlockUtils::print_thread_info("Released R" + std::to_string(resource2_id));
            } else {
                resource_manager_->get_detector()->unregister_waiting_for_resource(std::this_thread::get_id(), resource2_id);
                DeadlockUtils::print_thread_info("Failed to acquire R" + std::to_string(resource2_id));
            }
            
            resource1->unlock();
            resource_manager_->get_detector()->register_resource_release(std::this_thread::get_id(), resource1_id);
            DeadlockUtils::print_thread_info("Released R" + std::to_string(resource1_id));
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    DeadlockUtils::print_thread_info("Worker Thread 1 exiting");
}

void DeadlockDemo::worker_thread_2(int resource1_id, int resource2_id) {
    DeadlockUtils::print_thread_info("Worker Thread 2 starting");
    
    while (demo_running_.load()) {
        DeadlockUtils::print_thread_info("Attempting to acquire R" + std::to_string(resource2_id) + " first");
        
        auto* resource2 = resource_manager_->get_resource(resource2_id);
        if (resource2 && resource2->try_lock_for(std::chrono::milliseconds(100))) {
            resource_manager_->get_detector()->register_resource_acquisition(std::this_thread::get_id(), resource2_id);
            DeadlockUtils::print_thread_info("Acquired R" + std::to_string(resource2_id));
            
            DeadlockUtils::simulate_work(std::chrono::milliseconds(200));
            
            DeadlockUtils::print_thread_info("Attempting to acquire R" + std::to_string(resource1_id));
            auto* resource1 = resource_manager_->get_resource(resource1_id);
            resource_manager_->get_detector()->register_waiting_for_resource(std::this_thread::get_id(), resource1_id);
            
            if (resource1 && resource1->try_lock_for(std::chrono::milliseconds(1000))) {
                resource_manager_->get_detector()->register_resource_acquisition(std::this_thread::get_id(), resource1_id);
                resource_manager_->get_detector()->unregister_waiting_for_resource(std::this_thread::get_id(), resource1_id);
                DeadlockUtils::print_thread_info("Acquired R" + std::to_string(resource1_id));
                
                DeadlockUtils::simulate_work(std::chrono::milliseconds(300));
                
                resource1->unlock();
                resource_manager_->get_detector()->register_resource_release(std::this_thread::get_id(), resource1_id);
                DeadlockUtils::print_thread_info("Released R" + std::to_string(resource1_id));
            } else {
                resource_manager_->get_detector()->unregister_waiting_for_resource(std::this_thread::get_id(), resource1_id);
                DeadlockUtils::print_thread_info("Failed to acquire R" + std::to_string(resource1_id));
            }
            
            resource2->unlock();
            resource_manager_->get_detector()->register_resource_release(std::this_thread::get_id(), resource2_id);
            DeadlockUtils::print_thread_info("Released R" + std::to_string(resource2_id));
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    DeadlockUtils::print_thread_info("Worker Thread 2 exiting");
}

void DeadlockDemo::deadlock_prevention_scenario() {
    std::string thread_name = "Prevention Thread " + DeadlockUtils::get_current_thread_id_string();
    DeadlockUtils::print_thread_info(thread_name + " starting");
    
    while (demo_running_.load()) {
        // Use ordered resource acquisition to prevent deadlock
        std::vector<int> needed_resources = {0, 1, 2}; // All three resources
        
        DeadlockUtils::print_thread_info(thread_name + " attempting ordered acquisition");
        
        if (resource_manager_->acquire_resources_ordered(needed_resources, std::chrono::milliseconds(2000))) {
            DeadlockUtils::print_thread_info(thread_name + " successfully acquired all resources");
            
            // Simulate work with resources
            DeadlockUtils::simulate_work(std::chrono::milliseconds(1000));
            
            resource_manager_->release_resources(needed_resources);
            DeadlockUtils::print_thread_info(thread_name + " released all resources");
        } else {
            DeadlockUtils::print_thread_info(thread_name + " failed to acquire resources (timeout)");
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    
    DeadlockUtils::print_thread_info(thread_name + " exiting");
}

void DeadlockDemo::philosopher_thread(int philosopher_id, int left_fork, int right_fork) {
    std::string philosopher_name = "Philosopher " + std::to_string(philosopher_id);
    DeadlockUtils::print_thread_info(philosopher_name + " sitting down");
    
    while (demo_running_.load()) {
        // Think
        DeadlockUtils::print_thread_info(philosopher_name + " thinking");
        DeadlockUtils::simulate_work(std::chrono::milliseconds(1000 + (rand() % 1000)));
        
        // Try to eat (acquire both forks with ordering to prevent deadlock)
        std::vector<int> forks = {left_fork, right_fork};
        
        DeadlockUtils::print_thread_info(philosopher_name + " hungry, trying to acquire forks");
        
        if (resource_manager_->acquire_resources_ordered(forks, std::chrono::milliseconds(2000))) {
            DeadlockUtils::print_thread_info(philosopher_name + " eating");
            DeadlockUtils::simulate_work(std::chrono::milliseconds(500 + (rand() % 1000)));
            
            resource_manager_->release_resources(forks);
            DeadlockUtils::print_thread_info(philosopher_name + " finished eating, put down forks");
        } else {
            DeadlockUtils::print_thread_info(philosopher_name + " couldn't get forks, staying hungry");
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    DeadlockUtils::print_thread_info(philosopher_name + " leaving the table");
}

void DeadlockDemo::wait_for_threads() {
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads_.clear();
}

void DeadlockDemo::cleanup() {
    demo_running_.store(false);
    wait_for_threads();
}

// ================================
// ScopedResourceLock Implementation
// ================================

ScopedResourceLock::ScopedResourceLock(const std::vector<SharedResource*>& resources)
    : resources_(resources), locked_(false) {
}

ScopedResourceLock::~ScopedResourceLock() {
    if (locked_) {
        unlock_all();
    }
}

bool ScopedResourceLock::try_lock_all(const std::chrono::milliseconds& timeout) {
    auto start_time = std::chrono::steady_clock::now();
    
    for (auto* resource : resources_) {
        auto remaining_time = timeout - (std::chrono::steady_clock::now() - start_time);
        if (remaining_time <= std::chrono::milliseconds(0) || 
            !resource->try_lock_for(std::chrono::duration_cast<std::chrono::milliseconds>(remaining_time))) {
            // Failed to acquire, release all previously acquired
            for (auto* acquired : resources_) {
                if (acquired == resource) break;
                acquired->unlock();
            }
            return false;
        }
    }
    
    locked_ = true;
    return true;
}

void ScopedResourceLock::unlock_all() {
    for (auto* resource : resources_) {
        resource->unlock();
    }
    locked_ = false;
}

// ================================
// PerformanceMonitor Implementation
// ================================

PerformanceMonitor::PerformanceMonitor() 
    : deadlock_count_(0), successful_acquisitions_(0), timeout_count_(0) {
}

void PerformanceMonitor::start_monitoring() {
    start_time_ = std::chrono::high_resolution_clock::now();
    reset_statistics();
}

void PerformanceMonitor::stop_monitoring() {
    // Monitoring stopped
}

void PerformanceMonitor::record_deadlock() {
    deadlock_count_.fetch_add(1);
}

void PerformanceMonitor::record_successful_acquisition() {
    successful_acquisitions_.fetch_add(1);
}

void PerformanceMonitor::record_timeout() {
    timeout_count_.fetch_add(1);
}

void PerformanceMonitor::print_statistics() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);
    
    std::cout << "\n=== PERFORMANCE STATISTICS ===\n";
    std::cout << "Monitoring Duration: " << duration.count() << " ms\n";
    std::cout << "Deadlocks Detected: " << deadlock_count_.load() << "\n";
    std::cout << "Successful Acquisitions: " << successful_acquisitions_.load() << "\n";
    std::cout << "Timeouts: " << timeout_count_.load() << "\n";
    std::cout << "================================\n\n";
}

void PerformanceMonitor::reset_statistics() {
    deadlock_count_.store(0);
    successful_acquisitions_.store(0);
    timeout_count_.store(0);
}

// ================================
// DeadlockUtils Implementation
// ================================

namespace DeadlockUtils {
    void simulate_work(const std::chrono::milliseconds& duration) {
        std::this_thread::sleep_for(duration);
    }
    
    void print_thread_info(const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::cout << "[" << std::put_time(std::localtime(&time_t), "%H:%M:%S") 
                  << "." << std::setfill('0') << std::setw(3) << ms.count() 
                  << "] Thread " << std::hex << std::this_thread::get_id() 
                  << ": " << message << std::endl;
    }
    
    std::string get_current_thread_id_string() {
        std::stringstream ss;
        ss << std::hex << std::this_thread::get_id();
        return ss.str().substr(0, 4); // Return first 4 characters for brevity
    }
}

// ================================
// Main Function for Demonstration
// ================================

int main() {
    std::cout << "========================================\n";
    std::cout << "   DEADLOCK PATTERN DEMONSTRATION\n";
    std::cout << "   Embedded Systems Design Patterns\n";
    std::cout << "========================================\n\n";
    
    PerformanceMonitor monitor;
    monitor.start_monitoring();
    
    DeadlockDemo demo;
    
    try {
        // Run classic deadlock demonstration
        demo.run_classic_deadlock_demo();
        
        std::cout << "\nPress Enter to continue to prevention demo...";
        std::cin.get();
        
        // Run deadlock prevention demonstration
        demo.run_prevention_demo();
        
        std::cout << "\nPress Enter to continue to dining philosophers demo...";
        std::cin.get();
        
        // Run dining philosophers demonstration
        demo.run_dining_philosophers_demo();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    
    monitor.stop_monitoring();
    monitor.print_statistics();
    
    std::cout << "\n========================================\n";
    std::cout << "   DEADLOCK PATTERN DEMO COMPLETED\n";
    std::cout << "========================================\n";
    
    return 0;
}
