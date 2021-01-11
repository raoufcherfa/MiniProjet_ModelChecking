# MiniProjetModelChecking

## Authors:

####	Amine YAHOUNI - 11928535

####	Abderaouf CHERFA - 11928528	

## Introduction:

Ce document a pour but de décrire le déroulement de notre mini-projet un model checker pour la logique CTL ( l’algorithme du model Checking ).
C’est le résultat du travail qui nous a permis de réaliser un Algorithme dont le cadre applicatif permet , ce projet était réalisé en language C++ en respectant plusieurs instructions.

- Un model checker CTL ayant comme entrée un fichier contenant une description textuelle d'une structure une formule CTL. 
- En sortie, on a une réponse quand à la satisfaction de la formule donnée par le système.

## Descreption des classes :

Ce projet contients 4 classe En cpp : une classe qui contient la structure de l'arbre et plusieurs fonctions qui nous permets d'analyser les expression.
- etatMachine : une classe qui contient la fonction qui nous permet de lire l'état de la machine (de l'expression).
- appelerOperation : une classe qui contient les fonctions qui permet d'appeler les operation sur le graphe.
- mainModelChechking : une classe main qui a pour but d'excuter l'ensemble de projet.
## Instruction d'excution:

####	Ajouter un fichier test :


![testFile Image (Login!)](/images/exemplefile.png "exemple file")


####	Pour compiler le programme

	make
	
### Pour excuter le projet 
	 
	make run IN="fichier" 

## Exemple d'excution et Résultats

![sortie Image (Login!)](/images/exec.png "exemple file")


