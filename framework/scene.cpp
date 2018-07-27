#include "scene.hpp"
#include <vector>
#include <set>
#include <map>
using namespace std;
// Aufgabe 6.5
Scene open_sdf_datei(string const& filename){
  Scene scene; // 重要
  ifstream inf;
  inf.open(filename);
  string sline;
  string differ_string;
  if(!inf){
    cerr<<"open failed"<<endl;
  }
  while(getline(inf,sline)){
    istringstream istrm(sline);
    while(istrm>>differ_string){
      if(differ_string=="#")
           {break;}
      if(differ_string=="define"){
             cout<<"define";
             istrm>>differ_string;
             if(differ_string=="material"){
              cout<<" material"<<endl;
              auto c = make_shared<Material>(); // shared_ptr<Material> c
              istrm>>c->name;
              istrm>>(c->ka).r;
              istrm>>(c->ka).g;
              istrm>>(c->ka).b;

              istrm>>(c->kd).r;
              istrm>>(c->kd).g;
              istrm>>(c->kd).b;

              istrm>>(c->ks).r;
              istrm>>(c->ks).g;
              istrm>>(c->ks).b;

              istrm>>c->exponente_m;
              cout<<c->name<<" "<<(c->ka).r<<" "<<(c->ka).g<<" "<<(c->ka).b;
              cout<<" "<<(c->kd).r<<" "<<(c->kd).g<<" "<<(c->kd).b;
              cout<<" "<<(c->ks).r<<" "<<(c->ks).g<<" "<<(c->ks).b;
              cout<<" "<<c->exponente_m<<endl;

              (scene.vector_material).push_back(c); // vector
              (scene.set_material).insert(c);       // set        
              (scene.map_material).insert(make_pair(c->name,c)); // map              
             }
// Aufgabe 7.2 Datei SDF shape lesen
             if(differ_string=="shape"){
              cout<<" shape" <<endl;
              istrm>>differ_string;
              if(differ_string=="box"){
                auto box_objekt = make_shared<Box>(); // shared_ptr<Box>
          
                box_objekt->set_name(differ_string);
                string name_box=box_objekt->get_name();
                istrm>> name_box;

                istrm>> (box_objekt->minimum_).x;
                istrm>> (box_objekt->minimum_).y;
                istrm>> (box_objekt->minimum_).z;
                istrm>> (box_objekt->maximum_).x;
                istrm>> (box_objekt->maximum_).y;
                istrm>> (box_objekt->maximum_).z;
                istrm>> differ_string;
                box_objekt->material_=  map_find(differ_string,scene.map_material);

                (scene.container_objekt).push_back(box_objekt);

                cout<<box_objekt->get_name()<<" "<<(box_objekt->minimum_).x<<" "<<(box_objekt->minimum_).y<<" "
                    <<(box_objekt->minimum_).z<<" "<<(box_objekt->maximum_).x<<" "<<(box_objekt->maximum_).y<<" "<<
                    (box_objekt->maximum_).z<<" "<<(box_objekt->material_)->name<<endl;
               // (scene.composite_objekt).add(box_objekt);
              }
             if(differ_string=="sphere"){
                auto sphere_objekt = make_shared<Sphere>();

                sphere_objekt->set_name(differ_string);
                string name_sphere=sphere_objekt->get_name();
                istrm>> name_sphere;

                istrm>> (sphere_objekt->mittelpunkt_).x;
                istrm>> (sphere_objekt->mittelpunkt_).y;
                istrm>> (sphere_objekt->mittelpunkt_).z;
                istrm>> sphere_objekt->radius_;
              
                istrm>> differ_string;
                sphere_objekt->material_=map_find(differ_string,scene.map_material);
                (scene.container_objekt).push_back(sphere_objekt);

                cout<<sphere_objekt->get_name()<<" "<<(sphere_objekt->mittelpunkt_).x<<" "<<(sphere_objekt->mittelpunkt_).y<<" "
                <<(sphere_objekt->mittelpunkt_).z<<" "<<sphere_objekt->radius_<<" "<<(sphere_objekt->material_)->name<<endl;
               
               // (scene.composite_objekt).add(sphere_objekt);
              }
// Aufgabe 7.2 unsicher 先不要做
             /* if(differ_string=="composite"){
                // 也就是意味着 读SDF的时候 我需要知道我加入的对象的类型和名字？且顺序,不可以是shape
                   istrm>>(scene.composite_objekt).name_;

                   auto objekt = make_shared<Box> ();
                   istrm>> objekt->name_;
                   (scene.composite_objekt).add(objekt);

                   auto objekt1 = make_shared<Sphere> ();
                   istrm>> objekt1->name_;
                   (scene.composite_objekt).add(objekt1);  

                   cout<<(scene.composite_objekt).composite_.front()->name_<<endl; 
              }*/

             }
    }
  }
}
inf.close();
return scene;
}
// Aufgabe 6.5 Find-Methode fuer vector!!!!!
material_ptr vector_find(string const& such_name, vector<material_ptr> vector_material){
  auto t = find_if( vector_material.begin(), vector_material.end(), 
           [&such_name](shared_ptr<Material> const& m){ return (m->name)==such_name; } ); //Lamdas
 if( t!=vector_material.end() ){
    //cout<<"Find it!"<<endl;
    //cout<< *(*t)<<endl; //!!!!!超级重要！！！！！
    return *t;
  }
  else{
     //cout<<"Find it not."<<endl;
     return nullptr;
  }
}

// Aufgabe 6.5 Find-Methode fuer Map!!!!
material_ptr map_find(string const& such_name, map<string, shared_ptr<Material> > map_material){
  auto it = map_material.find(such_name);
  if( it != map_material.end() )
  {
    //cout<<"Find it!"<<endl;
    //cout<<*(it->second)<<endl;
    return it->second;
  }
 else{
    //cout<<"Find it not."<<endl;
    return nullptr;
  }
}

// Aufgabe 6.5 Find-Methode fuer Set!!!!
material_ptr set_find(string const& such_name, set< shared_ptr<Material> > set_material){
  auto t = find_if( set_material.begin(), set_material.end(), 
           [&such_name](shared_ptr<Material> const& m){ return (m->name)==such_name; } ); //Lamdas
 if( t!=set_material.end() ){
    cout<<"Find it!"<<endl;
    cout<< *(*t)<<endl; //!!!!!超级重要！！！！！
    return *t;
  }
  else{
     cout<<"Find it not."<<endl;
     return nullptr;
  }
}
