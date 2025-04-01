#include <stdio.h>
#include <string.h>
#include "image.h"
#include "sequence_point.h"
#include "simplification_bezier.h"

char* extraire_nom_fichier(char* chemin_fichier) {
    char *filename = strrchr(chemin_fichier, '/');
    if (filename) filename++;
    else filename = chemin_fichier;

    char *dot = strrchr(filename, '.');
    if (dot) *dot = '\0';

    return filename;
}

/* Ecriture de l'en-tete du fichier */
void exporter_entete_eps(FILE* dest, UINT L, UINT H) {
    fprintf(dest, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(dest, "%%%%BoundingBox: %d %d %d %d\n\n", -1, 0, L, H+1);
}

void exporter_fin_fichier_eps(FILE* dest, char* mode) {
    fprintf(dest, "\n0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(dest, "%s\n", mode);
    fprintf(dest, "showpage\n");

    fclose(dest);
}

FILE* ouvrir_fichier_dest(char *nom) {
    FILE* dest;
    char *dest_name = malloc(strlen(nom) + 5);

    strcpy(dest_name, nom);
    strcat(dest_name, ".eps");
    dest = fopen(dest_name, "w");
    free(dest_name);
    if (dest == NULL) {
        fprintf(stderr, "Impossible de créer le fichier %s\n", nom);
        exit(1);
    }

    return dest;
}

/* Exporte une sequence de contours au format eps */
void exporter_image_eps(Image I, SequenceContours *seq_contours, char* nom, char* mode) {
    FILE *dest;
    Cellule_Liste_Point *cel;
    CelluleSeqContours *cel_seq_contours;
    Contour C;

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    
    dest = ouvrir_fichier_dest(nom);
    exporter_entete_eps(dest, L, H);

    /* On parcourt chaque contour de la séquence */
    cel_seq_contours = seq_contours->first;
    while (cel_seq_contours != NULL) {
        C = cel_seq_contours->value;
        /* On se place sur le point à l'origine */
        if (C.first != NULL) fprintf(dest, "%f %f moveto\n", C.first->data.x, H-C.first->data.y);
        cel = C.first;

        /* On trace une ligne pour chaque point du contour */
        while (cel != NULL) {
            if (cel->suiv != NULL) {
                fprintf(dest, "%f %f lineto", cel->suiv->data.x, H-cel->suiv->data.y);
            }
            fprintf(dest, "\n");
            cel = cel->suiv;
        }
        cel_seq_contours = cel_seq_contours->suiv;
    }

    exporter_fin_fichier_eps(dest, mode);
}

void exporter_bezier_eps(Image I, SequenceContours* seq_contours, char* nom, char* mode) {
    FILE *dest;
    Cellule_Liste_Point *cel;
    CelluleSeqContours *cel_seq_contours;
    Contour C;

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    
    dest = ouvrir_fichier_dest(nom);
    exporter_entete_eps(dest, L, H);

    /* On parcourt chaque contour de la séquence */
    cel_seq_contours = seq_contours->first;
    while (cel_seq_contours != NULL) {
        C = cel_seq_contours->value;

        /* On se place sur le point à l'origine */
        if (C.first != NULL) {
            fprintf(dest, "%f %f moveto\n", C.first->data.x, H-C.first->data.y);
            cel = C.first->suiv;
        }


        /* On trace une courbe pour chaque point du contour */
        while (cel != NULL && cel->suiv != NULL && cel->suiv->suiv != NULL) {
            fprintf(dest, "%f %f %f %f %f %f curveto", 
                cel->data.x, H-cel->data.y,
                cel->suiv->data.x, H-cel->suiv->data.y,
                cel->suiv->suiv->data.x, H-cel->suiv->suiv->data.y
            );
            fprintf(dest, "\n");
            cel = cel->suiv->suiv->suiv;
        }
        cel_seq_contours = cel_seq_contours->suiv;
    }

    exporter_fin_fichier_eps(dest, mode);
}
