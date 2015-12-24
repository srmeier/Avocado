/*
*/

#include "AdPlayer.h"

//-----------------------------------------------------------------------------
AdPlayer::AdPlayer(void): AdEntity(8*4, 8*15, 8*2, 8*2, "npc_player") {
	hasPuzzlePiece = false;
}

//-----------------------------------------------------------------------------
AdPlayer::~AdPlayer(void) {}

//-----------------------------------------------------------------------------
void AdPlayer::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	m_iFrameCount++;
	if(m_iFrameCount == 16) {
		m_iFrameCount = 0;

		m_iFrame++;
		if(m_iFrame > 1) m_iFrame = 0;
	}
}
