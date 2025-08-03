# Channel Pattern

## Overview
The Channel Pattern defines an end-to-end processing chain that transfers data from sensor acquisition through a series of data transformations to final actuation. Each channel is a self-contained unit that can be replicated for redundancy to enhance safety and reliability. Channels process data sequentially through different transformation steps. In our example, an EMGChannel acquires a raw voltage from an EMG sensor, converts it to a frequency, applies a moving average filter, and finally converts the filtered frequency to a light color for output.

## Diagram Overview

### Class Diagram
The class diagram (see *ClassDiagram.puml*) shows the main components:
- **EMGChannel**  
  The container that links the various transformation stages.
- **EMGSensorDeviceDriver**  
  Acquires raw sensor data.
- **ConvertToFrequency**  
  Converts voltage data to frequency.
- **movingAverageFilter**  
  Smooths out rapid fluctuations in the computed frequency.
- **CalculateColor**  
  Maps the filtered frequency to RGB values.
- **LightDeviceDriver**  
  Drives the actuator (light) with the computed color.

*Explanation:*  
The diagram depicts how the EMGChannel aggregates several processing objects, each representing a distinct processing stage. The links between these objects (set up via initialization functions) form the channel’s processing pipeline. Data flows from the sensor driver, through the conversion and filtering stages, and finally to the device driver, enabling redundancy and fault identification.

### Sequence Diagram
The sequence diagram (see *SequenceDiagram.puml*) illustrates the synchronous processing of a data sample:
1. The channel’s **acquireData()** method is called.
2. **EMGSensorDeviceDriver_acquireData()** collects raw voltage.
3. The data is passed to **ConvertToFrequency_computeFreq()** which calculates the fundamental frequency.
4. The computed frequency flows into **movingAverageFilter_filter()** for smoothing.
5. The filtered result is then processed by **CalculateColor_freqToColor()**, computing an RGB value.
6. Finally, **LightDeviceDriver_setLightColor()** is invoked to update the actuator output.

*Explanation:*  
This sequence shows the step-by-step handoff of data between channel components. Each processing stage executes its function and passes the result along the chain. This clear flow ensures end-to-end integrity and makes it easier to replicate or modify individual segments for enhanced reliability.

## Usage Guidelines
- **For Understanding:**  
  Start with the Class Diagram to see how channel components are assembled and then study the Sequence Diagram for the detailed data flow.
- **For Implementation:**  
  Use the component interfaces shown in the diagrams to build a pipeline that gathers, processes, and outputs data. The channel pattern supports redundancy by allowing multiple instances or alternative transformation functions.

## Integration with Code
These diagrams relate to the following files:
- `EMGChannel.h/.c` – Implements the channel container and initialization routines.
- `EMGSensorDeviceDriver.h/.c`, `ConvertToFrequency.h/.c`, `movingAverageFilter.h/.c`, `CalculateColor.h/.c`, `LightDeviceDriver.h/.c` – Define the processing stages.

## Commands

```bash
gcc -o ChannelPattern.exe EMGChannel.c EMGSensorDeviceDriver.c ConvertToFrequency.c movingAverageFilter.c CalculateColor.c LightDeviceDriver.c ...existing code...
./ChannelPattern.exe
```
├── CalculateColor.h/.cpp           # Frequency to color mapping
├── LightDeviceDriver.h/.cpp        # RGB light controller
└── EMGChannel.h/.cpp               # Complete EMG channel
```

## Class Diagram

The class diagram shows the relationship between components:

- **Inheritance**: Data transforms inherit from AbstractDataTransform
- **Composition**: Channel contains sensors, transforms, and actuators
- **Chain of Responsibility**: Transforms are linked in a processing chain

See [ClassDiagram.md](ClassDiagram.md) for detailed UML diagrams.

## Sequence Diagrams

Three sequence diagrams illustrate different processing scenarios:

1. **Basic Channel Processing**: Synchronous data flow
2. **EMG Biofeedback Example**: Specific EMG processing steps
3. **Asynchronous Processing**: Queue-based processing with parallel stages

See [SequenceDiagram.md](SequenceDiagram.md) for detailed sequences.

## Building the Project

### Prerequisites

- C++14 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or higher

### Build Instructions

#### Windows (Visual Studio)
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
```

### Running the Demo

```bash
# From build directory
./bin/ChannelPatternDemo

# Or using CMake
cmake --build . --target run
```

## Usage Example

```cpp
#include "EMGChannel.h"

int main() {
    // Create and initialize EMG channel
    EMGChannel emgChannel;
    emgChannel.initialize();
    
    // Configure parameters
    emgChannel.setSensitivity(3);
    emgChannel.setBrightness(0.8);
    
    // Run biofeedback processing
    emgChannel.runBiofeedback(100);
    
    return 0;
}
```

## Key Design Patterns Used

### Channel Pattern
- **Purpose**: End-to-end data processing pipeline
- **Benefits**: Modularity, configurability, fault isolation
- **Implementation**: Chain of data transformations

### Chain of Responsibility
- **Purpose**: Pass data through a sequence of processors
- **Benefits**: Flexible processing pipeline, easy to extend
- **Implementation**: Each transform forwards data to the next

### Template Method (in base classes)
- **Purpose**: Define algorithm structure, allow customization
- **Benefits**: Code reuse, consistent interface
- **Implementation**: Virtual methods in base classes

### RAII (Resource Acquisition Is Initialization)
- **Purpose**: Automatic resource management
- **Benefits**: Memory safety, exception safety
- **Implementation**: Smart pointers, destructors

## Configuration Options

### EMG Sensor
- **Sensitivity**: Amplification factor for EMG signals
- **Noise Threshold**: Minimum signal level to process
- **Sampling Rate**: Data acquisition frequency

### Frequency Converter
- **Buffer Size**: Number of samples for FFT analysis
- **Sampling Rate**: Input data rate for frequency calculation

### Moving Average Filter
- **Window Size**: Number of samples to average
- **Reset Capability**: Clear filter history

### Color Calculator
- **Frequency Range**: Min/max frequencies for color mapping
- **Color Space**: HSV to RGB conversion parameters

### Light Driver
- **Brightness**: Overall light intensity (0.0-1.0)
- **Color Validation**: RGB value bounds checking

## EMG Processing Details

### Signal Acquisition
1. **Raw EMG**: Voltage readings from muscle electrodes
2. **Amplification**: Configurable gain for signal strength
3. **Noise Filtering**: Threshold-based noise removal

### Frequency Analysis
1. **Sample Collection**: Circular buffer for real-time processing
2. **Windowing**: Hamming window for frequency analysis
3. **FFT**: Discrete Fourier Transform for frequency domain
4. **Peak Detection**: Find dominant frequency component

### Signal Conditioning
1. **Moving Average**: Smooth rapid frequency changes
2. **Configurable Window**: Adjustable smoothing level
3. **Real-time Update**: Continuous filter state update

### Color Mapping
1. **Frequency Normalization**: Map to 0-1 range
2. **HSV Color Space**: Hue based on frequency
3. **RGB Conversion**: Final color values for display
4. **Brightness Control**: Adjustable intensity

## Benefits Demonstrated

- ✅ **Modularity**: Each component is independently testable
- ✅ **Configurability**: Runtime parameter adjustment
- ✅ **Extensibility**: Easy to add new transformation stages
- ✅ **Reusability**: Components work in different contexts
- ✅ **Maintainability**: Changes isolated to specific components
- ✅ **Performance**: Efficient data flow with minimal copying
- ✅ **Safety**: Memory-safe with modern C++ practices

## Potential Extensions

### Additional Transformations
- **Digital Filters**: IIR/FIR filter implementations
- **Signal Conditioning**: Calibration and linearization
- **Feature Extraction**: Statistical analysis of signals
- **Pattern Recognition**: Classification and detection

### Alternative Actuators
- **Audio Output**: Sound generation based on signals
- **Motor Control**: Physical movement actuation
- **Display Systems**: Text/graphical feedback
- **Network Output**: Remote monitoring capabilities

### Advanced Features
- **Multi-Channel**: Process multiple sensor inputs
- **Redundancy**: Fault-tolerant channel configurations
- **Calibration**: Automatic signal conditioning
- **Data Logging**: Historical data storage and analysis

## Real-World Applications

### Medical Devices
- **Biofeedback Systems**: Muscle rehabilitation therapy
- **Prosthetic Control**: EMG-controlled artificial limbs
- **Monitoring Equipment**: Continuous patient monitoring

### Industrial Control
- **Process Control**: Multi-stage manufacturing processes
- **Quality Assurance**: Real-time inspection systems
- **Safety Systems**: Fault detection and response

### Embedded Systems
- **IoT Devices**: Sensor data processing pipelines
- **Automotive**: Engine control and monitoring
- **Aerospace**: Flight control data processing

## Testing

The implementation includes several validation mechanisms:

### Component Testing
- Individual component functionality
- Parameter validation and bounds checking
- Error handling and recovery

### Integration Testing
- End-to-end data flow validation
- Chain configuration verification
- Performance benchmarking

### Simulation Testing
- Synthetic signal generation
- Known input/output validation
- Edge case handling

## Performance Considerations

### Memory Management
- **Smart Pointers**: Automatic memory cleanup
- **RAII**: Resource cleanup in destructors
- **Minimal Copying**: Efficient data passing

### Real-time Processing
- **Circular Buffers**: Efficient data storage
- **In-place Processing**: Minimize memory allocation
- **Configurable Rates**: Adjustable processing frequency

### Scalability
- **Modular Design**: Easy to add/remove components
- **Parameter Tuning**: Runtime configuration
- **Resource Monitoring**: Track memory and CPU usage

## License

This implementation is provided for educational and research purposes. See individual source files for specific licensing terms.

## Contributing

Contributions are welcome! Please follow these guidelines:

1. **Code Style**: Follow existing C++ coding conventions
2. **Documentation**: Update comments and README for changes
3. **Testing**: Add tests for new functionality
4. **Performance**: Consider real-time processing requirements

## References

1. **Real-Time Design Patterns** by Bruce Powel Douglass
2. **Embedded System Design Patterns** - Channel Pattern documentation
3. **Design Patterns: Elements of Reusable Object-Oriented Software** by Gang of Four
4. **Modern C++ Design** by Andrei Alexandrescu

---

For questions or support, please refer to the source code comments and documentation.
