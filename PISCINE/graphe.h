#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"
class graphe
{
    public:

        graphe(std::string,std::string);
        ~graphe();
        void PRIM(int);
        void afficher(Svgfile& svgout) const;
        void parcoursBFS(std::string) const;
        void afficherBFS(std::string) const;
        void parcoursDFS(std::string) const;
        void afficherDFS(std::string) const;
        void verif();
        void pointPareto(Svgfile& svgout, std::string couleur) const;
        int rechercher_afficherToutesCC() const;

    protected:

    private:
        std::unordered_map<std::string,Sommet*> m_sommets;
        std::unordered_map<std::string,Arete*> m_aretes;
        int m_ordre;
};

#endif
