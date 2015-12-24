/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- 

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- 
*/

#include "AdBase.h"
#include "AdLevel.h"
#include "AdScreen.h"
#include "AdTiledManager.h"
#include "AdSpriteManager.h"

#include "AdPlayer.h"

//-----------------------------------------------------------------------------
#define MAX_PACKET 0xFF

//-----------------------------------------------------------------------------
#define WOOD_WAIT_TIME 5000

//-----------------------------------------------------------------------------
#define FLAG_QUIT 0x0000
#define FLAG_WOOD_UPDATE 0x0010

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(8*40, 8*30, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	// NETWORK TESTING
	/*
	IPaddress ip;
	TCPsocket socket;

	if(SDLNet_ResolveHost(&ip, "23.88.121.38", 8099) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	socket = SDLNet_TCP_Open(&ip);
	if(socket == NULL) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	SDLNet_SocketSet socket_set;
	socket_set = SDLNet_AllocSocketSet(1);
	if(socket_set == NULL) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	if(SDLNet_TCP_AddSocket(socket_set, socket) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	uint16_t flag = FLAG_WOOD_UPDATE;
	uint8_t temp_data[MAX_PACKET];

	int offset = 0;
	memcpy(temp_data+offset, &flag, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	int num_sent = SDLNet_TCP_Send(socket, temp_data, offset);
	if(num_sent < offset) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
	}
	*/
	//

	// TESTING
	AdLevel* lvl = new AdLevel();
	lvl->Load("testing");

	AdPlayer player;
	lvl->SetPlayer(&player);

	SDL_Surface* text1 = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!#$%");
	SDL_Surface* text2 = AdSpriteManager::BuildSprite("~*()-+=[]\"'<>.?/");
	//

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		AdScreen::Clear();

		// NETWORK TESTING
		/*
		static uint32_t ms_timer = SDL_GetTicks();
		if((SDL_GetTicks()-ms_timer) > WOOD_WAIT_TIME) {
			ms_timer = SDL_GetTicks();

			uint16_t flag = FLAG_WOOD_UPDATE;
			uint8_t temp_data[MAX_PACKET];

			int offset = 0;
			memcpy(temp_data+offset, &flag, sizeof(uint16_t));
			offset += sizeof(uint16_t);

			int num_sent = SDLNet_TCP_Send(socket, temp_data, offset);
			if(num_sent < offset) {
				fprintf(stderr, "%s\n", SDLNet_GetError());
			}
		}

		if(SDLNet_CheckSockets(socket_set, 0) == -1) {
			fprintf(stderr, "%s\n", SDLNet_GetError());
			system("pause");
			exit(-1);
		}

		int length = 0;
		uint8_t* data = NULL;

		if(SDLNet_SocketReady(socket)) {
			uint8_t temp_data[0xFF];
			length = SDLNet_TCP_Recv(socket, temp_data, 0xFF);

			if(length <= 0) {
				if(SDLNet_TCP_DelSocket(socket_set, socket) == -1) {
					fprintf(stderr, "%s\n", SDLNet_GetError());
					exit(-1);
				}

				SDLNet_TCP_Close(socket);
				const char* err = SDLNet_GetError();
				if(strlen(err) == 0)
					printf("DB: server disconnected\n");
				else
					fprintf(stderr, "%s\n", err);
			} else {
				printf("%d\n", length);

				data = (uint8_t*) malloc(length*sizeof(uint8_t));
				memcpy(data, temp_data, length);

				int offset = 0;
				uint16_t flag = *(uint16_t*) &data[offset];
				offset += sizeof(uint16_t);

				uint8_t amt_wood;

				switch(flag) {
					case FLAG_WOOD_UPDATE: {
						amt_wood = *(uint8_t*) &data[offset];
						offset += sizeof(uint8_t);
					} break;

					default: {
						printf("not processed.\n");
					} break;
				}

				printf("amount of wood: %d\n", amt_wood);

				free(data);
			}
		}
		*/
		//

		// TESTING
		lvl->Update(&sdlEvent);
		lvl->Render();

		SDL_Point pnt = {0, 0};
		//AdScreen::DrawSprite(pnt, text1);

		pnt.y += 8;
		//AdScreen::DrawSprite(pnt, text2);
		//

		AdScreen::Present();
	}

	// TESTING
	delete lvl;

	SDL_FreeSurface(text1);
	SDL_FreeSurface(text2);
	//

	// NETWORK TESTING
	/*
	flag = FLAG_QUIT;
	memset(temp_data, 0x00, MAX_PACKET);

	offset = 0;
	memcpy(temp_data+offset, &flag, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	num_sent = SDLNet_TCP_Send(socket, temp_data, offset);
	if(num_sent < offset) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
	}

	if(SDLNet_TCP_DelSocket(socket_set, socket) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_TCP_Close(socket);
	*/
	//

	AdBase::Quit();

	return 0;
}
