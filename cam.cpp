#include "cam.h"

void MDE_TranslateCenter(MDE_Space *space, int direction){
	
	switch(direction){
		case MDE_PLUSX:
			space->cam.center[0]+=space->cam.lineSpeed;
		break;

		case MDE_MINUSX:
			space->cam.center[0]-=space->cam.lineSpeed;
		break;

		case MDE_PLUSY:
			space->cam.center[1]+=space->cam.lineSpeed;
		break;

		case MDE_MINUSY:
			space->cam.center[1]-=space->cam.lineSpeed;
		break;
	}
}

void MDE_Zoom(MDE_Space *space, bool direction){
	space->cam.centerDist+=(direction)?space->cam.lineSpeed:-space->cam.lineSpeed;
	space->cam.unitPitch=1/space->cam.centerDist;
}
