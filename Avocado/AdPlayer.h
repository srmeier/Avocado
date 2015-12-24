#ifndef __ADPLAYER_H_
#define __ADPLAYER_H_

#include "AdEntity.h"

//-----------------------------------------------------------------------------
class AdPlayer: public AdEntity {
public:
	bool hasPuzzlePiece;

public:
	void Update(class AdLevel* pLvl);

public:
	AdPlayer(void);
	~AdPlayer(void);
};

#endif
