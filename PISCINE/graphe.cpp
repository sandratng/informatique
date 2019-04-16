#include <fstream>
#include <iostream>
#include "graphe.h"

graphe::graphe(std::string nomFichier, std::string nomFichierPoids){
    std::ifstream ifs{nomFichier};
    std::ifstream ifsPoids{nomFichierPoids};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    if (!ifsPoids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierPoids );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_arete;
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extr�mit�s
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        m_aretes.insert({id_arete, new Arete{id_arete,id,id_voisin}});
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�
    }
    int nb_arete, nb_poids;
    double poids;
    ifsPoids >> nb_arete; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre aretes");
    ifsPoids >> nb_poids; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre poids");

    for(int a=0; a<nb_arete; ++a)
    {
        ifsPoids>>id_arete; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture id arete");
        for(int e=0; e<nb_poids; ++e)
        {
            ifsPoids>>poids; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture poids");
            (m_aretes.find(id_arete))->second->ajouterPoids(poids);
        }
    }

}
void graphe::afficher() const{
  int compteur = 0;
  for (auto x : m_sommets)
  {
      compteur++;
  }
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"   ordre : "<< compteur << std::endl;
    for( auto x = m_sommets.begin(); x != m_sommets.end(); ++x)
    {
      std::cout << "   sommet : ";
      x->second->afficherData();
      x->second->afficherVoisins();

     std::cout << std::endl;
      }

     std::cout << std::endl;
}

void graphe::parcoursBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}

int graphe::rechercher_afficherToutesCC() const{
    int nb =1;
    std::unordered_set<std::string> map;
    std::cout<<"composantes connexes :"<<std::endl;
    for( auto x : m_sommets)
    {
map = x.second->rechercherCC();
std::cout << "cc" << nb << std::endl;
   for( auto y : map)
   {
      std::cout << y << "   ";
   }
  }
std::cout << std::endl;
return nb;
}


graphe::~graphe()
{
    //dtor
}
