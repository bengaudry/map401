#include "simplification_bezier.h"

int main(int argc, char** argv) {
    Point E1, E2, E0;
    Bezier2 B2;
    Bezier3 B3;
    // TESTS SUR LES COURBES DE BEZIER DE DEG 2
    // Réponses ici : 
    // https://cours.univ-grenoble-alpes.fr/pluginfile.php/1028987/mod_folder/content/0/Partiel_mars_2024_avec_corrige.pdf?forcedownload=1

    printf("====== TEST 1 ======\n");

    B2.C0 = set_point(0, 0);
    B2.C1 = set_point(3, 0);
    B2.C2 = set_point(6, 3);

    afficher_bezier2(B2);
    B3 = bezier2_vers_bezier3(B2);
    afficher_bezier3(B3);

    printf("\n====== TEST 2 ======\n");

    B2.C0 = set_point(6, 3);
    B2.C1 = set_point(9, 6);
    B2.C2 = set_point(6, 6);

    afficher_bezier2(B2);
    B3 = bezier2_vers_bezier3(B2);
    afficher_bezier3(B3);

    printf("\n====== TEST 3 ======\n");

    B2.C0 = set_point(6, 6);
    B2.C1 = set_point(0, 6);
    B2.C2 = set_point(0, 3);

    afficher_bezier2(B2);
    B3 = bezier2_vers_bezier3(B2);
    afficher_bezier3(B3);

    printf("\n====== TEST 4 ======\n");
    afficher_bezier2(B2);

    E0 = eval_bezier2(B2, 0);
    E1 = eval_bezier2(B2, 0.5);
    E2 = eval_bezier2(B2, 1);

    affiche_point("C(0)  ", E0);
    affiche_point("C(1/2)", E1);
    affiche_point("C(1)  ", E2);

    printf("\nPoint C(0) = C0: %s\n", points_egaux(E0, B2.C0) ? "Correct" : "Incorrect");
    printf("Point C(1/2)   : %s\n", points_egaux(E1, set_point(1.5, 5.25)) ? "Correct" : "Incorrect");
    printf("Point C(1) = C2: %s\n", points_egaux(E2, B2.C2) ? "Correct" : "Incorrect");

    printf("\n====== TEST 5 ======\n");
    afficher_bezier3(B3);

    E0 = eval_bezier3(B3, 0);
    E1 = eval_bezier3(B3, 0.5);
    E2 = eval_bezier3(B3, 1);

    affiche_point("C(0)  ", E0);
    affiche_point("C(1/2)", E1);
    affiche_point("C(1)  ", E2);

    printf("\nPoint C(0) = C0: %s\n", points_egaux(E0, B3.C0) ? "Correct" : "Incorrect");
    printf("Point C(1/2)   : %s\n", points_egaux(E1, set_point(1.5, 5.25)) ? "Correct" : "Incorrect");
    printf("Point C(1) = C3: %s\n", points_egaux(E2, B3.C3) ? "Correct" : "Incorrect");

    return 0;
}