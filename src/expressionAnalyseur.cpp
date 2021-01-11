#include <expressionAnalyseur.h>
#include <cstdio>

using namespace std;


string getProp(string expression, int pos) {
	string resultat = "(";
	int niveau = 1;
	for(int i = pos+1; niveau != 0; ++i){
		resultat += expression[i];
		if(expression[i] == '(') niveau++;
		if(expression[i] == ')') niveau--;
	}
	return resultat;
}

string getFunction(string expression, int pos){
	string resultat = "";
	while(expression[pos] != '('){
		resultat += expression[pos];
		pos++;
	}
	return resultat;
}


bool isFunction(string expression, int pos) {
	while(expression[pos] != '('){
		if (expression[pos] == ')') 
			return false;
		pos++;
	}
	return true;
}


int findFunction(string expression){
	int niveau = 0;
	for (int i = 0; i < (int)expression.length(); ++i) {
		if(expression[i] == '(') niveau++;
		else if(expression[i] == ')') niveau--;
		else if(niveau == 1 && isFunction(expression, i)) return i;
	}
	return -1;
}


string ax2ex(string p){
	string resultat = "(!(EX(!";
	resultat += p;
	resultat += ")))"; 
	return resultat;
}


string ef2eu(string p){
	string resultat = "(EU((TRUE),";
	resultat += p;
	resultat += "))"; 
	return resultat;
}


string ag2eu(string p){
	string resultat = "(!(EU((TRUE),(!";
	resultat += p;
	resultat += "))))"; 
	return resultat;
}


string eg2af(string p){
	string resultat = "(!(AF(!";
	resultat += p;
	resultat += ")))"; 
	return resultat;
}


string au2afeu(string gauche, string droite){
	string resultat = "((AF";
	resultat += droite;
	resultat += ")&(!(EU((!"; 
	resultat += droite;
	resultat += "),((!"; 	
	resultat += gauche;
	resultat += ")&(!"; 	
	resultat += droite;
	resultat += "))))))"; 
	return resultat;
}


string impl2or(string gauche, string droite){
	string resultat = "((!";
	resultat += gauche;
	resultat += ")|";
	resultat += droite;
	resultat += ")";
	return resultat;
}


string if2and(string gauche, string droite){
	string resultat = "(((!";
	resultat += gauche;
	resultat += ")|";
	resultat += droite;
	resultat += ")&((!";
	resultat += droite;
	resultat += ")|";
	resultat += gauche;
	resultat += "))";
	return resultat;
}


string removeParenthesisInLeaf(string leaf){
	string resultat = "";
	for(int i = 1; i < (int)leaf.length()-1; ++i){
		resultat += leaf[i];
	}
	return resultat;
}


void cleanArbre(noeudArbre_t *noeud){
	if(noeud == NULL) return;
	cleanArbre(noeud->gauche);
	cleanArbre(noeud->droite);
	delete noeud;
}


noeudArbre_t* parserCtlExpression(string expression) {
	string gauche, droite;
	noeudArbre_t *noeud = new noeudArbre_t();
	
	int posFunc = findFunction(expression);
	if (posFunc == -1){
		noeud->contenu = removeParenthesisInLeaf(expression);
		noeud->type = "prop";
		noeud->op = "add";
		noeud->gauche = NULL;
		noeud->droite = NULL;

		return noeud;
	}
	string fonction = getFunction(expression, posFunc);

	if(fonction == "AX"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		expression = ax2ex(gauche);
		fonction = "!";
		posFunc = 1;
	} 
	else if(fonction == "EF"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		expression = ef2eu(gauche);
		fonction = "EU";
		posFunc = 1;
	}
	else if(fonction == "AG"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		expression = ag2eu(gauche);
		fonction = "!";
		posFunc = 1;
	}
	else if(fonction == "EG"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		expression = eg2af(gauche);
		fonction = "!";
		posFunc = 1;
	}
	else if(fonction == "AU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		gauche = getProp(child, 1);
		droite = getProp(child, ++posColon);

		expression = au2afeu(gauche, droite);
		fonction = "&";
		posFunc = findFunction(expression);
	}
	else if(fonction == "->"){
		posFunc += 2;
		gauche = getProp(expression, 1);
		droite = getProp(expression, posFunc);

		expression = impl2or(gauche, droite);
		fonction = "|";
		posFunc = findFunction(expression);
	}
	else if(fonction == "<->"){
		posFunc += 3;
		gauche = getProp(expression, 1);
		droite = getProp(expression, posFunc);

		expression = if2and(gauche, droite);
		fonction = "&";
		posFunc = findFunction(expression);
	}

	if(fonction == "EX"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		noeud->contenu = expression;
		noeud->type = "fonction";
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = NULL;
	}
	else if(fonction == "AF"){
		posFunc += 2;
		gauche = getProp(expression, posFunc);

		noeud->contenu = expression;
		noeud->type = "fonction";	
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = NULL;
	}
	else if(fonction == "EU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		gauche = getProp(child, 1);
		droite = getProp(child, ++posColon);

		noeud->contenu = expression;
		noeud->type = "fonction";
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = parserCtlExpression(droite);
	}
	else if(fonction == "&"){
		gauche = getProp(expression, 1);
		droite = getProp(expression, ++posFunc);

		noeud->contenu = expression;
		noeud->type = "fonction";
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = parserCtlExpression(droite);
	}
	else if(fonction == "|"){
		gauche = getProp(expression, 1);
		droite = getProp(expression, ++posFunc);

		noeud->contenu = expression;
		noeud->type = "fonction";
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = parserCtlExpression(droite);
	}
	else if(fonction == "!"){
		gauche = getProp(expression, ++posFunc);

		noeud->contenu = expression;
		noeud->type = "fonction";
		noeud->op = fonction;
		noeud->gauche = parserCtlExpression(gauche);
		noeud->droite = NULL;
	}
	else {
		cout << "Fonction invalide: " << fonction << "\n";
		exit (EXIT_FAILURE);
	}

	return noeud;
}
