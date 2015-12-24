/*
*/

#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "NpcPuzzlePiece.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
void NpcPuzzlePiece::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	AdPlayer* pPlayer = pLvl->GetPlayer();

	if(pPlayer->hasPuzzlePiece) {
		m_iFrame = 1;
	} else {
		m_iFrame = 0;
	}
}
