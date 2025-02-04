#include <stdio.h>
#include "geometrie.h"

int main(void) {
    Point A, B;
    Vecteur U, V;
    double lambda;

    printf("====== TESTS POINTS ======\n");

    A = set_point(4, 2);
    B = set_point(0, -3);
    affiche_point("A", A); affiche_point("B", B);

    printf("\n");
    affiche_point("A+B", somme_points(A, B));
    affiche_point("2*A", mult_point_scalaire(A, 2));
    affiche_point("-A", mult_point_scalaire(A, -1));

    printf("\nd(A, B) = %f\n", distance_points(A, B));
    printf("d(B, A) = %f\n\n", distance_points(B, A));



    printf("====== TESTS VECTEURS ======\n");
    
    U = vect_bipoint(A, B);
    V = vect_bipoint(B, A);

    affiche_vect("AB", U);
    affiche_vect("BA", V);
    printf("\n");

    affiche_vect("AB+BA", somme_vecteurs(U, V));
    affiche_vect("2AB", mult_vect_scalaire(U, 2));
    affiche_vect("-AB", mult_vect_scalaire(U, -1));

    printf("\nProduit scalaire de AB et  BA : %f\n", produit_scalaire(U, V));
    printf("Norme AB : %f, Norme BA : %f\n\n", norme_vect(U), norme_vect(V));

    Point O = {.x= 0, .y= 0};
    Point X = {.x= 1, .y= 0};
    Point Y = {.x= 0, .y= 1};

    U = vect_bipoint(O, X);
    V = vect_bipoint(O, Y);
    affiche_vect("U", U); affiche_vect("V", V);
    printf("\nProduit scalaire de U et  V : %f\n", produit_scalaire(U, V));
    printf("Norme U : %f, Norme V : %f\n\n", norme_vect(U), norme_vect(V));

    return 0;
}
