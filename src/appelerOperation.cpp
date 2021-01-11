#include <appelerOperation.h>

using namespace std;


void opAdd (vector<graphNoeud_t> &graph, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].proprietes.count(valeur)) {
			graph[i].noeuds[valeur] = true;
		}
	}
}


void opAnd (vector<graphNoeud_t> &graph, string a, string b, string valeur) {
	
	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(a) && graph[i].noeuds.count(b)) {
			graph[i].noeuds[valeur] = true;
		}
	}
}


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


void opNot (vector<graphNoeud_t> &graph, string a, string valeur) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].noeuds.count(a) == 0) {
			graph[i].noeuds[valeur] = true;
		}
	}
}


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
