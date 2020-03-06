/*╞══════════════════════════════════════════════════════╡
	
	* File Name : crawler.c

	* Created By :  Octave                             
                                          
	* Creation Date : 27-02-2019

	* Last Modified : lun. 20 mai 2019 20:51:10 CEST

  ╞══════════════════════════════════════════════════════╡*/
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int x;
	int y;
	int seed;
	int vie = 20;
	int n = 150;
	int isPressed = 0;
	SDL_Event touche;
	char tab[25][25];
	if (argc != 2)
	{
		printf("Erreur, utilisation: <seed>\n");
		return 0;
	}
	SDL_Window *fenetre = SDL_CreateWindow("Crawler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, 0);
	SDL_Surface *fond = SDL_LoadBMP("textures/fond.bmp");
	SDL_Surface *gauche = SDL_LoadBMP("textures/gauche.bmp");
	SDL_Surface *droite = SDL_LoadBMP("textures/droite.bmp");
	SDL_Surface *devant = SDL_LoadBMP("textures/devant.bmp");
	SDL_Surface *derriere = SDL_LoadBMP("textures/derriere.bmp");
	SDL_Texture *texture_fond = SDL_CreateTextureFromSurface(renderer, fond);
	SDL_Texture *texture_gauche = SDL_CreateTextureFromSurface(renderer, gauche);
	SDL_Texture *texture_droite = SDL_CreateTextureFromSurface(renderer, droite);
	SDL_Texture *texture_devant = SDL_CreateTextureFromSurface(renderer, devant);
	SDL_Texture *texture_derriere = SDL_CreateTextureFromSurface(renderer, derriere);
	SDL_Rect rect_derriere = {350, 450, 135, 119};
	SDL_Rect rect_gauche = {200, 229, 107, 217};
	SDL_Rect rect_droite = {550, 225, 90, 221};
	SDL_Rect rect_devant = {400, 262, 63, 70}; // Création de la fenêtre et des textures
	
	SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV("son/porte.wav", &wavSpec, &wavBuffer, &wavLength);
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	seed = atoi(argv[1]);
	for (x = 0; x < 25; x++)
	{
		for (y = 0; y < 25; y++)
		{
			tab[x][y] = ' ';
		}
	}
	tab[0][0] = 'D';
	srandom(seed);
	x = rand() % 26;
	srandom(seed + 10);
	y = rand() % 26;
	tab[x][y] = 'A';
	seed++;
	while (n)
	{
		srandom(seed);
		x = rand() % 26;
		srandom(seed + 10);
		y = rand() % 26;
		while (tab[x][y] != ' ')
		{
			srandom(seed);
			x = rand() % 26;
			srandom(seed + 10);
			y = rand() % 26;
			seed++;
		}
		tab[x][y] = 'I';
		seed++;
		n--;
	}
	n = 75;
	while (n)
	{
		srandom(seed);
		x = rand() % 26;
		srandom(seed + 10);
		y = rand() % 26;
		while (tab[x][y] != ' ')
		{
			srandom(seed);
			x = rand() % 26;
			srandom(seed + 10);
			y = rand() % 26;
			seed++;
		}
		tab[x][y] = '!';
		seed++;
		n--;
	}
	x = 0;
	y = 0;
	while (vie > 0)
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture_fond, NULL, NULL);
		if ((y - 1) >= 0 && tab[y - 1][x] != 'I')
			SDL_RenderCopy(renderer, texture_devant, NULL, &rect_devant);
		if (x - 1 >= 0 && tab[y][x - 1] != 'I')
			SDL_RenderCopy(renderer, texture_gauche, NULL, &rect_gauche);
		if (x + 1 <= 24 && tab[y][x + 1] != 'I')
			SDL_RenderCopy(renderer, texture_droite, NULL, &rect_droite);
		if (y + 1 <= 24 && tab[y + 1][x] != 'I')
			SDL_RenderCopy(renderer, texture_derriere, NULL, &rect_derriere);
		SDL_RenderPresent(renderer);

		while (!isPressed)
		{
			SDL_WaitEvent(&touche);
			switch (touche.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			case SDL_KEYDOWN:
			{
				switch (touche.key.keysym.sym)
				{
				case SDLK_LEFT:
				{
					if (x - 1 >= 0 && tab[y][x - 1] != 'I')
					{
						int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
						SDL_PauseAudioDevice(deviceId, 0);
						system("sleep 1");
						x--;
						isPressed = 1;
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (x + 1 <= 24 && tab[y][x + 1] != 'I')
					{
						int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
						SDL_PauseAudioDevice(deviceId, 0);
						system("sleep 1");
						isPressed = 1;
						x++;
					}
				}
				break;
				case SDLK_UP:
				{
					if (y - 1 >= 0 && tab[y - 1][x] != 'I')
					{
						int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
						SDL_PauseAudioDevice(deviceId, 0);
						system("sleep 1");
						isPressed = 1;
						y--;
					}
				}
				break;
				case SDLK_DOWN:
				{
					if (y + 1 <= 24 && tab[y + 1][x] != 'I')
					{
						int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
						SDL_PauseAudioDevice(deviceId, 0);
						system("sleep 1");
						isPressed = 1;
						y++;
					}
				}
				break;
				}
				break;
			}
			}
		}
		isPressed = 0;
		if (tab[y][x] == 'A')
		{
			printf("Victoire\n");
			return 0;
		}
	}
	SDL_DestroyTexture(texture_fond);
    SDL_DestroyTexture(texture_derriere);
	SDL_DestroyTexture(texture_devant);
	SDL_DestroyTexture(texture_gauche);
	SDL_DestroyTexture(texture_droite);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(derriere);
	SDL_FreeSurface(gauche);
	SDL_FreeSurface(droite);
	SDL_FreeSurface(devant);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}
