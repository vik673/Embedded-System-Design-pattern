#ifndef Sensor_H

#define Sensor_H

/*## class Sensor */

typedef struct Sensor Sensor;
struct Sensor {

int filterFrequency;

int updateFrequency;

int value;

int whatKindOfInterface; /* MEMORYMAPPED or PORTMAPPED */
int *READADDR; /* address to read from sensor */
int *WRITEADDR; /* address to write to sensor */
int WRITEMASK; /* sensor command to force a read */
int SENSORPORT; /* port address for port-mapped I/O */


};

int Sensor_getFilterFrequency(const Sensor* const me);

void Sensor_setFilterFrequency(Sensor* const me, int p_filterFrequency);

int Sensor_getUpdateFrequency(const Sensor* const me);

void Sensor_setUpdateFrequency(Sensor* const me, int p_updateFrequency);

int Sensor_getValue(const Sensor* const me);

Sensor * Sensor_Create(void);

void Sensor_Destroy(Sensor* const me);

int acquireValue(Sensor *me);
    
#endif