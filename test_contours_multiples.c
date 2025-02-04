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

    printf("Largeur : %d\n", largeur_image(I));
    printf("Hauteur : %d\n", hauteur_image(I));

    seq_contours = initialiser_sequence_contours();
    parcourir_contours(I, seq_contours);
    printf("%d contours detectés\n", seq_contours->taille);

    cel_seq_contours = seq_contours->first;
    // while (cel_seq_contours != NULL) {
    //     ecrire_contour(cel_seq_contours->value);
    //     cel_seq_contours = cel_seq_contours->suiv;

    // }
    exporter_image_eps(I, seq_contours, extraire_nom_fichier(argv[1]), argv[2] == NULL ? "fill" : argv[2]);

    return 0;
}
