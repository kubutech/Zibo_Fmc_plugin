
//function to run udp server
void runUDPserver() {

	struct sockaddr_in server, si_other;

	//Initialise winsock
	int a = WSAStartup(MAKEWORD(2, 2), &wsa);

	//Create a socket
	s = socket(AF_INET, SOCK_DGRAM, 0);

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Set socket timeout to 1sec, so the recvfrom function doesn't block the execution idefinitely
	DWORD timeout = 1000;
	int check = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout);

	//Bind
	bind(s, (struct sockaddr*)&server, sizeof(server));
	
	char rcvBuf[BUFLEN];
	char sendBuf[BUFLEN];
	int slen, recv_len;

	while (true) {

		memset(sendBuf, 0, BUFLEN);
		memset(rcvBuf, 0, BUFLEN);

		slen = sizeof(si_other);

		if (recv_len = recvfrom(s, rcvBuf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR) {
			
		}
		else {
			msg_mutex.lock();
			if (rcvBuf[0] == '1') {
				memcpy(sendBuf, msg1, BUFLEN);
			}
			else if (rcvBuf[0] == '2') {
				memcpy(sendBuf, msg2, BUFLEN);
			}
			msg_mutex.unlock();

			int len = strlen(sendBuf);

			sendto(s, sendBuf, len, 0, (struct sockaddr*)&si_other, slen);
		}
		msg_mutex.lock();
		//check if X-Plane called XPlugnStop fuction and server should shut down
		if (isFinished) {
			msg_mutex.unlock();
			return;
		}
		msg_mutex.unlock();
	}
}

//Function that reads data from simulator and packs it into a message for UDP Server
float UpdateMessage(float          inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* time) {

	char data[25];
	char buf1[BUFLEN];
	char buf2[BUFLEN];

	if (lines1[0] == NULL) {

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

float FindDataRefs(float          inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* time)
{

	//CPT FMC
	lines1[0] = XPLMFindDataRef("laminar/B738/fmc1/Line00_L");
	lines1[1] = XPLMFindDataRef("laminar/B738/fmc1/Line01_L");
	lines1[2] = XPLMFindDataRef("laminar/B738/fmc1/Line02_L");
	lines1[3] = XPLMFindDataRef("laminar/B738/fmc1/Line03_L");
	lines1[4] = XPLMFindDataRef("laminar/B738/fmc1/Line04_L");
	lines1[5] = XPLMFindDataRef("laminar/B738/fmc1/Line05_L");
	lines1[6] = XPLMFindDataRef("laminar/B738/fmc1/Line06_L");
	lines1[7] = XPLMFindDataRef("laminar/B738/fmc1/Line_entry");
	lines1[8] = XPLMFindDataRef("laminar/B738/fmc1/Line00_S");
	lines1[9] = XPLMFindDataRef("laminar/B738/fmc1/Line01_X");
	lines1[10] = XPLMFindDataRef("laminar/B738/fmc1/Line02_X");
	lines1[11] = XPLMFindDataRef("laminar/B738/fmc1/Line03_X");
	lines1[12] = XPLMFindDataRef("laminar/B738/fmc1/Line04_X");
	lines1[13] = XPLMFindDataRef("laminar/B738/fmc1/Line05_X");
	lines1[14] = XPLMFindDataRef("laminar/B738/fmc1/Line06_X");
	lines1[15] = XPLMFindDataRef("laminar/B738/fmc1/Line01_S");
	lines1[16] = XPLMFindDataRef("laminar/B738/fmc1/Line02_S");
	lines1[17] = XPLMFindDataRef("laminar/B738/fmc1/Line03_S");
	lines1[18] = XPLMFindDataRef("laminar/B738/fmc1/Line04_S");
	lines1[19] = XPLMFindDataRef("laminar/B738/fmc1/Line05_S");
	lines1[20] = XPLMFindDataRef("laminar/B738/fmc1/Line06_S");
	lines1[21] = XPLMFindDataRef("laminar/B738/fmc1/Line00_M");
	lines1[22] = XPLMFindDataRef("laminar/B738/fmc1/Line01_M");
	lines1[23] = XPLMFindDataRef("laminar/B738/fmc1/Line02_M");
	lines1[24] = XPLMFindDataRef("laminar/B738/fmc1/Line03_M");
	lines1[25] = XPLMFindDataRef("laminar/B738/fmc1/Line04_M");
	lines1[26] = XPLMFindDataRef("laminar/B738/fmc1/Line05_M");
	lines1[27] = XPLMFindDataRef("laminar/B738/fmc1/Line06_M");
	lines1[28] = XPLMFindDataRef("laminar/B738/fmc1/Line00_G");
	lines1[29] = XPLMFindDataRef("laminar/B738/fmc1/Line01_G");
	lines1[30] = XPLMFindDataRef("laminar/B738/fmc1/Line02_G");
	lines1[31] = XPLMFindDataRef("laminar/B738/fmc1/Line03_G");
	lines1[32] = XPLMFindDataRef("laminar/B738/fmc1/Line04_G");
	lines1[33] = XPLMFindDataRef("laminar/B738/fmc1/Line05_G");
	lines1[34] = XPLMFindDataRef("laminar/B738/fmc1/Line06_G");
	lines1[35] = XPLMFindDataRef("laminar/B738/fmc1/Line06_LX");


	//FO FMC

	lines2[0] = XPLMFindDataRef("laminar/B738/fmc2/Line00_L");
	lines2[1] = XPLMFindDataRef("laminar/B738/fmc2/Line01_L");
	lines2[2] = XPLMFindDataRef("laminar/B738/fmc2/Line02_L");
	lines2[3] = XPLMFindDataRef("laminar/B738/fmc2/Line03_L");
	lines2[4] = XPLMFindDataRef("laminar/B738/fmc2/Line04_L");
	lines2[5] = XPLMFindDataRef("laminar/B738/fmc2/Line05_L");
	lines2[6] = XPLMFindDataRef("laminar/B738/fmc2/Line06_L");
	lines2[7] = XPLMFindDataRef("laminar/B738/fmc2/Line_entry");
	lines2[8] = XPLMFindDataRef("laminar/B738/fmc2/Line00_S");
	lines2[9] = XPLMFindDataRef("laminar/B738/fmc2/Line01_X");
	lines2[10] = XPLMFindDataRef("laminar/B738/fmc2/Line02_X");
	lines2[11] = XPLMFindDataRef("laminar/B738/fmc2/Line03_X");
	lines2[12] = XPLMFindDataRef("laminar/B738/fmc2/Line04_X");
	lines2[13] = XPLMFindDataRef("laminar/B738/fmc2/Line05_X");
	lines2[14] = XPLMFindDataRef("laminar/B738/fmc2/Line06_X");
	lines2[15] = XPLMFindDataRef("laminar/B738/fmc2/Line01_S");
	lines2[16] = XPLMFindDataRef("laminar/B738/fmc2/Line02_S");
	lines2[17] = XPLMFindDataRef("laminar/B738/fmc2/Line03_S");
	lines2[18] = XPLMFindDataRef("laminar/B738/fmc2/Line04_S");
	lines2[19] = XPLMFindDataRef("laminar/B738/fmc2/Line05_S");
	lines2[20] = XPLMFindDataRef("laminar/B738/fmc2/Line06_S");
	lines2[21] = XPLMFindDataRef("laminar/B738/fmc2/Line00_M");
	lines2[22] = XPLMFindDataRef("laminar/B738/fmc2/Line01_M");
	lines2[23] = XPLMFindDataRef("laminar/B738/fmc2/Line02_M");
	lines2[24] = XPLMFindDataRef("laminar/B738/fmc2/Line03_M");
	lines2[25] = XPLMFindDataRef("laminar/B738/fmc2/Line04_M");
	lines2[26] = XPLMFindDataRef("laminar/B738/fmc2/Line05_M");
	lines2[27] = XPLMFindDataRef("laminar/B738/fmc2/Line06_M");
	lines2[28] = XPLMFindDataRef("laminar/B738/fmc2/Line00_G");
	lines2[29] = XPLMFindDataRef("laminar/B738/fmc2/Line01_G");
	lines2[30] = XPLMFindDataRef("laminar/B738/fmc2/Line02_G");
	lines2[31] = XPLMFindDataRef("laminar/B738/fmc2/Line03_G");
	lines2[32] = XPLMFindDataRef("laminar/B738/fmc2/Line04_G");
	lines2[33] = XPLMFindDataRef("laminar/B738/fmc2/Line05_G");
	lines2[34] = XPLMFindDataRef("laminar/B738/fmc2/Line06_G");
	lines2[35] = XPLMFindDataRef("laminar/B738/fmc2/Line06_LX");

	execLight = XPLMFindDataRef("laminar/B738/indicators/fmc_exec_lights");
	msgLight = XPLMFindDataRef("laminar/B738/fmc/fmc_message");

	execLightFo = XPLMFindDataRef("laminar/B738/indicators/fmc_exec_lights_fo");
	msgLightFo = XPLMFindDataRef("laminar/B738/fmc/fmc_message2");

	tdDistance = XPLMFindDataRef("laminar/B738/fms/vnav_td_dist");

	//if datarefs failed to initialize run fightloop again, otherwise stop loop execution
	if (lines1[0] == NULL) {
		return 0.05;
	}
	else {
		return 0;
	}

}