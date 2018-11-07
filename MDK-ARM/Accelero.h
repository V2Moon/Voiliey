#ifndef _ACCELERO_H_
#define _ACCELERO_H_

//Les valeurs reçues par capt
int X=0;
int Y=0;

//La valeur de l'angle de roulis
int angle=0;

void init_Accelero (void);
void set_g_select (void);
int get_angle (void);

#endif

