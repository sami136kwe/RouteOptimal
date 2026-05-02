#pragma once
#ifndef __GRAPHE_H__ 
#define __GRAPHE_H__ 

#include <map>
#include <cassert>
#include <queue>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>


#include <iostream>

template <class S>
class Graphe {
    /**/
    struct Arete {
        int indiceDepart; // indice du sommet de départ
        int indiceArrivee; // indice du sommet d'arrivée
        int poids;      // poids de l'arête

        Arete(int ia, int ib, int p) :indiceDepart(ia), indiceArrivee(ib), poids(p) {}

    };

    struct Sommet {
        Sommet() :s() {};
        Sommet(const S& s_) :s(s_) {};

        S s; // label du sommet qui lui correspond un indice

        std::vector<Arete> aretesSortantes;

        // vector<A> aretesEntrantes;//optionnel
    };

    // dictionnaire (lablel , indice)
    std::map<S, int> indices; // pour retrouver l'indice à partir du label du sommet

    // dictionnaire (indice, sommet)
    std::map<int, Sommet> sommets; //stock les sommets par indice

public:

    /*
     * Ajoute un sommet au graphe
     *   - s : label du sommet
     *
     * Détermine l'indice suivant pour le sommet
     * Stocker l'indice et le sommet dans les map
     *
     * Précondition : il ne doit existé un sommet ayant un label s
     */
    void ajouterSommet(const S& s) {
        assert(indices.count(s) == 0);
        int nouvelIndice = (int)sommets.size();
        indices[s] = nouvelIndice;
        sommets[nouvelIndice] = Sommet(s);
    };

    /*
    * Ajoute une arête au graphe
    *   - a : label du sommet de départ
    *   - b : label du sommet d'arrivée
    *   - p : poids de l'arête
    *
    * Determine les indices correspondant aux labels,
    * Création de l'arête puis on l'ajoute aux arêtes sortantes du sommet ayant
    * l'indice du sommet de départ
    *
    * Précondition : les sommets de labels a et b ont déjà été créés.
    */
    void ajouterArete(const S& a, const S& b, const int p) {
        assert(indices.count(a) > 0);
        assert(indices.count(b) > 0);
        int indiceA = indices.at(a);
        int indiceB = indices.at(b);
        sommets.at(indiceA).aretesSortantes.push_back(Arete(indiceA, indiceB, p));
    }

    /*
    * Retourne le label du Sommet à partir de l'indice
    */
    S labelSommet(int indice) const {
        return sommets.at(indice).s;
    }

    /*
    * Retrouve le label à partir de l'indice
    */
    int indiceSommet(const S& label) const {
        return indices.at(label);
    }

    /*
    * Affichage du graphe - Peut servir à tester la création du graphe
    * Liste les sommets, et pour chaque sommet ses arêtes sortantes
    *
    */
    void afficheGraphe() const {

        // Itérateur sur la map des sommets
        typename std::map<int, Sommet>::const_iterator itSommet;

        for (itSommet = sommets.begin(); itSommet != sommets.end(); ++itSommet) {

            int indice = itSommet->first;

            const Sommet& sommet = itSommet->second;

            std::cout << "Sommet [" << indice << "] - label : " << sommet.s << std::endl;

            // Itérateur sur les arêtes sortantes
            for (int i = 0; i < sommet.aretesSortantes.size(); i++) {
                const Arete& a = sommet.aretesSortantes[i];

                std::cout << "labels Depart - Arrivee : "
                    << labelSommet(a.indiceDepart)
                    << " -> "
                    << labelSommet(a.indiceArrivee)
                    << "  -  Poids: "
                    << a.poids
                    << std::endl;
            }
        }
    }

    template <class T>
    friend std::vector<int> dijkstra(const Graphe<T>& g, int source, int destination);

    template <class T>
    friend int coutChemin(const Graphe<T>& g, const std::vector<int>& chemin);
};

/*
* Détermine le chemin au coût le plus faible.
* Retourne un vecteur des labels des sommets du chemin
*
* source : indique le label de la position de départ (S)
* destination : indique le label de la position d'arrivée (G)
*/
template <class T>
std::vector<int> dijkstra(const Graphe<T>& g, int source, int destination) {
    std::map<int, int> distances;
    std::map<int, int> predecesseur;

    // Initialisation : toutes distances à l'infini, aucun prédécesseur
    typename std::map<int, typename Graphe<T>::Sommet>::const_iterator it;
    for (it = g.sommets.begin(); it != g.sommets.end(); ++it) {
        distances[it->first]    = INT_MAX;
        predecesseur[it->first] = -1;
    }
    distances[source] = 0;

    // File de priorité min : (coût, indice)
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > file;

    file.push(std::make_pair(0, source));

    while (!file.empty()) {
        int coutActuel   = file.top().first;
        int sommetActuel = file.top().second;
        file.pop();

        if (sommetActuel == destination) break;

        // Entrée obsolète : un meilleur coût a déjà été traité
        if (coutActuel > distances[sommetActuel]) continue;

        const std::vector<typename Graphe<T>::Arete>& aretes =
            g.sommets.at(sommetActuel).aretesSortantes;

        for (int i = 0; i < (int)aretes.size(); i++) {
            int voisin      = aretes[i].indiceArrivee;
            int nouveauCout = distances[sommetActuel] + aretes[i].poids;

            if (nouveauCout < distances[voisin]) {
                distances[voisin]    = nouveauCout;
                predecesseur[voisin] = sommetActuel;
                file.push(std::make_pair(nouveauCout, voisin));
            }
        }
    }

    // Reconstruction du chemin par remontée des prédécesseurs
    std::vector<int> chemin;
    if (distances[destination] == INT_MAX) return chemin; // aucun chemin

    for (int v = destination; v != -1; v = predecesseur[v])
        chemin.push_back(v);

    std::reverse(chemin.begin(), chemin.end());
    return chemin;
};

/*
* Détermine le coût du chemin à partir du chemin donné en paramètre
*
*/
template <class T>
int coutChemin(const Graphe<T>& g, const std::vector<int>& chemin) {
    int cout = 0;
    for (int i = 0; i < (int)chemin.size() - 1; i++) {
        int indiceActuel  = chemin[i];
        int indiceSuivant = chemin[i + 1];
        const std::vector<typename Graphe<T>::Arete>& aretes =
            g.sommets.at(indiceActuel).aretesSortantes;
        for (int j = 0; j < (int)aretes.size(); j++) {
            if (aretes[j].indiceArrivee == indiceSuivant) {
                cout += aretes[j].poids;
                break;
            }
        }
    }
    return cout;
};

#endif
