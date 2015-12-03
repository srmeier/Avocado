#ifndef __NPCTREE0_H_
#define __NPCTREE0_H_

#include "AdEntity.h"

//-----------------------------------------------------------------------------
class NpcTree0: public AdEntity {
public:
	void Update(class AdLevel* pLvl);
	void Render(class AdLevel* pLvl);

public:
	NpcTree0(void);
	~NpcTree0(void);
};

#endif
