// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_) {}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

// erste Probieren, funktioniert gut, kein Licht
/*void Renderer::render1(Camera const& camera,Sphere const& sphere){
  for(unsigned y=0; y<height_; ++y){
     float sy= 1.0-y*1.0/height_;
    for(unsigned x=0; x<width_; ++x){

      float sx= x*1.0/width_;
      Pixel p(x,y);
      Ray ray= camera.erzeugen_ray(sx,sy);
      float t=2000;
      auto result = sphere.istIntersect(ray,t);
      if(result.hit==true){
        float t=min(result.distance*(255.0f/18),255.0f);  // maximal Depth
        float depth=(255.0f-t)/255.0f;
        p.color=Color(depth,depth,depth); // white
      }
      else{
        p.color=Color(0,0,0); //schwarz
      }
     write(p);
    }
  }
  ppm_.save(filename_);
}*/

// rechnen_diffuse_reflexion, benutzt nicht, nur deutliche Idee
/*Color Renderer::rechnen_diffuse_reflexion(Light const& light, Ray const& ray, Material const& material, intersectionResult const& result, Color const& ambiente) const{
        glm::vec3 L = glm::normalize(light.position_ - result.position);
        glm::vec3 N = result.normal; //glm::vec3 N = sphere.getNormal(result.position);
        float LNdot = glm::dot(L,N); // erlaubt klein 0?

        glm::vec3 R = glm::normalize(2 * LNdot * N-L);
        glm::vec3 V = glm::normalize( ray.origin - result.position );

        float RVdot = glm::dot(R,V);

        Color spiegeln = (material.ks) * (pow(std::max(RVdot,(float)0),material.exponente_m ));
        Color diffuseColor = light.rechnen_intensitaet() * (material.kd) * std::max(glm::dot(L,N),(float)0);
        Color reflexion = ambiente*(material.ka); 
        return reflexion+diffuseColor+spiegeln;
}*/

void Renderer::render1(Scene const& scene){
  for(unsigned y=0.0; y<height_; ++y){
     float sy= 1.0-y*1.0/height_;
    for(unsigned x=0.0; x<width_; ++x){

      float sx= x*1.0/width_;
      Pixel p(x,y);
      Ray ray= scene.camera.erzeugen_ray(sx,sy);
      float t=2000;
      //intersectionResult result = sphere.istIntersect(ray,t);
     // intersectionResult result = scene.Intersect(ray);

      /*if(result.hit==true){
        //p.color = rechnen_diffuse_reflexion(light,ray,material,result,ambiente);
        //p.color.check();
        //cout<<L.r<<" "<<L.g<<" "<<L.b<<" "<<(float)glm::dot(L,N)<<" "<<N.r<<" "<<N.g<<" "<<N.b<<endl;
        //cout<<p.color.r<<" "<<p.color.g<<" "<<p.color.b<<endl;
        //cout<<N1.r<<" "<<N1.g<<" "<<N1.b<<endl;

        //p.color = scene.intersect(light,result);
        auto object = scene.container_objekt;
        Color const& ambiente{0,0,0};
        for( int i=0; i< object.size(); ++i ){
             p.color = scene.viel_object_intersect(ray);
        }
      }
      else{
        p.color = {0,0,0};
      }*/
        p.color = scene.viel_object_intersect(ray);
     write(p);
    }
  }
  ppm_.save(filename_);
}














