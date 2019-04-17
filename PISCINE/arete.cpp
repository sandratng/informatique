#include <iostream>
#include "arete.h"

/// CONSTRUCTEUR
Arete::Arete(std::string id,std::string S1,std::string S2,int nb_poids,int nbArete):m_id{id},m_S1{S1},m_S2{S2},m_nbPoids{nb_poids}, m_nbArete{nbArete}
{
}

/// DESTRUCTEUR
Arete::~Arete()
{
}

void Arete::ajouterPoids(double poids)
{
    std::cout << poids << "; ";
    m_poids.push_back(poids);
}

std::string Arete::getS1()
{
    return m_S1;
}

std::string Arete::getS2()
{
    return m_S2;
}
int Arete::getNbPoids()
{
    return m_nbPoids;
}

void Arete::afficherVec()
{
        std::cout << m_poids[2] << ";";

}

std::vector<double> Arete::getVector()
{
    return m_poids;
}

int Arete::getNbArete()
{
    return m_nbArete;
}
