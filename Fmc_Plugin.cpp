#include "Fmc_Plugin.h"

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

std::thread t;

PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strcpy(outName, "Fmc_Plugin");
	strcpy(outSig, "kuba.projects.Fmc_plugin");
	strcpy(outDesc, "Wysyla dane z wyswietlacza przez UDP");

	//Spawning thread to run UDP Server parallel to simulator
	t = std::thread(runUDPserver);

	//loop for updating message
	XPLMCreateFlightLoop_t messageParams;
	messageParams.structSize = sizeof(messageParams);
	messageParams.callbackFunc = UpdateMessage;
	messageParams.phase = 1;
	messageParams.refcon = NULL;

	//loop for finding Dataref variables
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
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
