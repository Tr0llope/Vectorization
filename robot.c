#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h> 
#include "robot.h"

Robot initialiser_robot(Image I, Point depart){
	Robot R;
	R.o= Est;
	R.x=depart.x;
	R.y=depart.y;
	return R;
}

void avancer(Robot *r){
	Orientation o = r->o;
	switch(o){
		case Nord:
			r->y=r->y-1;
			break;
		case Sud:
			r->y=r->y+1;
			break;
		case Est:
			r->x=r->x+1;
			break;
		case Ouest:
			r->x=r->x-1;
			break;
		default : break;
	}
}

void tourner_a_droite(Robot *r){
	Orientation o = r->o;
	switch(o){
		case Nord:
			o = Est;
			break;
		case Sud:
			o = Ouest;
			break;
		case Est:
			o = Sud;
			break;
		case Ouest:
			o = Nord;
			break;
		default : break;
	}
	r->o = o;
}
void tourner_a_gauche(Robot *r){
	Orientation o = r->o;
	switch(o){
		case Nord:
			o = Ouest;
			break;
		case Sud:
			o = Est;
			break;
		case Est:
			o = Nord;
			break;
		case Ouest:
			o = Sud;
			break;
		default : break;
	}
	r->o = o;
}
Point memoriser_position(Robot *r){
	return set_point(r->x,r->y);
  
}

  
