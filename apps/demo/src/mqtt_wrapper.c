

#include "mqtt_wrapper.h"

#include "libapi_xpos/inc/libapi_system.h"
static int mf_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	return comm_sock_recv(n->my_socket , buffer, len, timeout_ms);
}


static int mf_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	return comm_sock_send(n->my_socket , buffer, len);
}

void NetworkInit(Network* n)
{
	n->mqttread = mf_read;
	n->mqttwrite = mf_write;
}


int NetworkConnect(Network* n)
{
	int ret;
	//ap2_mbedtls_init(0,0);
	



	n->my_socket = comm_sock_create(1);

	//ap2_ssl_authmode( n->my_socket, 2);
	//ap2_ssl_init(n->my_socket , 0 ,0 , 0 ,0);

	ret = comm_sock_connect(n->my_socket , "18.195.227.162" , 1883 ,20*1000, (void*)0);
	//return ap2_sock_connect(n->my_socket , "64.233.188.206" , 8883 , (void*)0);
	if ( ret != 0)
	{
		comm_sock_close( n->my_socket );
	}
	return ret;

	//SYS_TRACE("n->my_socket==%d\r\n", n->my_socket);
	////ap2_ssl_authmode( n->my_socket, 2);
	////ap2_ssl_init(n->my_socket , 0 ,0 , 0 ,0);
	//ret = comm_sock_connect(n->my_socket , "18.195.227.162" , 1883);
	////return ap2_sock_connect(n->my_socket , "64.233.188.206" , 8883 , (void*)0);
	//if ( ret != 0)
	//{
	//	comm_sock_close( n->my_socket );
	//}
	//return ret;
}

void NetworkDisconnect(Network* n)
{
	comm_sock_close(n->my_socket);
}

