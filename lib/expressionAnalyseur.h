#ifndef EXPRESSIONANALYSEUR_H_
#define EXPRESSIONANALYSEUR_H_

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


typedef struct noeudArbre_s {
	string contenu;
	string type;
	string op;
	struct noeudArbre_s *gauche;
	struct noeudArbre_s *droite;
} noeudArbre_t;

noeudArbre_t* parserCtlExpression(string contenu);
void cleanArbre(noeudArbre_t *noeud);

#endif
