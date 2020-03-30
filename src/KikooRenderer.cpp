#include "Common/CommonIncludes.hpp"

#include "Image.hpp"

#include "Shape/Triangle.hpp"
#include "Shape/Sphere.hpp"
#include "Shape/MovingSphere.hpp"
#include "Shape/TriangleMesh.hpp"
#include "Shape/Instance.hpp"

#include "Material/EmissiveMaterial.hpp"
#include "Material/DiffuseMaterial.hpp"
#include "Material/MetalMaterial.hpp"
#include "Material/DiffSpecMaterial.hpp"

#include "Ray.hpp"
#include "Camera.hpp"

#include "Renderer.hpp"

int main(int argc, char *argv[])
{
	Renderer renderer;

	//Set shapes
	EmissiveMaterial emissive(rgb(1, 0, 1), (real)3.0);
	DiffuseMaterial diffuse(rgb(0.2));
	MetalMaterial metal(rgb(0.3), 100000);
	DiffSpecMaterial diffSpec(&diffuse, &metal, 0.05);

	Triangle t(vector3(-10, 4, 0), vector3(10, 4, 0), vector3(0, 4, 10), rgb(1, 0, 0));
	t.material = &emissive;

	TriangleMesh m0("untitled.obj");
	m0.material = &diffSpec;
	matrix4	transform0 = glm::translate(matrix4(1), vector3(1.5, 0, 0));
	Instance i0(transform0, &m0);

	TriangleMesh m1("untitled.obj");
	m1.material = &diffuse;
	matrix4	transform1 = glm::translate(matrix4(1), vector3(-1.5, 0, 0));
	Instance i1(transform1, &m1);

	renderer.shapes.push_back(&i0);
	renderer.shapes.push_back(&i1);
	// renderer.shapes.push_back(&t);


	//Set image
	int width = 1200;
	int height = 1000;
	Image img(width, height, rgb(0, 0, 0));
	
	//Set camera
	vector3 camPos = vector3(3, 2, 5);
	vector3 lookAt = vector3(0, 0, 0);
	double distanceToFocus = glm::distance(camPos, lookAt);
	Camera camera(camPos, lookAt, vector3(0, 1, 0), 70, (double)width/(double)height, 0.0001, distanceToFocus, 0, 1);
	
	//Skybox
	std::vector<std::string> skyboxFiles = {
		"res/Skybox/right.jpg",
		"res/Skybox/left.jpg",
		"res/Skybox/top.jpg",
		"res/Skybox/bottom.jpg",
		"res/Skybox/back.jpg",
		"res/Skybox/front.jpg",
	};
	renderer.skybox = Cubemap(skyboxFiles);

	int numSamples = 256;
	renderer.Render(img, camera, numSamples);

	
	return 1;
}