#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "contour.h"
#include "eps.h"
#include "sequence_point.h"
#include "simplification_contours.h"

char* extraire_nom_fichier(char* chemin_fichier) {
    char *filename = strrchr(chemin_fichier, '/');
    if (filename) filename++;
    else filename = chemin_fichier;

    char *dot = strrchr(filename, '.');
    if (dot) *dot = '\0';

    return filename;
}

int main (int argc, char **argv) {
    Image I;
    SequenceContours *seq_contours, *seq_contours_simple;
    CelluleSeqContours *cel_seq_contours, *cel_seq_contours_simple;
    Tableau_Point ContourTab;
    double d;

    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm> <d: distance-seuil>\n", argv[0]);
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    // Création d'une séquence de contours
    seq_contours = initialiser_sequence_contours();
    seq_contours_simple = initialiser_sequence_contours();
    parcourir_contours(I, seq_contours);
    printf("%d contours detectés\n", seq_contours->taille);

    // Parcours et affichage des contours de l'image
    int total_points = 0;
    int total_points_simplifies = 0;
    char **endptr;

    d = strtod(argv[2], endptr);

    cel_seq_contours = seq_contours->first;
    while (cel_seq_contours != NULL) {
        Contour cs = simplification_douglas_peucker(sequence_points_liste_vers_tableau(cel_seq_contours->value), 0, cel_seq_contours->value.taille-1, d);
        ajouter_cellule_seq_contours(seq_contours_simple, cs);

        total_points += cel_seq_contours->value.taille;
        total_points_simplifies += cs.taille;

        cel_seq_contours = cel_seq_contours->suiv;
    }

    // Affichage des statistiques
    printf("Total points: %d\n", total_points);
    printf("Total segments: %d\n", total_points - seq_contours->taille);

    printf("Total points après simplification: %d\n", total_points_simplifies);


    // Export au format eps
    char *nom_sortie = extraire_nom_fichier(argv[1]);
    exporter_image_eps(I, seq_contours, nom_sortie, "fill");        // export de l'image de base

    strcat(nom_sortie, "_simple");
    exporter_image_eps(I, seq_contours_simple, nom_sortie, "fill"); // export de l'image simplifiée

    return 0;
}
