#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "draw.h"
#include "cam.h"
#include "matrix.h"
#include "objread.h"

#define PI 3.1415

int ch_to_int(char *ch);
double frand(double fMin, double fMax);

int main(int argc, char **argv){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen=SDL_SetVideoMode(1000,600,32,SDL_DOUBLEBUF || SDL_RESIZABLE);
	SDL_FillRect(screen,NULL,0xdddddd);
	SDL_Flip(screen);
	SDL_Event event;
	MDE_Space space;
	int stop=0;
	int i;
	char *tmp_path;

	srand(time(NULL));
	/*for(i=1;i<argc;i++){
		if (argv[i][0]=='-'){
			switch (argv[i][1]){
				case 'v':
					 nbVertex=ch_to_int(argv[i]);
				break;

				case 't':
					 type=ch_to_int(argv[i]);
				break;
			}
		}
	}*/
	MDE_Vertex v;
	v.x=0;
	v.y=0;
	v.z=0;

	MDE_InitSpace(&space);
//	MDE_LoadObj(&space,v,"Model/cube.obj");
	cout << "aziz" << endl;
	cout << space.nbPolyhedron << endl;
	//MDE_DrawPolyhedron(screen,space.cam,space.polyhedron[1]);
	SDL_Flip(screen);
	//event(screen,&poly);
	while(!stop){
		SDL_PollEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				stop=1;
			break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						stop=1;
					break;

					case SDLK_l:
						MDE_LoadObj(&space,v,"Model/icosahedron.obj");
					break;

					case SDLK_RIGHT:
						MDE_Rotate(&space,Yaxe,1);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_LEFT:
						MDE_Rotate(&space,Yaxe,0);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_UP:
						MDE_Rotate(&space,Xaxe,1);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_DOWN:
						MDE_Rotate(&space,Xaxe,0);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP6:
						MDE_TranslateCenter(&space,MDE_PLUSX);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP4:
						MDE_TranslateCenter(&space,MDE_MINUSX);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP8:
						MDE_TranslateCenter(&space,MDE_PLUSY);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP2:
						MDE_TranslateCenter(&space,MDE_MINUSY);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP5:
						MDE_InitCam(&space.cam);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP9:
						MDE_Zoom(&space,1);
						MDE_DrawSpace(screen,&space);
					break;

					case SDLK_KP3:
						MDE_Zoom(&space,0);
						MDE_DrawSpace(screen,&space);
					break;
				}
			break;
		}
	}
	SDL_Quit();
return 0;
}

int ch_to_int(char *ch){
	int i;
	int numb=0;

	for (i=2;ch[i]>='0' && ch[i]<='9';i++){
		numb=10*numb+ch[i]-'0';
	}
return numb;
}

double frand(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
return fMin + f * (fMax - fMin);
}

