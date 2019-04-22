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
        std::vector<bool> getVecAllGraphesDij(int);
        std::vector<bool> getGraphPRIM(int);
        std::vector<bool> getGrapheIni();
        void CoutAllGraphes();
        int getNbAllGraphes();
        int getNbPoids();
        void optimisation();
        void optimisationDij();
        bool connexite(std::vector<bool>);
        bool connexiteDij(std::vector<bool>);
        void triCout2(int);
        void triCout3(int);

        void selectPareto();
        void affichageDijkstra(Svgfile& svgout);
        void affichagePareto(Svgfile& svgout);
        std::string calculPoidsTot(std::vector<bool>);
        float DijkstraPoint(int ,std::vector<bool> );
        void dijkstra();
        void selectDij();

    protected:

    private:
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<bool> m_grapheIni;
        std::vector<std::vector<bool>> m_allGraphes,m_allGraphesDij;
        std::vector<std::vector<bool>> m_graphPRIM;
        std::vector<std::vector<float>> m_coutAllGraphes, m_coutAllGraphesDij;
        std::vector<std::vector<float>> m_selectPareto, m_selectDij;
        int m_ordre, m_nbArete, m_nbPoids, m_nbAllGraphes, m_nbAllGraphesDij;
};

#endif
