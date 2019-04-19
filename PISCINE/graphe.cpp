
#include "graphe.h"
#include <algorithm>


graphe::graphe(std::string nomFichier, std::string nomFichierPoids){
    std::ifstream ifs{nomFichier};
    std::ifstream ifsPoids{nomFichierPoids};
    /// VERIFICATION DE L OUVERTURE FICHIER
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    if (!ifsPoids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierPoids );
    /// VERIFICATION DE L ORDRE DU GRAPHE
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    m_ordre = ordre;

    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int id_arete, id_voisin;
    int nb_arete, nb_poids;
    double poids=0;
    ifsPoids >> nb_arete; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre aretes");
    ifsPoids >> nb_poids; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture nombre poids");
    m_nbArete = nb_arete;
    m_nbPoids= nb_poids;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extr�mit�s
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        m_aretes.push_back(new Arete{id_arete,id,id_voisin});
        m_sommets[id]->ajouterVoisin(m_sommets[id_voisin]);
        m_sommets[id_voisin]->ajouterVoisin(m_sommets[id]);//remove si graphe orient�

    }

    std::cout << nb_poids;
    for(int a=0; a<nb_arete; ++a)
    {
        ifsPoids>>id_arete; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture id arete");
        for(int e=0; e<nb_poids; ++e)
        {
            ifsPoids>>poids; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture poids");
            m_aretes[id_arete]->ajouterPoids(poids);
        }
        m_grapheIni.push_back(true);
    }


}

std::vector<Arete*> graphe::triCout1(int poids, std::vector<Arete*> vecArete)
{
    std::sort(vecArete.begin(),vecArete.end(),[poids](Arete* a1, Arete* a2)
    {
        return a1->get_Cout(poids) < a2->get_Cout(poids) ;
    });
    return vecArete;
}

std::vector<bool> graphe::PRIM(int poids)
{
    /// TRIER ARRETES
    std::vector<Arete*> vecAretes = m_aretes;
    std::vector<Sommet*> vecSommets = m_sommets;
    std::vector<bool> vecPRIM;
    int fin;
    for(int i=0; i<m_nbArete; ++i)
    {
        vecPRIM.push_back(false);
    }
    vecAretes=triCout1(poids,vecAretes);
    vecPRIM[0]=true;
    vecSommets[vecAretes[0]->getS1()]->setMarque(true);
    vecSommets[vecAretes[0]->getS2()]->setMarque(true);
    for(int i = 0; i < m_ordre-1; ++i)
    {
        fin = 0;
        for(int j = 0; j < m_nbArete; ++j)
        {
            if(vecPRIM[j]==false && fin==0)
            {
                if(vecSommets[vecAretes[j]->getS1()]->getMarque()==true && vecSommets[vecAretes[j]->getS2()]->getMarque()==false)
                {
                    vecPRIM[j]=true;
                    vecSommets[vecAretes[j]->getS2()]->setMarque(true);
                    fin = 1;
                }else if(vecSommets[vecAretes[j]->getS2()]->getMarque()==true && vecSommets[vecAretes[j]->getS1()]->getMarque()==false)
                {
                    vecPRIM[j]=true;
                    vecSommets[vecAretes[j]->getS1()]->setMarque(true);
                    fin = 1;
                }
            }
        }
    }
    return vecPRIM;
}


void graphe::afficher(Svgfile& svgout, std::vector<bool> vecArete, double x, double y, std::string couleur) const
{

    double position_x=0, position_y=0, x1, x2, y1, y2;
    double dif_x=0, dif_y=0;
    std::string text;
    std::vector<float> vectCout;
    for(int a = 0; a < m_nbArete ; ++a)
    {
        if(vecArete[a]==true)
        {
            x1 = m_sommets[m_aretes[a]->getS1()]->getX()+x;
            x2 = m_sommets[m_aretes[a]->getS2()]->getX()+x;
            y1 = m_sommets[m_aretes[a]->getS1()]->getY()+y;
            y2 = m_sommets[m_aretes[a]->getS2()]->getY()+y;

            vectCout = m_aretes[a]->getCout();

            svgout.addLine(x1, y1, x2, y2, couleur);

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

            std::cout << to_string(vectCout[0]) << ";" << vectCout[1]<< "   ";
            for(int i=0; i<m_nbPoids-1; ++i)
            {
                text += to_string(vectCout[i]) + ";";
            }
            text += to_string(vectCout[m_nbPoids-1]);
            svgout.addText(position_x,position_y,text,couleur);
            text="";
        }
    }
    for( int i = 0; i < m_ordre ; ++i)
    {
        std::cout << "   sommet : ";
        m_sommets[i]->afficherData(svgout,x,y);

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
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

*/
graphe::~graphe()
{
    //dtor
}

std::vector<bool> graphe::getVecAllGraphes(int emplacement)
{
    return m_allGraphes[emplacement];
}

std::vector<bool> graphe::getGraphPRIM(int emplacement)
{
    return m_graphPRIM[emplacement];
}

std::vector<bool> graphe::getGrapheIni()
{
    return m_grapheIni;
}
void graphe::optimisation(graphe fichier)
{
    std::vector<bool> vecAretes;
    for(int i=0; i<m_nbArete; ++i)
    {
        vecAretes.push_back(false);
    }
    int puissance = 1, possib = 1;
    int compteur = 0;
    int nb = 0;
    int num = 0;
    for (int i=0; i<m_nbArete; ++i) /// on calcule le nombre de possibiltes
    {
        possib = possib*2;
        std::cout << possib << " "  << m_nbArete << " ";
    }
    for(int y = 0; y < possib; y++)
    {
        puissance = 1;
        nb = 0;
        for( auto j : vecAretes) /// pour chaque arete
        {
            if(compteur%(puissance) == 0)
            {
                j = !j;
            }

            if(j == true)
            {
                nb = nb + 1;
            }
            puissance = puissance * 2;
        }
        if(nb == m_ordre-1)
        {
            if (true == fichier.connexite(vecAretes))
            {
                m_allGraphes.push_back(vecAretes);
                num = num + 1;
                if (num%10000==0)
                {
                    std::cout << "num : "<< num << "  ";
                }
            }
        }
        compteur ++;
    }m_nbAllGraphes = num;
}

int graphe::getNbAllGraphes()
{
    return m_nbAllGraphes;
}

void graphe::eraseAllGraphes(int position)
{
    m_allGraphes.erase(m_allGraphes.begin()+position);
    m_nbAllGraphes -= 1;
}

bool graphe::connexite(std::vector<bool> vea)
{
    std::vector<bool> vecArete = vea;
    std::vector<Sommet*> vecSommets = m_sommets;
    int valide = 0;
    bool cycle=false, fin = false;
    for(auto o : vecSommets)
    {
        o->setMarque(false);
    }
    for(int i=0; i < m_nbArete; ++i)
    {
        if(vecArete[i]==true && valide ==0)
        {
            vecArete[i] = false;
            vecSommets[m_aretes[i]->getS1()]->setMarque(true);
            vecSommets[m_aretes[i]->getS2()]->setMarque(true);
            valide = 1;
        }
    }
    for(int e=0; e<m_ordre-1; e++)
    {
        for(int i=0; i < m_nbArete; ++i)
        {
            if(fin == true)
                break;
            if(vecArete[i]==true && fin == false)
            {
                if(vecSommets[m_aretes[i]->getS1()]->getMarque() == true && vecSommets[m_aretes[i]->getS2()]->getMarque() == false)
                {
                    vecSommets[m_aretes[i]->getS2()]->setMarque(true);
                    vecArete[i]=false;
                    fin = true;
                    valide ++;
                }else if(vecSommets[m_aretes[i]->getS2()]->getMarque() == true && vecSommets[m_aretes[i]->getS1()]->getMarque() == false)
                {
                    vecSommets[m_aretes[i]->getS1()]->setMarque(true);
                    vecArete[i]=false;
                    fin = true;
                    valide ++;
                }else if(vecSommets[m_aretes[i]->getS2()]->getMarque() == true && vecSommets[m_aretes[i]->getS1()]->getMarque() == true)
                {
                    cycle = true;
                    vecArete[i]=false;
                    fin = true;
                    valide ++;
                }
            }
        }
        fin = false;
    }
    if(valide != m_ordre-1 || cycle == true)
    {
        return false;
    }
    return true;
}

void graphe::CoutAllGraphes()
{
    std::vector<float> vecCout;
    for(int i=0; i< m_nbPoids;++i)
    {
        vecCout.push_back(0);
    }
    for(int i=0; i < m_nbAllGraphes; ++i)
    {
        for(int a=0; a<m_nbArete ; ++a)
        {
            if(m_allGraphes[i][a]==true)
            {
                for(int z=0; z<m_nbPoids; z++)
                {
                    vecCout[z] += m_aretes[a]->get_Cout(z);
                }
            }
        }
        m_coutAllGraphes.push_back(vecCout);
    }
}

