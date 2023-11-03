#include "Resources.h"

void InitResources(SDL_Renderer* renderer) {
	cout << "Begin resources initialization..." << endl;
	Fonts::Init();
	Audio::Init();
	Textures::Init(renderer);
}

void CleanResources() {
	cout << "Begin resources cleaning..." << endl;
	Fonts::Clean();
	Audio::Clean();
	Textures::Clean();
}

namespace Fonts {
	TTF_Font* RobotoRegular;
	
	void Init() {
		RobotoRegular = TTF_OpenFont("res/fonts/Roboto-Regular.ttf", 15);
		cout << "All fonts loaded !" << endl;
	}

	void Clean() {
		TTF_CloseFont(RobotoRegular);
		cout << "All fonts closed !" << endl;
	}
}

namespace Audio {
	Mix_Chunk* Bubbles[3];
	Mix_Chunk* Sand;
	Mix_Music* Crab;
	Mix_Chunk* Loose;

	void Init() {
		for (int i = 0; i < 3; i++)
		{
			string path = "res/audio/sfx/bubble" + to_string(i + 1) + ".mp3";
			Bubbles[i] = Mix_LoadWAV(path.c_str());
			if (Bubbles[i] == NULL) {
				printf("Error: %s", Mix_GetError());
			}
		}
		
		Sand = Mix_LoadWAV("res/audio/sfx/sand.mp3");
		Crab = Mix_LoadMUS("res/audio/musics/crab.mp3");
		Loose = Mix_LoadWAV("res/audio/sfx/loose.mp3");

		cout << "All audio sources loaded !" << endl;
	}

	void Clean() {
		cout << "All audio sources destroyed !" << endl;
	}
}

namespace Textures {
	map<int, SDL_Texture*> TileTextures;
	SDL_Texture* Cell;
	SDL_Texture* Map;

	void Init(SDL_Renderer* renderer) {
		for (int i = 0; i < 11; i++)
		{
			int value = pow(2, i + 1);
			string path = "res/images/" + to_string(value) + ".png";
			TileTextures[value] = IMG_LoadTexture(renderer, path.c_str());
		}

		 Map = IMG_LoadTexture(renderer, "res/images/map.jpg");
		 Cell = IMG_LoadTexture(renderer, "res/images/cell.jpg");

		cout << "All textures loaded !" << endl;
	}

	void Clean() {
		for (int i = 0; i < TileTextures.size(); i++)
		{
			SDL_DestroyTexture(TileTextures[pow(2, i + 1)]);
		}
		cout << "All textures destroyed !" << endl;
	}
}