# RouteOptimal - Recherche du plus court chemin (Dijkstra)

## Description
Ce projet implémente l'algorithme de Dijkstra pour trouver le chemin 
le moins coûteux sur un terrain virtuel. Le terrain est représenté 
par une grille contenant différents types d'éléments : plaines, forêts, 
montagnes et obstacles.

## Contexte
Projet réalisé dans le cadre du cours **INF3105 - Structures de données 
et algorithmes** à l'UQAM, session Hiver 2026.

## Fonctionnement
Une personne se déplace sur un terrain de S (départ) vers G (arrivée).
Chaque type de terrain a un coût de déplacement différent :

| Symbole | Type       | Coût |
|---------|------------|------|
| `.`     | Terrain plat | 1  |
| `F`     | Forêt       | 3   |
| `M`     | Montagne    | 10  |
| `#`     | Obstacle    | ❌  |
| `S`     | Départ      | -   |
| `G`     | Arrivée     | -   |

Le programme trouve automatiquement le chemin le moins coûteux 
et l'affiche avec des `*` sur la grille.

## Exemple
```
S * * * . . M . .
. # # * . F . . M
. . F * . . # . .
. M . * F . . F .
. . # * * M . . .
F . . M * * # . .
. . F . . * M . .
. # . . F * * # .
. . . M . . * * G
```

## Technologies utilisées
- **Langage :** C++
- **Librairie :** STL (vector, map, priority_queue)
- **Algorithme :** Dijkstra
- **Compilation :** g++ version 12

## Compilation et exécution
```bash
make
./routeoptimal fichier_terrain.txt
```

## Structure du projet
- `graphe.h` — Template Graphe avec liste d'adjacences
- `terrain.h / terrain.cpp` — Lecture et construction du graphe
- `dijkstra.cpp` — Implémentation de l'algorithme
- `main.cpp` — Point d'entrée du programme
- `Makefile` — Compilation

## Auteur
Sami — INF3105, Hiver 2026