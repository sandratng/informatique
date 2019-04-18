#include <iostream>
#include "svgfile.h"
#include "couleur.h"
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    std::unordered_map<int,std::vector<Arete*>> allGraphes;
    graphe Fichier{"broadway.txt", "broadway_weights_0.txt"};
    //Fichier.afficher(svgout,Fichier.getm_Aretes(),0, 0, "black");
    allGraphes = Fichier.optimisation();
    std::vector<Arete*> primP1 = Fichier.PRIM(0);
    Fichier.afficher(svgout,allGraphes.find(0)->second,0,0,"black");
    std::cout << endl;
    std::cout << endl;
    int i = 0;
for(auto a : allGraphes)
{

    for ( auto x : a.second)
    {

    std::cout << x->getMark();
    }
    i++;
    std::cout << std::endl;
}
    //Fichier.afficher(svgout, primP1, 400, 0,"red");
    return 0;
}
