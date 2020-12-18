/*=============================================================================
 * Copyright (c) 2019, SMA Project
 * Leandro Torrent <leandrotorrent92@gmail.com>
 * Miguel del Valle <m.e.delvallecamino@ieee.org>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2019/07/27
 * Version: 1.0
 *===========================================================================*/

#include <stdint.h>
#include <math.h>
//#include "sapi.h"

float* mq2Read();
float mq2ReadLPG();
float mq2ReadCO();
float mq2ReadSmoke();
void mq2Begin();
float MQ2MQRead();
float MQ2MQGetGasPercentage(float rs_ro_ratio, uint8_t gas_id);
float MQ2MQCalibration();
float MQ2MQResistanceCalculation(uint16_t raw_adc);
float MQ2MQGetPercentage(float rs_ro_ratio, float *pcurve);
int alarma (void);