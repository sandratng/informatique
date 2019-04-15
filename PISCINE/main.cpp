#include <iostream>
#include "svgfile.h"
#include "couleur.h"
using namespace std;

int main()
{
    Svgfile svgout;
    svgout.addCircle(29, 299, 20,2, Couleur(250,250,250));
    return 0;
}
