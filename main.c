#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "contour.h"
#include "eps.h"
#include "sequence_point.h"
#include "simplification_bezier.h"
#include "simplification_contours.h"

int main (int argc, char **argv) {
    Image I;
    SequenceContours *seq_contours, *seq_contours_simple;
    char mode[10] = "fill";

    if (argc != 2) {
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm>\n", argv[0]);
        exit(1);
    }

    I = lire_fichier_image(argv[1]);
    char *nom_sortie = extraire_nom_fichier(argv[1]);

    printf("Image : %s (%dx%d)\n", nom_sortie, largeur_image(I), hauteur_image(I));

    // Création d'une séquence de contours
    seq_contours = initialiser_sequence_contours();
    
    parcourir_contours(I, seq_contours);
    printf("%d contours initiaux\n", seq_contours->taille);

    printf("============ CHOIX DE LA SIMPLIFICATION ============\n");
    printf("(1) Simplification par segments\n");
    printf("(2) Simplification par courbes de Bézier de degré 2\n");
    printf("(3) Simplification par courbes de Bézier de degré 3\n");

    int choix = -1;
    do {
        printf("> ");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 3);

    printf("Choisir une distance seuil :\n");
    double d = -1.0;
    do {
        printf("> ");
        scanf("%lf", &d);
    } while (d < 0);

    switch (choix)
    {
        case 1:
            // Choix du mode de remplissage :
            printf("Choisir un mode de remplissage (stroke | fill) :\n");
            do {
                printf("> ");
                scanf("%9s", mode);  // Limit input to 9 chars to leave room for null terminator
            } while (strcmp(mode, "fill") != 0 && strcmp(mode, "stroke") != 0);

            seq_contours_simple = simplifier_seq_contours_dp(seq_contours, d);
            break;
        case 2:
            //seq_contours_simple = simplification_contours_bezier2(seq_contours, d);
            break;
        case 3:
            //seq_contours_simplifies = simplifier_par_bez_deg3();
            break;
        default:
            fprintf(stderr, "Choix invalide\n");
            exit(1);
    }

    if (seq_contours_simple == NULL) {
        fprintf(stderr, "Erreur lors de la simplification\n");
        exit(1);
    }

    // Export au format eps
    exporter_image_eps(I, seq_contours, nom_sortie, mode);        // export de l'image de base

    strcat(nom_sortie, "_simple");
    exporter_bezier_eps(I, seq_contours_simple, nom_sortie, mode); // export de l'image simplifiée

    return 0;
}