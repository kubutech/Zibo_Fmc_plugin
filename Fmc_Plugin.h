#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <winsock.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"

#define PORT 10000
#define BUFLEN 1024

XPLMDataRef lines1[36];
XPLMDataRef lines2[36];

XPLMDataRef execLight;
XPLMDataRef msgLight;

XPLMDataRef execLightFo;
XPLMDataRef msgLightFo;

XPLMDataRef tdDistance;

XPLMFlightLoopID loopDataref;
XPLMFlightLoopID loopMessage;

SOCKET s;
WSADATA wsa;
std::mutex msg_mutex;

BOOL isFinished = false;
char msg1[BUFLEN];
char msg2[BUFLEN];

#include "Fmc_plugin_functions.h"
