/*
*/

#include "AdBase.h"
#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "NpcAvocado.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
void NpcAvocado::Render(class AdLevel* pLvl) {
	AdEntity::Render(pLvl);

	if(m_bTriggered) {
		int ind[] = {
			2*64+14, 1*64+15, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+17, 1*64+13,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			2*64+13, 2*64+15, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+17, 1*64+14,
		};

		SDL_Surface* bkg = AdSpriteManager::BuildSprite(41, 9, ind);
		SDL_Point pnt = {-4, AdBase::GetHeight()-8*9+4};
		AdScreen::DrawSprite(pnt, bkg);
		SDL_FreeSurface(bkg);

		//>^.^< +^.^+ =^.^= ~^.^~
		SDL_Surface *msg, *msg0, *msg1, *msg2;
		AdPlayer* pPlayer = pLvl->GetPlayer();

		if(pPlayer->hasPuzzlePiece) {
			msg = AdSpriteManager::BuildSprite("AVOCADO JESUS: THANK YOU FOR FINDING");
			msg0 = AdSpriteManager::BuildSprite("THE PUZZLE PIECE!");
			msg1 = AdSpriteManager::BuildSprite("");
			msg2 = AdSpriteManager::BuildSprite("");
		} else {
			msg = AdSpriteManager::BuildSprite("AVOCADO JESUS: GREETINGS! WE ARE");
			msg0 = AdSpriteManager::BuildSprite("MISSING OUR PUZZLE PIECE AND WE NEED");
			msg1 = AdSpriteManager::BuildSprite("YOU TO HELP FIND IT!");
			msg2 = AdSpriteManager::BuildSprite("");
		}

		pnt.x += 8; pnt.y += 8;
		AdScreen::DrawSprite(pnt, msg);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, msg0);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, msg1);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, msg2);

		SDL_FreeSurface(msg);
		SDL_FreeSurface(msg0);
		SDL_FreeSurface(msg1);
		SDL_FreeSurface(msg2);
	}
}