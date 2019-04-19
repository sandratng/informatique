#ifndef GRAPHE_H
#define GRAPHE_H

#include "arete.h"

class graphe
{
    public:

        graphe(std::string,std::string);
        ~graphe();
        std::vector<bool> PRIM(int);
        void afficher(Svgfile& svgout, std::vector<bool>,double, double,std::string) const;
        //void parcoursBFS(std::string) const;
        //void afficherBFS(std::string) const;
        //void parcoursDFS(std::string) const;
        //void afficherDFS(std::string) const;
        //int rechercher_afficherToutesCC() const;
        std::vector<Arete*> triCout1(int,std::vector<Arete*>);
        void eraseAllGraphes(int);
        std::vector<bool> getVecAllGraphes(int);
        std::vector<bool> getGraphPRIM(int);
        std::vector<bool> getGrapheIni();
        void CoutAllGraphes();
        int getNbAllGraphes();
        void optimisation(graphe fichier);
        bool connexite(std::vector<bool>);
    protected:

    private:
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<bool> m_grapheIni;
        std::vector<std::vector<bool>> m_allGraphes;
        std::vector<std::vector<bool>> m_graphPRIM;
        std::vector<std::vector<float>> m_coutAllGraphes;
        int m_ordre, m_nbArete, m_nbPoids, m_nbAllGraphes;
};

#endif
