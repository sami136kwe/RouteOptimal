/**
* @brief TP5 - Application des graphes - Recherche du plus court chemin (Algorithme Dijkstra)
 * @course INF3105 - Structures de données et algorithmes
 * @session Hiver 2026
 * @author Sami Geagea GEAS72090507
 * @author Mehdi lyafy LYAM74090201
 * @date 2026-05-03
 */
#include <iostream>
#include "graphe.h"
#include "terrain.h"

using namespace std;

void test_terrain(const string& fichier) {
	cout << " Les graphe !" << endl << endl;

	Terrain t1(fichier);
	t1.afficherTerrain();

	Graphe<int> g = t1.construireGraphe();

	// g.afficheGraphe();

	// Trouver dynamiquement les indices de S et G
	// indice == label car tous les sommets sont ajoutés (meme les #)
	int start = -1, goal = -1;
	for (int i = 0; i < t1.getLignes(); i++) {
		for (int j = 0; j < t1.getColonnes(); j++) {
			int label = i * t1.getColonnes() + j;
			if (t1.getCase(i, j) == 'S') start = label;
			if (t1.getCase(i, j) == 'G') goal  = label;
		}
	}

	if (start == -1 || goal == -1) {
		cout << "Erreur : S ou G introuvable dans le terrain." << endl;
		return;
	}

	vector<int> chemin = dijkstra(g, start, goal);

	t1.afficherChemin(g, chemin);

	cout << "Cout du chemin : " << coutChemin(g, chemin) << endl;

	t1.dessinerChemin(g, chemin);
}

int main(int argc, char* argv[]) {
	std::cout << " INF 3105 - TP5 !" << std::endl;
	string fichier = (argc > 1) ? argv[1] : "terrain1_4x4.txt";
	test_terrain(fichier);
	return 0;
}