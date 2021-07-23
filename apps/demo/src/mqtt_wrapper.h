#pragma once
#include "mqtt_embed\MQTTClient\src\mf\MQTTMf.h"



void NetworkInit(Network* n);
int NetworkConnect(Network* n);
void NetworkDisconnect(Network* n);