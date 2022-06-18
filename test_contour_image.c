#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contour_image.h"
#include "robot.h"

int main(int argc, char **argv) {
        Image I, M;
        Robot r;
	FILE *f;
        // test commande valide
        if (argc < 4) {
                printf("Usage : %s <fichier entree Image> <fichier sortie contour.txt> <fichier sortie contour.eps>\n", argv[0]);
                return 1;
        }
	f=fopen(argv[3], "w");
        I=lire_fichier_image(argv[1]);
        ecrire_image(I);

        /* etape 1 */
        M=creer_image(largeur_image(I), hauteur_image(I));
        int x, y;
        for(y=1;y<=hauteur_image(I);y++){
                for(x=1;x<=largeur_image(I);x++){
                        if((get_pixel_image(I,x,y)==NOIR)&&(get_pixel_image(I,x,y-1)==BLANC)){
                                set_pixel_image(M, x, y, NOIR);
                        }
                }
        }

        /* etape 2 */
        Point noir;
        noir=trouver_pixel_noir(M);
        Point depart, position;
	
	/* ecriture du fichier eps */
	fprintf(f, "%!PS-Adobe-3.0 EPSF-3.0\n");
        fprintf(f, "%%%BoundingBox: 0 0 %u %u\n\n", largeur_image(I), hauteur_image(I));
	
	/* ecriture du fichier txt et initialisation des variables, structures */
        Contour C, C_simple;
	Tableau_Point C_tableau;
        int taille_tab, numero_contour=1, nb_point=0, nb_seg=0, j1=0, j2;

        // Tant qu'on trouve un pixel noir dans M
        while(noir.x>=0){

        // on initialise le robot au point noir trouve
        depart=set_point(noir.x-1, noir.y-1);
	fprintf(f, "%.0f %.0f moveto ", depart.x, hauteur_image(I)-depart.y);
        r=initialiser_robot(I, depart);
        position=memoriser_position(&r);
        // On initialise un contour
        C=creer_liste_Point_vide();

        // on calcule le contour
        bool boucle=true;
        while(boucle){
                // actualisation de l'image masque
                if(r.o==Est){
                        set_pixel_image(M, r.x+1, r.y+1, BLANC);
                }
                position=memoriser_position(&r);
                C=ajouter_element_liste_Point(C, position);
                avancer(&r);
                nb_point++;
                nb_seg++;
                nouvelle_orientation(I,&r);
		fprintf(f, "%.0f %.0f lineto ", position.x, hauteur_image(I)-position.y);

                if ((r.x==depart.x)&&(r.y==depart.y)&&(r.o==Est)){ boucle=false;
}


        }
        position=memoriser_position(&r);
        C=ajouter_element_liste_Point(C, position);
        //ecrire_contour_dans_fichier(C, argv[2], numero_contour);
        numero_contour++;
        nb_point++;
	
	// Simplification du contour 
	C_tableau=sequence_points_liste_vers_tableau(C);
	taille_tab=C_tableau.taille;
	j2=taille_tab;
	C_simple=algo_Douglas_Peucker(C,j1, j2, 2.0);
	ecrire_contour_dans_fichier(C_simple, argv[2], numero_contour);

        noir=trouver_pixel_noir(M);
        }

	
        printf("nb de contours: %d\n", numero_contour-1);
        printf("nb de points: %d\n", nb_point);
        printf("nb de segments: %d\n", nb_seg);
	
	/* ecriture du fichier eps */
	fprintf(f, "\nfill\n\n");
        fprintf(f, "showpage");
        fclose(f);
        return 0;
}
















