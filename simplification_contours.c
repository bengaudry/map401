#include "simplification_contours.h"
#include "sequence_point.h"
#include "geometrie.h"
#include "image.h"

Contour simplification_douglas_peucker(Tableau_Point tab_contour, int j1, int j2, double d) {
    int j, k;
    double dmax;
    Liste_Point L, L1, L2;
    

    Point Pj1 = tab_contour.tab[j1];
    Point Pj2 = tab_contour.tab[j2];

    dmax = 0;
    k = j1;
    for (j = j1+1; j <= j2; j++) {
        Point Pj = tab_contour.tab[j];
        double dj = distance_point_segment(Pj, Pj1, Pj2);

        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    L = creer_liste_Point_vide();

    if (dmax <= d) {
        L = ajouter_element_liste_Point(L, Pj1);
    } else {
        L1 = creer_liste_Point_vide();
        L2 = creer_liste_Point_vide();

        L1 = simplification_douglas_peucker(tab_contour, j1, k, d);
        L2 = simplification_douglas_peucker(tab_contour, k, j2, d);

        L = concatener_liste_Point(L1, L2);
    }
    return L;
}

SequenceContours* simplifier_seq_contours_dp (SequenceContours *seq, double d) {
    CelluleSeqContours *cel;
    SequenceContours *contours_simplifies;

    contours_simplifies = initialiser_sequence_contours();

    int nb_contours = seq->taille;
    int nb_segments = 0;
    int nb_seg_simplifies = 0;

    cel = seq->first;
    while (cel != NULL) {
        Contour contour_a_simplifier = cel->value;
        nb_segments += contour_a_simplifier.taille-1; // nb points - 1
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(contour_a_simplifier);
        
        Contour simplifie = simplification_douglas_peucker(tab_contour, 0, tab_contour.taille-1, d);
        nb_seg_simplifies+=simplifie.taille;

        ajouter_cellule_seq_contours(contours_simplifies, simplifie);
        cel = cel->suiv;
    }

    printf("%d contours\n", nb_contours);
    printf("%d segments initiaux\n", nb_segments);
    printf("%d segments après simplification (d=%f)\n", nb_seg_simplifies, d);

    return contours_simplifies;
}