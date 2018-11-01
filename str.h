#ifndef STR_H
#define STR_H

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

enum MDE_Axis{MDE_Xaxis,MDE_Yaxis,MDE_Zaxis};
enum MDE_TranslationAxes{MDE_PLUSX,MDE_MINUSX,MDE_PLUSY,MDE_MINUSY};

struct MDE_Spin{
	double spin_x,spin_y,spin_z;
};

struct MDE_Vertex{
	double x,y,z;
};

struct MDE_Polygon{
	MDE_Vertex normal;
	int nbVertex;
	MDE_Vertex **vertex;
};

struct MDE_Polyhedron{
	int nbVertex;
	int nbPolygon;
	MDE_Vertex *vertex;
	MDE_Polygon *polygon;
	MDE_Spin spin;
};

struct MDE_Cam{
	double angularSpeed;
	double lineSpeed;
	double center[2];
	double centerDist;
	double unitPitch;
};

struct MDE_File{
	int nbObj;
	MDE_Polyhedron *obj;
};

struct MDE_Axis{
	int thickness;
	char *name;
	MDE_Vertex unitVector;
};

struct MDE_Space{
	int MaxPolyhedron;
	int nbPolyhedron;
	MDE_Polyhedron *polyhedron;
	MDE_Cam cam;
	MDE_TranslationAxes transAxes;
	double Xmatrix[3][3];
	double Ymatrix[3][3];
	double Zmatrix[3][3];
	bool axes;
	MDE_Axis axis[3];
};

#endif
