#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_Ttf.h"
#include "SDL_Mixer.h"
#include <string>
#include <map>

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

	void Init(SDL_Renderer* renderer);
	void Clean();
}