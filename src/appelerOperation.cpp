#include <appelerOperation.h>

using namespace std;


/***
Fonction pour ajouter une propriété de l'arborescence sur le graphe
entrée: graphe et propriété
***/

void opAdd (vector<graphNoeud_t> &graph, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].proprietes.count(valeur)) {
			graph[i].noeuds[valeur] = true;
		}
	}
}
/***
Fonction pour ajouter une propriété de a et b dans le graphe
entrée: graphe, a, b et la propriété (a et b)
***/

void opAnd (vector<graphNoeud_t> &graph, string a, string b, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(a) && graph[i].noeuds.count(b)) {
			graph[i].noeuds[valeur] = true;
		}
	}
}
/***
Fonction pour ajouter une propriété de a ou b dans le graphe
entrée: graphe, a, b et la propriété (a ou b)
***/

void opOr (vector<graphNoeud_t> &graph, string a, string b, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		for (int j = 0; j < (int)graph[i].noeuds.size(); ++j) {
			if (graph[i].noeuds.count(a) || graph[i].noeuds.count(b)) {
				graph[i].noeuds[valeur] = true;
				break;
			}
		}
	}
}

/***
Fonction pour ajouter une propriété de  Non a dans le graphe
entrée: graphe, a, b et la propriété (Non a)
***/
void opNot (vector<graphNoeud_t> &graph, string a, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(a) == 0) {
			graph[i].noeuds[valeur] = true;
		}
	}
}

/***
Fonction pour ajouter une propriété de EX (a) sur le graphe
input: graphe, a et la propriété EX (a)
				Rechercher les nœuds qui ont un nœud suivant avec la propriété a
						et insérez la valeur de propriété sur ces nœuds
***/

void opEX (vector<graphNoeud_t> &graph, string a, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(valeur) == 0) {
			for (int j = 0; j < (int)graph[i].next.size(); ++j) {
				if (graph[graph[i].next[j]].noeuds.count(a)) {
					graph[i].noeuds[valeur] = true;
					break;
				}
			}
		}
	}
}

/***
Fonction pour ajouter une propriété de EU (a, b) dans le graphe
input: graphe, a, b et la propriété EU (a, b)
Rechercher les nœuds qui ont la propriété b et insérez la valeur de propriété sur ces nœuds
Ensuite, recherchez les nœuds qui ont la propriété a et un nœud suivant avec la valeur de propriété
et insérez la valeur de la propriété sur ces nœuds, de manière récursive
***/


void opEU (vector<graphNoeud_t> &graph, string a, string b, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(b)) {
			graph[i].noeuds[valeur] = true;
		}
	}

	bool aChanger = true;
	while (aChanger) {
		aChanger = false;
		for (int i = 0; i < (int)graph.size(); ++i) {
			if ((graph[i].noeuds.count(a) || a == "TRUE") && !graph[i].noeuds.count(valeur)) {
				for (int j = 0; j < (int)graph[i].next.size(); ++j) {
					if (graph[graph[i].next[j]].noeuds.count(valeur)) {
						graph[i].noeuds[valeur] = true;
						aChanger = true;
						break;
					}
				}
			}
		}
	}
}


/***
Fonction pour ajouter une propriété de AF (a) dans le graphe
entrée: graphe, a et la propriété AF (a)
Rechercher les nœuds qui ont la propriété a et insérez la valeur de propriété sur ces nœuds
Ensuite, recherchez les nœuds qui ont tous les nœuds voisins avec la valeur de propriété
et insérez la valeur de la propriété sur ces nœuds, de manière récursive
***/

void opAF (vector<graphNoeud_t> &graph, string a, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(a)) {
			graph[i].noeuds[valeur] = true;
		}
	}

	bool aChanger = true;
	bool allNextHave;
	while (aChanger) {
		aChanger = false;
		for (int i = 0; i < (int)graph.size(); ++i) {
			if (!graph[i].noeuds.count(valeur)) {
				allNextHave = true;
				for (int j = 0; j < (int)graph[i].next.size(); ++j) {
					if (!graph[graph[i].next[j]].noeuds.count(valeur)) {
						allNextHave = false;
						break;
					}
				}
				if (allNextHave && graph[i].next.size() != 0) {
					graph[i].noeuds[valeur] = true;
					aChanger = true;
				}
			}
		}
	}
}


/***
Fonction pour appeler la bonne opération pour une expression donnée
entrée: arbre d'expression, machine d'état
***/

void appelerOperation(noeudArbre_t *noeud, vector<graphNoeud_t> &graph){

    stack<noeudArbre_t*> origNoeuds;
    origNoeuds.push(noeud);

    stack<noeudArbre_t*> postNoeuds;
    noeudArbre_t* aux;

    while (!origNoeuds.empty())
    {
        noeudArbre_t *current = origNoeuds.top();
        origNoeuds.pop();

        postNoeuds.push(current);

        if (current->gauche)
            origNoeuds.push(current->gauche);

        if (current->droite)
            origNoeuds.push(current->droite);
    }

    while (!postNoeuds.empty())
    {
	    aux = postNoeuds.top();

		if(aux->type == "function"){

			if(aux->op == "EX"){
				opEX(graph, aux->gauche->contenu, aux->contenu);
			}
			else if(aux->op == "AF"){
				opAF(graph, aux->gauche->contenu, aux->contenu);
			}
			else if(aux->op == "EU"){
				opEU(graph, aux->gauche->contenu, aux->droite->contenu, aux->contenu);
			}
			else if(aux->op == "!"){
				opNot(graph, aux->gauche->contenu, aux->contenu);
			}
			else if(aux->op == "&"){
				opAnd(graph, aux->gauche->contenu, aux->droite->contenu, aux->contenu);
			}
			else if(aux->op == "|"){
				opOr(graph, aux->gauche->contenu, aux->droite->contenu, aux->contenu);
			}
			else printf("Erreur lors de l'appel des algorithmes!");

		}
		else{
			opAdd(graph, aux->contenu);
		}

	    postNoeuds.pop();
    }
}
