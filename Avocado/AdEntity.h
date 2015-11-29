#ifndef __ADENTITY_H_
#define __ADENTITY_H_

#include "AdBase.h"
#include "AdTiledManager.h"

//-----------------------------------------------------------------------------
class AdEntity {
friend class AdTiledManager;

protected:
	int            m_iFrame;
	SDL_Surface**  m_pFrames;
	int            m_iFrameCount;
	AdTiledManager m_aniMap;

public:
	SDL_Rect m_recTrigger;

	int      m_iI;
	int      m_iJ;

	int      m_iMoveframe;
	int      m_iMovedirec;

	bool     m_bMoving;
	bool     m_bFreeToMove;

	int      m_iForcedirec;
	bool     m_bForceMove;

	bool     m_bUp;
	bool     m_bDown;
	bool     m_bLeft;
	bool     m_bRight;

	bool     m_bUpCheck;
	bool     m_bDownCheck;
	bool     m_bLeftCheck;
	bool     m_bRightCheck;

	char     m_pSendTo[NAME_LENGTH];

protected:
	bool m_bTriggered;
	char m_pType[NAME_LENGTH];

protected:
	virtual void Load(duk_context* pCtx);

public:
	const char* GetType(void) {return m_pType;}
	const bool  IsTriggered(void) {return m_bTriggered;}

public:
	virtual void Unload(void);

	virtual void Update(class AdLevel* pLvl);
	virtual void Render(class AdLevel* pLvl);

	bool DoesCollide(
		class AdTiledManager* pMap, int iDirec = -1,
		int iOffsetI = 0, int iOffsetJ = 0
	);

	void HandleMovement(class AdTiledManager* pMap);

public:
	AdEntity(
		int iX = 0, int iY = 0,
		int iW = 0, int iH = 0,
		const char* pFileName = NULL
	);
	~AdEntity(void);
};

#endif
