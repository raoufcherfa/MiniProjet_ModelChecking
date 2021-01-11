#include <expressionAnalyseur.h>
#include <etatMachine.h>
#include <appelerOperation.h>

using namespace std;

/***
Fonction pour imprimer le résultat de l'expression appliquée dans la machine à états
entrée: machine à états, expression modifiée, expression originale
***/
void afficherResultat(vector<graphNoeud_t> &graph, string expression, string initExpression){

	cout << "Expression: " << initExpression << "\n";
	cout << "Etats: ";

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].noeuds.count(expression)){
			cout << graph[i].id << ' ';
		}
	}
	cout << "\n";
}

int main(){

	vector<graphNoeud_t> smGraphy;
	noeudArbre_t *ctlArbre;

	smGraphy = lireEtatMachine();

	string expression;
	cin >> expression;
	ctlArbre = parserCtlExpression(expression);

	appelerOperation(ctlArbre, smGraphy);
	afficherResultat(smGraphy, ctlArbre->contenu, expression);

	cleanArbre(ctlArbre);

	return 0;
}
