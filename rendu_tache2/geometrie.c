#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometrie.h"

////// OPERATIONS SUR LES POINTS \\\\\\

/* Crée le point de coordonées (x, y) */
Point set_point(double x, double y) {
    Point P;

    P.x = x;
    P.y = y;

    return P;
}

/* Somme P1+P2 */
Point somme_points(Point P1, Point P2) {
    return set_point(P1.x+P2.x, P1.y+P2.y);
}

/* Retourne le point produit a*(x, y) = (a*x, a*y) */
Point mult_point_scalaire(Point P, double a) {
    return set_point(P.x*a, P.y*a);
}

/* Retourne la distance entre deux points A et B : ||AB->|| = ||BA->|| */
double distance_points(Point A, Point B) {
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

void affiche_point(char *nom, Point P) {
    printf("%s = (%f, %f)\n", nom, P.x, P.y);
}




////// OPERATIONS SUR LES VECTEURS \\\\\\

/* Vecteur correspondant au bipoint AB-> */
Vecteur vect_bipoint(Point A, Point B) {
    Vecteur V;

    V.x = B.x - A.x;
    V.y = B.y - A.y;

    return V;
}

/* Retourne V = V1 + V2 */
Vecteur somme_vecteurs(Vecteur V1, Vecteur V2) {
    Vecteur V;

    V.x = V1.x + V2.x;
    V.y = V1.y + V2.y;

    return V;
}

/* Retourne le vecteur produit a*(x, y) = (a*x, a*y) */
Vecteur mult_vect_scalaire(Vecteur V, double a) {
    Vecteur Vmult;

    Vmult.x = a*V.x;
    Vmult.y = a*V.y;

    return Vmult;
}

/* Retourne le produit scalaire entre V1 et V2 */
double produit_scalaire(Vecteur V1, Vecteur V2) {
    return V1.x*V2.x + V1.y*V2.y;
}

/* Retourne la norme du vecteur V */
double norme_vect(Vecteur V) {
    return sqrt(V.x*V.x + V.y*V.y);
}

void affiche_vect(char *nom, Vecteur V) {
    printf("%s-> = (%f, %f)\n", nom, V.x, V.y);
}
