#include "matrix.h"

#define AS 0.02

void MDE_Rotate(MDE_Space *space, MDE_Axis axis, bool direction){
	int i,j;


	switch(axis){
		case MDE_Xaxis:
			if(direction)
				space->cam.angularSpeed=AS;
			else
				space->cam.angularSpeed=-AS;
			
			MDE_InitMatrix(space);
			for(i=0;i<space->nbPolyhedron;i++){
				for(j=0;j<space->polyhedron[i].nbVertex;j++)
					MDE_MatrixMul(&space->polyhedron[i].vertex[j],space->cam,space->Xmatrix);
				for(j=0;j<space->polyhedron[i].nbPolygon;j++)
					MDE_MatrixMul(&space->polyhedron[i].polygon[j].normal,space->cam,space->Xmatrix);
			}
		break;

		case MDE_Yaxis:
			if(direction)
				space->cam.angularSpeed=AS;
			else
				space->cam.angularSpeed=-AS;

			MDE_InitMatrix(space);
			for(i=0;i<space->nbPolyhedron;i++){
				for(j=0;j<space->polyhedron[i].nbVertex;j++)
					MDE_MatrixMul(&space->polyhedron[i].vertex[j],space->cam,space->Ymatrix);
				for(j=0;j<space->polyhedron[i].nbPolygon;j++)
					MDE_MatrixMul(&space->polyhedron[i].polygon[j].normal,space->cam,space->Xmatrix);
			}
		break;
	}
}

void MDE_MatrixMul(MDE_Vertex *vertex, MDE_Cam cam, double matrix[3][3]){
	double newMatrix[3];
	int i;

	for(i=0;i<3;i++){
		newMatrix[i]=(vertex->x-cam.center[0])*matrix[0][i]+(vertex->y+cam.center[1])*matrix[1][i]+vertex->z*matrix[2][i];
	}
	vertex->x=newMatrix[0];
	vertex->y=newMatrix[1];
	vertex->z=newMatrix[2];
}
