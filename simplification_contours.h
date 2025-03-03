#ifndef _SIMPLIFICATION_CONTOURS_H_
#define _SIMPLIFICATION_CONTOURS_H_

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
    Point C4;
} Bezier3;

SequenceContours* simplifier_seq_contours_dp (SequenceContours *seq, double d);

#endif
