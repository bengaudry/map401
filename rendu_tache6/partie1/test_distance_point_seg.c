#include <stdio.h>
#include "geometrie.h"

int main(int argc, char **argv) {
    double x, y;
    Point P, A, B;

    printf("P.x : ");
    scanf("%lf", &x);
    printf("P.y : ");
    scanf("%lf", &y);

    P = set_point(x, y);

    printf("\nA.x : ");
    scanf("%lf", &x);
    printf("A.y : ");
    scanf("%lf", &y);

    A = set_point(x, y);

    printf("\nB.x : ");
    scanf("%lf", &x);
    printf("B.y : ");
    scanf("%lf", &y);

    B = set_point(x, y);
    
    printf("Distance entre P et [AB] : %f\n", distance_point_segment(P, A, B));

    return 0;
}
