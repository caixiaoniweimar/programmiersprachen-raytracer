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
              auto c = make_shared<Material>();
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
    cout<<"Find it!"<<endl;
    cout<< *(*t)<<endl; //!!!!!超级重要！！！！！
    return *t;
  }
  else{
     cout<<"Find it not."<<endl;
     return nullptr;
  }
}

// Aufgabe 6.5 Find-Methode fuer Map!!!!
material_ptr map_find(string const& such_name, map<string, shared_ptr<Material> > map_material){
  auto it = map_material.find(such_name);
  if( it != map_material.end() )
  {
    cout<<"Find it!"<<endl;
    cout<<*(it->second)<<endl;
    return it->second;
  }
 else{
    cout<<"Find it not."<<endl;
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
  // Fuer Geometry
  /*Box b;
  string box_name = b.name_;
  float  min_x= (b.minimum_).x;
  float  min_y= (b.minimum_).y;
  float  min_z= (b.minimum_).z;

  float  max_x= (b.maximum_).x;
  float  max_y= (b.maximum_).y;
  float  max_z= (b.maximum_).z;*/
/*if(differ_string=="shape"){
              cout<<" shape"<<endl;
              istrm>>differ_string;
              if(differ_string=="box"){
                istrm>>box_name;
                istrm>>min_x;
                istrm>>min_y;
                istrm>>min_z;
                istrm>>max_x;
                istrm>>max_y;
                istrm>>max_z;
                //istrm>>c;
                //cout<<box_name<<" "<<min_x<<" "<<min_y<<" "<<min_z<<" "<<max_x<<" "<<max_y<<" "<<max_z<<" "
              }
             }
             if(differ_string=="light"){
              cout<<" light"<<endl;
             }
             if(differ_string=="camera"){
              cout<<" camera"<<endl;
             }
        }
        if(differ_string=="render"){
          cout<<"render"<<endl;
        }*/