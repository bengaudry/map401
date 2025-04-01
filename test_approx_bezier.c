#include <stdio.h>
#include "simplification_bezier.h"
#include "contour.h"

int main() {
    Contour C;
    Bezier2 B2;
    Bezier3 B3;

    printf("===== TEST A =====\n");
    C = creer_liste_Point_vide();
    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(-2, -2));

    B2 = approx_bezier2(C, 0, 1);
    supprimer_liste_Point(C);
    afficher_bezier2(B2);

    
    printf("===== TEST B =====\n");
    printf("===== TEST B - Bezier 2 =====\n");
    C = creer_liste_Point_vide();
    B2.C0 = set_point(0, 2);
    B2.C1 = set_point(0, 9);
    B2.C2 = set_point(2, 5);

    double n = 4.0;
    C = ajouter_element_liste_Point(C, eval_bezier2(B2, (double)0/n));
    C = ajouter_element_liste_Point(C, eval_bezier2(B2, (double)1/n));
    C = ajouter_element_liste_Point(C, eval_bezier2(B2, (double)2/n));
    C = ajouter_element_liste_Point(C, eval_bezier2(B2, (double)3/n));
    C = ajouter_element_liste_Point(C, eval_bezier2(B2, (double)4/n));

    Tableau_Point T = sequence_points_liste_vers_tableau(C);

    printf("Courbe de bézier originale: \n");
    afficher_bezier2(B2);
    printf("Courbe de bézier approximative: \n");
    afficher_bezier2(approx_bezier2(C, 0, 4));

    supprimer_liste_Point(C);

    printf("===== TEST B - Bezier 3 =====\n");
    C = creer_liste_Point_vide();
    B3.C0 = set_point(0, 2);
    B3.C1 = set_point(1, 9);
    B3.C2 = set_point(3, 1);
    B3.C3 = set_point(4, 1);

    n = 4.0;
    C = ajouter_element_liste_Point(C, eval_bezier3(B3, (double)0.0/n));
    C = ajouter_element_liste_Point(C, eval_bezier3(B3, (double)1.0/n));
    C = ajouter_element_liste_Point(C, eval_bezier3(B3, (double)2.0/n));
    C = ajouter_element_liste_Point(C, eval_bezier3(B3, (double)3.0/n));
    C = ajouter_element_liste_Point(C, eval_bezier3(B3, (double)4.0/n));

    printf("Courbe de bézier originale: \n");
    afficher_bezier3(B3);
    printf("Courbe de bézier approximative: \n");
    afficher_bezier3(approx_bezier3(C, 0, 4));

    supprimer_liste_Point(C);

    printf("===== TEST C =====\n");
    C = creer_liste_Point_vide();
    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 1));
    C = ajouter_element_liste_Point(C, set_point(1, 2));
    C = ajouter_element_liste_Point(C, set_point(2, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 3));
    C = ajouter_element_liste_Point(C, set_point(4, 3));
    C = ajouter_element_liste_Point(C, set_point(5, 3));

    B2 = approx_bezier2(C, 0, 8);
    supprimer_liste_Point(C);
    afficher_bezier2(B2);

    return 0;
}
