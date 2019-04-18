#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"


Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData(Svgfile& svgout, double x, double y) const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
     svgout.addDisk(m_x+x,m_y+y,5,"black");
     svgout.addText(m_x-17 + x,m_y-5+y,to_string(m_id),"black");
 }


int Sommet::getDegre()
{
  int nb = 0;
  for ( auto a : m_voisins)
  {
    nb ++;
  }
  return nb;
}

 int Sommet::getID()
 {
     return m_id;
 }

 double Sommet::getX()
 {
     return m_x;
 }

 double Sommet::getY()
 {
     return m_y;
 }

 bool Sommet::getMarque()
 {
     return m_marque;
 }

 void Sommet::setMarque(bool marque)
 {
     m_marque = marque;
 }

/*
std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue <const Sommet*> file;
    std::unordered_set <const Sommet*> voisinDecouvert;

    file.push(this);
    voisinDecouvert.insert(this);

    while(!file.empty())
    {
      const Sommet*s = file.front();
      file.pop();

      for(const auto &v : s->m_voisins)
      {
        if(voisinDecouvert.count(v)==0)
        {
          file.push(v);
          voisinDecouvert.insert(v);
          l_pred.insert({v->m_id,s->m_id});
        }
      }
    }
    return l_pred;
}
std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const{
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"DFS a completer"<<std::endl;
    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC() const{
    std::unordered_set<std::string> cc;
      cc.insert(m_id);
    for( auto x : m_voisins)
    {
      cc.insert(x->m_id);
    }
std::cout << std::endl;
    return cc;
}*/
Sommet::~Sommet()
{
    //dtor
}
