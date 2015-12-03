/*
*/

#include "NpcTree0.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
NpcTree0::NpcTree0(void) {
	m_iFrame = 1;
}

//-----------------------------------------------------------------------------
NpcTree0::~NpcTree0(void) {}

//-----------------------------------------------------------------------------
void NpcTree0::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	if(m_bTriggered) {
		m_iFrame = 0;
	} else {
		m_iFrameCount++;
		if(m_iFrameCount == 32) {
			m_iFrameCount = 0;

			m_iFrame++;
			if(m_iFrame > 2) m_iFrame = 1;
		}
	}
}

//-----------------------------------------------------------------------------
void NpcTree0::Render(class AdLevel* pLvl) {
	AdEntity::Render(pLvl);

	if(m_bTriggered) {
		int ind[] = {
			2*64+14, 1*64+15, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+16, 1*64+17, 1*64+13,
			1*64+18, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 1*64+12, 2*64+18,
			2*64+13, 2*64+15, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+16, 2*64+17, 1*64+14,
		};

		SDL_Surface* bkg = AdSpriteManager::BuildSprite(10, 3, ind);
		SDL_Point pnt = {m_recTrigger.x+4-8*9/2, m_recTrigger.y-24};
		AdScreen::DrawSprite(pnt, bkg);
		SDL_FreeSurface(bkg);


		//>^.^< +^.^+ =^.^= ~^.^~
		SDL_Surface* msg = AdSpriteManager::BuildSprite("WELCOME!");
		pnt.x += 8; pnt.y += 8;
		AdScreen::DrawSprite(pnt, msg);
		SDL_FreeSurface(msg);
	}
}
