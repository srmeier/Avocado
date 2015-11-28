/*
*/

#include "AdLevel.h"
#include "AdEntity.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdEntity::AdEntity(void) {}

//-----------------------------------------------------------------------------
AdEntity::~AdEntity(void) {}

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
}

//-----------------------------------------------------------------------------
void AdEntity::Unload(void) {
	m_bTriggered = false;
	memset(m_pType, 0x00, NAME_LENGTH);
	memset(&m_recTrigger, 0x00, sizeof(SDL_Rect));
}

//-----------------------------------------------------------------------------
void AdEntity::Update(AdLevel* pLvl) {
	SDL_Rect recResult;
	SDL_Rect recPlayer = pLvl->GetPlayer()->m_recTrigger;

	if(SDL_IntersectRect(&m_recTrigger, &recPlayer, &recResult))
		m_bTriggered = true;
	else
		m_bTriggered = false;
}

//-----------------------------------------------------------------------------
void AdEntity::Render(AdLevel* pLvl) {}
