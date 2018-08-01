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

// Beispiel render()
/*void Renderer::render()
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
}*/

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

void Renderer::render(Scene const& scene){
  for(unsigned y=0.0; y<height_; ++y){
      // float sy= 1.0-y*1.0/height_;       erste CameraModell, aber failed
    for(unsigned x=0.0; x<width_; ++x){

      //float sx= x*1.0/width_;
      Pixel p(x,y);
      Ray ray= scene.camera.erzeugen_ray(x,y,height_,width_);
      p.color = viel_object(scene,ray); // bestimmt depth
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace( shared_ptr<Shape> const& objekt, Scene const& scene, Ray const& ray, unsigned depth) const{
  Color result_Color{0,0,0};
  float t=1000;
  intersectionResult schnittpunkt = (scene.root)->istIntersect(ray,t);

  Color amb = (scene.ambiente)*(objekt->material_->ka); // amb nur einmal!

  if( schnittpunkt.hit ==true ){
    // rechnen Diffuse 
        for( int i=0; i< scene.container_light.size(); ++i ){
          Ray light_ray{ schnittpunkt.position, scene.container_light[i].position_ - schnittpunkt.position };

          light_ray.origin += light_ray.direction*(float)0.001; // no intersect with self

          // glm::vec3 L = light_ray.direction;
          glm::vec3 L = glm::normalize(scene.container_light[i].position_ - schnittpunkt.position);
          glm::vec3 N = schnittpunkt.normal;
          float LNdot = glm::dot(L,N);

          // here Objekt ist closet!!!!

          //wenn nicht erfolgreich, dann probieren scene.root oder scene.container_objekt
          intersectionResult ob_andere_objekt = scene.root->istIntersect(light_ray,t);
          float light_position_x = scene.container_light[i].position_.x;
          float lightray_origin_x = light_ray.origin.x;
          float lightray_direction_x = light_ray.direction.x;

          float lightray_distance1 = glm::distance( scene.container_light[i].position_ , light_ray.origin );
          float lightray_distance = ( (light_position_x - lightray_origin_x)/ lightray_direction_x  );

          if(lightray_distance1==lightray_distance){
            cout<<"Ich habe richtig verstanden."<<endl;
          }

          // kein Schatten!!
          if( !ob_andere_objekt.hit || ob_andere_objekt.distance > lightray_distance ) {
            result_Color += ( scene.container_light[i].rechnen_intensitaet() )*
                ( objekt->material_->kd ) * max( LNdot,0.0f );

              glm::vec3 R = glm::normalize(2 * LNdot * N-L);
              glm::vec3 V = -ray.direction;
              glm::vec3 V1 = glm::normalize( scene.camera.eye_ - schnittpunkt.position );
              // gucken, welche richtig ist
              if( V.x == V1.x && V.y == V1.y && V.z == V1.z ){
                cout<<"Ich habe richtig verstanden 2."<<endl;
              }
              float RVdot = glm::dot(R,V);

              result_Color += ( scene.container_light[i].rechnen_intensitaet() )*
              pow( max(RVdot,0.0f), (objekt->material_)->exponente_m );
          }
        }
// reflektion von andere Objekte!!!!!!!!!
    Color ks_wert = objekt->material_->ks;
    if( depth>0 ){
      glm::vec3 V = ray.direction; // schnittpunkt.position - cam.eye
      glm::vec3 N = schnittpunkt.normal;
      float VNdot = glm::dot(N,V);
      glm::vec3 R = glm::normalize( V-2*VNdot*N );

      Ray reflektion_Ray{ schnittpunkt.position, R };
      reflektion_Ray.origin += reflektion_Ray.direction*(float)0.001;
      Color reflektion_Color = raytrace(objekt, scene, reflektion_Ray, depth-1);
    }
      result_Color+=amb;
  }
  else{
      result_Color=amb;
  }
  return result_Color;
}
//reflection反射,倒影 refraction折射

Color Renderer::viel_object(Scene const& scene, Ray const& ray) const{
    float minDistance = 100;
    intersectionResult minResult = intersectionResult{};
    int size = scene.container_objekt.size();

    int min_object_index= -1;
           
    // for all object 
    for( int i=0; i<size; ++i ){
      float t = 2000;
      intersectionResult result = scene.container_objekt[i]->istIntersect(ray,t); // result.hit 0/1; result.t auch change; beidem funktionieren

      if( result.hit==true  &&(result.distance < minDistance) ){ // hit=1
        minDistance = result.distance;
        min_object_index=i;
      }
    }
    if(min_object_index != -1){  // index unmoeglich gleich -1 !!! das heisst, nie zurueck ambiente
      return raytrace(scene.container_objekt[min_object_index],scene,ray,3); 
    }
    else{
      return scene.ambiente; // ambiente
    }
}













