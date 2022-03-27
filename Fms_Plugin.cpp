#include "Fms_Plugin.h"

#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifndef XPLM301
#error This is made to be compiled against the XPLM301 SDK
#endif



std::thread t(runUDPserver);

float UpdateMessage(float          inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* time) {

	char data[25];
	char buf1[BUFLEN];
	char buf2[BUFLEN];

	if (lines1[0] == NULL) {
		fprintf(g, "Cannot load dataref\n");
	}
	else {
		memset(buf1, 0, BUFLEN);
		memset(buf2, 0, BUFLEN);

		for (int i = 0; i < 36; i++) {
			memset(data, 0, 25);
			int returnSize = XPLMGetDatab(lines1[i], &data, 0, 50);
			strcat(buf1, data);
			strcat(buf1, "&");
		}
		float td = XPLMGetDataf(tdDistance);
		char tdDist[4];
		memset(tdDist, 0, 4);
		sprintf(tdDist, "%d", (int)td);
		strcat(buf1, tdDist);
		strcat(buf1, "&");

		char light[1];
		light[0] = XPLMGetDatai(execLight) + 48;
		strcat(buf1, light);
		strcat(buf1, "&");

		light[0] = XPLMGetDatai(msgLight) + 48;
		strcat(buf1, light);
		strcat(buf1, "&");

		for (int i = 0; i < 36; i++) {
			memset(data, 0, 25);
			int returnSize = XPLMGetDatab(lines2[i], &data, 0, 50);
			strcat(buf2, data);
			strcat(buf2, "&");
		}
		strcat(buf2, tdDist);
		strcat(buf2, "&");

		light[0] = XPLMGetDatai(execLightFo) + 48;
		strcat(buf2, light);
		strcat(buf2, "&");

		light[0] = XPLMGetDatai(msgLightFo) + 48;
		strcat(buf2, light);
		strcat(buf2, "&");

		buf1[strlen(buf1) - 1] = 0;
		buf2[strlen(buf2) - 1] = 0;

		msg_mutex.lock();
		memset(msg1, 0, BUFLEN);
		memset(msg2, 0, BUFLEN);
		memcpy(msg1, buf1, BUFLEN);
		memcpy(msg2, buf2, BUFLEN);
		msg_mutex.unlock();

	}
	return 0.1;
}


PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strcpy(outName, "ziboFMS");
	strcpy(outSig, "kuba.projects.ziboFMS");
	strcpy(outDesc, "Wysyla dane z wyswietlacza przez UDP");


	fprintf(g, "Start Pluginu");

	XPLMCreateFlightLoop_t messageParams;
	messageParams.structSize = sizeof(messageParams);
	messageParams.callbackFunc = UpdateMessage;
	messageParams.phase = 1;
	messageParams.refcon = NULL;

	XPLMCreateFlightLoop_t datarefParams;
	datarefParams.structSize = sizeof(datarefParams);
	datarefParams.callbackFunc = FindDataRefs;
	datarefParams.phase = 1;
	datarefParams.refcon = NULL;

	loopDataref = XPLMCreateFlightLoop(&datarefParams);
	loopMessage = XPLMCreateFlightLoop(&messageParams);

	XPLMScheduleFlightLoop(loopDataref, 0.01, 0);
	XPLMScheduleFlightLoop(loopMessage, 0.5, 2);


	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	XPLMDestroyFlightLoop(loopMessage);
	XPLMDestroyFlightLoop(loopDataref);
	msg_mutex.lock();
	isFinished = true;
	msg_mutex.unlock();
	t.join();
	fclose(g);
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
