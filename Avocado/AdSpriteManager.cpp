/*
*/

#include "AdBase.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
SDL_Surface** AdSpriteManager::s_pTiles;
int           AdSpriteManager::s_iNumTile;

int AdSpriteManager::s_iSprWidth;
int AdSpriteManager::s_iSprHeight;

//-----------------------------------------------------------------------------
bool AdSpriteManager::Init(int iWidth, int iHeight) {
	s_iSprWidth  = iWidth;
	s_iSprHeight = iHeight;

	SDL_Surface* surface = SDL_LoadBMP(SPRITE_LOCATION);

	if(surface == NULL) {
		fprintf(stderr, SDL_GetError());
		return false;
	}

	s_iNumTile = (surface->w/s_iSprWidth)*(surface->h/s_iSprHeight)+1;
	s_pTiles   = (SDL_Surface**) malloc(s_iNumTile*sizeof(SDL_Surface*));

	int i, x, y;
	SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};
	for(i=0; i<s_iNumTile; i++) {
		s_pTiles[i] = SDL_CreateRGBSurface(0, s_iSprWidth, s_iSprHeight, 24, 0x00, 0x00, 0x00, 0x00);
		if(i==0) {
			SDL_FillRect(s_pTiles[i], NULL, 0xFF00FF);
		} else {
			x = (i-1)%(surface->w/s_iSprWidth);
			y = (i-x)/(surface->w/s_iSprWidth);
			rect.x = s_iSprWidth*x, rect.y = s_iSprHeight*y;
			SDL_BlitSurface(surface, &rect, s_pTiles[i], NULL);
		}
	}

	SDL_FreeSurface(surface);
	surface = NULL;

	return true;
}

//-----------------------------------------------------------------------------
void AdSpriteManager::Quit(void) {
	int i;
	for(i=0; i<s_iNumTile; i++) {
		SDL_FreeSurface(s_pTiles[i]);
		s_pTiles[i] = NULL;
	}

	free(s_pTiles);
	s_pTiles = NULL;
}

//-----------------------------------------------------------------------------
SDL_Surface* AdSpriteManager::BuildSprite(int iWidth, int iHeight, int pIndices[]) {
	SDL_Surface* pSprite = NULL;
	pSprite = SDL_CreateRGBSurface(
		0, s_iSprWidth*iWidth, s_iSprHeight*iHeight,
		24, 0x00, 0x00, 0x00, 0x00
	);

	SDL_SetColorKey(pSprite, 1, 0xFF00FF);
	SDL_FillRect(pSprite, 0, 0xFF00FF);

	int i, j;
	SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};
	for(j=0; j<iHeight; j++) {
		for(i=0; i<iWidth; i++) {
			rect.x = s_iSprWidth*i, rect.y = s_iSprHeight*j;
			SDL_BlitSurface(s_pTiles[pIndices[iWidth*j+i]], NULL, pSprite, &rect);
		}
	}

	return pSprite;
}

//-----------------------------------------------------------------------------
SDL_Surface* AdSpriteManager::BuildSprite(const char* pString) {
	if(pString == NULL) return NULL;

	int iStrLen = (int) strlen(pString);

	SDL_Surface* pSprite = NULL;
	pSprite = SDL_CreateRGBSurface(
		0, s_iSprWidth*iStrLen, s_iSprHeight,
		24, 0x00, 0x00, 0x00, 0x00
	);

	SDL_SetColorKey(pSprite, 1, 0xFF00FF);
	SDL_FillRect(pSprite, 0, 0xFF00FF);

	int i;
	for(i=0; i<iStrLen; i++) {
		SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};

		int iIndex = 0x00;
		switch(pString[i]) {
			case 'A' : iIndex = 0x01; break;
			case 'B' : iIndex = 0x02; break;
			case 'C' : iIndex = 0x03; break;
			case 'D' : iIndex = 0x04; break;
			case 'E' : iIndex = 0x05; break;
			case 'F' : iIndex = 0x06; break;
			case 'G' : iIndex = 0x07; break;
			case 'H' : iIndex = 0x08; break;
			case 'I' : iIndex = 0x09; break;
			case 'J' : iIndex = 0x0A; break;
			case 'K' : iIndex = 0x0B; break;
			case 'L' : iIndex = 0x0C; break;
			case 'M' : iIndex = 0x0D; break;
			case 'N' : iIndex = 0x0E; break;
			case 'O' : iIndex = 0x0F; break;
			case 'P' : iIndex = 0x10; break;
			case 'Q' : iIndex = 0x11; break;
			case 'R' : iIndex = 0x12; break;
			case 'S' : iIndex = 0x13; break;
			case 'T' : iIndex = 0x14; break;
			case 'U' : iIndex = 0x15; break;
			case 'V' : iIndex = 0x16; break;
			case 'W' : iIndex = 0x17; break;
			case 'X' : iIndex = 0x18; break;
			case 'Y' : iIndex = 0x19; break;
			case 'Z' : iIndex = 0x1A; break;
			case '1' : iIndex = 0x1B; break;
			case '2' : iIndex = 0x1C; break;
			case '3' : iIndex = 0x1D; break;
			case '4' : iIndex = 0x1E; break;
			case '5' : iIndex = 0x1F; break;
			case '6' : iIndex = 0x20; break;
			case '7' : iIndex = 0x21; break;
			case '8' : iIndex = 0x22; break;
			case '9' : iIndex = 0x23; break;
			case '0' : iIndex = 0x24; break;
			case '!' : iIndex = 0x25; break;
			case '#' : iIndex = 0x26; break;
			case '$' : iIndex = 0x27; break;
			case '%' : iIndex = 0x28; break;
			case '~' : iIndex = 0x29; break;
			case '*' : iIndex = 0x2A; break;
			case '(' : iIndex = 0x2B; break;
			case ')' : iIndex = 0x2C; break;
			case '-' : iIndex = 0x2D; break;
			case '+' : iIndex = 0x2E; break;
			case '=' : iIndex = 0x2F; break;
			case '[' : iIndex = 0x30; break;
			case ']' : iIndex = 0x31; break;
			case '\"': iIndex = 0x32; break;
			case '\'': iIndex = 0x33; break;
			case '<' : iIndex = 0x34; break;
			case '>' : iIndex = 0x35; break;
			case '.' : iIndex = 0x36; break;
			case '?' : iIndex = 0x37; break;
			case '/' : iIndex = 0x38; break;
		}

		rect.x = s_iSprWidth*i;
		SDL_BlitSurface(s_pTiles[iIndex], NULL, pSprite, &rect);
	}

	return pSprite;
}
