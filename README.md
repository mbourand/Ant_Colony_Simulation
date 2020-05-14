# Ant_Colony_Simulation

Ce dépôt contient le code source d'une simulation de colonie de fourmis, vous pouvez trouver **l'éxécutable** dans l'onglet [releases](https://github.com/mbourand/Ant_Colony_Simulation/releases).

<p align="center">
  <img style="margin-left: auto; margin-right=auto; display: block;" src="https://i.imgur.com/hd0M133.png" width="650">
</p>

## Fonctionnement

Il y a deux types de cases :
- Des **obstacles** que les fourmis ne peuvent pas franchir
- De la **nourriture** que les fourmis cherchent à ramener à la fourmillière

Chaque case contient une **valeur de phéromones**.

Les phéromones ont pour rôle d'attirer les fourmis vers elles, **plus une case a de phéromones, plus les fourmis vont passer par cette case**.

### Déplacement des fourmis
Les fourmis se comportent de cette façon :

1. Pour **trouver de la nourriture**, les fourmis se déplacent plus ou moins aléatoirement jusqu'à tomber sur une case nourriture.

2. Une fois de la nourriture trouvée, elles **reviennent à la fourmillière** en empruntant plus ou moins le même chemin qu'à l'allée.

3. Sur le chemin du retour, les fourmis **déposent des phéromones** sur les cases où elles passent.

4. Une fois retournées à la fourmillière, les fourmis **repartent chercher de la nourriture**.

De cette façon, les fourmis vont créer **des chemins de phéromones** qui indiqueront aux autres fourmis que de la nourriture se trouve par ici.

## Code couleur

- Les **obstacles** sont représentés en blanc  <img src="https://i.imgur.com/BfRdWd8.png">
- La **nourriture** est représentée en vert  <img src="https://via.placeholder.com/15/00ff00?text=+">
- Les **fourmis** sont représentées en rouge  <img src="https://via.placeholder.com/15/ff0000?text=+">
lorsqu'elles cherchent de la nourriture et en orange  <img src="https://via.placeholder.com/15/ffa000?text=+"> lorsqu'elles en ramènent.
- Les **phéromones** sont représentés en bleu  <img src="https://via.placeholder.com/15/0064ff?text=+"> plus la couleur est claire, plus il y a de phéromones sur la case.
