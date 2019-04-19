#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>
#include "sommet.h"

class Arete
{
    public:
        /// constructeur
        Arete(int, int, int);
        /// destructeur
        ~Arete();
        void ajouterPoids(float);
        int getS1();
        int getS2();
        std::vector<float> getCout();
        float get_Cout(int);
        void afficherVec();

    private:
        /// Poids de l'arête
        std::vector<float> m_poids;

        /// Donnees des arêtes
        int m_id; // Identifiant
        int m_S1, m_S2; // 2 Sommets

};


#endif // ARETE_H_INCLUDED
