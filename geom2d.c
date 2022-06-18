#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types_macros.h"
#include "geom2d.h"

/* cree le point de coordonnees (x,y) */
Point set_point(double x, double y){
	Point P= {x, y};
	return P;
}

/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B){
	Vecteur V={B.x-A.x, B.y-A.y};
	return V;
}


/* somme P1+P2 */
Point add_point(Point P1, Point P2){
	return set_point(P1.x+P2.x, P1.y+P2.y);
}

/* somme U+V */
Vecteur add_vecteur(Vecteur U, Vecteur V){
	Vecteur W={U.x+V.x, U.y+V.y};
	return W;
}
/* produit x*P */
Point prod_point(double x, Point P){
	return set_point(x*P.x, x*P.y);
}

/* produit x*V */
Vecteur prod_vecteur(double x, Vecteur V){
	Vecteur W={x*V.x, x*V.y};
	return W;
}

/* produit scalaire U*V */
double prod_scalaire(Vecteur U, Vecteur V){
	return U.x*V.x+U.y*V.y;
}

/* norme de V */
double norme(Vecteur V){
	return sqrt(V.x*V.x+V.y*V.y);
}
/* distance entre A et B */
double distance(Point A, Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

double distance_point_segment(Point P, Point A, Point B){
	Vecteur AB=vect_bipoint(A, B);
	Vecteur AP=vect_bipoint(A, P);
	Vecteur BP=vect_bipoint(B, P);
	if((A.x==B.x)&&(A.y==B.y)) return norme(AP);
	else{
		/* calcul de lambda */
		double lambda;
		lambda=prod_scalaire(AP, AB)/prod_scalaire(AB, AB);
		if(lambda<0) return norme(AP);
		else if(lambda>1) return norme(BP);
		else{
			Point Q= add_point(A, prod_point(lambda, add_point(B, prod_point(-1.0, A))));
			Vecteur QP=vect_bipoint(Q, P);
			return norme(QP);
		}
	}
}




