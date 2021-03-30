# ProjetSysteme
## Forme de la requete
  Chaque argument est séparé d'un espace
  - Jour "Jx"
  - Heure sous format nombre, sans h "22"
  - Destination "T" ou "M"
  - Nombre de places reservées allant de 1 à 4

Programme client-serveur communiquant ainsi :
  - Pere->Fils : Pipe anonyme
  - Fils->Pere : Signaux déroutés

## L'utilité des fonctions est en commentaire dans le namespace

## Le namespace contient :
  - L'initialisation de la matrice
  - Les fonctions utilisées
  - L'initialisation du moyen pipe
  
## La structure de donnée utilisée
C'est une matrice C++ simple déclarée ainsi : 
```
int Matrice[5][4];
```

Pour ce qui est des indices elle respecte les indices du tableau sur l'énoncé
