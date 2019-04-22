#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe Fichier{"cubetown.txt", "cubetown_weights_0.txt"};

    int choix;
    std::cout<<"MENU :"<< std::endl
            << " 1 - PRIM " << std::endl
            << " 2 - PARETO"<< std::endl
            << " 3 - DIJKSTRA"<< std::endl;
    std::cin >> choix;
    /// PRIM
    if(choix == 1)
    {
        std::vector<bool> prim;
        std::string text;
        for(int i=0; i<Fichier.getNbPoids();++i)
        {
            if(i==0)
                Fichier.afficher(svgout,Fichier.getGrapheIni(),0,0,"black");
            prim = Fichier.PRIM(i);
            text = Fichier.calculPoidsTot(prim);
            svgout.addText((i+1)%2*400 + 100, ((i+1)/2)*400 + 50,"AFFICHAGE PRIM : Cout "+ to_string(i) + " "+text, "black");
            Fichier.afficher(svgout, prim, (i+1)%2*400, ((i+1)/2)*400, "black");
        }
    }


    /// PARETO
    if(choix == 2)
    {
        Fichier.optimisation();
        Fichier.CoutAllGraphes();
        Fichier.triCout2(1);
        Fichier.selectPareto();
        Fichier.affichagePareto(svgout);
    }



    /// DIJKSTRA

    if (choix ==3)
    {
        Fichier.optimisationDij();
        std::cout << "dij";
        Fichier.dijkstra();
        Fichier.triCout3(1);
        std::cout << "Selection Dij" << std::endl;
        Fichier.selectDij();
        std::cout << "affichage";
        Fichier.affichageDijkstra(svgout);
    }


    return 0;
}
