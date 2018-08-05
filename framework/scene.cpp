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

              string name;
              Color ka,kd,ks;
              bool refraction;  
              float refraction_index;
	            float exponente_m;

              istrm>>name;
              istrm>>(ka).r;
              istrm>>(ka).g;
              istrm>>(ka).b;
              istrm>>(kd).r;
              istrm>>(kd).g;
              istrm>>(kd).b;
              istrm>>(ks).r;
              istrm>>(ks).g;
              istrm>>(ks).b;
              istrm>>(refraction);
              istrm>>(refraction_index);
              istrm>>exponente_m;
              auto c = make_shared<Material>(name,ka,kd,ks,refraction,refraction_index,exponente_m);
              (scene.vector_material).push_back(c); // vector
              (scene.set_material).insert(c);       // set        
              (scene.map_material).insert(make_pair(c->name,c)); // map 
              cout<<c->name<<" "<<(c->ka).r<<" "<<(c->ka).g<<" "<<(c->ka).b;
              cout<<" "<<(c->kd).r<<" "<<(c->kd).g<<" "<<(c->kd).b;
              cout<<" "<<(c->ks).r<<" "<<(c->ks).g<<" "<<(c->ks).b;
              cout<<" "<<c->exponente_m<<endl;           
             } // sieht aus richtig
             
             if(differ_string=="shape"){
              cout<<" shape ";
              istrm>>differ_string;
              if(differ_string=="box"){
                string box_name,material_name;
                glm::vec3 minimum_,maximum_;

                istrm>> box_name;
                istrm>> (minimum_).x;
                istrm>> (minimum_).y;
                istrm>> (minimum_).z;
                istrm>> (maximum_).x;
                istrm>> (maximum_).y;
                istrm>> (maximum_).z;
                istrm>> differ_string;
                shared_ptr<Material> material=  map_find(differ_string,scene.map_material);

                auto box_objekt = make_shared<Box>(box_name,material,minimum_,maximum_); // shared_ptr<Box>
                (scene.container_objekt).push_back(box_objekt);

                cout<<box_objekt->get_name()<<" "<<(box_objekt->get_min()).x<<" "<<(box_objekt->get_min()).y<<" "
                    <<(box_objekt->get_min()).z<<" "<<(box_objekt->get_max()).x<<" "<<(box_objekt->get_max()).y<<" "<<
                    (box_objekt->get_max()).z<<" "<<(box_objekt->get_material())->name<<endl;
              
              }
              if(differ_string=="dreieck"){
                string name;
                glm::vec3 punkt1_,punkt2_,punkt3_;

                istrm>> name;
                istrm>> (punkt1_).x;
                istrm>> (punkt1_).y;
                istrm>> (punkt1_).z;
                istrm>> (punkt2_).x;
                istrm>> (punkt2_).y;
                istrm>> (punkt2_).z;
                istrm>> (punkt3_).x;
                istrm>> (punkt3_).y;
                istrm>> (punkt3_).z;
                istrm>> differ_string;
                shared_ptr<Material> material=  map_find(differ_string,scene.map_material);

                auto dreieck_objekt = make_shared<Dreieck>(name,material,punkt1_,punkt2_,punkt3_); // shared_ptr<Box>
                (scene.container_objekt).push_back(dreieck_objekt);
                cout<<dreieck_objekt->get_name()<<" "<<(dreieck_objekt->get_punkt1()).x<<" "<<(dreieck_objekt->get_punkt1()).y<<" "
                <<(dreieck_objekt->get_punkt1()).z<<" "<<(dreieck_objekt->get_punkt2()).x<<" "<<(dreieck_objekt->get_punkt2()).y<<" "<<
                (dreieck_objekt->get_punkt2()).z<<" "<<(dreieck_objekt->get_punkt3()).x<<" "<<(dreieck_objekt->get_punkt3()).y<<" "<<
                (dreieck_objekt->get_punkt3()).z<<" "<<(dreieck_objekt->get_material())->name<<endl;
              }
             if(differ_string=="sphere"){
                string name;
                glm::vec3 mittelpunkt_;
                float radius_;

                istrm>> name;
                istrm>> (mittelpunkt_).x;
                istrm>> (mittelpunkt_).y;
                istrm>> (mittelpunkt_).z;
                istrm>> radius_;
                istrm>> differ_string;
                shared_ptr<Material> material=map_find(differ_string,scene.map_material);
                auto sphere_objekt = make_shared<Sphere>(name,material,mittelpunkt_,radius_);
               
                (scene.container_objekt).push_back(sphere_objekt);
                cout<<sphere_objekt->get_name()<<" "<<(sphere_objekt->get_mittelpunkt()).x<<" "<<(sphere_objekt->get_mittelpunkt()).y<<" "
                <<(sphere_objekt->get_mittelpunkt()).z<<" "<<sphere_objekt->get_radius()<<" "<<(sphere_objekt->get_Material())->name<<endl;
              }
            if(differ_string=="composite"){
                string composite_name;
                istrm>> composite_name;
                auto composite = make_shared<Composite>(composite_name);

                int size =scene.container_objekt.size();
                while( istrm>> differ_string ){
                    shared_ptr<Shape> shape = shape_vector_find( differ_string, scene.container_objekt );
                if( size !=0 ){
                    composite->add(shape);
                    size--;
                }
               }
                scene.root = composite;
                cout<<scene.root->get_name();

                int size2 = scene.root->composite_.size();
                for( int i=0; i< size2; ++i ){
                  shared_ptr<Shape> knoten = scene.root->composite_[i];
                  auto name = (*knoten).get_name();
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
      if(differ_string=="transform"){
        cout<<"transform ";
        string objekt_name;
        istrm>>objekt_name;
        cout<<objekt_name<<" ";
        istrm>>differ_string;
        if(differ_string=="translate"){
          cout<<"translate ";
          glm::vec3 translation_vector;
          istrm>> translation_vector.x;
          istrm>> translation_vector.y;
          istrm>> translation_vector.z;
          glm::mat4 translation_mat = translation(translation_vector);
          // Am Ende =translation_mat * vec4;
          cout<<" "<<translation_vector.x<<" "<<translation_vector.y<<" "<<translation_vector.z<<endl;
        }
        if(differ_string=="scale"){
          cout<<"scale ";
          glm::vec3 skalierung_vector;
          istrm>> skalierung_vector.x;
          istrm>> skalierung_vector.y;
          istrm>> skalierung_vector.z;
          glm::mat4 skalierung_mat = scale(skalierung_vector);

          cout<<skalierung_vector.x<<" "<<skalierung_vector.y<<" "<<skalierung_vector.z<<endl;
        }
        if(differ_string =="rotate"){
          cout<<"rotate ";
          float winkel;
          glm::vec3 rotation_vector;
          istrm>>winkel;
          istrm>>rotation_vector.x;
          istrm>>rotation_vector.y;
          istrm>>rotation_vector.z;
          glm::mat4 rotation_mat = rotation(winkel,rotation_vector);// Am Ende =rotation_mat * vec4;
          
          cout<<winkel<<" "<<rotation_vector.x<<" "<<rotation_vector.y<<" "<<rotation_vector.z<<endl;
        }
        
      }
      if(differ_string=="render"){
        istrm>>scene.width;
        istrm>>scene.height;
        istrm>>scene.filename;
        cout<<scene.width<<" "<<scene.height<<" "<<scene.filename<<endl;
      }
    }
  }
inf.close();
return scene;
}

// Aufgabe 7.5
glm::mat4 translation(glm::vec3 translation_vector){
  glm::mat4 result(0.0f);
  result[0] = glm::vec4 {1.0f,0.0f,0.0f,0.0f};
  result[1] = glm::vec4 {0.0f,1.0f,0.0f,0.0f};
  result[2] = glm::vec4 {0.0f,0.0f,1.0f,0.0f};
  result[3] = glm::vec4 {translation_vector,1.0f};
  return result;
}

glm::mat4 scale(glm::vec3 skalierung_vector){
  glm::mat4 result(0.0f);
  result[0] = glm::vec4 { skalierung_vector.x ,0.0f,0.0f,0.0f};
  result[1] = glm::vec4 {0.0f,skalierung_vector.y,0.0f,0.0f};
  result[2] = glm::vec4 {0.0f,0.0f,skalierung_vector.z,0.0f};
  result[3][3] = 1.0f;
  return result;
}

glm::mat4 rotation(float winkel, glm::vec3 rotation_vector){
  glm::mat4 result(0.0f);
  if(rotation_vector.x > 0.0f){ // Drehe die X-Achse um; Bedingung: >0.0f oder == 1.0f
    result[0][0] = 1.0f;
    result[1][1] = cos(winkel * M_PI /180);
    result[1][2] = -sin(winkel * M_PI /180);
    result[2][1] = sin(winkel * M_PI /180);
    result[2][2] = cos(winkel * M_PI /180);
    result[3][3] = 1.0f;
  }
  if(rotation_vector.y > 0.0f){  // Drehe die Y-Achse um
    result[0][0] = cos(winkel * M_PI /180);
    result[0][2] = sin(winkel * M_PI /180);
    result[1][1] = 1.0f;
    result[2][0] = -sin(winkel * M_PI /180);
    result[2][2] = cos(winkel * M_PI /180);
    result[3][3] = 1.0f;
  }
  if(rotation_vector.z > 0.0f){  // Drehe die Z-Achse um
    result[0][0] = cos(winkel * M_PI /180);
    result[0][1] = -sin(winkel * M_PI /180);
    result[1][0] = sin(winkel * M_PI /180);
    result[1][1] = cos(winkel * M_PI /180);
    result[2][2] = 1.0f;
    result[3][3] = 1.0f;
  }
  return result;
}

shared_ptr<Shape> shape_vector_find( string const& such_name, vector<shared_ptr<Shape>> container_objekt ){
  auto t = find_if(container_objekt.begin(), container_objekt.end(), 
            [&such_name](shared_ptr<Shape> const& m){ return (m->get_name())==such_name; } );
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










