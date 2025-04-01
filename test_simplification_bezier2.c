#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "contour.h"
#include "eps.h"
#include "sequence_point.h"
#include "simplification_bezier.h"

int main (int argc, char **argv) {
    Image I;
    SequenceContours *seq_contours, *seq_contours_simplifies;
    CelluleSeqContours *cel_seq_contours, *cel_seq_contours_simplifies;
    Tableau_Point ContourTab;
    double d;

    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm> <d: distance-seuil>\n", argv[0]);
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    // Création d'une séquence de contours
    seq_contours = initialiser_sequence_contours();
    
    parcourir_contours(I, seq_contours);
    printf("%d contours detectés\n", seq_contours->taille);

    // Parcours et affichage des contours de l'image
    char **endptr;
    d = strtod(argv[2], endptr);
    printf("d=%f\n", d);

    // Simplification : 
    seq_contours_simplifies = simplification_contours_bezier2(seq_contours, d);

    // Export au format eps
    char *nom_sortie = extraire_nom_fichier(argv[1]);
    exporter_image_eps(I, seq_contours, nom_sortie, "fill");        // export de l'image de base

    strcat(nom_sortie, "_simple");
    exporter_bezier_eps(I, seq_contours_simplifies, nom_sortie, "fill"); // export de l'image simplifiée

    return 0;
}