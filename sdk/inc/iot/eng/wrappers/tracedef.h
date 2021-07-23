#pragma once

#include "pub\osl\inc\osl_log.h"

//#define LOG_KEY_OPEN				1

#define APP_TRACE(...) 			osl_log("pub",LOG_LEVEL_TRACE, __VA_ARGS__);
#define APP_TRACE_BUFF(a,b) 	osl_log_buff("pub",LOG_LEVEL_TRACE,a,b);
#define APP_TRACE_BUFF_TIP(a,b,c) 	osl_log_buff_tip("pub",LOG_LEVEL_TRACE,a,b , c ,1 );
