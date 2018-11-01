#ifndef INIT_H
#define INIT_H

#include "str.h"
#include <math.h>

void MDE_InitSpace(MDE_Space *space);
void MDE_InitPolyhedron(MDE_Polyhedron *poly, int nbVertex);
void MDE_InitCam(MDE_Cam *cam);
void MDE_InitMatrix(MDE_Space *space);
void MDE_InitPolygon(MDE_Polygon *poly);
void MDE_PolyOverflow(MDE_Space *space);

#endif
