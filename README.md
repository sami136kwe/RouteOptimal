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

## Recherche opérationnelle — Le cadre de ce projet

La **recherche opérationnelle (RO)** est une discipline scientifique qui applique des méthodes mathématiques et algorithmiques pour **modéliser et résoudre des problèmes de décision complexes** : minimiser un coût, maximiser un profit, optimiser une ressource ou planifier un itinéraire.

### Définition formelle

```
Minimiser (ou maximiser) : f(x)        ← fonction objectif
Sous les contraintes     : g(x) ≤ b    ← contraintes du problème
```

Où `x` représente les **variables de décision** — ici, le chemin choisi sur le terrain.

### Lien avec ce projet

RouteOptimal est un problème de RO classique : le **problème du plus court chemin** (*shortest path problem*).

| Élément RO | Correspondance dans RouteOptimal |
|---|---|
| **Variables de décision** | Quel chemin emprunter de `S` à `G` ? |
| **Fonction objectif** | Minimiser le coût total du déplacement |
| **Contraintes** | Obstacles `#` infranchissables, déplacements sur la grille |
| **Modèle mathématique** | Graphe orienté pondéré `G = (V, E, w)` |
| **Algorithme de résolution** | Dijkstra |

### Domaines d'application de la RO

- **Logistique et transport** : optimisation des routes de livraison (FedEx, Amazon), planification d'horaires ferroviaires.
- **Télécommunications** : conception de réseaux à coût minimal (→ lien direct avec les ARM, section 8).
- **Intelligence artificielle** : recherche dans un espace d'états, planification de mouvements de robots.
- **Jeux vidéo** : calcul de trajectoires pour les personnages non-joueurs (A*, section 7).
- **Finance** : optimisation de portefeuilles, arbitrage sur les marchés.

| Algorithme | Question RO résolue |
|---|---|
| **Dijkstra** | Quel est le chemin le moins coûteux depuis une source vers tous les autres sommets ? |
| **Floyd-Warshall** | Quels sont les chemins minimaux entre toutes les paires de sommets du réseau ? |
| **Bellman-Ford** | Même question que Dijkstra, mais avec des coûts négatifs possibles (ex. réductions, remboursements). |
| **A\*** | Comment trouver le plus court chemin plus rapidement grâce à une estimation intelligente de la distance restante ? |
| **Contractions hiérarchiques** | Comment calculer des itinéraires optimaux en temps réel sur des réseaux de millions de nœuds ? |
| **Tarjan (CFC)** | Quelles parties d'un réseau sont mutuellement accessibles ? (ex. circuits de dépendances, détection de blocages) |
| **Prim-Jarník / Kruskal (ARM)** | Comment connecter tous les points d'un réseau au coût total minimal, sans redondance ? |

> En résumé, les graphes sont le **langage de modélisation** de la RO, et les algorithmes de graphes sont ses **outils de résolution**.

---

## Auteur
Sami — INF3105, Hiver 2026
