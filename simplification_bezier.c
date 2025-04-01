#include "bezier.h"
#include "sequence_point.h"
#include "simplification_bezier.h"

Bezier2 approx_bezier2 (Contour CONT, int j1, int j2) {
    Bezier2 B;
    Point Pj1, Pj2;
    double n = (double)(j2-j1);

    Tableau_Point TabContour = sequence_points_liste_vers_tableau(CONT);
    Pj1 = TabContour.tab[j1];
    Pj2 = TabContour.tab[j2];

    if (n == 1) {
        B.C1 = mult_point_scalaire(somme_points(Pj1, Pj2), 0.5);
    } else {
        double alpha, beta;
        alpha = 3*n/(n*n-1);
        beta = (1-2*n)/(2*n+2);
    
        Point sum = set_point(0, 0);
        for (int i = 1; i <= n-1; i++) {
            sum = somme_points(sum, TabContour.tab[i+j1]);
        }

        Point alp = mult_point_scalaire(sum, alpha);
        Point bep = mult_point_scalaire(somme_points(Pj1, Pj2), beta);
        B.C1 = somme_points(alp, bep);
    }

    B.C0 = Pj1;
    B.C2 = Pj2;
    return B;
}

double calculer_gamma(double k, double n) {
    return 6*k*k*k*k - 8*n*k*k*k + 6*k*k - 4*n*k + n*n*n*n - n*n;
}

Bezier3 approx_bezier3 (Contour CONT, int j1, int j2) {
    Bezier3 B;
    Point Pj1, Pj2;
    double alpha, beta, lambda, denom;
    double n = (double)(j2-j1);

    if (n < 3) {
        Bezier2 B2 = approx_bezier2(CONT, j1, j2);
        B = bezier2_vers_bezier3(B2);
        return B;
    }

    // n >= 3
    Tableau_Point TabContour = sequence_points_liste_vers_tableau(CONT);
    Pj1 = TabContour.tab[j1];
    Pj2 = TabContour.tab[j2];


    denom = (3*n+6)*(3*n*n+1);
    alpha = (-15*n*n*n+5*n*n+2*n+4)/denom;
    beta = (10*n*n*n-15*n*n+n+2)/denom;
    lambda = (70*n)/(3*(n*n-1)*(n*n-4)*(3*n*n+1));
    
    Point sum_c1 = set_point(0, 0);
    Point sum_c2 = set_point(0, 0);
    for (int i = 1; i <= n-1; i++) {
        sum_c1 = somme_points(sum_c1, mult_point_scalaire(TabContour.tab[i+j1], calculer_gamma((double)i, n)));
        sum_c2 = somme_points(sum_c1, mult_point_scalaire(TabContour.tab[i+j1], calculer_gamma(n-(double)i, n)));
    }

    B.C0 = Pj1;
    B.C1 = somme_points(
        mult_point_scalaire(Pj1, alpha),
        somme_points(
            mult_point_scalaire(sum_c1, lambda),
            mult_point_scalaire(Pj2, beta)
        )
    );
    B.C2 = somme_points(
        mult_point_scalaire(Pj1, beta),
        somme_points(
            mult_point_scalaire(sum_c2, lambda),
            mult_point_scalaire(Pj2, alpha)
        )
    );
    B.C3 = Pj2;

    return B;
}

SequenceBezier2 simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d) {
    int j, k;
    double n, dmax;
    double ti, dj;
    SequenceBezier2 L, L1, L2;
    Bezier2 B2;
    Tableau_Point tab_contour;

    n = (double)(j2-j1);    
    B2 = approx_bezier2(C, j1, j2);

    tab_contour = sequence_points_liste_vers_tableau(C);
    dmax = 0;
    k = j1;
    B2 = approx_bezier2(C, j1, j2);
    for (j = j1+1; j < j2; j++) {
        ti = (double)(j-j1) / n;
        dj = distance_points(tab_contour.tab[j], eval_bezier2(B2, ti));

        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    L = initialiser_sequence_bezier2();

    if (dmax <= d) {
        ajouter_cellule_seq_bezier2(&L, B2);
    } else {
        L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
        L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);

        L = concatener_seq_bezier2(L1, L2);
    }
    return L;
}

SequenceContours* simplification_contours_bezier2(SequenceContours *seq_contours, double d) {
    SequenceContours *seq_contours_simplifies;
    CelluleSeqContours *cel_seq_contours;
    Contour cont, cont_simpl;
    Bezier2 B2;
    Bezier3 B3;

    SequenceBezier2 seqb2;
    CelluleSeqBezier2 *cel_seq_b2;

    seq_contours_simplifies = initialiser_sequence_contours();

    cel_seq_contours = seq_contours->first;
    while (cel_seq_contours != NULL) {
        // simplification par courbes de degré 2
        cont = cel_seq_contours->value;
        seqb2 = simplification_douglas_peucker_bezier2(cont, 0, cont.taille, d);

        // convertir la séquence de courbes en contour
        cont_simpl = creer_liste_Point_vide();

        cel_seq_b2 = seqb2.first;

        while (cel_seq_b2 != NULL && cel_seq_b2->suiv != NULL) {
            B2 = cel_seq_b2->value;
            B3 = bezier2_vers_bezier3(B2);

            // Ajouter le premier point de la premiere courbe (pour le moveto)
            if (cel_seq_b2 == seqb2.first) {
                cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C0);
            }

            cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C1);
            cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C2);
            cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C3);
            cel_seq_b2 = cel_seq_b2->suiv;
        }

        if (cel_seq_b2 != NULL) {
            B2 = cel_seq_b2->value;
            B3 = bezier2_vers_bezier3(B2);

            cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C1);
            cont_simpl = ajouter_element_liste_Point(cont_simpl, B3.C2);
        }

        // ajouter le contour à la liste de contours
        ajouter_cellule_seq_contours(seq_contours_simplifies, cont_simpl);

        cel_seq_contours = cel_seq_contours->suiv;
    }

    return seq_contours_simplifies;
}
