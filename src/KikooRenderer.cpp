#include "Common/CommonIncludes.hpp"

#include "Image.hpp"
#include "Shape/Triangle.hpp"
#include "Shape/Sphere.hpp"
#include "Ray.hpp"
#include "Sample.hpp"

int main(int argc, char *argv[])
{
	Triangle t(glm::vec3(0, 0, -4), glm::vec3(150, 300, -4), glm::vec3(300, 0, -4), rgb(1, 0, 0));
	Sphere s(glm::vec3(150, 150, -5), 100, rgb(0, 1, 0));

	int width = 300;
	int height = 300;
	Image img(width, height, rgb(0, 0, 0));
	
	int numSamples = 32;
	std::vector<glm::vec2> samples(numSamples);
	Random(samples, numSamples);
	BoxFilter(samples, numSamples);

	std::vector<Shape*> shapes;
	shapes.push_back(&t);
	shapes.push_back(&s);

	for(int x=0; x<width; x++) {
		std::cout << x << std::endl;
		for(int y=0; y<height; y++) {

			rgb color(0);
			real inverseNumSamples = 1.0 / (real)numSamples;
			for(int j=0; j<numSamples; j++) {
				Ray r(glm::vec3(x + samples[j].x, y + samples[j].y, 0), glm::vec3(0, 0, -1));
				real closest = 1001;
				for(int i=0; i<shapes.size(); i++) {
					HitPoint h;
					bool hit = shapes[i]->Hit(r, 0.0001, 1000, 0, h);
					if(hit && h.t < closest) {
						closest = h.t;
						color += h.color * inverseNumSamples;
					}
				}
			}


			img.set(x, y, color);
		}
	}

	img.WritePPM("Test.ppm");
	std::cout << "HERE" << std::endl;
	return 1;
}