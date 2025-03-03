#include "simplification_contours.h"
#include "sequence_point.h"
#include "geometrie.h"
#include "image.h"

/* Algorithme de doulas peucker pour la simplification de contours
 * d réel >= 0 la distance seuil
 */
Contour simplification_douglas_peucker(Tableau_Point ContourTab, int j1, int j2, double d) {
    int k, dmax;
    Contour L, L1, L2;

    L = creer_liste_Point_vide();

    dmax = 0;
    k = j1;
    for (int j = j1+1; j <= j2; j++) {
        double dj = distance_point_segment(ContourTab.tab[j], ContourTab.tab[j1], ContourTab.tab[j2]);
        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
        L = ajouter_element_liste_Point(L, ContourTab.tab[j1]);
        L = ajouter_element_liste_Point(L, ContourTab.tab[j2]);
    } else {
        L1 = simplification_douglas_peucker(ContourTab, j1, k, d);
        L2 = simplification_douglas_peucker(ContourTab, k, j2, d);

        L = concatener_liste_Point(L1, L2);
    }

    return L;
} 
