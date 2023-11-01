#include "Resources.h"

void InitResources() {
	std::cout << "Begin resources initialization..." << std::endl;
	Fonts::Init();
	Audio::Init();
	Textures::Init();
}

void CleanResources() {
	std::cout << "Begin resources cleaning..." << std::endl;
	Fonts::Clean();
	Audio::Clean();
	Textures::Clean();
}

namespace Fonts {
	TTF_Font* RobotoRegular;
	
	void Init() {
		RobotoRegular = TTF_OpenFont("res/fonts/Roboto-Regular.ttf", 15);
		std::cout << "All fonts loaded !" << std::endl;
	}

	void Clean() {
		TTF_CloseFont(RobotoRegular);
		std::cout << "All fonts closed !" << std::endl;
	}
}

namespace Audio {
	void Init() {
		std::cout << "All audio sources loaded !" << std::endl;
	}

	void Clean() {
		std::cout << "All audio sources destroyed !" << std::endl;
	}
}

namespace Textures {
	void Init() {
		std::cout << "All textures loaded !" << std::endl;
	}

	void Clean() {
		std::cout << "All textures destroyed !" << std::endl;
	}
}