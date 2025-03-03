#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
#include "eps.h"
#include "sequence_point.h"

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
    SequenceContours *seq_contours;
    CelluleSeqContours *cel_seq_contours;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm> <mode: 'fill' | 'stroke' | null>\n", argv[0]);
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    // Création d'une séquence de contours
    seq_contours = initialiser_sequence_contours();
    parcourir_contours(I, seq_contours);
    printf("%d contours detectés\n", seq_contours->taille);

    // Parcours et affichage des contours de l'image
    int total_points = 0;
    cel_seq_contours = seq_contours->first;
    while (cel_seq_contours != NULL) {
        ecrire_contour(cel_seq_contours->value);
        printf("%d segments\n\n", cel_seq_contours->value.taille);
        total_points += cel_seq_contours->value.taille;
        cel_seq_contours = cel_seq_contours->suiv;
    }

    // Affichage des statistiques
    printf("%d contours\n", seq_contours->taille);
    printf("Total points: %d\n", total_points);
    printf("Total segments: %d\n", total_points - seq_contours->taille);

    // Export au format eps
    exporter_image_eps(I, seq_contours, extraire_nom_fichier(argv[1]), argv[2] == NULL ? "fill" : argv[2]);

    return 0;
}
