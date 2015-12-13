/*
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"
gcc main.c -o server -lSDL2 -lSDL2_net
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

//-----------------------------------------------------------------------------
#define MAX_PACKET 0xFF
#define MAX_SOCKETS 0x04
#define SERVER_SOCKET 0x00

//-----------------------------------------------------------------------------
#define WOOD_WAIT_TIME 5000

//-----------------------------------------------------------------------------
#define FLAG_WOOD_UPDATE 0x0010

//-----------------------------------------------------------------------------
typedef struct {
	int in_use;
	int questing;
	uint8_t amt_wood;
	uint32_t timer_wood;
} Client;

//-----------------------------------------------------------------------------
int next_ind = 1;
Client clients[MAX_SOCKETS];
SDLNet_SocketSet socket_set;
TCPsocket sockets[MAX_SOCKETS];

//-----------------------------------------------------------------------------
void CloseSocket(int index) {
	if(sockets[index] == NULL) {
		fprintf(stderr, "ER: Attempted to delete a NULL socket.\n");
		return;
	}

	if(SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	memset(&clients[index], 0x00, sizeof(Client));
	SDLNet_TCP_Close(sockets[index]);
	sockets[index] = NULL;
}

//-----------------------------------------------------------------------------
int AcceptSocket(int index) {
	if(sockets[index]) {
		fprintf(stderr, "ER: Overriding socket at index %d.\n", index);
		CloseSocket(index);
	}

	sockets[index] = SDLNet_TCP_Accept(sockets[SERVER_SOCKET]);
	if(sockets[index] == NULL) return 0;

	clients[index].in_use = 1;
	if(SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	return 1;
}

//-----------------------------------------------------------------------------
void SendData(int index, uint8_t* data, uint16_t length, uint16_t flag) {
	uint8_t temp_data[MAX_PACKET];

	int offset = 0;
	memcpy(temp_data+offset, &flag, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	memcpy(temp_data+offset, data, length);
	offset += length;

	int num_sent = SDLNet_TCP_Send(sockets[index], temp_data, offset);

	if(num_sent < offset) {
		fprintf(stderr, "ER: SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		CloseSocket(index);
	}
}

//-----------------------------------------------------------------------------
uint8_t* RecvData(int index, uint16_t* length, uint16_t* flag) {
	uint8_t temp_data[MAX_PACKET];
	int num_recv = SDLNet_TCP_Recv(sockets[index], temp_data, MAX_PACKET);

	if(num_recv <= 0) {
		CloseSocket(index);
		const char* err = SDLNet_GetError();
		if(strlen(err) == 0) {
			printf("DB: client disconnected\n");
		} else {
			fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
		}

		return NULL;
	} else {
		int offset = 0;
		*flag = *(uint16_t*) &temp_data[offset];
		offset += sizeof(uint16_t);

		*length = (num_recv-offset);

		uint8_t* data = (uint8_t*) malloc((num_recv-offset)*sizeof(uint8_t));
		memcpy(data, &temp_data[offset], (num_recv-offset));

		return data;
	}
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
		fprintf(stderr, "ER: SDL_Init: %s\n", SDL_GetError());
		exit(-1);
	}

	if(SDLNet_Init() == -1) {
		fprintf(stderr, "ER: SDLNet_Init: %s\n", SDLNet_GetError());
		exit(-1);
	}

	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, NULL, 8099) == -1) {
		fprintf(stderr, "ER: SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-1);
	}

	sockets[SERVER_SOCKET] = SDLNet_TCP_Open(&ip);
	if(sockets[SERVER_SOCKET] == NULL) {
		fprintf(stderr, "ER: SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(-1);
	}

	socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS);
	if(socket_set == NULL) {
		fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(-1);
	}

	if(SDLNet_TCP_AddSocket(socket_set, sockets[SERVER_SOCKET]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	int running = 1;
	while(running) {
		int num_rdy = SDLNet_CheckSockets(socket_set, 1000);

		if(num_rdy <= 0) {
			// NOTE: none of the sockets are ready
			int ind;
			for(ind=0; ind<MAX_SOCKETS; ++ind) {
				if(!clients[ind].in_use) continue;

				/*
				if(clients[ind].questing &&
					(SDL_GetTicks()-clients[ind].timer_wood)>WOOD_WAIT_TIME
				) {
					
					clients[ind].questing = 0;
					clients[ind].amt_wood += 4;
					char msg[0xFF] = "> quest complete\n\r";
					SendData(ind, msg, (strlen(msg)+1));
					
				}
				*/

				clients[ind].amt_wood += 4;

				/*
				uint16_t length = 0;
				uint8_t data[MAX_PACKET];

				memcpy(data+length, &clients[ind].amt_wood, sizeof(uint8_t));
				length += sizeof(uint8_t);

				SendData(ind, data, length, FLAG_WOOD_UPDATE);
				*/
			}
		} else {
			int ind;
			for(ind=0; (ind<MAX_SOCKETS) && num_rdy; ++ind) {
				if(sockets[ind] == NULL) continue;
				if(!SDLNet_SocketReady(sockets[ind])) continue;

				if(ind == SERVER_SOCKET) {
					int got_socket = AcceptSocket(next_ind);
					if(!got_socket) {
						num_rdy--;
						continue;
					}

					// NOTE: get a new index
					int chk_count;
					for(chk_count=0; chk_count<MAX_SOCKETS; ++chk_count) {
						if(sockets[(next_ind+chk_count)%MAX_SOCKETS] == NULL) break;
					}

					next_ind = (next_ind+chk_count)%MAX_SOCKETS;
					printf("DB: new connection (next_ind = %d)\n", next_ind);

					num_rdy--;
				} else {
					uint8_t* data;
					uint16_t flag;
					uint16_t length;
					
					data = RecvData(ind, &length, &flag);
					if(data == NULL) {
						num_rdy--;
						continue;
					}

					switch(flag) {
						case FLAG_WOOD_UPDATE: {
							uint16_t offset = 0;
							uint8_t send_data[MAX_PACKET];

							memcpy(send_data+offset, &clients[ind].amt_wood, sizeof(uint8_t));
							offset += sizeof(uint8_t);

							SendData(ind, send_data, offset, FLAG_WOOD_UPDATE);
						} break;
					}

					/*
					uint8_t* data; int length;

					data = RecvData(ind, &length);
					if(data == NULL) {
						num_rdy--;
						continue;
					}

					int i;
					for(i=0; i<length; ++i) {
						if(data[i] == '\n') data[i] = '\0';
						if(data[i] == '\r') data[i] = '\0';
					}

					// TEMP: add a NULL terminator
					data = (uint8_t*) realloc(data, (length+1));
					data[length] = '\0';

					int was_processed = 0;
					if(!strcmp(data, "exit")) {

						was_processed = 1;
						running = 0;

					} else if(!strcmp(data, "quit")) {

						was_processed = 1;
						CloseSocket(ind);

					} else if(!strcmp(data, "get data")) {

						was_processed = 1;
						char msg[0xFF] = {};
						sprintf(msg, "> wood: %d\n\r", clients[ind].amt_wood);
						//SendData(ind, msg, (strlen(msg)+1));

					} else if(!strcmp(data, "quest")) {

						was_processed = 1;
						if(!clients[ind].questing) {
							clients[ind].questing = 1;
							clients[ind].timer_wood = SDL_GetTicks();
							char msg[0xFF] = "> started quest\n\r";
							//SendData(ind, msg, (strlen(msg)+1));
						} else {
							char msg[0xFF] = "> currently running quest\n\r";
							//SendData(ind, msg, (strlen(msg)+1));
						}

					}

					if(was_processed) printf("PR: %s\n", data);
					free(data);
					*/

					num_rdy--;
				}
			}
		}
	}

	int i;
	for(i=0; i<MAX_SOCKETS; ++i) {
		if(sockets[i] == NULL) continue;
		CloseSocket(i);
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
	SDL_Quit();

	return 0;
}
