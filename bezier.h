#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "sequence_point.h"

typedef struct {
    Point C0;
    Point C1;
    Point C2;
} Bezier2;

typedef struct {
    Point C0;
    Point C1;
    Point C2;
    Point C3;
} Bezier3;

/* Point de la courbe en t */
Point eval_bezier2(Bezier2 B, double t);

/* Point de la courbe en t */
Point eval_bezier3(Bezier3 B, double t);

/* Élévation de degré d'une courbe de bézier */
Bezier3 bezier2_vers_bezier3 (Bezier2 B2);

void afficher_bezier3(Bezier3 B);
void afficher_bezier2(Bezier2 B);

////// SEQUENCES DE BEZIER 2 ///////
typedef struct cellule_seq_bezier2_ {
   Bezier2 value;
   struct cellule_seq_bezier2_* suiv;
} CelluleSeqBezier2;

typedef struct {
   int taille;
   CelluleSeqBezier2* first;
   CelluleSeqBezier2* last;
} SequenceBezier2;

SequenceBezier2 initialiser_sequence_bezier2();
/* Ajoute une cellule à la fin d'une séquence de contours */
void ajouter_cellule_seq_bezier2(SequenceBezier2 *seq, Bezier2 B2);
SequenceBezier2 concatener_seq_bezier2(SequenceBezier2 L1, SequenceBezier2 L2);

////// SEQUENCES DE BEZIER 3 ///////
typedef struct cellule_seq_bezier3_ {
   Bezier3 value;
   struct cellule_seq_bezier3_* suiv;
} CelluleSeqBezier3;

typedef struct {
   int taille;
   CelluleSeqBezier3* first;
   CelluleSeqBezier3* last;
} SequenceBezier3;

SequenceBezier3 initialiser_sequence_bezier3();
/* Ajoute une cellule à la fin d'une séquence de contours */
void ajouter_cellule_seq_bezier3(SequenceBezier3 *seq, Bezier3 B3);
SequenceBezier3 concatener_seq_bezier3(SequenceBezier3 L1, SequenceBezier3 L3);

#endif
