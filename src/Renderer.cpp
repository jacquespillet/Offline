#include "Renderer.hpp"

#include "Sample.hpp"
#include "Common/ThreadingUtil.hpp"
#include "Material/Material.hpp"

bool Renderer::Hit(Ray ray, HitPoint& hitPoint, real time) const {
    real closest = std::numeric_limits<real>::max();
    
    bool globalHit = false;
    for(int i=0; i<shapes.size(); i++) {
        HitPoint h;
        bool localHit = shapes[i]->Hit(ray, 0.0001, 1000, time, h);
        globalHit |= localHit;
        if(localHit && h.t < closest) {
            closest = h.t;
            hitPoint = h;
        }
    }

    return globalHit;
}


rgb Renderer::GetColor(const Ray& ray, int depth, int currentSample) const {    
    HitPoint hitPoint;
    bool dummy_bool = true;
    float brdf_scale;
    
    bool hit = Hit(ray, hitPoint, timeSamples[currentSample]);
    if (hit) 
    {
        rgb c(0,0,0);

        c += hitPoint.material->EmittedRadiance(hitPoint.uvw, -ray.Direction());

        vector3 outDir;
        rgb hitColor;
        real pdfValue=1;
        real brdfValue=1;
        if(depth < 30 && hitPoint.material->DiffuseDirection(hitPoint.uvw, ray.Direction(), brdfSamples[currentSample], hitColor, outDir, pdfValue, brdfValue)) 
        {
            Ray ref(hitPoint.p, outDir);
            c += brdfValue*hitColor*GetColor(ref, depth+1, currentSample) / pdfValue;
        }

       return c + ambient * hitPoint.material->AmbientResponse(hitPoint.uvw, ray.Direction());
    }
    else {
        if(skybox.init) {
            glm::vec3 backgroundColor = skybox.Sample(ray.Direction());
            return backgroundColor; 
        } else {
            rgb backgroundColor = rgb(0);
            return backgroundColor;
        }        
    }
}



void Renderer::Render(Image& target, Camera& _camera, int _numSamples) {
    numSamples = _numSamples;
    camera = _camera;

	pixelSamples.resize(numSamples);
	Jitter(pixelSamples, numSamples);
	BoxFilter(pixelSamples, numSamples);
	
	lensSamples.resize(numSamples);
	Jitter(lensSamples, numSamples);
	
	timeSamples.resize(numSamples);
	Jitter(timeSamples, numSamples);

	brdfSamples.resize(numSamples);

    int width = target.GetWidth();
    int height = target.GetHeight();


    ThreadPool( std::function<void(uint64_t, uint64_t)>([this, width, height, &target](uint64_t i, uint64_t t) {
    // for(int i=0; i<width * height; i++) {
	    
		int x = i % width;
		int y = i / width;

        Jitter(brdfSamples, numSamples);
		
        if(x ==0) std::cout << y << " / " << height << std::endl;

		rgb color(0);
		real inverseNumSamples = 1.0 / (real)numSamples;
		for(int j=0; j<numSamples; j++) {
			real correctedX = pixelSamples[j].x + x;
			real correctedY = pixelSamples[j].y + y;
			Ray r = camera.GetRay((real)x/(real)width, (real)y/(real)height, lensSamples[j].x, lensSamples[j].y);
            color += GetColor(r, 0, j) * inverseNumSamples;
		}

		color = glm::min(vector3(1.0f), glm::max(vector3(0.0f), color));
		target.set(x, y, color);
    }), width * height).Block();
    std::cout << "HERE" << std::endl;
	// }

	target.gammaCorrect(2.2);
	target.WritePPM("Test.ppm");        
}