#pragma once

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_Ttf.h"
#include "SDL_Mixer.h"

using namespace std;

void InitResources(SDL_Renderer* renderer);
void CleanResources();

namespace Fonts {
	extern TTF_Font* RobotoRegular;

	void Init();
	void Clean();
}

namespace Audio {
	void Init();
	void Clean();
}

namespace Textures {
	extern map<int, SDL_Texture*> TileTextures;
	extern SDL_Texture* Map;
	extern SDL_Texture* Cell;

	void Init(SDL_Renderer* renderer);
	void Clean();
}