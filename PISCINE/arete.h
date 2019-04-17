#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>

class Arete
{
    public:
        /// constructeur
        Arete(std::string,std::string,std::string,int);
        /// destructeur
        ~Arete();
        void ajouterPoids(double);
        std::string getS1();
        std::string getS2();
        std::vector<double> getVector();
        void afficherVec();
        int getNbPoids();

    private:
        /// Poids de l'arête
        std::vector<double> m_poids;

        /// Donnees des arêtes
        std::string m_id; // Identifiant
        std::string m_S1, m_S2; // 2 Sommets
        int m_nbPoids;

};


#endif // ARETE_H_INCLUDED
