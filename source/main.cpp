#include <iostream>
#include <memory>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <color.hpp>
#include <glm/vec3.hpp>
#include <scene.hpp>
#include <material.hpp>
using namespace std;

// Aufgabe 6.5
bool operator < (shared_ptr<Material> const& m1, shared_ptr<Material> const& m2){
    return ( m1->name < m2->name ? true: false );
}

bool operator== (shared_ptr<Material> const& m1, shared_ptr<Material> const& m2){
    return ( m1->name == m2->name );
}

int main(){
  Scene s1;
  s1=open_sdf_datei("beispiel.xsd");
  cout<<endl;
  cout<<"Test Find:"<<endl;
// Find Methode fuer vector
  vector<shared_ptr<Material>> v1 = s1.vector_material;
  cout<<"Find Methode fuer vector:"<<endl;
  vector_find("red",v1);
  vector_find("blue",v1);
  vector_find("green",v1);

// Find Methode fuer map
  cout<<"Find Methode fuer map:"<<endl;
  map<string, shared_ptr<Material> > m1 = s1.map_material;
  map_find("red",m1);
  map_find("blue",m1);
  map_find("green",m1);

// Find Methode fuer set
  set<shared_ptr<Material>> set1=s1.set_material;
  cout<<"Find Methode fuer set:"<<endl;
  set_find("red",set1);
  set_find("blue",set1);
  set_find("green",set1);
  return 0;
}