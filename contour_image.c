#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types_macros.h"
#include"contour_image.h"
#include "robot.h"


Cellule_Liste_Point *creer_element_liste_Point(Point v){
	Cellule_Liste_Point* el;
	el =(Cellule_Liste_Point*)malloc(sizeof(Cellule_Liste_Point));
	if(el==NULL){
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}


Liste_Point creer_liste_Point_vide(){
	Liste_Point L = {0,NULL,NULL};
	return L;
}

Liste_Segment creer_liste_Segment_vide(){
	Liste_Segment L = {0,NULL,NULL};
	return L;
}

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e){
	Cellule_Liste_Point *el;
	el=creer_element_liste_Point(e);
	if(L.taille==0){
		L.first=L.last=el;
	}else{
		L.last->suiv=el;
		L.last=el;
	}
	L.taille++;
	return L;
}

Liste_Point supprimer_liste_Point(Liste_Point L){
	Cellule_Liste_Point *el=L.first;
	while(el){
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el=suiv;
	}
	L.first=L.last=NULL;
	L.taille=0;
	return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2){
	if(L1.taille==0) return L2;
	if(L2.taille==0) return L1;
	L1.last->suiv=L2.first;
	L1.last=L2.last;
	L1.taille += L2.taille;
	return L1;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L){
	Tableau_Point T;
	T.taille=L.taille;
	T.tab=malloc(sizeof(Point)*T.taille);
	
	if(T.tab==NULL){
		fprintf(stderr, "sequence_points_liste_vers_tableau");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	int k=0;
	Cellule_Liste_Point *el=L.first;
	while(el){
		T.tab[k]=el->data;
		k++;
		el=el->suiv;
	}
	return T;
}

void ecrire_contour(Liste_Point L){
	Tableau_Point TP= sequence_points_liste_vers_tableau(L);
	int k;
	int nP=TP.taille;
	printf("%d points, ", nP);
	printf("%d segments : [", nP-1);
	for(k=0;k<nP;k++){
		Point P=TP.tab[k];
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	}
	printf("]\n");
	free(TP.tab);
}

void ecrire_contour_dans_fichier(Liste_Point L, char *fichier, int numero_contour){
	FILE *f;
	f=fopen(fichier, "a");
	Tableau_Point TP= sequence_points_liste_vers_tableau(L);
	int k;
	int nP=TP.taille;
	fprintf(f,"%d\n\n", numero_contour);
	fprintf(f,"%d\n", nP);
	for(k=0;k<nP;k++){
		Point P=TP.tab[k];
		fprintf(f,"%5.1f %5.1f\n", P.x, P.y);
	}
	fprintf(f,"\n");
	free(TP.tab);
}


Point trouver_pixel_depart(Image I){
	Point depart=set_point(0.0, 0.0);
	int y=1;
	while(y<=hauteur_image(I)){
		int x=1;
		while(x<=largeur_image(I)){
			if((get_pixel_image(I,x,y)==NOIR)&&(get_pixel_image(I,x,y-1)==BLANC)){
				depart=set_point((double)x-1, (double)y-1);
				return depart;
			}
		x=x+1;
		}
	y=y+1;
	}
	return depart;
}

Pixel valeur_pixel_gauche(Image I, Robot r){
  Orientation o = r.o;
  Pixel pG;
  int x,y;
  x=r.x;
  y=r.y;
	switch(o){
		case Nord:
			pG=get_pixel_image(I,x,y);
			break;
		case Sud:
			pG=get_pixel_image(I,x+1,y+1);
			break;
		case Est:
			pG=get_pixel_image(I,x+1,y);
			break;
		case Ouest:
			pG=get_pixel_image(I,x,y+1);
			break;
		default : break;
	}
  return pG;
}
Pixel valeur_pixel_droit(Image I, Robot r){
  Orientation o = r.o;
  Pixel pD;
  int x,y;
  x=r.x;
  y=r.y;
	switch(o){
		case Nord:
			pD=get_pixel_image(I,x+1,y);
			break;
		case Sud:
			pD=get_pixel_image(I,x,y+1);
			break;
		case Est:
			pD=get_pixel_image(I,x+1,y+1);
			break;
		case Ouest:
			pD=get_pixel_image(I,x,y);
			break;
		default : break;
	}
  return pD;
}  

void nouvelle_orientation(Image I, Robot *r){
  Pixel pG, pD;
  pG=valeur_pixel_gauche(I,*r);
  pD=valeur_pixel_droit(I,*r);
  if(pG==NOIR) tourner_a_gauche(r);
  else if(pD==BLANC) tourner_a_droite(r);
}

Cellule_Liste_Segment *init_elem_segment(Segment S){
	Cellule_Liste_Segment *Sc=*(Cellule_Liste_Segment*)malloc(sizeof(Cellule_Liste_Segment));
	return S;
}

void ajouter_element_liste_segment(Segment S, Liste_Segment *L ){
    Cellule_Liste_Segment *el = init_elem_segment(S);
    if(L->taille == 0) L->first = L->last = el;
    else{
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

Liste_Point algo_Douglas_Peucker(Contour C, int j1, int j2, double d){
	Tableau_Point P=sequence_points_liste_vers_tableau(C);
	Liste_Segment L=creer_liste_Segment_vide();
	double dmax=0.0, dj;
	int j, k=j1;
	for(j=j1+1;j<j2;j++){
		dj=distance_point_segment(P.tab[j], P.tab[j1], P.tab[j2]);
		if(dmax<dj){
			dmax=dj;
			k=j;
			}
	}
	if(dmax<=d){
		Cellule_Liste_Segment *S = malloc(sizeof(Segment));
		S->Segment.A.x=P.tab[j1].x;
		S->Segment.A.y=P.tab[j1].y;
		S->Segment.B.x=P.tab[j2].x;
		S->Segment.B.y=P.tab[j2].y;
		S->suiv=NULL;
		
		ajouter_element_liste_segment(S->Segment, &L);
		return L;
		
	}else{
		Liste_Point L1, L2;
		L1=algo_Douglas_Peucker(C, j1, k,d);
		L2=algo_Douglas_Peucker(C, k, j2,d);
		L=concatener_liste_Point(L1,L2);
		return L;
	}
	
}











