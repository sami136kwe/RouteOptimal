/**
 * @brief TP5 - Application des graphes - Recherche du plus court chemin (Algorithme Dijkstra)
 * @course INF3105 - Structures de données et algorithmes
 * @session Hiver 2026
 * @author Sami Geagea GEAS72090507
 * @author Mehdi lyafy LYAM74090201
 * @date 2026-05-03
 */

#include "terrain.h"
#include <set>

// Coût d'entrée dans une case selon son type
static int coutCase(char c) {
    switch (c) {
        case 'F': return 3;
        case 'M': return 10;
        default:  return 1; // '.', 'S', 'G'
    }
}

void Terrain::afficherTerrain() const {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++)
            cout << grille[i][j];
        cout << endl;
    }
}

void Terrain::lireTerrain(const string& fichier) {
    ifstream ifs(fichier);
    ifs >> lignes >> colonnes;

    grille = new char*[lignes];
    for (int i = 0; i < lignes; i++) {
        string ligne;
        ifs >> ligne;
        grille[i] = new char[colonnes];
        for (int j = 0; j < colonnes; j++)
            grille[i][j] = ligne[j];
    }
}

/* Constructin du graphe */
Graphe<int> Terrain::construireGraphe() const {
    Graphe<int> g;

    for (int i = 0; i < lignes; i++)
        for (int j = 0; j < colonnes; j++)
            if (grille[i][j] != '#')
                g.ajouterSommet(i * colonnes + j);


    const int di[] = {-1, 1, 0, 0};
    const int dj[] = { 0, 0,-1, 1};

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            if (grille[i][j] == '#') continue;

            int labelDepart = i * colonnes + j;

            for (int d = 0; d < 4; d++) {
                int ni = i + di[d];
                int nj = j + dj[d];

                if (ni < 0 || ni >= lignes || nj < 0 || nj >= colonnes) continue;
                if (grille[ni][nj] == '#') continue;

                int labelArrivee = ni * colonnes + nj;
                g.ajouterArete(labelDepart, labelArrivee, coutCase(grille[ni][nj]));
            }
        }
    }

    return g;
}

/* Affiche le chemin donné en paramètre */
void Terrain::afficherChemin(const Graphe<int>& g, const vector<int>& chemin) const {
    if (chemin.empty()) {
        cout << "Aucun chemin trouvé." << endl;
        return;
    }

    cout << "Chemin (" << chemin.size() << " sommets) :" << endl;

    for (int i = 0; i < (int)chemin.size(); i++) {
        int label = g.labelSommet(chemin[i]);
        int li    = label / colonnes;
        int col   = label % colonnes;

        cout << "[" << li << "," << col << "](" << grille[li][col] << ")";
        if (i < (int)chemin.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

/*
* Dessine la grille représentant le terrain et le chemin trouvé par Dijkstra
* Le chemin est représenté par des étoiles (*)
*/
void Terrain::dessinerChemin(const Graphe<int>& g, const vector<int>& chemin) const {
    if (chemin.empty()) {
        cout << "Aucun chemin à dessiner." << endl;
        afficherTerrain();
        return;
    }

    set<int> surChemin;
    for (int i = 0; i < (int)chemin.size(); i++)
        surChemin.insert(g.labelSommet(chemin[i]));

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            int label = i * colonnes + j;
            char c    = grille[i][j];

            if (surChemin.count(label) && c != 'S' && c != 'G')
                cout << '*';
            else
                cout << c;
        }
        cout << endl;
    }
}