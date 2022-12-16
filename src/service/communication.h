#pragma once
#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "WiFi.h"
#include "lwip/sockets.h"
#include "lwip/err.h"

void communication_init_wifi(const char* w_ssid,const char* w_pw);

uint8_t communication_create_socket_connection(uint16_t port, const char* master_ip_address);


#endif