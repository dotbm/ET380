#pragma once

#include "pub/pub.h"

enum{
	Power_ShutDown,
	Power_Low,
	Power_Charge,
	Power_Out,		
	Net_Config_Mode,
	Net_Gprs_Mode,
	Net_Wifi_Mode,
	Wifi_AirKiss_Config,
	Wifi_AP_Config,
	Wifi_Config_Success,
	Wifi_Config_Fail,
};

typedef int (*_tts_system_play)( int type, void *data);

LIB_EXPORT void osl_tts_system_set_func( _tts_system_play playproc);

LIB_EXPORT int osl_tts_system_play( int type, void *data);