#include "types_macros.h"

typedef struct Point_
{
	double x, y;
}Point;

typedef struct Vecteur_
{
	double x, y;
}Vecteur;

typedef struct Segment_
{
	Point A;
	Point B;
}Segment;

/* cree le point de coordonnees (x,y) */
Point set_point(double x, double y);

/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B);

/* somme P1+P2 */
Point add_point(Point P1, Point P2);

/* somme U+V */
Vecteur add_vecteur(Vecteur U, Vecteur V);

/* produit x*P */
Point prod_point(double x, Point P);

/* produit x*V */
Vecteur prod_vecteur(double x, Vecteur V);

/* produit scalaire U*V */
double prod_scalaire(Vecteur U, Vecteur V);

/* norme de V */
double norme(Vecteur V);

/* distance entre A et B */
double distance(Point A, Point B);

/* distance entre P et AB */
double distance_point_segment(Point P, Point A, Point B);
