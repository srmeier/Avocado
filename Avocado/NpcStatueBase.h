#ifndef __NPCSTATUEBASE_H_
#define __NPCSTATUEBASE_H_

#include "AdEntity.h"

//-----------------------------------------------------------------------------
class NpcStatueBase: public AdEntity {
public:
	void Update(class AdLevel* pLvl);
	void Render(class AdLevel* pLvl);
};

#endif
