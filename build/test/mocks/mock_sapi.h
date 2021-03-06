/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_SAPI_H
#define _MOCK_SAPI_H

#include "unity.h"
#include "sapi.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_sapi_Init(void);
void mock_sapi_Destroy(void);
void mock_sapi_Verify(void);




#define adcRead_IgnoreAndReturn(cmock_retval) adcRead_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void adcRead_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, uint16_t cmock_to_return);
#define adcRead_StopIgnore() adcRead_CMockStopIgnore()
void adcRead_CMockStopIgnore(void);
#define adcRead_ExpectAndReturn(analogInput, cmock_retval) adcRead_CMockExpectAndReturn(__LINE__, analogInput, cmock_retval)
void adcRead_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, adcMap_t analogInput, uint16_t cmock_to_return);
typedef uint16_t (* CMOCK_adcRead_CALLBACK)(adcMap_t analogInput, int cmock_num_calls);
void adcRead_AddCallback(CMOCK_adcRead_CALLBACK Callback);
void adcRead_Stub(CMOCK_adcRead_CALLBACK Callback);
#define adcRead_StubWithCallback adcRead_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
