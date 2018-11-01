#include "init.h"

void MDE_InitSpace(MDE_Space *space){
	int i;

	MDE_InitMatrix(space);
	MDE_InitCam(&space->cam);
	space->nbPolyhedron=0;
	space->polyhedron=new MDE_Polyhedron[10];
	space->MaxPolyhedron=10;
	space->axes=true;
	space->axis[0].unitVector.x=1;
	space->axis[0].unitVector.y=0;
	space->axis[0].unitVector.z=0;
	space->axis[0].thickness=10;
	space->axis[1].unitVector.x=0;
	space->axis[1].unitVector.y=1;
	space->axis[1].unitVector.z=0;
	space->axis[1].thickness=10;
	space->axis[2].unitVector.x=0;
	space->axis[2].unitVector.y=0;
	space->axis[2].unitVector.z=1;
	space->axis[2].thickness=10;
	/*space->nbPolyhedron=rand()%4+1;
	space->polyhedron=new MDE_Polyhedron[space->nbPolyhedron];
	for(i=0;i<space->nbPolyhedron;i++){	
		MDE_InitPolyhedron(&space->polyhedron[i],4);
	}*/
}

void MDE_PolyOverflow(MDE_Space *space){
	int i;
	MDE_Polyhedron *tmp=new MDE_Polyhedron[space->MaxPolyhedron+10];
	for(i=0;i<space->MaxPolyhedron;i++)
		tmp[i]=space->polyhedron[i];
	delete[] space->polyhedron;
	space->MaxPolyhedron+=10;
	space->polyhedron=new MDE_Polyhedron[space->MaxPolyhedron];
	for(i=0;i<space->MaxPolyhedron-10;i++)
		space->polyhedron[i]=tmp[i];
}

void MDE_InitPolyhedron(MDE_Polyhedron *poly, int nbVertex){
	int i,j,k;

	poly->nbVertex=nbVertex;
	poly->vertex=new MDE_Vertex[nbVertex];
	for(i=0;i<nbVertex;i++){
		poly->vertex[i].x=rand()%201-100;
		poly->vertex[i].y=rand()%201-100;
		poly->vertex[i].z=rand()%201-100;
	}
	poly->nbPolygon=4;
	poly->polygon=new MDE_Polygon[4];
	for(j=0;j<4;j++){
		poly->polygon[j].nbVertex=3;
		poly->polygon[j].vertex=new MDE_Vertex*[3];
	}
	/*for(i=0;i<poly->nbPolygon;i++){
		initPolygon(&poly->polygon[i]);
	}*/
	
	for(k=0;k<4;k++){
		poly->polygon[k].vertex[0]=&poly->vertex[k];
		poly->polygon[k].vertex[1]=&poly->vertex[(k+1)%4];
		poly->polygon[k].vertex[2]=&poly->vertex[(k+2)%4];
	}
}

void MDE_InitCam(MDE_Cam *cam){
	cam->center[0]=0;
	cam->center[1]=0;
	cam->angularSpeed=0.005;
	cam->lineSpeed=0.01;
	cam->centerDist=1.0;
	cam->unitPitch=1/cam->centerDist;
}

/*void initPolygon(MDE_Polygon *poly){
	int i;
	
	poly->nbVertex=4;
	poly->vertex=new MDE_Vertex*[3];
	for(i=0;i<3;i++){
		poly->vertex[i].x=(double)rand()%1000;
		poly->vertex[i].y=rand()%600;
	}
}*/

void MDE_InitMatrix(MDE_Space *space){
	space->Xmatrix[0][0]=1;
	space->Xmatrix[0][1]=0;
	space->Xmatrix[0][2]=0;
	space->Xmatrix[1][0]=0;
	space->Xmatrix[1][1]=cos(space->cam.angularSpeed);
	space->Xmatrix[1][2]=sin(space->cam.angularSpeed);
	space->Xmatrix[2][0]=0;
	space->Xmatrix[2][1]=-sin(space->cam.angularSpeed);
	space->Xmatrix[2][2]=cos(space->cam.angularSpeed);

	space->Ymatrix[0][0]=cos(space->cam.angularSpeed);
	space->Ymatrix[0][1]=0;
	space->Ymatrix[0][2]=-sin(space->cam.angularSpeed);
	space->Ymatrix[1][0]=0;
	space->Ymatrix[1][1]=1;
	space->Ymatrix[1][2]=0;
	space->Ymatrix[2][0]=sin(space->cam.angularSpeed);
	space->Ymatrix[2][1]=0;
	space->Ymatrix[2][2]=cos(space->cam.angularSpeed);
	
	space->Zmatrix[0][0]=cos(space->cam.angularSpeed);
	space->Zmatrix[0][1]=sin(space->cam.angularSpeed);
	space->Zmatrix[0][2]=0;
	space->Zmatrix[1][0]=-sin(space->cam.angularSpeed);
	space->Zmatrix[1][1]=cos(space->cam.angularSpeed);
	space->Zmatrix[1][2]=0;
	space->Zmatrix[2][0]=0;
	space->Zmatrix[2][1]=0;
	space->Zmatrix[2][2]=1;
}
