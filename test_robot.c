#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "robot.h"
#include "image.h"
#include "contour_image.h"

int main(int argc, char **argv) {
  Image I;
  Point depart;
  depart=trouver_pixel_depart(I);
  I=lire_fichier_image(argv[1]);
  Robot R;
  init_robot(&R,depart);
  return 0;
}
