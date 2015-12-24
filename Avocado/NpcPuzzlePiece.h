#ifndef __NPCPUZZLEPIECE_H_
#define __NPCPUZZLEPIECE_H_

#include "AdEntity.h"

//-----------------------------------------------------------------------------
class NpcPuzzlePiece: public AdEntity {
public:
	void Update(class AdLevel* pLvl);
};

#endif
