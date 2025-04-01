#ifndef _EPS_H_
#define _EPS_H_

char* extraire_nom_fichier(char* chemin_fichier);
void exporter_image_eps(Image I, SequenceContours *seq_contours, char* nom, char* mode);
void exporter_bezier_eps(Image I, SequenceContours* seq_contours, char* nom, char* mode);

#endif
