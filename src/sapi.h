#include <math.h>

static uint16_t * direccion;
typedef uint8_t bool_t;

typedef enum {
	   CH1 = 0,
	   CH2 = 1,
	   CH3 = 2,
	   CH4 = 3,
} adcMap_t;

uint16_t adcRead( adcMap_t analogInput );