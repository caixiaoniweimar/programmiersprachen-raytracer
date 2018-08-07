#include <renderer.hpp>
#include <window.hpp>
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <shape.hpp>
#include <pixel.hpp>
#include <sphere.hpp>
#include <light.hpp>
#include <material.hpp>
#include <scene.hpp>
#include <vector>
#include <fensterchen.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*void erzeugen_datei(string const& file1, string const& file2){
  ifstream in(file1); //先把文件1的内容复制到文件2;
  ofstream out(file2);
     if(in){
         string line;
         while(getline(in,line)){
             out << line << endl;
         }
     }

  ifstream inf; // 更改文件2的某个内容
  ofstream ofs(file2,ios::in|ios::out);
    inf.open(file2);  // erlaubt nicht, lesen und write zusammen
    string sline;
    string differ_string;
    while(getline(inf,sline)){
      istringstream istrm(sline);
      while(istrm>>differ_string){
        if(differ_string=="define"){
          istrm>>differ_string;
          if(differ_string=="camera"){
              istrm>>differ_string;
              istrm>>differ_string;
              float wert = atof(differ_string.c_str())+1;
              differ_string = wert;
              ofs.seekp(17,ios::beg);
              string writeStrContent = differ_string;
              const char * writeCharContent = writeStrContent.c_str();
              ofs.write(writeCharContent, writeStrContent.size());
          }
        }
      }
    }
    ofs.close();
    in.close();
    out.close();
}
 void fileCopy(string file1,string file2){
     ifstream in(file1);
     ofstream out(file2);
     if(in){
         string line;
         while(getline(in,line)){
             out << line << endl;
         }
     }
     in.close();
     out.close();
 }*/
int main(int argc, char* argv[])
{
  //std::string const filename = "./checkerboard.ppm";
  //unsigned const image_width = 500;
  //unsigned const image_height = 500;

  Scene scene{};
  scene=open_sdf_datei("beispiel.sdf");
  //system("cp" "beispiel.sdf" "beispiel2.sdf"); einfach
  //fileCopy("beispiel.sdf","beispiel1.sdf");
  Renderer renderer{scene,scene.width, scene.height, scene.filename};
  renderer.render();

  //create separate thread to see updates of pixels while rendering 创建单独的线程以在渲染时查看像素的更新
  std::thread render_thread([&renderer]() {renderer.render();});

  Window window{{scene.width, scene.height}};
  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  render_thread.join();
  return 0;
}

