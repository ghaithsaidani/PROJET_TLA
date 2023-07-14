#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Terminal.h"
#include "ctype.h"

struct identifiant {
    char name[100];
    enum Terminal type;
};

struct identifiant tab_identifiants[100];
int compteuridentifiant = 0;


int table_element_index(char *x, struct identifiant tab[]) {
    for (int i = 0; i < sizeof(tab); ++i) {
        if (strcmp(tab[i].name, x) == 0)
            return i;
    }
    return -1;
}

// Analyseur lexical
void analyseurLexical(char *nomFichier) {
    FILE *f = fopen(nomFichier, "r");
    if (f == NULL) {
        printf("\n=> Echec lors de louverture du fichier %s!", nomFichier);
    } else {
        char ch;
        while ((ch = fgetc(f)) != EOF) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                continue;
            } else if (ch == '(') {
                printf("%s ", terminaux_tab[PARENTHESEOUVRANTE]);
            } else if (ch == ')') {
                printf("%s ", terminaux_tab[PARENTHESEFERMANTE]);
            } else if (ch == ';') {
                printf("%s ", terminaux_tab[POINTVIRGULE]);
            } else if (ch == ':') {
                printf("%s ", terminaux_tab[DEUXPOINTS]);
            } else if (ch == ',') {
                printf("%s ", terminaux_tab[VIRGULE]);
            } else if (ch == '.') {
                printf("%s ", terminaux_tab[POINT]);
            } else if (ch == '<' || ch == '>' || ch == '=') {
                char suivant = fgetc(f);
                if (suivant != '=' || (ch == '<' || suivant != '>'))
                    ungetc(suivant, f);
                printf("%s ", terminaux_tab[OPREL]);
            } else if (ch == '+' || ch == '-'
                    ) {
                printf("%s ", terminaux_tab[OPADD]);
            } else if (ch == '|') {
                char suivant = fgetc(f);
                if (suivant != '|') {
                    printf("Erreur lexical");
                    break;
                }
                else   printf("%s ", terminaux_tab[OPADD]);
            } else if (ch == '*' || ch == '/' || ch == '%'
                    ) {
                printf("%s ", terminaux_tab[OPMUL]);
            } else if (ch == '&') {
                char suivant = fgetc(f);
                if (suivant != '&') {
                    printf("Erreur lexical");
                    break;
                }
                else   printf("%s ", terminaux_tab[OPADD]);
            } else if (isdigit(ch)) {
                char number[100];
                int i = 0;
                number[i++] = ch;
                while (isdigit(ch = fgetc(f))) {
                    number[i++] = ch;
                }
                number[i] = '\0';
                ungetc(ch, f);
                printf("%s ", terminaux_tab[NB]);
            } else if (isalpha(ch)) {
                char identifier[100];
                int i = 0;
                identifier[i++] = ch;
                while (isdigit(ch = fgetc(f)) || isalpha(ch)) {
                    identifier[i] = ch;
                    i++;
                }
                identifier[i] = '\0';
                ungetc(ch, f);

                if (strcmp(identifier, "programme") == 0) {
                    printf("%s ", terminaux_tab[PROGRAMME]);
                } else if (strcmp(identifier, "var") == 0) {
                    printf("%s ", terminaux_tab[VAR]);
                } else if (strcmp(identifier, "integer") == 0) {
                    printf("%s ", terminaux_tab[INTEGER]);
                } else if (strcmp(identifier, "char") == 0) {
                    printf("%s ", terminaux_tab[CHAR]);
                } else if (strcmp(identifier, "float") == 0) {
                    printf("%s ", terminaux_tab[FLOAT]);
                } else if (strcmp(identifier, "begin") == 0) {
                    printf("%s ", terminaux_tab[BEGIN]);
                } else if (strcmp(identifier, "end") == 0) {
                    printf("%s ", terminaux_tab[END]);
                } else if (strcmp(identifier, "if") == 0) {
                    printf("%s ", terminaux_tab[IF]);
                } else if (strcmp(identifier, "then") == 0) {
                    printf("%s ", terminaux_tab[THEN]);
                } else if (strcmp(identifier, "else") == 0) {
                    printf("%s ", terminaux_tab[ELSE]);
                } else if (strcmp(identifier, "while") == 0) {
                    printf("%s ", terminaux_tab[WHILE]);
                } else if (strcmp(identifier, "do") == 0) {
                    printf("%s ", terminaux_tab[DO]);
                } else if (strcmp(identifier, "for") == 0) {
                    printf("%s ", terminaux_tab[FOR]);
                } else if (strcmp(identifier, "read") == 0) {
                    printf("%s ", terminaux_tab[READ]);
                } else if (strcmp(identifier, "readln") == 0) {
                    printf("%s ", terminaux_tab[READLN]);
                } else if (strcmp(identifier, "write") == 0) {
                    printf("%s ", terminaux_tab[WRITE]);
                } else if (strcmp(identifier, "writeln") == 0) {
                    printf("%s ", terminaux_tab[WRITELN]);
                } else {
                    if (table_element_index(identifier, tab_identifiants) == -1) {
                        strcpy(tab_identifiants[compteuridentifiant].name, identifier);
                        compteuridentifiant++;
                    }
                    printf("%s%d ", terminaux_tab[ID], table_element_index(identifier, tab_identifiants)+1);
                }
            } else {
                printf("Erreur : Caractère inconnu '%c'\n", ch);
                exit(1);
            }
        }
    }
    fclose(f);

}

int main() {
    analyseurLexical("test.txt");

    return 0;
}
