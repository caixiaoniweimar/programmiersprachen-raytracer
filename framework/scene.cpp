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
              cout<<" material ";
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

              istrm>>(c->refraction);
              istrm>>(c->refraction_index);
              istrm>>c->exponente_m;

              (scene.vector_material).push_back(c); // vector
              (scene.set_material).insert(c);       // set        
              (scene.map_material).insert(make_pair(c->name,c)); // map 
              cout<<c->name<<" "<<(c->ka).r<<" "<<(c->ka).g<<" "<<(c->ka).b;
              cout<<" "<<(c->kd).r<<" "<<(c->kd).g<<" "<<(c->kd).b;
              cout<<" "<<(c->ks).r<<" "<<(c->ks).g<<" "<<(c->ks).b;
              cout<<" "<<c->exponente_m<<endl;           
             }
             
// Aufgabe 7.2 Datei SDF shape lesen
             if(differ_string=="shape"){
              cout<<" shape ";
              istrm>>differ_string;
              if(differ_string=="box"){
                auto box_objekt = make_shared<Box>(); // shared_ptr<Box>
          
                istrm>> box_objekt->name_;

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
              
              }
             if(differ_string=="sphere"){
                auto sphere_objekt = make_shared<Sphere>();

                istrm>> sphere_objekt->name_;

                istrm>> (sphere_objekt->mittelpunkt_).x;
                istrm>> (sphere_objekt->mittelpunkt_).y;
                istrm>> (sphere_objekt->mittelpunkt_).z;
                istrm>> sphere_objekt->radius_;
              
                istrm>> differ_string;
                sphere_objekt->material_=map_find(differ_string,scene.map_material);
                (scene.container_objekt).push_back(sphere_objekt);

                cout<<sphere_objekt->get_name()<<" "<<(sphere_objekt->mittelpunkt_).x<<" "<<(sphere_objekt->mittelpunkt_).y<<" "
                <<(sphere_objekt->mittelpunkt_).z<<" "<<sphere_objekt->radius_<<" "<<(sphere_objekt->material_)->name<<endl;
              }
            if(differ_string=="composite"){

                //string composite_name;
                //istrm>> composite_name;
                //auto composite = make_shared<Composite>(composite_name);
                auto composite = make_shared<Composite>();
                istrm>> composite->name_;

                int size =scene.container_objekt.size();
          
                while( istrm>> differ_string ){
                    shared_ptr<Shape> shape = shape_vector_find( differ_string, scene.container_objekt );
                if( size !=0 ){
                    composite->add(shape);
                    size--;
                }
               }
                scene.root = composite;
                cout<<scene.root->name_;

                int size2 = scene.root->composite_.size();
                for( int i=0; i< size2; ++i ){
                  shared_ptr<Shape> knoten = scene.root->composite_[i];
                  auto name = (*knoten).name_;
                  cout<<" "<<name;
                }
                cout<<endl;
            }

             }
      if(differ_string=="light"){
                Light light{};
                istrm >> light.name_;
                istrm >> light.position_.x;
                istrm >> light.position_.y;
                istrm >> light.position_.z;
                istrm >> light.color_.r;
                istrm >> light.color_.g;
                istrm >> light.color_.b;
                istrm >> light.brightness_;
                (scene.container_light).push_back(light);
                cout<<" "<<light.name_<<" "<<light.position_.x<<" "<<light.position_.y<<" "<<
                    light.position_.z<<" "<<light.color_.r<<" "<<light.color_.g<<" "
                    <<light.color_.b<<" "<<light.brightness_<<endl;
            }
      if(differ_string=="camera"){  //camera kein Problem
                istrm>> (scene.camera).name_;
                istrm>> (scene.camera).fov_x_;
                istrm>> (scene.camera).eye_.x;
                istrm>> (scene.camera).eye_.y;
                istrm>> (scene.camera).eye_.z;
                istrm>> (scene.camera).dir_.x;
                istrm>> (scene.camera).dir_.y;
                istrm>> (scene.camera).dir_.z;
                istrm>> (scene.camera).up_.x;
                istrm>> (scene.camera).up_.y;
                istrm>> (scene.camera).up_.z;
                cout<<" "<<(scene.camera).name_<<" "<<(scene.camera).fov_x_<<" "<<(scene.camera).eye_.x<<
                " "<<(scene.camera).eye_.y<<" "<<(scene.camera).eye_.z<<" "<<(scene.camera).dir_.x<<
                " "<<(scene.camera).dir_.y<<" "<<(scene.camera).dir_.z<<" "<<(scene.camera).up_.x<<" "
                <<(scene.camera).up_.y<<" "<<(scene.camera).up_.z<<endl;     
        }  
      }
      if(differ_string=="ambient"){
          istrm>>scene.ambiente.r;
          istrm>>scene.ambiente.g;
          istrm>>scene.ambiente.b;
          cout<<"ambiente: "<<scene.ambiente.r<<" "<<scene.ambiente.g<<" "<<scene.ambiente.b<<endl;
      }

    }
  }
inf.close();
return scene;
}

shared_ptr<Shape> shape_vector_find( string const& such_name, vector<shared_ptr<Shape>> container_objekt ){
  auto t = find_if(container_objekt.begin(), container_objekt.end(), 
            [&such_name](shared_ptr<Shape> const& m){ return (m->name_)==such_name; } );
  if( t!=container_objekt.end() ){
    return *t;
  }
  else{
    return nullptr;
  }
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




