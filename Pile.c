#include "Pile.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Pile InitPile(){
    return NULL;
}

int pile_vide(Pile p){
    return p == NULL ? 1 : 0;
}
char *Sommet(Pile p){
    if(!pile_vide(p))
        return p->val;
}
Pile empiler(Pile p,char *valeur){
    Pile cel= (Pile) malloc(sizeof (cellule));
    strcpy(p->val,valeur);
    cel->suivant=p;
    return p;
}
int depiler(Pile p){
    Pile celadepiler=p;
    if(pile_vide(p)){
        printf("vous ne pouvez depiler car pile est vide");
        return 0;
    }
    else{
        p=celadepiler->suivant;
        free(celadepiler);
        return 1;
    }
}

