#ifndef __ADENTITY_H_
#define __ADENTITY_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdEntity {
friend class AdTiledManager;

public:
	SDL_Rect m_recTrigger;

protected:
	bool m_bTriggered;
	char m_pType[NAME_LENGTH];

protected:
	virtual void Load(duk_context* pCtx);

public:
	const char* GetType(void) {return m_pType;}

public:
	virtual void Unload(void);

public:
	virtual void Update(class AdLevel* pLvl);
	virtual void Render(class AdLevel* pLvl);

public:
	AdEntity(void);
	virtual ~AdEntity(void);
};

#endif
