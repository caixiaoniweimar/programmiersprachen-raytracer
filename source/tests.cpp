#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <color.hpp>
#include <cmath>
#include <glm/vec3.hpp> 
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <memory>
#include <ray.hpp>
#include <material.hpp>
#include <camera.hpp>
#include <scene.hpp>
using namespace std;
// Aufgabe 5.2
/*TEST_CASE ("test_area_sphere_box","[area]"){ //Standardkonstruktor
    //auto sphere1 = Sphere{}; //4r^2\pi
    Sphere sphere1{};
    REQUIRE(sphere1.area()==Approx(12.56637).epsilon(0.01));
    Box box1{}; // min: 0.0.0 max:1.1.1
    REQUIRE(box1.area()==6);

    Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
    REQUIRE(sphere2.area()==0);
    Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
    REQUIRE(box2.area()==52);
    
    Sphere sphere3{ glm::vec3{2.0f,2.0f,2.0f}, 2.0f };
	REQUIRE(sphere3.area()==Approx(50.2654).epsilon(0.01));
}

TEST_CASE ("test_volume_sphere","[volume]"){
	Sphere sphere1{}; // (4/3) * M_PI * radius_ * radius_ * radius_
	Box box1{};
	REQUIRE(sphere1.volume()==Approx(4.18879).epsilon(0.01) );
	REQUIRE(box1.volume()==1);

	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE(sphere2.volume()==0 );
	REQUIRE(box2.volume()==24);

	Sphere sphere3{ glm::vec3{2.0f,2.0f,2.0f}, 2.0f };
	REQUIRE(sphere3.volume()==Approx(33.5103).epsilon(0.01));
}

TEST_CASE("test_get_mittelpunkt","[test_get_mittelpunkt]"){
	Sphere sphere1{};
	REQUIRE( sphere1.get_mittelpunkt().x==0.0f );
	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	REQUIRE( sphere2.get_mittelpunkt().x==1.0f);
}

TEST_CASE("test_get_radius","[get_radius]"){
	Sphere sphere1{};
	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	REQUIRE( sphere1.get_radius()==1.0f);
	REQUIRE( sphere2.get_radius()==0.0f );
}

TEST_CASE("test_get_min","test_get_min"){
	Box box1{}; // min: 0.0.0 max:1.1.1
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE( box1.get_min().x==0.0f);
	REQUIRE( box2.get_min().y==2.0f);
}

TEST_CASE("test_get_max","test_get_max"){
	Box box1{}; // min: 0.0.0 max:1.1.1
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE( box1.get_max().x==1.0f);
	REQUIRE( box2.get_max().z==5.0f);
}

// Aufgabe 5.6 
TEST_CASE("intersect_ray_sphere","[intersect]"){
	// Ray
	glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
	// ray direction has to be normalized!
	// you can use:
	// v=glm::normalize(some_vector)
	glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

	// Sphere
	glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
	float sphere_radius{1.0f};

	float distance=0.0f;
	auto result=glm::intersectRaySphere(
		ray_origin,ray_direction,
		sphere_center,
		sphere_radius*sphere_radius,
		distance);
	REQUIRE( result ==true);
	REQUIRE( distance==Approx(4.0f) );
}

TEST_CASE("intersect","[intersect_ray]"){
	Sphere sphere1{glm::vec3{0.0f,0.0f,5.0f},1.0f};
	Ray ray{};
	float distance=0.0f;
	auto result =sphere1.intersect(ray,distance);
	REQUIRE( result==false );
	REQUIRE( distance==Approx(-4.0f) );

	Ray ray1{ glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.0f,0.0f,1.0f}};
	float distance1=0.0f;
	auto result1 =sphere1.intersect(ray1,distance1);
	REQUIRE( result1==true );
	REQUIRE( distance1==Approx(4.0f) );
}

// Aufgabe 6.3
TEST_CASE("intersect_box","[intersect_box]"){
	Box box1{ glm::vec3{1.0f,0.0f,0.0f},glm::vec3{6.0f,5.0f,5.0f} };
	Ray ray{ glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{2.0f,2.0f,2.0f} }; // 第一点0,0,0 第二点2,2,2
	float distance=0.0f; // egal
	auto result=box1.intersect(ray,distance);
	REQUIRE( result == true );

	Box box2{ glm::vec3{0.0f,0.0f,0.0f},glm::vec3{5.0f,5.0f,5.0f} };
	Ray ray2{ glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{-1.0f,-2.0f,0.0f} };
	float distance2=1.0f; 
	auto result2=box2.intersect(ray2,distance2);
	REQUIRE( result2 == false );

	Box box3{ glm::vec3{1.0f,0.0f,0.0f},glm::vec3{6.0f,5.0f,5.0f} };
	Ray ray3{ glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.001f,0.001f,0.001f} }; // 第一点0,0,0 第二点2,2,2
	float distance3=0.0f; // egal
	auto result3=box3.intersect(ray3,distance3);
	REQUIRE( result3 == true );

	Box box4{ glm::vec3{1.0f,0.0f,0.0f},glm::vec3{6.0f,5.0f,5.0f} };
	Ray ray4{ glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.001f,0.001f,0.001f} }; 
	float distance4=0.0f; // egal
	auto result4=box4.intersect(ray4,distance4);
	REQUIRE( result4 == true );

}*/

int main(int argc, char *argv[])
{	
  return Catch::Session().run(argc, argv);
}
