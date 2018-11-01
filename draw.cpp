#include "draw.h"

void MDE_DrawAxis(SDL_Surface *screen, MDE_Space *space);
}

void MDE_SetVertex(SDL_Surface *screen, MDE_Polygon *poly, int nVertex, int x, int y){
}

void MDE_DrawSegment(SDL_Surface *screen, MDE_Cam cam, MDE_Vertex *vA, MDE_Vertex *vB){
	int x=0;
	int y=0;
	double Xdif=(vB->x-vA->x)*cam.unitPitch;
	double Ydif=(vB->y-vA->y)*cam.unitPitch;
	double coef;

	if(Xdif!=0){
		coef=Ydif/Xdif;
		if(coef>=-1 && coef<=1){
			for(;(Xdif>0)?x<=Xdif:x>=Xdif;(Xdif>0)?x++:x--){
				//MDE_SetPixel(screen,static_cast<int>((x+vA->x-cam.center[0])*cam.unitPitch)+500,static_cast<int>((coef*x+vA->y-cam.center[1])*cam.unitPitch)+300,0x000000);
				MDE_SetPixel(screen,static_cast<int>((vA->x-cam.center[0])*cam.unitPitch)+500+x,static_cast<int>(coef*x+(vA->y-cam.center[1])*cam.unitPitch)+300,0x000000);
			}
		}
		else{
			for(;(Ydif>0)?y<=Ydif:y>=Ydif;(Ydif>0)?y++:y--){
				MDE_SetPixel(screen,static_cast<int>((1/coef)*y+(vA->x-cam.center[0])*cam.unitPitch)+500,static_cast<int>((vA->y-cam.center[1])*cam.unitPitch)+300+y,0x000000);
			}
		}
	}
	else{
		for(;(Ydif>0)?y<=Ydif:y>=Ydif;(Ydif>0)?y++:y--){
			MDE_SetPixel(screen,static_cast<int>((vA->x-cam.center[0])*cam.unitPitch)+500,static_cast<int>((vA->y-cam.center[1])*cam.unitPitch)+300+y,0x000000);
		}
	}
}

void MDE_DrawPolygon(SDL_Surface *screen, MDE_Cam cam, MDE_Polygon *poly){
	int i;

	for(i=0;i<poly->nbVertex;i++){
		MDE_DrawSegment(screen,cam,poly->vertex[i],poly->vertex[(i+1)%poly->nbVertex]);
	}
}

void MDE_DrawPolyhedron(SDL_Surface *screen, MDE_Cam cam, MDE_Polyhedron *poly){
	int i;

	for(i=0;i<poly->nbPolygon;i++){
	//	cout << poly->polygon[i].normal.z << endl;
	//	if(poly->polygon[i].normal.z>=0)
			MDE_DrawPolygon(screen,cam,&poly->polygon[i]);
	}
}

void MDE_DrawSpace(SDL_Surface *screen, MDE_Space *space){
	int i;

	SDL_FillRect(screen,NULL,0xbbbbbb);
	if(space->axes==true){
		for(i=0;i<3;i++)
			MDE_DrawAxis(screen,space->axis[i])
	}
	for(i=0;i<space->nbPolyhedron;i++){
		MDE_DrawPolyhedron(screen,space->cam,&space->polyhedron[i]);
	}
	SDL_Flip(screen);
}

void MDE_SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel){

	Uint8 *p;
	int bpp; 
	if(x>=0 && y>=0 && x<surface->w && y<surface->h)
	{
		bpp = surface->format->BytesPerPixel;

		p = (Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

		switch(bpp) 
		{
			case 1:
				*p = pixel;
				break;

			case 2:
				*(Uint16 *)p = pixel;
				break;

			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				} else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;

			case 4:
				*(Uint32 *)p = pixel;
				break;
		}
	}
}
