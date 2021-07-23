#include "mainpage.h"

#include "libapi_xpos/inc/libapi_system.h"
#include "libapi_xpos/inc/libapi_gui.h"

static unsigned int tick_power = 0;
static unsigned int tick_func = 0;

static void main_page_powerkey_check(gui_key_event *key_event, int ret)
{
	if(ret == 0){			// 无按键
		if(tick_power != 0 && Sys_TimerCheck(tick_power) == 0){
			
			Sys_TtsPlay("shut");
			while(osl_tts_state()==1)
			{
				osl_Sleep(500);
			}


			osl_Sleep(1000);
			osl_power_off();
		}
	}
	else{
		if(key_event->status == 1 && key_event->keycode == KEY_QUIT){	
			if(tick_power == 0){
				tick_power = Sys_TimerOpen(2000);
			}
		}
		else{
			tick_power = 0;
		}
	}
}

static void main_page_funckey_check(gui_key_event *key_event, int ret)
{
	if(ret == 0){			// 无按键
		if(tick_func != 0 && Sys_TimerCheck(tick_func) == 0){
			SYS_TRACE("func_proc0-----------------------------------\r\n");
			gui_wifi_set_page();
			tick_func = 0;
		}
	}
	else{
		if(key_event->status == 1 && key_event->keycode == KEY_OK){	
			if(tick_func == 0){

				SYS_TRACE("func_proc------------------\r\n\r\n");
				tick_func = Sys_TimerOpen(2000);
			}
		}
		else{
			tick_func = 0;
		}
	}
}

#define TTS_VOLUME_MIN			"minv.mp3"		
#define TTS_VOLUME_MAX			"maxv.mp3"		
#define TTS_VOLUME_NOR			"volnor.mp3"	



static void main_page_play_start()
{

	Sys_TtsPlay("welc.mp3");
	/*osl_tts_play("morefun");
	osl_tts_play("yunspeak");*/
	
}

void main_page_proc()
{
	int ret;
	gui_key_event key_event = {0};
	int keycode;
	int volume = osl_get_tts_sound();

	main_page_play_start();



	while(1){

		ret = gui_key_getevent(&key_event);
		keycode = key_event.keycode;

		main_page_powerkey_check(&key_event, ret);
		main_page_funckey_check(&key_event, ret);

		if(ret == 1){

			SYS_TRACE("gui key:%d,%d\r\n", key_event.keycode, key_event.status);

			if(key_event.status == 0){
				if(keycode == KEY_QUIT){

				
				}
				else if(keycode == KEY_UP){

					if(volume > 0){
						volume -= 1;
						osl_set_tts_sound(volume);
						Sys_TtsPlay(TTS_VOLUME_NOR);
					}
					else{		

						Sys_TtsPlay(TTS_VOLUME_MIN);
					}


					SYS_TRACE("volume:%d\r\n", volume);
					//paint_flag =1;
				}
				else if(keycode == KEY_DOWN)
				{

					
					if(volume < 5){
						volume += 1;
						osl_set_tts_sound(volume);
						Sys_TtsPlay(TTS_VOLUME_NOR);
					}
					else{

						Sys_TtsPlay(TTS_VOLUME_MAX);
					}
					SYS_TRACE("volume:%d\r\n", volume);
					//paint_flag =1;
				}
			
				else if(keycode == KEY_OK)
				{

					http_sync();
				
				}
			}
		}
		osl_Sleep(100);
		//mqtt_loop();
	}

	//pt_proc();
}