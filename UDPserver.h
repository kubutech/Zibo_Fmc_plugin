

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

			//fprintf(g, "Sent Packet- %dbytes:\n%s\n", len, sendBuf);
		}
		msg_mutex.lock();
		if (isFinished) {
			msg_mutex.unlock();
			return;
		}
		msg_mutex.unlock();
		
	}
	
}