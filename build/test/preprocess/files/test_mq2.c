#include "build/temp/_test_mq2.c"
#include "mock_sapi.h"
#include "src/mq2.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"








void setUp(void) {

    void mq2Begin();

}



void tearDown(void) {



}





void test_calibracion_sensorMQ2(void) {

    float resistenciaSensorCleanAir = 5 * (1023 - 100)/100;

    adcRead_CMockExpectAndReturn(43, CH1, 100);

    float resistenciaSensorNormalizada = MQ2MQCalibration();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((resistenciaSensorCleanAir/9.83))), (UNITY_INT)(UNITY_UINT16)((resistenciaSensorNormalizada)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT16);

}





void test_obtener_LPG (void) {



    adcRead_CMockExpectAndReturn(51, CH1, 100);

    float lpg = mq2ReadLPG();



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((2.50133)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((2.50133))), (UNITY_FLOAT)((UNITY_FLOAT)((lpg))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(54)));



}



void test_obtener_CO (void) {



    adcRead_CMockExpectAndReturn(60, CH1, 100);

    float co = mq2ReadCO();



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((4.078309)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((4.078309))), (UNITY_FLOAT)((UNITY_FLOAT)((co))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(63)));



}





void test_obtener_smoke (void) {



    adcRead_CMockExpectAndReturn(70, CH1, 100);

    float smoke = mq2ReadSmoke();



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((3.242329)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((3.242329))), (UNITY_FLOAT)((UNITY_FLOAT)((smoke))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(73)));



}
