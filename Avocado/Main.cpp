/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- for transitions and stuff I need a level manager (aka overworld)
	this is needed so that memory don't swap for under the for-loops and stuff

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

#include "AdEntity.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(8*40, 8*30, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	// TESTING
	AdLevel* lvl = new AdLevel();
	lvl->Load("testing");

	AdEntity player(8*4, 8*15, 8*2, 8*2, "npc_player");

	lvl->SetPlayer(&player);

	//lvl->Load("testing0");
	//lvl->SetPlayer(&player);

	SDL_Surface* text1 = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!#$%");
	SDL_Surface* text2 = AdSpriteManager::BuildSprite("~*()-+=[]\"'<>.?/");
	//

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		AdScreen::Clear();

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

	AdBase::Quit();

	return 0;
}
