

/*=================================================================================================================================
 * Leandro Torrent <leandrotorrent92@gmail.com>
 
 Trabajo Práctico N4 - TSSE

 Se realizan pruebas unitarias para la librería "mq2.h"
 Utilicé esta librería anteriormente para sensar concentracion de humo con el sensor MQ2.
 
 Tuve problemas al momento de usar la libreria math.h, el programa al compilar no linkeaba (usando ceedling),
 por lo que tuve que dejar de usar las funciones pow() y log() para hallar valores verdaderos de concentracion de gas.
 *===============================================================================================================================

Requisitos:
    *El sistema debe poder calibrar el sensor de concentracion de gas exponiendolo
     a aire limpio (no contaminado)
    *El sistema debe poder sensar la concentracion de gas licuado de petroleo (LPG)
    *El sistema debe poder sensar la concentracion de CO 
    *El sistema debe poder sensar la concentracion de Humo (Smoke)

*/


#include "unity.h"
#include "mq2.h"
#include "mock_sapi.h"
#include <math.h>

#define RO_CLEAN_AIR_FACTOR 9.83

void setUp(void) {
    void mq2Begin();
}

void tearDown(void) {

}

//El sistema debe poder calibrar el sensor de concentracion de gas exponiendolo a aire limpio (no contaminado)
void test_calibracion_sensorMQ2(void) {
    float resistenciaSensorCleanAir = 5 * (1023 - 100)/100; //Obtenido usando la formula de MQ2MQResistanceCalculation()
    adcRead_ExpectAndReturn(CH1,100);
    float resistenciaSensorNormalizada = MQ2MQCalibration();
    TEST_ASSERT_EQUAL_UINT16((resistenciaSensorCleanAir/RO_CLEAN_AIR_FACTOR),resistenciaSensorNormalizada);
}

//El sistema debe poder sensar la concentracion de gas licuado de petroleo (LPG)
void test_obtener_LPG (void) {
    
    adcRead_ExpectAndReturn(CH1,100);
    float lpg = mq2ReadLPG();

    TEST_ASSERT_EQUAL_FLOAT(2.50133,lpg);

}
// El sistema debe poder sensar la concentracion de CO 
void test_obtener_CO (void) {
    
    adcRead_ExpectAndReturn(CH1,100);
    float co = mq2ReadCO();

    TEST_ASSERT_EQUAL_FLOAT(4.078309,co);

}

// El sistema debe poder sensar la concentracion de Humo (Smoke)
void test_obtener_smoke (void) {
    
    adcRead_ExpectAndReturn(CH1,100);
    float smoke = mq2ReadSmoke();

    TEST_ASSERT_EQUAL_FLOAT(3.242329,smoke);

}
