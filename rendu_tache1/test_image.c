#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

int main (int argc, char **argv) {
    Image I;

    if (argc < 2) {
        ERREUR_FATALE("Chemin vers le fichier requis");
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    ecrire_image(I);
    I = negatif_image(I);
    ecrire_image(I);

    return 0;
}