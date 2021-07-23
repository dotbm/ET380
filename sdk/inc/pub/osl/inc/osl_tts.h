#include "pub/pub.h"
#pragma once

LIB_EXPORT void osl_tts_init();
LIB_EXPORT void osl_tts_power_lock();
LIB_EXPORT void osl_tts_power_unlock();
LIB_EXPORT void osl_tts_batch_begin();
LIB_EXPORT void osl_tts_batch_end();
LIB_EXPORT int osl_tts_play(char * sndfile);
LIB_EXPORT void osl_tts_beep(int hz, int ms);
LIB_EXPORT void osl_tts_set_play_func(void * func);
LIB_EXPORT int osl_tts_state();
LIB_EXPORT void osl_tts_clear();

LIB_EXPORT void  osl_play_gprs();
LIB_EXPORT void osl_play_wifi();

LIB_EXPORT void osl_PCM_OpenStream();
LIB_EXPORT void osl_PCM_CloseStream();