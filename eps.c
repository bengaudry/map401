#include <stdio.h>
#include <string.h>
#include "image.h"
#include "sequence_point.h"

/* Exporte une sequence de contours au format eps */
void exporter_image_eps(Image I, SequenceContours *seq_contours, char* nom, char* mode) {
    FILE *dest;
    Cellule_Liste_Point *cel;
    CelluleSeqContours *cel_seq_contours;
    Contour C;
    int L, H;
    char *dest_name = nom;

    strcat(dest_name, ".eps");
    dest = fopen(dest_name, "w");
    if (dest == NULL) {
        fprintf(stderr, "Impossible de créer le fichier %s\n", nom);
        return;
    }

    /* Ecriture de l'en-tete du fichier */
    L = largeur_image(I);
    H = hauteur_image(I);

    fprintf(dest, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(dest, "%%%%BoundingBox: %d %d %d %d\n\n", -1, 0, L, H+1);

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

    fprintf(dest, "\n0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(dest, "%s\n", mode);
    fprintf(dest, "showpage\n");

    fclose(dest);
}
