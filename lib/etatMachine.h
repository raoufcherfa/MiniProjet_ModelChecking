#ifndef ANALYSEURM_H_
#define ANALYSEURM_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;


typedef struct graphNoeud_s {
	int id;
	vector<int> next;
	map<string, bool> proprietes;
	map<string, bool> noeuds;
} graphNoeud_t;

vector<graphNoeud_t> lireEtatMachine();

#endif