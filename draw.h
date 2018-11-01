#ifndef DRAW_H
#define DRAW_H

#include "str.h"

void MDE_SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void MDE_DrawAxis(SDL_Surface *screen, MDE_Space *space);
void MDE_SetVertex(SDL_Surface *screen, MDE_Polygon *poly, int x, int y);
void MDE_DrawSegment(SDL_Surface *screen, MDE_Cam cam, MDE_Vertex *vA, MDE_Vertex *vB);
void MDE_DrawPolygon(SDL_Surface *screen, MDE_Cam cam, MDE_Polygon *poly);
void MDE_DrawPolyhedron(SDL_Surface *screen, MDE_Cam cam, MDE_Polyhedron *poly);
void MDE_DrawSpace(SDL_Surface *screen, MDE_Space *space);
void MDE_DrawSpaceAxes(SDL_Surface *screen, MDE_Space *space);

#endif
