#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>

class Arete
{
    public:
        /// constructeur
        Arete(std::string,std::string,std::string,int,int);
        /// destructeur
        ~Arete();
        void ajouterPoids(double);
        std::string getS1();
        std::string getS2();
        std::vector<double> getVector();
        int getNbArete();
        void afficherVec();
        int getNbPoids();

    private:
        /// Poids de l'ar�te
        std::vector<double> m_poids;
        bool m_marque = true;

        /// Donnees des ar�tes
        std::string m_id; // Identifiant
        std::string m_S1, m_S2; // 2 Sommets
        int m_nbPoids;
        int m_nbArete;

};


#endif // ARETE_H_INCLUDED
