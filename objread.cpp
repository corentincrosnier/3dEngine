#include "objread.h"

#define scale 50

char cur;
char pre;

double MDE_ConvertVertex(FILE *f_obj);
MDE_Polygon MDE_ConvertPolygon(FILE *f_obj, MDE_Vertex *normal, MDE_Vertex *vertex, int offset);

void MDE_LoadObj(MDE_Space *space, MDE_Vertex center, const char *f_path){
	FILE *f_obj;
	f_obj=fopen(f_path,"r");
	int i;
	int n=0;
	int v=0;
	int f=0;
	int o=-1;
	int nbObj=0;
	int offset=0;
	bool os=true;
	MDE_Vertex *normal;
	int nbNorm=0;

	//space->nbPolyhedron=0;
	while((cur=fgetc(f_obj))!=EOF){
		if(space->nbPolyhedron==space->MaxPolyhedron)
			MDE_PolyOverflow(space);
		if(pre=='\n'){
			if(cur=='o'){
				nbObj++;
				space->nbPolyhedron++;
			}
		}
		pre=cur;
	}
	if(space->nbPolyhedron==0){
		os=false;
		o=0;
		space->polyhedron[space->nbPolyhedron-nbObj].nbVertex=0;
		space->polyhedron[space->nbPolyhedron-nbObj].nbPolygon=0;
		space->nbPolyhedron++;
	}
	fseek(f_obj,0,SEEK_SET);
	while((cur=fgetc(f_obj))!=EOF){
		if(pre=='\n'){
			switch(cur){
				case 'o':
					o++;
					space->polyhedron[o].nbVertex=0;
					space->polyhedron[o].nbPolygon=0;
				break;
				case 'v':
					if((cur=fgetc(f_obj))=='t')
						break;
					if(cur=='n'){
						nbNorm++;
						break;
					}
					fseek(f_obj,-1,SEEK_CUR);
					space->polyhedron[o].nbVertex++;
				break;
				case 'f':
					space->polyhedron[o].nbPolygon++;
				break;
			}
		}
		pre=cur;
	}
	if(os==false)
		o=0;
	else
		o=-1;
	for(i=0;i<space->nbPolyhedron;i++){
		space->polyhedron[i].vertex=new MDE_Vertex[space->polyhedron[i].nbVertex];
		space->polyhedron[i].polygon=new MDE_Polygon[space->polyhedron[i].nbPolygon];
	}
	normal=new MDE_Vertex[nbNorm];
	fseek(f_obj,0,SEEK_SET);
	while((cur=fgetc(f_obj))!=EOF){
		if(pre=='\n'){
			switch(cur){
				case 'o':
					o++;
					if(o>0)
						offset+=space->polyhedron[o-1].nbVertex;
					v=0;
					f=0;
				break;
				case 'v':
					if((cur=fgetc(f_obj))=='t')
						break;
					else if(cur=='n'){
						normal[n].x=MDE_ConvertVertex(f_obj);
						normal[n].y=MDE_ConvertVertex(f_obj);
						normal[n].z=MDE_ConvertVertex(f_obj);
						n++;
						break;
					}
					fseek(f_obj,-1,SEEK_CUR);
					space->polyhedron[o].vertex[v].x=center.x+scale*MDE_ConvertVertex(f_obj);
					space->polyhedron[o].vertex[v].y=center.y-scale*MDE_ConvertVertex(f_obj);
					space->polyhedron[o].vertex[v].z=center.z+scale*MDE_ConvertVertex(f_obj);
					v++;
				break;
				case 'f':
					space->polyhedron[o].polygon[f]=MDE_ConvertPolygon(f_obj,normal,space->polyhedron[o].vertex,offset);
					f++;
				break;
			}
		}
		pre=cur;
	}
	/*while(!stop){
		switch((cur=fgetc(f_obj))){
			case 'v':
				if(first)
					obj->nbVertex++;
				else{
					if(!i)
						obj->vertex=new MDE_Vertex[obj->nbVertex];
					fseek(f_obj,1,SEEK_CUR);
					cout << "vertex[" << i << "].x=" << (obj->vertex[i].x=MDE_ConvertVertex(f_obj)) << endl;
					cout << "vertex[" << i << "].y=" << (obj->vertex[i].y=MDE_ConvertVertex(f_obj)) << endl;
					cout << "vertex[" << i << "].z=" << (obj->vertex[i].z=MDE_ConvertVertex(f_obj)) << endl;
					i++;
				}
			break;
			case 'f':
				if(first)
					obj->nbPolygon++;
				else{
					if(j==0)
						obj->polygon=new MDE_Polygon[obj->nbPolygon];
					obj->polygon[j]=MDE_ConvertPolygon(f_obj,obj->vertex);
					j++;
				}
			break;
			case EOF:
				if(first){
					first=false;
					fseek(f_obj,0,SEEK_SET);
				}
				else
					stop=1;
			break;
		}
	}*/
	fclose(f_obj);
}

/*MDE_Polygon MDE_ConvertPolygon(FILE *f_obj, MDE_Vertex *vertex, int offset){
	bool stop=false;
	bool first=true;
	long fpos=ftell(f_obj);
	int space=0;
	int slash=0;
	MDE_Polygon polygon;
	polygon.nbVertex=0;


	while(!stop){
		cur=fgetc(f_obj);
		if(!first){
			if(cur>='0' && cur<='9'){
				switch(slash){
					case 0:
						fseek(f_obj,-1,SEEK_CUR);
						polygon.vertex[space-1]=&vertex[(int)(MDE_ConvertVertex(f_obj))-offset-1];
				}
			}
			else if(cur=='/'){
				slash++;
			}
		}
		if(cur==' '){
			if(first)
				polygon.nbVertex++;
			else{
				slash=0;
				space++;
			}
		}
		else if(cur=='\n' || cur==EOF){
			if(first){
				fseek(f_obj,fpos,SEEK_SET);
				polygon.vertex=new MDE_Vertex*[polygon.nbVertex];
				first=false;
			}
			else
				stop=true;
		}
	}
return polygon;
}*/

MDE_Polygon MDE_ConvertPolygon(FILE *f_obj, MDE_Vertex *normal, MDE_Vertex *vertex, int offset){
	bool stop=false;
	bool first=true;
	long fpos=ftell(f_obj);
	int v=0;
	int slash=0;
	MDE_Polygon polygon;
	polygon.nbVertex=0;

	cur=fgetc(f_obj);
	while(cur!='\n' && cur!=EOF){
		for(;cur==' ';cur=fgetc(f_obj));
		while(cur!=' ' && cur!='\n' && cur!=EOF)
			cur=fgetc(f_obj);
		polygon.nbVertex++;
	}
	polygon.vertex=new MDE_Vertex*[polygon.nbVertex];
	fseek(f_obj,fpos,SEEK_SET);
	while((cur=fgetc(f_obj))!='\n' && cur!=EOF){
		if(cur>='0' && cur<='9'){
			switch(slash){
				case 0:
					fseek(f_obj,-1,SEEK_CUR);
					polygon.vertex[v]=&vertex[(int)(MDE_ConvertVertex(f_obj))-offset-1];
					fseek(f_obj,-1,SEEK_CUR);
					v++;
				break;
				case 2:
					fseek(f_obj,-1,SEEK_CUR);
					polygon.normal=normal[(int)MDE_ConvertVertex(f_obj)-1];
					fseek(f_obj,-1,SEEK_CUR);
				break;
			}
		}
		else if(cur=='/'){
			cur=fgetc(f_obj);
			for(;cur>='0' && cur<='9';cur=fgetc(f_obj));
			fseek(f_obj,-1,SEEK_CUR);
			slash++;
		}
		else if(cur==' ')
			slash=0;
	}


return polygon;
}

double MDE_ConvertVertex(FILE *f_obj){
	int sign=1;
	bool point=false;
	float ret=0;
	int i=0;

	cur=fgetc(f_obj);
	while(!(cur>='0' && cur<='9') && cur!='-' && cur!='.' && cur!=',')
		cur=fgetc(f_obj);
	fseek(f_obj,-1,SEEK_CUR);

	while((cur=fgetc(f_obj))!=' ' && cur!='\n' && cur!='/'){
		if(cur>='0' && cur<='9'){
			if(!point)
				ret*=10;
			else
				i--;
			ret+=(cur-'0')*pow(10,i);
		}
		else if(cur=='.' || cur==','){
			point=true;
			i=0;
		}
		else if(cur=='-')
			sign*=-1;
	}
return ret*sign;
}
