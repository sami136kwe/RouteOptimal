/**
* @brief TP5 - Application des graphes - Recherche du plus court chemin (Algorithme Dijkstra)
 * @course INF3105 - Structures de données et algorithmes
 * @session Hiver 2026
 * @author Sami Geagea GEAS72090507
 * @author Mehdi lyafy LYAM74090201
 * @date 2026-05-03
 */
#ifndef __TERRAIN_H__
#define __TERRAIN_H__ 

#include <iostream>
#include <fstream>
#include <string>
#include "graphe.h"


using namespace std;

class Terrain {

public:
    Terrain() : lignes(0), colonnes(0), grille(nullptr) {}

    /* Constructeur fait appel à la lecture du fichier du terrain */
    Terrain(const string& fichier) : lignes(0), colonnes(0), grille(nullptr) {
        lireTerrain(fichier);
    }


    ~Terrain() {
        for (int i = 0; i < lignes; i++)
            delete[] grille[i];
        delete[] grille;
    }

    int getLignes() const { return lignes; }
    int getColonnes() const { return colonnes; }

    char getCase(int i, int j) const {
        return grille[i][j];
    }
    /* Constructin du graphe */
    Graphe<int> construireGraphe() const;

    /* Affiche la grille représentant le terrain */
    void afficherTerrain() const;

    /* Affiche le chemin donné en paramètre */
    void afficherChemin(const Graphe<int>& g, const vector<int>& chemin) const;

    /* Dessine la grille représentant le terrain et le chemin trouvé par Dijkstra 
    *  Le chemin est représenté par des étoiles (*)
    */
    void dessinerChemin(const Graphe<int>& g, const vector<int>& chemin) const;

private:
    int lignes;
    int colonnes;
    char** grille;

    /* Lecture du fichier terrain */
    void lireTerrain(const string& fichier);
};


#endif
