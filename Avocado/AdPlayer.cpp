/*
*/

#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdPlayer::AdPlayer(void) {
	m_iMouseX     = 0;
	m_iMouseY     = 0;
	m_bMouseLeft  = false;
	m_bMouseRight = false;
}

//-----------------------------------------------------------------------------
AdPlayer::~AdPlayer(void) {}

//-----------------------------------------------------------------------------
void AdPlayer::Update(AdLevel* pLvl) {
	AdTiledManager* pMap;
	pMap = pLvl->GetTiledMap();
	
	HandleMovement(pMap);
}

//-----------------------------------------------------------------------------
void AdPlayer::Render(AdLevel* pLvl) {
	SDL_Point pnt = {m_recTrigger.x, m_recTrigger.y};
	AdScreen::DrawSprite(pnt, m_pFrames[m_iFrame]);
}
