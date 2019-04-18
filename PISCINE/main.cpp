#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe Fichier{"triville.txt", "triville_weights_0.txt"};
    Fichier.afficher(svgout,Fichier.getm_Aretes(),0, 0, "black");
    std::vector<Arete*> primP1 = Fichier.PRIM(0);
    Fichier.afficher(svgout, primP1, 400, 0,"red");
    return 0;
}
