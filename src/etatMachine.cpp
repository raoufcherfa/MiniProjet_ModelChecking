#include <etatMachine.h>

using namespace std;


/***
Fonction de lecture de l'entrée
sortie: la machine d'état
***/

vector<graphNoeud_t> lireEtatMachine() {

	graphNoeud_t g;
	vector<graphNoeud_t> v;
	int N;
	int quant;
	string prop;
	int etat;

	cin >> N;
	v.resize(N);

	while(N--) {
		cin >> g.id;

		if (g.id > (int)v.size()) {
			cout << "Machine etat malformée!\n";
			exit (EXIT_FAILURE);
		}
		cin >> quant;

		while(quant--) {
			cin >> prop;
			g.proprietes[prop] = true;
		}
		g.proprietes["TRUE"] = true;
		cin >> quant;

		while (quant--) {
			cin >> etat;

			if (etat > (int)v.size()) {
				cout << "Machine etat malformée!\n";
				exit (EXIT_FAILURE);
			}

			g.next.push_back(etat - 1);
		}

		v[g.id - 1] = g;

		g.proprietes.clear();
		g.next.clear();
	}

	return v;
}
