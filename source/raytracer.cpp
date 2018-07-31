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
int main(int argc, char* argv[])
{
  //unsigned const image_width = 800;
  //unsigned const image_height = 600; //窗口的大小
  std::string const filename = "./checkerboard.ppm";
  unsigned const image_width = 600;
  unsigned const image_height = 600;

  Renderer renderer{image_width, image_height, filename};
  
  //create separate thread to see updates of pixels while rendering 创建单独的线程以在渲染时查看像素的更新
  //std::thread render_thread([&renderer]() {renderer.render();});

  Material red{};
  Sphere sphere1{glm::vec3{0,10,-10},5};
  Light light{"sun",{50,-40,10},{1,1,1},1};
  Camera camera{};
  Color ambiente{0.0f,0.0f,0.0f};
  //Light light{"sun",{1,1,1},{1,1,1},10};
  //Sphere sphere1{glm::vec3{0,5,-10},5.0};

  //renderer.render1(camera,sphere1);
  //renderer.render1(camera,red,sphere1,light,ambiente);
  //renderer.render1(camera,red,sphere1,light);
  Scene scene{};

  //多个物体,一盏灯
  //Sphere sphere_1{ {-2,5,-2}, 4.0 };
  //Sphere sphere_2{ {5,5,-7}, 3.0 };


  //Material material_1 { "red", {1,0,0},{1,0,0},{1,1,1},16};
  //Material material_2 { "blue",{0,0,1},{0,0,1},{1,1,1},16};
  scene=open_sdf_datei("beispiel.xsd");
  renderer.render1(scene);
  //sphere_1.material_ {material_1};
  //sphere_2.material_ {material_2};
  //vector<shared_ptr<Shape>> objekt = scene.container_objekt;
  //objekt.push_back(sphere_1);
  //cout<<sphere_1->name_<<endl;
  //scene.container_objekt.push_back(sphere_2);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  //render_thread.join();
  return 0;
}
