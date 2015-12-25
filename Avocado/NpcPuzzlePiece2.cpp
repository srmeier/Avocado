/*
*/

#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "NpcPuzzlePiece2.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
void NpcPuzzlePiece2::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	AdPlayer* pPlayer = pLvl->GetPlayer();

	if(pPlayer->hasPuzzlePiece) {
		m_iFrame = 0;
	} else {
		m_iFrame = 1;
	}
}
