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
		AdScreen::DrawSprite(pnt, text1);

		pnt.y += 8;
		AdScreen::DrawSprite(pnt, text2);
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
