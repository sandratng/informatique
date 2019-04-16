#include <iostream>
#include "arete.h"

/// CONSTRUCTEUR
Arete::Arete(std::string id,std::string S1,std::string S2):m_id{id},m_S1{S1},m_S2{S2}
{
}

/// DESTRUCTEUR
Arete::~Arete()
{
}

void Arete::ajouterPoids(double poids)
{
    m_poids.push_back(poids);
}

