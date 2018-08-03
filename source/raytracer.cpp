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
  unsigned const image_width = 500;
  unsigned const image_height = 500;
  Scene scene{};
  scene=open_sdf_datei("beispiel.xsd");
 // scene=open_sdf_datei("beispiel.xsd");
  Renderer renderer{scene,image_width, image_height, filename};
  renderer.render();
  
  //create separate thread to see updates of pixels while rendering 创建单独的线程以在渲染时查看像素的更新
  //std::thread render_thread([&renderer]() {renderer.render();});
  //renderer.render(scene);

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
