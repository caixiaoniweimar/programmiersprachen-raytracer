// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(Scene const& scene, unsigned w, unsigned h, std::string const& file)
  : scene(scene)
  , width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_) {}

// Beispiel render() (initiale)
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

void Renderer::render(){
  for(unsigned y=0.0; y<height_; ++y){
    for(unsigned x=0.0; x<width_; ++x){
        Pixel p(x,y);
        Ray ray= scene.camera.erzeugen_ray(x,y,width_,height_);
        p.color = raytrace(ray,10); // bestimmt depth
      write(p);
    }
  }
  ppm_.save(filename_);
}


Color Renderer::check(Color const& color) const{
  float max_wert=max(color.r,max(color.g,color.b));
  if(max_wert>1.0){
    return (color/max_wert);
  }
  else
    return color;
}

Color Renderer::raytrace(Ray const& ray, unsigned depth) const{
  Color result_Color{0,0,0};
  float t=2000;
  intersectionResult schnittpunkt = (scene.root)->istIntersect(ray,t);
  
  Color amb{0,0,0};
  if( schnittpunkt.hit ==true ){
    // rechnen I_a*K_a, rechnen nur ont Time;  I_a->ambiente(color),  k_a von Material Attribute ka
        amb = (scene.ambiente)*(schnittpunkt.closest_shape->material_->ka);
        // wenn es viele Light in scene gibt;
        for( int i=0; i< scene.container_light.size(); ++i ){
          Ray light_ray{ schnittpunkt.position, scene.container_light[i].position_ - schnittpunkt.position };
          light_ray.origin += light_ray.direction*(float)0.001; // Wichtig, dann gibt es kein Intersect mit selbst
        
          float t1=2000;
          intersectionResult ob_andere_objekt = scene.root->istIntersect(light_ray,t1);

          float light_position_x = scene.container_light[i].position_.x;
          float lightray_origin_x = light_ray.origin.x;
          float lightray_direction_x = light_ray.direction.x;
          
          float lightray_distance1 = glm::distance( scene.container_light[i].position_ , light_ray.origin );
          float lightray_distance = ( (light_position_x - lightray_origin_x)/ lightray_direction_x  ); 
          //lightray_distance1=lightrat_distance ich habe richtig verstanden

          
          glm::vec3 L = light_ray.direction;
          //glm::vec3 L1 = glm::normalize(scene.container_light[i].position_ - schnittpunkt.position); L1=L
          glm::vec3 N = schnittpunkt.normal;
          float LNdot = glm::dot(L,N);

          // kein Schatten!! wenn hit=flase, dann heisst kein Schatten, I=I_a*k_a + I_ip(k_d*dot(N,L)+k_s*dot(R,V)^m);
          // I_ip jede Licht!!! rechnen_intensitaet: brightness*light_color
          // ueberprufen ob andere objekt zwischen Lichtquelle und schnittpunkt liegt, wenn Objekt liegt, dann gibt es
          // Schatten,Farbe nur I_a*k_a
          if( ob_andere_objekt.hit==false || ob_andere_objekt.distance > lightray_distance ) {

              glm::vec3 R = glm::normalize(2 * LNdot * N-L);
              glm::vec3 V = -ray.direction;
              glm::vec3 V1 = glm::normalize( scene.camera.eye_ - schnittpunkt.position );
              // V=V1,ich habe wieder verstanden.
              float RVdot = glm::dot(R,V);

              // zuerste plus I_ip*k_d*dot(N,L)
              result_Color += ( scene.container_light[i].rechnen_intensitaet() )*( schnittpunkt.closest_shape->material_->kd ) * max( LNdot,0.0f );
              // dann plus I_ip*k_s*dot(R,V)^m
              result_Color += ( scene.container_light[i].rechnen_intensitaet() )* (schnittpunkt.closest_shape->material_->ks)*
                              pow( max(RVdot,0.0f), (schnittpunkt.closest_shape->material_)->exponente_m );
            // aus Adrian Folien Page 18!!!sehr wichtig!!! und verstanden!!
          }
        }

// reflektion von andere Objekte!!!!!!!!!
    Color ks_wert = schnittpunkt.closest_shape->material_->ks;
    if( depth>0 ){
      glm::vec3 V = ray.direction; //
      glm::vec3 V1 = glm::normalize(schnittpunkt.position-scene.camera.eye_); // V=V1
      glm::vec3 N = schnittpunkt.normal;
      float VNdot = glm::dot(N,V);
      glm::vec3 R = glm::normalize( V-2*VNdot*N );

      Ray reflektion_Ray{ schnittpunkt.position, R };
      reflektion_Ray.origin += reflektion_Ray.direction*(float)0.001;
      Color reflektion_Color = raytrace(reflektion_Ray, depth-1);

    bool ob_refraction = schnittpunkt.closest_shape->material_->refraction;
    // refraction opacity zwischen 0~1 0->Undurchsichtigkeit 1->glass
    // erzeugen ein Objekt ueberpruefen, ob Methode richtig ist.
    Color refraktion_Color{0,0,0};
    if( ob_refraction && depth>0){
      float q;
      float refrac_index = schnittpunkt.closest_shape->material_->refraction_index;
      float VNdot1 = glm::dot(N,V);
      if(VNdot1 <0){
        VNdot1 = -VNdot1;
        q=1/refrac_index;
      }
      else{
        q=refrac_index;
        N=-N;
      }
      float VNdot2 = 1-q*q*(1-VNdot1*VNdot1);
      if(VNdot2>0){
        VNdot2 = sqrt(VNdot2);
      }
      else{
        VNdot2 = 0;
      }
      glm::vec3 T = glm::normalize( q*V+(q*VNdot1-VNdot2)*N );

      Ray refraction_ray{ schnittpunkt.position, T };
      refraction_ray.origin += refraction_ray.direction*(float)0.001;

      refraktion_Color = raytrace(refraction_ray,depth-1);
    }

      result_Color+=(reflektion_Color)*(ks_wert)*0.3+(refraktion_Color);
    }
    result_Color+=amb;
// Aufgabe 7.1 Tone_mapping
    //result_Color.r=result_Color.r/(1+result_Color.r); //-> zu dunkel
    //result_Color.g=result_Color.g/(1+result_Color.g);
    //result_Color.b=result_Color.b/(1+result_Color.b);
   
    // Die Farbe sieht aus schoener.
   result_Color=check(result_Color);
    //check ob noch Color >1.0f, nein! gut
    /*if(result_Color.r>1.0f){
      cout<<"r:"<<result_Color.r<<endl;
    }
    if(result_Color.g>1.0f){
      cout<<"g:"<<result_Color.g<<endl;
    }
    if(result_Color.b>1.0f){
      cout<<"b:"<<result_Color.b<<endl;
    }*/
    result_Color.r = pow(result_Color.r, 1.2f); // 1.2f->scene.gamma
    result_Color.g = pow(result_Color.g, 1.2f);
    result_Color.b = pow(result_Color.b, 1.2f);
/* Mein Verständnis von Tone_mapping ist wie folgt:
  [0,1]->[0,255]  Die Helligkeit des Bildschirmes: pow(v,gamma), Mac gamma->1.8
*/
  }
  else{
    result_Color = scene.ambiente;
  }
  return result_Color;
}
//reflection反射,倒影 refraction折射

