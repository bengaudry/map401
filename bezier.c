#include "bezier.h"
#include "sequence_point.h"
#include "simplification_bezier.h"

/* Point de la courbe en t */
Point eval_bezier2(Bezier2 B, double t) {
    double a1, a2, a3;
    if (t < 0 || t > 1) {
        fprintf(stderr, "eval_bezier2 : t doit être un réel entre 0 et 1\n");
        exit(1);
    }

    a1 = (1.0-t)*(1.0-t);
    a2 = 2.0*t*(1.0-t);
    a3 = t*t;

    return somme_points(
        somme_points(
            mult_point_scalaire(B.C0, a1),
            mult_point_scalaire(B.C1, a2)
        ), mult_point_scalaire(B.C2, a3)
    );
}

/* Point de la courbe en t */
Point eval_bezier3(Bezier3 B, double t) {
    double a1, a2, a3, a4;
    if (t < 0 || t > 1) {
        fprintf(stderr, "eval_bezier3 : t doit être un réel entre 0 et 1\n");
        exit(1);
    }

    a1 = (1.0-t)*(1.0-t)*(1.0-t);
    a2 = 3.0*t*(1.0-t)*(1.0-t);
    a3 = 3.0*t*t*(1.0-t);
    a4 = t*t*t;

    return somme_points(
        somme_points(
            mult_point_scalaire(B.C0, a1),
            mult_point_scalaire(B.C1, a2)
        ),
        somme_points(
            mult_point_scalaire(B.C2, a3),
            mult_point_scalaire(B.C3, a4)
        )
    );
}

/* Élévation de degré d'une courbe de bézier */
Bezier3 bezier2_vers_bezier3 (Bezier2 B2) {
    Bezier3 B3;

    B3.C0 = B2.C0;

    B3.C1 = somme_points(mult_point_scalaire(B2.C0, (double)1/3), mult_point_scalaire(B2.C1, (double)2/3)); // C'1 = 1/3(C0 + 2C1)
    B3.C2 = somme_points(mult_point_scalaire(B2.C1, (double)2/3), mult_point_scalaire(B2.C2, (double)1/3)); // C'2 = 1/3(2C1 + C2)
    
    B3.C3 = B2.C2;

    return B3;
}

/* Convertir une séquence de bézier 2 en une séquence de bézier 3 */
SequenceBezier3 seq_bez2_vers_seq_bez3 (SequenceBezier2 seq2) {
    SequenceBezier3 seq3;
    CelluleSeqBezier2 *cel;

    seq3 = initialiser_sequence_bezier3();
    cel = seq2.first;
    while (cel != NULL) {
        ajouter_cellule_seq_bezier3(&seq3, bezier2_vers_bezier3(cel->value));
        cel = cel->suiv;
    }
    return seq3;
}

void afficher_bezier2(Bezier2 B) {
    printf("> Courbe de bézier de degré 2\n");
    affiche_point("C0", B.C0);
    affiche_point("C1", B.C1);
    affiche_point("C2", B.C2);
    printf("\n");
}

void afficher_bezier3(Bezier3 B) {
    printf("> Courbe de bézier de degré 3\n");
    affiche_point("C0", B.C0);
    affiche_point("C1", B.C1);
    affiche_point("C2", B.C2);
    affiche_point("C3", B.C3);
    printf("\n");
}


////// SEQUENCES DE BEZIER 2 ///////

SequenceBezier2 initialiser_sequence_bezier2() {
	SequenceBezier2 seq;
	seq.taille = 0;
	seq.first = NULL;
	seq.last = NULL;
	return seq;
}

/* Ajoute une cellule à la fin d'une séquence de contours */
void ajouter_cellule_seq_bezier2(SequenceBezier2* seq, Bezier2 B2) {
	CelluleSeqBezier2* cel_seq;

	if (seq == NULL) {
		fprintf(stderr, "Sequence non initialisée, arret.\n");
		exit(1);
	}

	cel_seq = malloc(sizeof(CelluleSeqBezier2));
    if (cel_seq == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire, arret.\n");
        exit(1);
    }

	cel_seq->value = B2;
	cel_seq->suiv = NULL;

	if (seq->first == NULL) {
		seq->first = cel_seq;
		seq->last = cel_seq;
		seq->taille = 1;
		return;
	}

	seq->last->suiv = cel_seq;
	seq->taille = seq->taille + 1;
	seq->last = cel_seq;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
SequenceBezier2 concatener_seq_bezier2(SequenceBezier2 L1, SequenceBezier2 L2)
{
	/* cas ou l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;

	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}


////// SEQUENCES DE BEZIER 3 ///////

SequenceBezier3 initialiser_sequence_bezier3() {
	SequenceBezier3 seq;
	seq.taille = 0;
	seq.first = NULL;
	seq.last = NULL;
	return seq;
}

/* Ajoute une cellule à la fin d'une séquence de contours */
void ajouter_cellule_seq_bezier3(SequenceBezier3* seq, Bezier3 B3) {
	CelluleSeqBezier3* cel_seq;

	if (seq == NULL) {
		fprintf(stderr, "Sequence non initialisée, arret.\n");
		exit(1);
	}

	cel_seq = malloc(sizeof(CelluleSeqBezier3));
	cel_seq->value = B3;
	cel_seq->suiv = NULL;

	if (seq->first == NULL) {
		seq->first = cel_seq;
		seq->last = cel_seq;
		seq->taille = 1;
		return;
	}

	seq->last->suiv = cel_seq;
	seq->taille = seq->taille + 1;
	seq->last = cel_seq;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
SequenceBezier3 concatener_seq_bezier3(SequenceBezier3 L1, SequenceBezier3 L2)
{
	/* cas ou l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;

	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}
