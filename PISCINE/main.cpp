#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe Fichier{"triville.txt", "triville_weights_0.txt"};
    //Fichier.afficher(svgout,Fichier.getGrapheIni(),0,0,"black");


    //std::cout << std::endl << Fichier.getNbAllGraphes() << std::endl;
    //Fichier.afficher(svgout, Fichier.getVecAllGraphes(1),0,0,"red");

    //std::vector<Arete*> primP1 = Fichier.PRIM(1);

    //Fichier.afficher(svgout, Fichier.getVecAllGraphes(7),0,0,"red");
    //std::cout << "DAZDSA" << Fichier.getNbAllGraphes() << std::endl;

    /// PRIM

    /*
    std::vector<bool> prim;
    std::string text;
    for(int i=0; i<Fichier.getNbPoids();++i)
    {
        prim = Fichier.PRIM(i);
        text = Fichier.calculPoidsTot(prim);
        svgout.addText(i%2*400 + 100, (i/2)*400 + 50,"AFFICHAGE PRIM : Cout "+ to_string(i) + " "+text, "black");
        Fichier.afficher(svgout, prim, i%2*400, (i/2)*400, "black");
    }*/

    /// PARETO

    Fichier.optimisation();
    Fichier.CoutAllGraphes();
    Fichier.triCout2(1);
    Fichier.selectPareto();
    Fichier.affichagePareto(svgout);



    return 0;
}
