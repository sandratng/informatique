#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe Fichier{"manhattan.txt", "manhattan_weights_0.txt"};
    Fichier.afficher(svgout,Fichier.getGrapheIni(),0,0,"black");
    Fichier.optimisation(Fichier);
    std::cout << std::endl << Fichier.getNbAllGraphes() << std::endl;
    //Fichier.afficher(svgout, Fichier.getVecAllGraphes(1),0,0,"red");

    //std::vector<Arete*> primP1 = Fichier.PRIM(1);

    Fichier.afficher(svgout, Fichier.getVecAllGraphes(7),0,0,"red");
    std::cout << "DAZDSA" << Fichier.getNbAllGraphes() << std::endl;
    return 0;
}
