/*
*/

#include "NpcTree0.h"

//-----------------------------------------------------------------------------
NpcTree0::NpcTree0(void) {
	m_iFrame = 1;
	m_bTriggerToggle = false;
}

//-----------------------------------------------------------------------------
NpcTree0::~NpcTree0(void) {}

//-----------------------------------------------------------------------------
void NpcTree0::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	if(m_bTriggered) {

	}

	//if(m_bTriggered) m_bTriggerToggle = true;

	if(m_bTriggered /*m_bTriggerToggle*/) {
		m_iFrame = 0;
	} else {
		m_iFrameCount++;
		if(m_iFrameCount == 32) {
			m_iFrameCount = 0;

			m_iFrame++;
			if(m_iFrame > 2) m_iFrame = 1;
		}
	}
}
