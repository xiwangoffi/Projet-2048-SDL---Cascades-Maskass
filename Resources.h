#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_Ttf.h"
#include "SDL_Mixer.h"

void InitResources();
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
	void Init();
	void Clean();
}