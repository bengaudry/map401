#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
#include "sequence_point.h"

int main (int argc, char **argv) {
    Image I;

    if (argc < 2) {
        ERREUR_FATALE("Chemin vers le fichier requis");
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    printf("Largeur : %d\n", largeur_image(I));
    printf("Hauteur : %d\n", hauteur_image(I));
    
    Contour c = parcourir_contour(I);
    ecrire_contour(c);

    printf("Nombre de segments : %d\n", taille_liste_points(c)-1);

    return 0;
}
