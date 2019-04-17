#ifndef GRAPHE_H
#define GRAPHE_H

#include "arete.h"

class graphe
{
    public:

        graphe(std::string,std::string);
        ~graphe();
        std::vector<Arete*> PRIM(int);
        void afficher(Svgfile& svgout, std::vector<Arete*>,std::string) const;
        //void parcoursBFS(std::string) const;
        //void afficherBFS(std::string) const;
        //void parcoursDFS(std::string) const;
        //void afficherDFS(std::string) const;
        //int rechercher_afficherToutesCC() const;
        std::vector<Arete*> triCout1(int,std::vector<Arete*>);
        std::vector<Arete*> getm_Aretes();
    protected:

    private:
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

        int m_ordre, m_nbArete, m_nbPoids;
};

#endif
