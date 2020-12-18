/*=============================================================================
 * Copyright (c) 2019, SMA Project
 * Leandro Torrent <leandrotorrent92@gmail.com>
 * Miguel del Valle <m.e.delvallecamino@ieee.org>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2019/07/27
 * Version: 1.0
 *===========================================================================*/
/*=====[Inclusion of own header]=============================================*/

#include "mq2.h"
#include "sapi.h"
#include <math.h>			// No linkea al compilar. No pude usar las funciones pow() y log()
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



float RL_VALUE = 5;								//define the load resistance on the board, in kilo ohms

float RO_CLEAN_AIR_FACTOR = 9.83;
int CALIBARAION_SAMPLE_TIMES = 1;
int CALIBRATION_SAMPLE_INTERVAL = 50;
int READ_SAMPLE_INTERVAL = 50;
int READ_SAMPLE_TIMES = 5;

float LPGCurve[3] = { 2.3, 0.21, -0.47 };
float COCurve[3] = { 2.3, 0.72, -0.34 };
float SmokeCurve[3] = { 2.3, 0.53, -0.44 };
float Ro = 10;
uint8_t GAS_LPG = 0;
uint8_t GAS_CO = 1;
uint8_t GAS_SMOKE = 2;

float lpg = 0;
float co = 0;
float smoke = 0;
/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
void mq2Begin() {
	Ro = MQ2MQCalibration();
}


 
/*
 * Reads data from MQ2.
 */
float* mq2Read() {

	lpg = MQ2MQGetGasPercentage(MQ2MQRead() / Ro, GAS_LPG);
	co = MQ2MQGetGasPercentage(MQ2MQRead() / Ro, GAS_CO);
	smoke = MQ2MQGetGasPercentage(MQ2MQRead() / Ro, GAS_SMOKE);

	
	
	float values[3] = { lpg, co, smoke };
	return values;
}

/*
 * reads data, returns LPG value in ppm
 */
float mq2ReadLPG() {
	return lpg = MQ2MQGetGasPercentage(MQ2MQRead() / 10, GAS_LPG);
}

/*
 * reads data, returns CO value in ppm
 */
float mq2ReadCO() {
	return co = MQ2MQGetGasPercentage(MQ2MQRead() / 10, GAS_CO);
}


/*
 * reads data, returns Smoke value in ppm
 */
float mq2ReadSmoke() {
	return smoke = MQ2MQGetGasPercentage(MQ2MQRead() / 10, GAS_SMOKE);
}

/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQ2MQResistanceCalculation(uint16_t raw_adc) {
	return (((float) RL_VALUE * (1023 - raw_adc) / raw_adc));
}

/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQ2MQCalibration() {                                           // This should be done in 'clean air'
	float val = 0;                                                   
	for (int i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {                //take multiple samples
		val += MQ2MQResistanceCalculation(adcRead(CH1));                
		//delay(CALIBRATION_SAMPLE_INTERVAL);
	}
	val = val / CALIBARAION_SAMPLE_TIMES;                               //calculate the average value                                
	val = val / RO_CLEAN_AIR_FACTOR;                                    //divided by RO_CLEAN_AIR_FACTOR yields the Ro according to the chart in the datasheet
	return val;
}

/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQ2MQRead() {
	int i;
	float rs = 0;
	uint16_t val = adcRead(CH1); 

	for (i = 0; i < READ_SAMPLE_TIMES; i++) {
		rs += MQ2MQResistanceCalculation(val);
	}
	rs = rs / READ_SAMPLE_TIMES;
	return rs;
}

/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  ppm of the target gas
Remarks: This function passes different curves to the MQGetPercentage function which 
         calculates the ppm (parts per million) of the target gas.
************************************************************************************/
float MQ2MQGetGasPercentage(float rs_ro_ratio, uint8_t gas_id) {
	if (gas_id == GAS_LPG) {
		return MQ2MQGetPercentage(rs_ro_ratio, LPGCurve);
	} else if (gas_id == GAS_CO) {
		return MQ2MQGetPercentage(rs_ro_ratio, COCurve);
	} else if (gas_id == GAS_SMOKE) {
		return MQ2MQGetPercentage(rs_ro_ratio, SmokeCurve);
	}
	return 0;
}

/*****************************  MQGetPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         pcurve      - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
************************************************************************************/ 
float MQ2MQGetPercentage(float rs_ro_ratio, float *pcurve) {
//	return (pow(10, ((( log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));		//Esta formula es la correcta pero no linkea math.h

    return ((((rs_ro_ratio/40) - pcurve[1]) / pcurve[2]) + pcurve[0]); //Esta formula no es correcta pero la us para probar el testing. Tenia problemas con la libreria math.h y no podia compilar.
}

int alarma (void) {
		return 1;
}