#include <xdk_et.h>

#include "libapi_xpos/inc/libapi_system.h"

#include "player_proc.h"
#include "mqtt_embed/MQTTClient/src/MQTTClient.h"

static unsigned char sendbuf[512];
static unsigned char readbuf[512];
static char cid[32];
static unsigned char s_status[32];
static unsigned char s_msg[32];
static MQTTClient *s_client=0;


static void mqtt_comm_messageArrived(MessageData* md)
{
	MQTTMessage* m = md->message;

	sprintf(s_msg,"r:%*s",m->payloadlen, m->payload);

	SYS_TRACE("messageArrived(%d):\r\n%s", m->payloadlen, s_msg);

}


static int mqtt_subscribe_yield( MQTTClient *c ) 
{
	int rc;
	int subsqos = 2;
	MQTTSubackData suback;

	sprintf(s_status,"Subscribe..");
	rc = MQTTSubscribeWithResults(c, "testNode/handshake/pub", subsqos, mqtt_comm_messageArrived, &suback);
	SYS_TRACE("rc from sub:%d\r\n", rc);
	if ( rc == 0)
	{
		sprintf(s_status,"Recving..");
		while( MQTTIsConnected(c) )
		{					
			MQTTYield(c, 1000);
			//osl_Sleep(100);
		}
	}
	else{
		sprintf(s_status,"Subscribe failed,%d",rc);
	}
	return rc;
}


static int mqtt_comm_run() 
{
	int rc = 0;
	Network n;
	char ip[20]={0};
	int port= 0;
	
	strcpy(s_status,"Connecting..");

	SYS_TRACE("Connecting\r\n");

	NetworkInit(&n);
	rc = NetworkConnect(&n);	
	SYS_TRACE("rc from net:%d\r\n", rc);

	Sys_Delay(2000);
	if ( rc == 0 )
	{
		MQTTClient c;
		MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

		MQTTClientInit(&c, &n, 20000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));
		//data.willFlag = 0;
		//data.MQTTVersion = 4;
		//osl_getTerminalID(cid,sizeof(cid));
	/*	strcpy(cid,"client_1");
		data.clientID.cstring = cid;*/
		//data.username.cstring = "admin";
		//data.password.cstring = "admin";
		//data.keepAliveInterval = 20;
		//data.cleansession = 1;


		osl_getTerminalID( cid,32);
		//strcpy( st_mqtt_data->clientId);
		//	strcpy(st_mqtt_data->mqUsername,"Signature|LTAI3bzRuB9yziK3|post-cn-0pp15t2z403");
		//	strcpy(st_mqtt_data->mqPassword,"DSbjijoVy7GHIllRLkHWmfLb0LE=");
		data.clientID.cstring = cid;
		//data.username.cstring = st_mqtt_data->mqUsername;
		//data.password.cstring = st_mqtt_data->mqPassword;
		data.username.cstring = "";
		data.password.cstring = "";
		data.keepAliveInterval = 60;
		data.cleansession = 0;

		rc = MQTTConnect(&c, &data);
		s_client = &c;
		SYS_TRACE("rc from connect:%d\r\n", rc);

		Sys_Delay(1000);
		if ( rc == 0 )
		{


			rc=mqtt_subscribe_yield(&c);

			MQTTDisconnect(&c);
		}
		else{
			sprintf(s_status,"Connect,%d",rc);
		}
		NetworkDisconnect(&n);
	}	
	else{
		sprintf(s_status,"Network anomaly,%d",rc);
	}

	s_client = 0;
	return 0;
}




int player_proc_statuspage()
{
	

	return 0;
}


static void mqtt_comm_task(void * p) 
{
	int ret = 0;
	enum{
		net_state,
		net_state_player,
		iot_init,
		iot_init_player,

		ticks_count
	};
	int ticks[ticks_count];

	int netstate = 0;


	SYS_TRACE("mqtt_comm_task\r\n");
	memset( ticks,0x00,sizeof(int) * ticks_count);

	//开机检查网络  30秒(60-30) 无网络  播报网络异常
	ticks[net_state_player] = Sys_TimerOpen(30*1000);

	ticks[net_state] =Sys_TimerOpen(1000);

	while(1)
	{
		//Waiting network..
		if ( Sys_TimerCheck(ticks[net_state])==0 )
		{
			int newnetstate  = comm_net_link_state();
			ticks[net_state] =Sys_TimerOpen(1000);

			if ( netstate != newnetstate)
			{
				netstate = newnetstate;

				if ( netstate == 1)
				{//网络连接成功
					Sys_TtsPlay("nets.mp3");
					SYS_TRACE("play_netinit_succed\r\n");

					//网络成功  立即开始连接服务
					ticks[iot_init] = 0;
				}
				else{
					//网络由成功到失败的  立即开始播报
					ticks[net_state_player] = 0;
				}
			}
		}

		SYS_TRACE("mqtt_comm_task net state %d\r\n", netstate);
		if ( netstate == 0)
		{

			SYS_TRACE("mqtt_comm_task net state %d  %d\r\n",  ticks[net_state_player],Sys_TimerCheck(ticks[net_state_player]) );
			//网络连接失败
			if ( ticks[net_state_player] == 0 || Sys_TimerCheck(ticks[net_state_player]) == 0)
			{
				//网络连接失败   60s播报一次
				Sys_TtsPlay("netf.mp3");
				SYS_TRACE("ap2_play_net_err \r\n");
				ticks[net_state_player]=Sys_TimerOpen(60000);
			}
			SYS_TRACE("waitting network1 %d\r\n", osl_GetTickDiff(ticks[net_state_player] ));
			Sys_Delay(1000);
			continue;

		}


		//mqtt run
		mqtt_comm_run();

		//Wait one second and try again
		Sys_Delay(1000);
	}
}

#define _APP_TASK_SIZE 4096

static  unsigned int  pTaskStk[_APP_TASK_SIZE];


int player_proc_init()
{
	int nerr=0;
	memset(cid, 0x00, sizeof(cid));
	sprintf(s_status,"Loading..");

	Sys_TaskCreate(mqtt_comm_task,0,(char *)&(pTaskStk[0]),_APP_TASK_SIZE);
	return 0;
}