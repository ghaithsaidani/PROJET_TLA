#ifndef PROJET_TLA_PILE_H
#define PROJET_TLA_PILE_H
#define max 50


typedef struct cellule{
    char val[max];
    struct cellule *suivant;
}cellule;

typedef struct cellule *Pile;

Pile InitPile();
int pile_vide(Pile p);
char *Sommet(Pile p);
Pile empiler(Pile p,char *valeur);
int depiler(Pile p);

#endif
