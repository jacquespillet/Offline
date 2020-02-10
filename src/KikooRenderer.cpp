#include "Common/CommonIncludes.hpp"

#include "Image.hpp"

#include "Shape/Triangle.hpp"
#include "Shape/Sphere.hpp"
#include "Shape/MovingSphere.hpp"
#include "Shape/TriangleMesh.hpp"
#include "Shape/Instance.hpp"

#include "Ray.hpp"
#include "Sample.hpp"
#include "Camera.hpp"


int main(int argc, char *argv[])
{
	Triangle t(vector3(1, 0, 0), vector3(-1, 0, 0), vector3(0, 1, 0), rgb(1, 0, 0));
	MovingSphere s(vector3(0, 0, 0), 1, rgb(0, 1, 0), 0, 1);
	TriangleMesh m("untitled.obj");

	matrix4 transform(1);
	transform = glm::rotate(transform, 0.4, vector3(0, 1, 0));
	transform = glm::translate(transform, vector3(1, 0, 0));
	Instance i(transform, &m);

	

	int width = 300;
	int height = 300;
	Image img(width, height, rgb(0, 0, 0));
	
	int numSamples = 1;
	std::vector<vector2> pixelSamples(numSamples);
	Random(pixelSamples, numSamples);
	BoxFilter(pixelSamples, numSamples);
	
	std::vector<vector2> lensSamples(numSamples);
	Random(lensSamples, numSamples);
	
	std::vector<real> timeSamples(numSamples);
	Random(timeSamples, numSamples);

	std::vector<Shape*> shapes;
	// shapes.push_back(&t);
	// shapes.push_back(&s);
	shapes.push_back(&i);

	//1. Create the camera 
	vector3 camPos = vector3(0, 0, 2);
	vector3 lookAt = vector3(0, 0, 0);
	double distanceToFocus = glm::distance(camPos, lookAt);
	Camera camera(camPos, lookAt, vector3(0, 1, 0), 70, (double)width/(double)height, 0.0001, distanceToFocus, 0, 1);

	for(int i=0; i<width * height; i++) {
		int x = i % width;
		int y = i / width;

		if(x ==0) std::cout << y << " / " << height << std::endl;

		rgb color(0);
		real inverseNumSamples = 1.0 / (real)numSamples;
		for(int j=0; j<numSamples; j++) {
			real correctedX = pixelSamples[j].x + x;
			real correctedY = pixelSamples[j].y + y;
			Ray r = camera.GetRay((real)x/(real)width, (real)y/(real)height, lensSamples[j].x, lensSamples[j].y);

			//Find color
			real closest = std::numeric_limits<real>::max();
			HitPoint closestHit;
			closestHit.t = -1;
			for(int i=0; i<shapes.size(); i++) {
				HitPoint h;
				bool hit=false;
				hit = shapes[i]->Hit(r, 0.0001, 1000, timeSamples[j], h);
				if(hit && h.t < closest) {
					closest = h.t;
					closestHit = h;
				}
			}

			if(closestHit.t > 0) color += closestHit.color * inverseNumSamples;
		}

		color = glm::min(vector3(1.0f), glm::max(vector3(0.0f), color));
		img.set(x, y, color);
	}
	img.gammaCorrect(2.2);
	img.WritePPM("Test.ppm");
	return 1;
}