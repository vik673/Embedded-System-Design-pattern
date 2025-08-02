#ifndef DEADLOCK_PATTERN_H
#define DEADLOCK_PATTERN_H

#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <atomic>
#include <condition_variable>
#include <memory>
#include <iostream>
#include <string>
#include <queue>

/**
 * @brief Resource class representing a shared resource in the system
 */
class SharedResource {
private:
    std::mutex mutex_;
    std::string name_;
    int id_;
    std::atomic<bool> is_locked_;
    std::thread::id current_owner_;

public:
    explicit SharedResource(const std::string& name, int id);
    ~SharedResource() = default;

    // Lock operations
    bool try_lock();
    bool try_lock_for(const std::chrono::milliseconds& timeout);
    void lock();
    void unlock();

    // Information methods
    bool is_locked() const { return is_locked_.load(); }
    const std::string& get_name() const { return name_; }
    int get_id() const { return id_; }
    std::thread::id get_owner() const { return current_owner_; }
};

/**
 * @brief Deadlock detector that monitors resource allocation
 */
class DeadlockDetector {
private:
    std::mutex detector_mutex_;
    std::map<std::thread::id, std::vector<int>> thread_resources_;
    std::map<std::thread::id, std::vector<int>> thread_waiting_;
    std::atomic<bool> deadlock_detected_;

public:
    DeadlockDetector();
    
    void register_resource_acquisition(std::thread::id thread_id, int resource_id);
    void register_resource_release(std::thread::id thread_id, int resource_id);
    void register_waiting_for_resource(std::thread::id thread_id, int resource_id);
    void unregister_waiting_for_resource(std::thread::id thread_id, int resource_id);
    
    bool detect_deadlock();
    void print_deadlock_info();
    void reset();
    
    bool is_deadlock_detected() const { return deadlock_detected_.load(); }
};

/**
 * @brief Resource manager that provides deadlock prevention strategies
 */
class ResourceManager {
private:
    std::vector<std::unique_ptr<SharedResource>> resources_;
    std::unique_ptr<DeadlockDetector> detector_;
    std::mutex manager_mutex_;
    
    // Lock ordering for prevention
    std::vector<int> lock_order_;
    
public:
    ResourceManager();
    ~ResourceManager() = default;
    
    // Resource management
    int create_resource(const std::string& name);
    SharedResource* get_resource(int id);
    
    // Deadlock prevention strategies
    bool acquire_resources_ordered(const std::vector<int>& resource_ids, 
                                 const std::chrono::milliseconds& timeout = std::chrono::milliseconds(1000));
    void release_resources(const std::vector<int>& resource_ids);
    
    // Banking algorithm for safe resource allocation
    bool is_safe_state(const std::vector<int>& request, std::thread::id thread_id);
    
    // Monitoring
    void print_resource_status();
    bool check_for_deadlock();
    
    DeadlockDetector* get_detector() { return detector_.get(); }
};

/**
 * @brief Demonstrates classic deadlock scenarios
 */
class DeadlockDemo {
private:
    std::unique_ptr<ResourceManager> resource_manager_;
    std::vector<std::thread> threads_;
    std::atomic<bool> demo_running_;
    
public:
    DeadlockDemo();
    ~DeadlockDemo();
    
    // Demo scenarios
    void run_classic_deadlock_demo();
    void run_dining_philosophers_demo();
    void run_banking_problem_demo();
    void run_prevention_demo();
    
    // Individual scenario methods
    void classic_deadlock_scenario();
    void deadlock_prevention_scenario();
    void banker_algorithm_demo();
    
    // Utility methods
    void wait_for_threads();
    void cleanup();
    
private:
    // Worker functions for different scenarios
    void worker_thread_1(int resource1_id, int resource2_id);
    void worker_thread_2(int resource1_id, int resource2_id);
    void philosopher_thread(int philosopher_id, int left_fork, int right_fork);
    void banker_client_thread(int client_id, const std::vector<int>& max_resources);
};

/**
 * @brief RAII wrapper for safe resource acquisition
 */
class ScopedResourceLock {
private:
    std::vector<SharedResource*> resources_;
    bool locked_;
    
public:
    explicit ScopedResourceLock(const std::vector<SharedResource*>& resources);
    ~ScopedResourceLock();
    
    bool try_lock_all(const std::chrono::milliseconds& timeout = std::chrono::milliseconds(1000));
    void unlock_all();
    
    bool is_locked() const { return locked_; }
};

/**
 * @brief Performance monitor for deadlock pattern analysis
 */
class PerformanceMonitor {
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    std::atomic<int> deadlock_count_;
    std::atomic<int> successful_acquisitions_;
    std::atomic<int> timeout_count_;
    
public:
    PerformanceMonitor();
    
    void start_monitoring();
    void stop_monitoring();
    void record_deadlock();
    void record_successful_acquisition();
    void record_timeout();
    
    void print_statistics();
    void reset_statistics();
};

// Utility functions for demonstration
namespace DeadlockUtils {
    void simulate_work(const std::chrono::milliseconds& duration);
    void print_thread_info(const std::string& message);
    std::string get_current_thread_id_string();
}

#endif // DEADLOCK_PATTERN_H
