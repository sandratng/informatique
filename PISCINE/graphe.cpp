#include <fstream>
#include <iostream>
#include <sstream>
#include "graphe.h"

template <typename T>
std::string to_string(T const& value) {
    std::stringstream sstr;
    sstr << value;
    return sstr.str();
}

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
    m_ordre = ordre;
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
    int nb_arete, nb_poids;
    double poids=0;
    ifsPoids >> nb_arete; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre aretes");
    ifsPoids >> nb_poids; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre poids");
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extr�mit�s
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        m_aretes.insert({id_arete, new Arete{id_arete,id,id_voisin,nb_poids,nb_arete}});
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�
    }

    std::cout << nb_poids;
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


void graphe::PRIM(int poids)
{
    /// TRIER ARRETES
    std::vector<Arete*> vecArete;
    for(int i=0; i<m_aretes.find(0)->second->getNbArete(); ++i)
    {
        vecArete.push_back(m_aretes.find(to_string(i))->second);
    }




    /*int ordre = m_ordre - 1;
    std::unordered_map<std::string,Sommet*> sommets = m_sommets;
    std::string sAct = "0", sPrec= "R";

    for(int i=0; i<ordre; i++)
    {
        for(int e=0; e<m_ordre; ++e)
        {
            if(m_aretes[e]->second->getS1() == sAct || m_aretes[e]->second->getS1() == sPrec)
            {

            }
        }
    }*/
}

void graphe::afficher(Svgfile& svgout) const{
  int compteur = 0;
  int cpt_arete = 0;
  for (auto x : m_sommets)
  {
      compteur++;
  }

  for (auto a : m_aretes)
  {
      cpt_arete++;
  }
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"   ordre : "<< compteur << std::endl;
    std::cout<<"   nombre d'arete : "<< cpt_arete << std::endl;

    for( auto x = m_sommets.begin(); x != m_sommets.end(); ++x)
    {
        std::cout << "   sommet : ";
        x->second->afficherData(svgout);

        std::cout << std::endl;
    }
    int nb_poids=0;
    double position_x=0, position_y=0, x1, x2, y1, y2;
    double dif_x=0, dif_y=0;
    std::string text;
    std::vector<double> vectArete;
    for(auto a = m_aretes.begin(); a != m_aretes.end(); ++a)
    {
        x1 = m_sommets.find(a->second->getS1())->second->getX();
        x2 = m_sommets.find(a->second->getS2())->second->getX();
        y1 = m_sommets.find(a->second->getS1())->second->getY();
        y2 = m_sommets.find(a->second->getS2())->second->getY();
        vectArete = a->second->getVector();
        nb_poids = a ->second -> getNbPoids();

        svgout.addLine(x1, y1, x2, y2, "black");

        if(x1==x2)
        {
            dif_x=0;
            position_x = x1;
        }
        else if(x1<x2)
        {
            position_x = x1;
            dif_x = x2-x1;
        }else
        {
            position_x = x2;
            dif_x = x1-x2;
        }


        if(y1==y2)
        {
            dif_y=0;
            position_y = y1;
        }
        else if(y1<y2)
        {
            position_y = y1;
            dif_y = y2-y1;
        }else
        {
            position_y = y2;
            dif_y = y1-y2;
        }
        dif_x = dif_x/2;
        position_x += dif_x;

        dif_y = dif_y/2;
        position_y += dif_y;
        std::cout << x1 << " " << x2 << ";";
        if(x1==x2)
        {
            position_x += 5;
        }
        if(y1==y2)
        {
            position_y -= 5;
        }
        if(y1!=y2 && x1!=x2)
        {
            position_x += 5;
            position_y += 5;
        }

        std::cout << to_string(vectArete[0]) << ";" << vectArete[1]<< "   ";
        for(int i=0; i<nb_poids-1; ++i)
        {
            text += to_string(vectArete[i]) + ";";
        }
        text += to_string(vectArete[nb_poids-1]);
        svgout.addText(position_x,position_y,text,"black");
        text="";
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
/*
void graphe::verif()
{
    int puissance = 1, possib = 1;
    int compteur = 0;
    int nb = 0;
    bool sommets[m_ordre];

    for ( auto k : m_aretes) /// on calcule le nombre de possibiltes
    {
        possib = possib*2;
    }
    for(int i = 0; i < possib; i++)
    {
        for( auto j : m_aretes) /// pour chaque arete
        {
            puissance *= 2;
            if(compteur%puissance == 0)
            {
                j.second->changeMarque();
            }
            if(j.second->getMarque == 1)
            {
                nb += 1;
              //  S1 = m_aretes[j]->second->getS1();
              //  S2 = m_aretes[j]->second->getS2();
              //  m_sommets[S1]->second->changeMarque();
              //  m_sommets[S2]->second->changeMarque();

            }
        }
        if(nb == m_ordre-1)
        {
            /// on retient la possibilitée si le nombre d'arrete est celui de l'ordre du graphe moins 1
            /// on ajoute un nouveau graphe en fonciton de ces aretes
            new Graph = nouveau;

        }
        compteur ++;
    }
}
*/
void graphe::pointPareto(Svgfile& svgout, std::string couleur) const
{
    std::vector<double> poids;
    int poidsTot1= 0, poidsTot2= 0;

    for( auto i : m_aretes)
    {
        poids = i.second->getVector();
        poidsTot1 = poidsTot1 + poids[0];
        poidsTot2 = poidsTot2 + poids[1];
    }
    svgout.addDisk(poidsTot1+500,poidsTot2,5,couleur);

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
