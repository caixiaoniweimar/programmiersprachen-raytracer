#include <iostream>
#include <memory>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <color.hpp>
#include <glm/vec3.hpp>
#include <scene.hpp>
//#include <scenes/beispiel.sdf>
using namespace std;

int main(){
/*// Aufgabe 5.8
{
  cout<<"Aufgabe 5.8:"<<endl;
  Color red{255,0,0};
  glm::vec3 position{0.0f,0.0f,0.0f};
  Sphere* ss1=new Sphere{"sphere_ss1",red,position,1.2}; // im Freestore, dymnamisch
  Shape* ss2=new Sphere{"sphere_ss2",red,position,1.2}; 
  cout<<endl; 

  cout<<"cout ss1:"<<endl;
  ss1->print(cout);
  cout<<endl<<endl;

  if (nullptr != ss1) {
  	delete ss1;
    ss1 = nullptr;
  }

  cout<<"\n cout ss2:"<<endl;
  ss2->print(cout);
  cout<<endl<<endl;

  if (nullptr != ss2) {
  	delete ss2;
    ss2 = nullptr;
  }

}

  for (int i = 0; i < 3; ++i) {
  	std::cout << "\n";
  }
  std::cout << "end of test for task 5.8\n\n";
*/
  open_sdf_datei("beispiel.txt");
  return 0;
}