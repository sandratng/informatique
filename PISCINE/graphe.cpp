
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

std::string graphe::calculPoidsTot(std::vector<bool> vecArete)
{
    std::vector<float> vecPoids;
    std::string text;
    for(int i=0; i<m_nbPoids; ++i)
    {
        vecPoids.push_back(0);
    }
    for(int i=0; i<m_nbArete; ++i)
    {
        if(vecArete[i]==true)
        {
            for(int j=0; j<m_nbPoids;++j)
            {
                vecPoids[j] += m_aretes[i]->get_Cout(j);
            }
        }
    }
    text = "(";
    for(int i=0; i<m_nbPoids-1;i++)
    {
        text += to_string(vecPoids[i]) + ";";
    }
    text += to_string(vecPoids[m_nbPoids-1]) + ")";
    return text;
}

std::vector<bool> graphe::PRIM(int poids)
{
    /// TRIER ARRETES
    std::vector<Arete*> vecAretes = m_aretes;
    std::vector<Sommet*> vecSommets = m_sommets;
    std::vector<bool> vecPRIM;
    int fin;
    for(int i=0; i<m_ordre;i++)
    {
        vecSommets[i]->setMarque(false);
    }
    for(int i=0; i<m_nbArete; ++i)
    {
        vecPRIM.push_back(false);
    }
    vecAretes=triCout1(poids,vecAretes);
    vecPRIM[vecAretes[0]->getID()]=true;
    vecSommets[vecAretes[0]->getS1()]->setMarque(true);
    vecSommets[vecAretes[0]->getS2()]->setMarque(true);
    for(int i = 0; i < m_ordre-1; ++i)
    {
        fin = 0;
        for(int j = 0; j < m_nbArete; ++j)
        {
            if(fin == 1)
                break;
            if(vecPRIM[vecAretes[j]->getID()]==false)
            {
                if(vecSommets[vecAretes[j]->getS1()]->getMarque()==true && vecSommets[vecAretes[j]->getS2()]->getMarque()==false)
                {
                    vecPRIM[vecAretes[j]->getID()]=true;
                    vecSommets[vecAretes[j]->getS2()]->setMarque(true);
                    fin = 1;
                }else if(vecSommets[vecAretes[j]->getS2()]->getMarque()==true && vecSommets[vecAretes[j]->getS1()]->getMarque()==false)
                {
                    vecPRIM[vecAretes[j]->getID()]=true;
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

        m_sommets[i]->afficherData(svgout,x,y);


    }

}

graphe::~graphe()
{
    //dtor
}

std::vector<bool> graphe::getVecAllGraphes(int emplacement)
{
    return m_allGraphes[emplacement];
}
std::vector<bool> graphe::getVecAllGraphesDij(int emplacement)
{
    return m_allGraphesDij[emplacement];
}

std::vector<bool> graphe::getGraphPRIM(int emplacement)
{
    return m_graphPRIM[emplacement];
}

std::vector<bool> graphe::getGrapheIni()
{
    return m_grapheIni;
}

int graphe::getNbPoids()
{
    return m_nbPoids;
}

void graphe::optimisation()
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
            if(true == connexite(vecAretes))
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

void graphe::optimisationDij()
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
        //std::cout << possib << " "  << m_nbArete << " ";
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

        if(nb >= m_ordre-1)
        {
            if(true == connexiteDij(vecAretes))
            {
                m_allGraphesDij.push_back(vecAretes);
                num = num + 1;
                if (num%10000==0)
                {
                    std::cout << "num : "<< num << "  ";
                }
            }
        }
        compteur ++;
    }m_nbAllGraphesDij = num;
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
    int valide = 0, cpt=0;
    bool fin = false;
    for(auto o : vecSommets)
    {
        o->setMarque(false);
    }
    for(int i=0; i < m_nbArete; ++i)
    {
        if(vecArete[i]==true)
        {
            cpt++;
            if(valide ==0)
            {
                vecArete[i] = false;
                vecSommets[m_aretes[i]->getS1()]->setMarque(true);
                vecSommets[m_aretes[i]->getS2()]->setMarque(true);
                valide = 1;
            }
        }
    }
    for(int e=0; e<cpt; e++)
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
                }
            }
        }
        fin = false;
    }
    if(valide != cpt)
    {
        return false;
    }
    return true;
}

bool graphe::connexiteDij(std::vector<bool> vea)
{
    std::vector<bool> vecArete = vea;
    std::vector<Sommet*> vecSommets = m_sommets;
    int valide = 0, cpt=0;
    bool fin = false;
    for(auto o : vecSommets)
    {
        o->setMarque(false);
    }
    for(int i=0; i < m_nbArete; ++i)
    {
        if(vecArete[i]==true)
        {
            cpt++;
            if(valide ==0)
            {
                vecArete[i] = false;
                vecSommets[m_aretes[i]->getS1()]->setMarque(true);
                vecSommets[m_aretes[i]->getS2()]->setMarque(true);
                valide = 2;
            }
        }
    }
    for(int e=0; e<cpt; e++)
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
                    fin = true;
                    vecArete[i]=false;
                }
            }
        }
        fin = false;
    }
    if(valide != m_ordre)
    {
        return false;
    }
    return true;
}

void graphe::CoutAllGraphes()
{
    std::vector<float> vecCout;
    for(int i=0; i< m_nbPoids+1;++i)
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
        vecCout[m_nbPoids]= i;
        m_coutAllGraphes.push_back(vecCout);
        for(size_t i=0; i<vecCout.size(); i++)
        {
            vecCout[i] = 0;
        }
    }
}

void graphe::triCout2(int poids)
{
    std::sort(m_coutAllGraphes.begin(),m_coutAllGraphes.end(),[poids](std::vector<float> a1, std::vector<float> a2)
    {
        return a1[poids] < a2[poids];
    });
}
void graphe::triCout3(int poids)
{
    std::sort(m_coutAllGraphesDij.begin(),m_coutAllGraphesDij.end(),[poids](std::vector<float> a1, std::vector<float> a2)
    {
        return a1[poids] < a2[poids];
    });
}
void graphe::selectPareto()
{
    m_selectPareto.push_back(m_coutAllGraphes[0]);
    float poidsMAx = m_coutAllGraphes[0][0];
    for(int i=1; i < m_nbAllGraphes; ++i)
    {
        if(m_coutAllGraphes[i][0] < poidsMAx)
        {
            poidsMAx = m_coutAllGraphes[i][0];
            m_selectPareto.push_back(m_coutAllGraphes[i]);

        }
    }
}

void graphe::affichagePareto(Svgfile& svgout)
{
    std::string text;
    svgout.addGrid(10);
    for(int i=0; i<m_nbAllGraphes; i++)
    {
        svgout.addDisk(m_coutAllGraphes[i][0]*10, 800 - m_coutAllGraphes[i][1]*10, 3, "red");
    }
    for(size_t i=0; i< m_selectPareto.size(); i++)
    {
        text = "(";
        Svgfile svgal{"output" + to_string(i) +".svg"};
        for(int j=0; j< m_nbPoids-1; j++)
        {
            text += to_string(m_selectPareto[i][j]) + ";";
        }
        text += to_string(m_selectPareto[i][m_nbPoids-1]) + ")" ;
        svgal.addText(50,50,text,"black");
        afficher(svgal,getVecAllGraphes(m_selectPareto[i][m_nbPoids]), 0, 0,"black");
        svgout.addDiskC(m_selectPareto[i][0]*10, 800 - m_selectPareto[i][1]*10, 3, "output" + to_string(i) +".svg", "green");
    }
}

float graphe::DijkstraPoint(int pointDebut, std::vector<bool> vecArete)
{
    std::vector<int> vecPointDecouvert;
    int pointMarque, cpt = 0, pointActuel, pointPrec, ok = 0;
    std::vector<Sommet*> vecSommets = m_sommets;
    std::vector<float> vecPoids;
    float poids, poidsTotale = 0;

    for(int i = 0; i < m_ordre; ++i)
        vecSommets[i]->setMarque(false);

    vecSommets[pointDebut]->setPoids(0);
    pointMarque = pointDebut;
    vecSommets[pointDebut]->setMarque(true);
    cpt++;
    while(cpt != m_ordre)
    {
        for(int i =0; i<m_nbArete; ++i)
        {
            if(vecArete[i] == true && ((pointMarque == m_aretes[i]->getS1())||(m_aretes[i]->getS2()==pointMarque)) && vecSommets[m_aretes[i]->getS1()]->getMarque()!= vecSommets[m_aretes[i]->getS2()]->getMarque())
            {
                if (vecSommets[m_aretes[i]->getS1()]->getMarque()== true && vecSommets[m_aretes[i]->getS2()]->getMarque()== false)
                {
                    pointActuel = m_aretes[i]->getS2();
                    pointPrec = m_aretes[i]->getS1();
                }
                if (vecSommets[m_aretes[i]->getS1()]->getMarque()== false && vecSommets[m_aretes[i]->getS2()]->getMarque()== true)
                {
                    pointActuel = m_aretes[i]->getS1();
                    pointPrec = m_aretes[i]->getS2();
                }
                poids = vecSommets[pointPrec]->getPoids() + m_aretes[i]->get_Cout(1);
                for(size_t j = 0; j< vecPointDecouvert.size(); ++j)
                {
                    if(vecPointDecouvert[j]==pointActuel)
                    {
                        if(poids<vecSommets[pointActuel]->getPoids())
                            vecSommets[pointActuel]->setPoids(poids);
                        ok = 1;
                    }
                }
                if(ok == 0)
                {
                    vecPointDecouvert.push_back(pointActuel);
                    vecSommets[pointActuel]->setPoids(poids);
                }
                ok = 0;
            }
        }
        for(size_t j=0; j<vecPointDecouvert.size(); ++j)
        {
            vecPoids.push_back(vecSommets[vecPointDecouvert[j]]->getPoids());
        }
        std::sort(vecPoids.begin(),vecPoids.end(),[](float a1, float a2)
        {
            return a1 < a2 ;
        });
        for(int j=0; j< m_ordre; ++j)
        {
            if(vecSommets[j]->getPoids() == vecPoids[0] && vecSommets[j]->getMarque() == false)
            {
                pointMarque = j;
                vecSommets[j]->setMarque(true);
                for(size_t e =0; e<vecPointDecouvert.size(); ++e)
                {
                    if(vecPointDecouvert[e] == j)
                    {
                        vecPointDecouvert.erase(vecPointDecouvert.begin()+e);
                    }
                }
                cpt++;
                break;
            }
        }
        vecPoids.clear();
    }

    for(int i = 0 ; i<m_ordre;++i)
    {
        poidsTotale += vecSommets[i]->getPoids();
    }
    return poidsTotale;
}


void graphe::dijkstra()
{
    std::vector<float> vecCout;
    float poids;
    for(int i=0; i< m_nbPoids+1;++i)
    {
        vecCout.push_back(0);
    }
    for(size_t i = 0; i< m_allGraphesDij.size(); ++i)
    {
        for(int a=0; a<m_nbArete ; ++a)
        {
            if(m_allGraphesDij[i][a]==true)
            {
                for(int z=0; z<m_nbPoids; z++)
                {
                    vecCout[z] += m_aretes[a]->get_Cout(z);
                }
            }
        }

        poids = 0;
        for(int j = 0; j<m_ordre; j++)
        {
            poids += DijkstraPoint(j, m_allGraphesDij[i]);
        }
        vecCout[m_nbPoids]= i;
        vecCout[1] = poids;
        m_coutAllGraphesDij.push_back(vecCout);
        for(size_t i=0; i<vecCout.size(); i++)
        {
            vecCout[i] = 0;
        }
    }
}

void graphe::selectDij()
{
    m_selectDij.push_back(m_coutAllGraphesDij[0]);
    float poidsMAx = m_coutAllGraphesDij[0][0];
    for(size_t i=1; i < m_coutAllGraphesDij.size(); ++i)
    {
        if(m_coutAllGraphesDij[i][0] < poidsMAx)
        {
            poidsMAx = m_coutAllGraphesDij[i][0];
            m_selectDij.push_back(m_coutAllGraphesDij[i]);
            //std::cout << "dedad" << m_coutAllGraphesDij[i][m_nbPoids];
        }
    }
}


void graphe::affichageDijkstra(Svgfile& svgout)
{
    std::string text;
    svgout.addGrid(20,35,true,"lightgrey");
    for(size_t i=0; i<m_allGraphesDij.size(); i++)
    {
        svgout.addDisk(m_coutAllGraphesDij[i][0]*5, 800 - m_coutAllGraphesDij[i][1]*0.143, 3, "red");
    }
    for(size_t i=0; i< m_selectDij.size(); i++)
    {
        text = "(";
        Svgfile svgal{"dij" + to_string(i) +".svg"};
        for(int j=0; j< m_nbPoids-1; j++)
        {
            text += to_string(m_selectDij[i][j]) + ";";
        }
        text += to_string(m_selectDij[i][m_nbPoids-1]) + ")" ;
        svgal.addText(50,50,text,"black");
        afficher(svgal,getVecAllGraphesDij(m_selectDij[i][m_nbPoids]), 0, 0, "black");
        svgout.addDiskC(m_selectDij[i][0]*5, 800 - m_selectDij[i][1]*0.143, 3, "dij" + to_string(i) +".svg","green");
    }
}

