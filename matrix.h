#ifndef MATRIX_H
#define MATRIX_H

#include "init.h"

void MDE_Rotate(MDE_Space *space, int Axe, bool direction);
void MDE_MatrixMul(MDE_Vertex *vertex, MDE_Cam cam, double matrix[3][3]);
#endif
