#ifndef _SIMPLIFICATION_BEZIER_H_
#define _SIMPLIFICATION_BEZIER_H_

#include "sequence_point.h"
#include "bezier.h"

Bezier2 approx_bezier2 (Contour CONT, int j1, int j2);
Bezier3 approx_bezier3 (Contour CONT, int j1, int j2);

SequenceBezier2 simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d);
SequenceContours* simplification_contours_bezier2(SequenceContours *seq, double d);

#endif
