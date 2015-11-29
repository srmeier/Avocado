/*
*/

#include "AdLevel.h"
#include "AdEntity.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdEntity::AdEntity(
	int iX /*= 0*/, int iY /*= 0*/,
	int iW /*= 0*/, int iH /*= 0*/,
	const char* pFileName /*= NULL*/
) {
	m_bTriggered = false;
	memset(m_pType, 0x00, NAME_LENGTH);

	m_recTrigger.x = iX;
	m_recTrigger.y = iY;
	m_recTrigger.w = iW;
	m_recTrigger.h = iH;

	m_iFrame       = 0;
	m_pFrames      = NULL;

	m_iI           = 0;
	m_iJ           = 0;

	m_iMoveframe   = 0;
	m_iMovedirec   = 0;

	m_bMoving      = false;
	m_bFreeToMove  = true;

	m_iForcedirec  = 0;
	m_bForceMove   = false;

	m_bUp          = false;
	m_bDown        = false;
	m_bLeft        = false;
	m_bRight       = false;

	m_bUpCheck     = false;
	m_bDownCheck   = false;
	m_bLeftCheck   = false;
	m_bRightCheck  = false;

	if(pFileName) {
		m_aniMap.Load(pFileName);

		// NOTE: create an SDL_Surface for each frame
		m_pFrames = (SDL_Surface**) malloc(m_aniMap.nLayers()*sizeof(SDL_Surface*));

		for(int j=0; j<m_aniMap.nLayers(); ++j) {
			if(m_aniMap.GetLayer(j)) {
				m_pFrames[j] = AdSpriteManager::BuildSprite(
					m_aniMap.Width(), m_aniMap.Height(), m_aniMap.GetLayer(j)
				);
			} else {
				m_pFrames[j] = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------------------
AdEntity::~AdEntity(void) {
	Unload();
}

//-----------------------------------------------------------------------------
void AdEntity::Load(duk_context* pCtx) {
	Unload();

	duk_get_prop_string(pCtx, -1, "type");
	strcpy(m_pType, duk_get_string(pCtx, -1));
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "x");
	m_recTrigger.x = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "y");
	m_recTrigger.y = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "width");
	m_recTrigger.w = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "height");
	m_recTrigger.h = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	// NOTE: load the animation frames
	if(duk_get_prop_string(pCtx, -1, "properties")) {
		if(duk_get_prop_string(pCtx, -1, "frames")) {
			m_aniMap.Load(duk_get_string(pCtx, -1));

			// NOTE: create an SDL_Surface for each frame
			m_pFrames = (SDL_Surface**) malloc(m_aniMap.nLayers()*sizeof(SDL_Surface*));

			for(int j=0; j<m_aniMap.nLayers(); ++j) {
				if(m_aniMap.GetLayer(j)) {
					m_pFrames[j] = AdSpriteManager::BuildSprite(
						m_aniMap.Width(), m_aniMap.Height(), m_aniMap.GetLayer(j)
					);
				} else {
					m_pFrames[j] = NULL;
				}
			}
		} duk_pop(pCtx);
	} duk_pop(pCtx);
}

//-----------------------------------------------------------------------------
void AdEntity::Unload(void) {
	m_bTriggered = false;
	memset(m_pType, 0x00, NAME_LENGTH);
	memset(&m_recTrigger, 0x00, sizeof(SDL_Rect));

	for(int j=0; j<m_aniMap.nLayers(); ++j) {
		if(m_pFrames && m_pFrames[j]) {
			SDL_FreeSurface(m_pFrames[j]);
			m_pFrames[j] = NULL;
		}
	}

	if(m_pFrames) {
		free(m_pFrames);
		m_pFrames = NULL;
	}
}

//-----------------------------------------------------------------------------
void AdEntity::Update(AdLevel* pLvl) {
	AdEntity* pPlayer = pLvl->GetPlayer();

	if(pPlayer != NULL) {
		SDL_Rect recResult;
		SDL_Rect recPlayer = pPlayer->m_recTrigger;

		if(SDL_IntersectRect(&m_recTrigger, &recPlayer, &recResult))
			m_bTriggered = true;
		else
			m_bTriggered = false;
	}

	AdTiledManager* pMap;
	pMap = pLvl->GetTiledMap();
	
	HandleMovement(pMap);
}

//-----------------------------------------------------------------------------
void AdEntity::Render(AdLevel* pLvl) {
	if(m_pFrames==NULL) return;
	SDL_Point pnt = {m_recTrigger.x, m_recTrigger.y};
	AdScreen::DrawSprite(pnt, m_pFrames[m_iFrame]);
}

//-----------------------------------------------------------------------------
bool AdEntity::DoesCollide(
	class AdTiledManager* pMap, int iDirec /*= -1*/,
	int iOffsetI /*= 0*/, int iOffsetJ /*= 0*/
) {
	int iW = (int) floor(m_recTrigger.w/8.0f);
	int iH = (int) floor(m_recTrigger.h/8.0f);

	bool bCollides = false;

	switch(iDirec) {
		case UP_DIREC: {
			bool bTemp = true;
			for(int i=0; i<iW; ++i) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)-1)==0
				);
			} bCollides = !bTemp;
		} break;

		case DOWN_DIREC: {
			bool bTemp = true;
			for(int i=0; i<iW; ++i) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)+iH)==0
				);
			} bCollides = !bTemp;
		} break;

		case LEFT_DIREC: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)-1, (m_iJ+iOffsetJ)+j)==0
				);
			} bCollides = !bTemp;
		} break;

		case RIGHT_DIREC: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+iW, (m_iJ+iOffsetJ)+j)==0
				);
			} bCollides = !bTemp;
		} break;

		default: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				for(int i=0; i<iW; ++i)
					bTemp = (bTemp && pMap->GetTile(
						COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)+j)==0
					);
			} bCollides = !bTemp;
		} break;
	}

	return bCollides;
}

//-----------------------------------------------------------------------------
void AdEntity::HandleMovement(class AdTiledManager* pMap) {
	m_iI = (int) floor(m_recTrigger.x/8.0f);
	m_iJ = (int) floor(m_recTrigger.y/8.0f);

	if(!m_bFreeToMove && !m_bMoving) return;

	if(m_iMoveframe>0) m_iMoveframe--;
	else if(m_bMoving) {
		m_bMoving = false;
		m_bForceMove = false;
	}

	if(!m_bMoving) {
		if(m_bForceMove) {
			if(m_iForcedirec==UP_DIREC &&
				!DoesCollide(pMap, UP_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = UP_DIREC;
			} else if(m_iForcedirec==DOWN_DIREC &&
				!DoesCollide(pMap, DOWN_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = DOWN_DIREC;
			} else if(m_iForcedirec==LEFT_DIREC &&
				!DoesCollide(pMap, LEFT_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = LEFT_DIREC;
			} else if(m_iForcedirec==RIGHT_DIREC &&
				!DoesCollide(pMap, RIGHT_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = RIGHT_DIREC;
			} else {
				// NOTE: if the forced moves results in a collision then toggle
				// off the forced move
				m_bForceMove = false;
			}
		} else {
			if(m_bUp && !DoesCollide(pMap, UP_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = UP_DIREC;
			} else if(m_bDown && !DoesCollide(pMap, DOWN_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = DOWN_DIREC;
			} else if(m_bLeft && !DoesCollide(pMap, LEFT_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = LEFT_DIREC;
			} else if(m_bRight && !DoesCollide(pMap, RIGHT_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = RIGHT_DIREC;
			}
		}
	}

	if(m_bMoving) {
		switch(m_iMovedirec) {
			case UP_DIREC:    m_recTrigger.y--; break;
			case DOWN_DIREC:  m_recTrigger.y++; break;
			case LEFT_DIREC:  m_recTrigger.x--; break;
			case RIGHT_DIREC: m_recTrigger.x++; break;
		}
	}
}
