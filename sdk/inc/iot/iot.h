#pragma once

#include "pub/pub.h"


//÷ß≥÷∞¢¿Ô‘∆
#include "eng/infra/infra_types.h"
#include "eng/infra/infra_defs.h"
#include "eng/mqtt/mqtt_api.h"
#include "eng/mqtt/mqtt_wrapper.h"
#include "eng/infra/infra_compat.h"

typedef struct _iot_info{
	int (*_HAL_GetDeviceName)(char device_name[IOTX_DEVICE_NAME_LEN]);
	int (*_HAL_GetProductKey)(char product_key[IOTX_PRODUCT_KEY_LEN]);
	int (*_HAL_GetProductSecret)(char product_secret[IOTX_PRODUCT_SECRET_LEN + 1]);

	int (*_HAL_GetFirmwareVersion)(char *version);

	int (*_Kv_GetDeviceSecret)(char device_secret[IOTX_DEVICE_SECRET_LEN]);
	int (*_Kv_SetDeviceSecret)(char device_secret[IOTX_DEVICE_SECRET_LEN]);
	
}iot_info;

LIB_EXPORT int iot_init( iot_info *options );
