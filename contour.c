#include <stdlib.h>
#include <stdio.h>
#include "sequence_point.h"
#include "geometrie.h"
#include "image.h"
#include "contour.h"


/* Renvoie les coordonnées du point correspondant au premier pixel noir de l'image */
Point trouver_premier_point(Image I) {
    int x, y;
    int H, L;
    Pixel pixel_courant, pixel_nord;

    H = hauteur_image(I);
    L = largeur_image(I);

    for (y = 1; y <= H; y++) {
        for (x = 1; x <= L; x++) {
            pixel_courant = get_pixel_image(I, x, y);
            pixel_nord = get_pixel_image(I, x, y-1);

            if (pixel_courant == NOIR && pixel_nord == BLANC) {
                return set_point(x-1, y-1);
            }
        }
    }

    return set_point(-1, -1); // Ne devrait pas arriver
}

Orientation tourner_a_gauche(Orientation O) {
    switch (O) {
        case Ouest: return Sud;
        case Sud: return Est;
        case Est: return Nord;
        case Nord: return Ouest;
    }
}

Orientation tourner_a_droite(Orientation O) {
    switch (O) {
        case Nord: return Est;
        case Est: return Sud;
        case Sud: return Ouest;
        case Ouest: return Nord;
    }
}

Point calculer_nouvelle_position_robot(Point P, Orientation or_robot) {
    switch (or_robot) {
        case Est: return set_point(P.x+1, P.y);
        case Sud: return set_point(P.x, P.y+1);
        case Ouest: return set_point(P.x-1, P.y);
        case Nord: return set_point(P.x, P.y-1);
    }
}

Pixel pixel_gauche(Image I, Point P, Orientation O) {
    switch (O) {
        case Nord: return get_pixel_image(I, P.x, P.y);
        case Est: return get_pixel_image(I, P.x+1, P.y);
        case Sud: return get_pixel_image(I, P.x+1, P.y+1);
        case Ouest: return get_pixel_image(I, P.x, P.y+1);
    }
}

Pixel pixel_droit(Image I, Point P, Orientation O) {
    switch (O) {
        case Nord: return get_pixel_image(I, P.x+1, P.y);
        case Est: return get_pixel_image(I, P.x+1, P.y+1);
        case Sud: return get_pixel_image(I, P.x, P.y+1);
        case Ouest: return get_pixel_image(I, P.x, P.y);
    }
}

Contour parcourir_contour(Image I) {
    Orientation or_robot;
    Point pos_robot, pos_initial_robot;
    Contour contour;

    contour = creer_liste_Point_vide();

    or_robot = Est;
    pos_initial_robot = trouver_premier_point(I);

    if (pos_initial_robot.x == -1 && pos_initial_robot.y == -1) {
        fprintf(stderr, "Pas de contour a détecter\n");
        exit(1);
    };

    pos_robot = pos_initial_robot;
    do {
        contour = ajouter_element_liste_Point(contour, pos_robot);
        pos_robot = calculer_nouvelle_position_robot(pos_robot, or_robot); // On avance le robot de 1
    
        if (pixel_gauche(I, pos_robot, or_robot) == NOIR) or_robot = tourner_a_gauche(or_robot);
        else if (pixel_droit(I, pos_robot, or_robot) == BLANC) or_robot = tourner_a_droite(or_robot);
    } while (!points_egaux(pos_robot, pos_initial_robot) || or_robot != Est);
    
    contour = ajouter_element_liste_Point(contour, pos_robot);
    return contour;
}
