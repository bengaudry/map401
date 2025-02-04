#ifndef _CALCUL_H_
#define _CALCUL_H_

typedef struct {
    double x, y; /* Coordonnées */
} Vecteur;

typedef struct {
    double x, y; /* Coordonnées */
} Point;

////// OPERATIONS SUR LES POINTS \\\\\\

/* Crée le point de coordonées (x, y) */
Point set_point(double x, double y);

/* Somme P1+P2 */
Point somme_points(Point P1, Point P2);

/* Retourne le point produit a*(x, y) = (a*x, a*y) */
Point mult_point_scalaire(Point P, double a);

/* Retourne la distance entre deux points A et B : ||AB->|| = ||BA->|| */
double distance_points(Point A, Point B);

void affiche_point(char *nom, Point P);




////// OPERATIONS SUR LES VECTEURS \\\\\\

/* Vecteur correspondant au bipoint AB-> */
Vecteur vect_bipoint(Point A, Point B);

/* Retourne V = V1 + V2 */
Vecteur somme_vecteurs(Vecteur V1, Vecteur V2);

/* Retourne le vecteur produit a*(x, y) = (a*x, a*y) */
Vecteur mult_vect_scalaire(Vecteur V, double a);

/* Retourne le produit scalaire entre V1 et V2 */
double produit_scalaire(Vecteur V1, Vecteur V2);

/* Retourne la norme du vecteur V */
double norme_vect(Vecteur V);

void affiche_vect(char *nom, Vecteur V);


#endif
