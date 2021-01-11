# MiniProjetModelChecking

## Authors:

####	Amine YAHOUNI - 11928535

####	Abderaouf CHERFA - 11928528	

## Introduction:

Ce document a pour but de décrire le déroulement de notre mini-projet d'un model checker pour la logique CTL ( l’algorithme du model Checking ).
Dans le cadre de notre module Systéme complexe on a réalisé en language C++ un projet qui a pout but d'eavluer une expression ctl sur un graphe donné en respectant plusieurs instructions.</br>
les entrées et sortie :
- Un model checker CTL ayant comme entrée un fichier contenant une description textuelle d'une structure une formule CTL. 
- En sortie, on a une réponse quand à la satisfaction de la formule donnée par le système.

## Descreption des classes :

Ce projet contients 4 classe En cpp : 

- **expressionAnalyseur** : une classe qui contient la structure de l'arbre et plusieurs fonctions qui nous permetent d'analyser les expressions(**commentaire pour l'utilité de chacune d'entre elle**).
- **etatMachine** : une classe qui contient la fonction qui nous permet de lire l'état de la machine (de l'expression).
- **appelerOperation** : une classe qui contient les fonctions qui permet d'appeler les operation sur le graphe.
- **mainModelChechking** : une classe main qui a pour but d'excuter l'ensemble de projet.
## Instruction d'excution:

####	Ajouter un fichier test :


![testFile Image (Login!)](/images/exemplefile.png "exemple file")

<ol>
<li>La première ligne a la valeur de <strong>totLines</strong>  non nul décrivant les états totaux de notre machine à états</li>
<li>
	Les lignes suivantes <strong>totLinhas</strong> auront les éléments suivants séparés par un espace
	<ul>
	<li>Identificateur d'état unique (type entier)</li>
	<li>Total totProps des propriétés (type entier)</li>
	<li>Séquence de chaînes <strong>totProps</strong> représentant les étiquettes des propriétés données comme identificateurs valides, séparées par un espace</li>
	<li>Nombre total d'états <strong>totProxEstad</strong> à venir (type entier)</li>
	<li>Séquence d'identificateurs <strong>totProxEstad</strong> valide des états suivants, séparés par un espace</li>
	</ul>
</li>
<li>La dernière ligne doit inclure l'expression CTL à vérifier.</li>
</ol>

####	Pour compiler le programme

	make
	
### Pour excuter le projet 
	 
	make run IN="fichier"
(**IN="test.txt"** pour notre exemple) 

## Exemple d'excution et Résultats

![sortie Image (Login!)](/images/exec.png "exemple file")



