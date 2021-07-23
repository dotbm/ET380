


#include "mainpage.h"
#include "player_proc.h"
#include "libapi_xpos/inc/libapi_system.h"

#define APP_VER				"demo-V1.0.5"


static int   tts_system_play_fun( int type, void *data)
{

	switch(type)
	{

	case X_Power_ShutDown:
		{
			Sys_TtsPlay("lows.mp3");
			return 1;
		}
	case X_Power_Low:
		{
			Sys_TtsPlay("lowc.mp3");
			return 1;
		}
	case X_Power_Charge:
		{

			Sys_TtsPlay("char.mp3");
			return 1;
		}
	case X_Power_Out:
		{
			Sys_TtsPlay("disc.mp3");
			return 1;
		}
	case X_Net_Gprs_Mode:
		{
			Sys_TtsPlay("gprs.mp3");
			return 1;
		}
	case X_Net_Wifi_Mode:
		{
			Sys_TtsPlay("wifi.mp3");
			return 1;
		}
	case X_Net_Config_Mode:
		{
			Sys_TtsPlay("cnet.mp3");
			return 1;
		}
	case X_Wifi_AirKiss_Config:
		{
			return 1;
		}
	case X_Wifi_AP_Config:
		{
			return 1;
		}
	case X_Wifi_Config_Success:
		{
			Sys_TtsPlay("csuc.mp3");
			return 1;
		}
	case X_Wifi_Config_Fail:
		{
			Sys_TtsPlay("cfail.mp3");
			return 1;
		}
	}
	return 0;
}
static void _app_work_task()
{
	Sys_ttsSystemSetFunc(&tts_system_play_fun);

#ifdef WIN32
	osl_log_sound_set(2);
#endif

	player_proc_init();
	main_page_proc();
}

void app_main(int p)
{
	Sys_Start(APP_VER, _app_work_task);
}


#ifdef CPU_1903
void main()
{
	app_main(0);
}
#endif

