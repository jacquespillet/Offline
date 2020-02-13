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
    bool hit = Hit(ray, hitPoint, timeSamples[currentSample]);
    if(hit && depth < 10) {            
        //Generate out direction
        vector3 outDir;
        rgb hitColor, hitColorBrdf;
        real brdfValue, pdfValue;


        hitPoint.material->DiffuseDirection(hitPoint.uvw, ray.Direction(), brdfSamples[currentSample], hitColor, outDir, pdfValue);        
        hitPoint.material->ExplicitBrdf(hitPoint.uvw, ray.Direction(), outDir, hitColorBrdf, brdfValue);

        rgb emitted = hitPoint.material->EmittedRadiance(hitPoint.uvw, outDir);

        if(glm::length(emitted) > 0) { 
            return emitted;
        }

        // Create out ray
        Ray scatteredRay(hitPoint.p, outDir);

        real cosT = glm::dot(outDir, hitPoint.uvw.W);

        //Rendering equation : 
        // BRDF * Lo * cosT
        return brdfValue * (hitColor * GetColor(scatteredRay, depth+1, currentSample));
    } else {
        glm::vec3 direction = glm::normalize(ray.Direction());
        double t = 0.5 * direction.y + 1.0;
        glm::vec3 backgroundColor = (1.0 - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1);
        // rgb backgroundColor = rgb(0);
        return backgroundColor;
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
	// }

	target.gammaCorrect(2.2);
	target.WritePPM("Test.ppm");        
}