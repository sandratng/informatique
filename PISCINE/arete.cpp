#include "arete.h"

/// CONSTRUCTEUR
Arete::Arete(int id,int S1,int S2):m_id{id},m_S1{S1},m_S2{S2}
{
}

/// DESTRUCTEUR
Arete::~Arete()
{
}

void Arete::ajouterPoids(float poids)
{
    std::cout << poids << "; ";
    m_poids.push_back(poids);
}

int Arete::getID()
{
    return m_id;
}

int Arete::getS1()
{
    return m_S1;
}

int Arete::getS2()
{
    return m_S2;
}

void Arete::afficherVec()
{
        std::cout << m_poids[2] << ";";

}

std::vector<float> Arete::getCout()
{
    return m_poids;
}

float Arete::get_Cout(int poids)
{
    return m_poids[poids];
}
