#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "geometrie.h"
#include "sequence_point.h"

typedef enum { Nord, Sud, Est, Ouest } Orientation;

/* Renvoie les coordonnées du premier pixel noir de l'image */
Point trouver_premier_point(Image img);

Contour parcourir_contour(Image I);

#endif
