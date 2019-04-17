#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe Fichier{"manhattan.txt", "manhattan_weights_0.txt"};
    Fichier.afficher(svgout);
    Fichier.pointPareto(svgout,"green");
    return 0;
}
