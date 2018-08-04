#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include "scene.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>


class Renderer
{
public:
  Renderer(Scene const& scene, unsigned w, unsigned h, std::string const& file);

  void render();
  void write(Pixel const& p);
  Color check(Color const& color) const;
  Color raytrace(Ray const& ray, unsigned depth) const;
  
  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  Scene scene;
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
