#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "image.h"
//#include "geom2d.h"

typedef enum { Nord, Est, Sud, Ouest } Orientation;

typedef struct {
  double x, y;
  Orientation o;
} Robot;

Point trouver_pixel_depart(Image I);

/* initialiser le robot r en position du position de depart et orientation EST */
void init_robot(Robot r, Point depart);

Robot initialiser_robot(Image I, Point depart);
/* faire avancer le robot d'une case */
void avancer(Robot *r);

/* faire tourner le robot d'un quart de tour sur la gauche */
void tourner_a_gauche(Robot *r);

/* faire tourner le robot d'un quart de tour sur la droite */
void tourner_a_droite(Robot *r);

/*mémoriser la position du robot */
Point memoriser_position(Robot *r);

#endif

