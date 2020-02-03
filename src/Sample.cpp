#include "Sample.hpp"


void Random(std::vector<glm::vec2>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    for(int i=0; i<numSamples; i++) {
        samples[i].x = GetRand();
        samples[i].y = GetRand();
    }
}


void Jitter(std::vector<glm::vec2>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    int sqrtSamples = (int)(std::sqrt(numSamples));

    for(int i=0; i<sqrtSamples; i++) {
        for(int j=0; j<sqrtSamples; j++) {
            real x = ((real)i + GetRand()) / (real)sqrtSamples;
            real y = ((real)j + GetRand()) / (real)sqrtSamples;

            samples[i * sqrtSamples + j].x = x;
            samples[i * sqrtSamples + j].y = y;
        }        
    }
}

void NRooks(std::vector<glm::vec2>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    //Put samples on diagonal
    for(int i=0; i<numSamples; i++) {
        samples[i].x = ((real)i + GetRand()) / (real)(numSamples);
        samples[i].y = ((real)i + GetRand()) / (real)(numSamples);
    }

    //Set the x of the current with the x of another existing one, and inversely
    for(int i=numSamples-2; i>=0; i--) {
        int targetX = int(GetRand() * (real)i);
        real tempX = samples[i+1].x;

        samples[i+1].x = samples[targetX].x;
        samples[targetX].x = tempX;
    }
}

void MultiJitter(std::vector<glm::vec2>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    int sqrtSamples = (int)std::sqrt(numSamples);
    real subCellWidth = 1.0f / (real)(numSamples);

    for(int i=0; i<sqrtSamples;i++) {
        for(int j=0; j<sqrtSamples;j++) {
            samples[i * sqrtSamples + j].x = i * sqrtSamples * subCellWidth + j * subCellWidth + GetRand() * subCellWidth;
            samples[i * sqrtSamples + j].y = j * sqrtSamples * subCellWidth + i * subCellWidth + GetRand() * subCellWidth;
        }
    }

    for(int i=0; i<sqrtSamples;i++) {
        for(int j=0; j<sqrtSamples;j++) {
            int k = j + int(GetRand() * (sqrtSamples - j - 1));
            real t = samples[i * sqrtSamples + j].x;
            samples[i * sqrtSamples + j].x = samples[i * sqrtSamples + k].x;
            samples[i * sqrtSamples + k].x = t;

            
            k = j + int(GetRand() * (sqrtSamples - j - 1));
            t = samples[j * sqrtSamples + i].y;
            samples[j * sqrtSamples + i].y = samples[k * sqrtSamples + i].y;
            samples[k * sqrtSamples + i].y = t;
        }
    }
}

void Shuffle(std::vector<glm::vec2>& samples, int numSamples) {
    for(int i=numSamples-2; i>=0; i--) {
        int target  = (int)(GetRand() * (real)i);
        glm::vec2 tmp = samples[i+1];
        samples[i+1] = samples[target];
        samples[target] = tmp;
    }
}


//Resample from 0->1 to -0.5 -> 0.5
void BoxFilter(std::vector<glm::vec2>& samples, int numSamples) {
    for(int i=0; i<numSamples; i++) {
        samples[i].x = samples[i].x-0.5f;
        samples[i].y = samples[i].y-0.5f;
    }
}

//Resample from 0->1 to -0.5 -> 0.5 using tent filter
void TentFilter(std::vector<glm::vec2>& samples, int numSamples) {
    for(int i=0; i<numSamples; i++) {
        real x = samples[i].x;
        real y = samples[i].y;

        if(x < -0.5) samples[i].x = (real)std::sqrt(2.0 * (real)x) - 1.0f;
        else samples[i].x = 1.0 - (real)std::sqrt(2.0 - 2.0 * (real)x);

        if(y < -0.5) samples[i].y = (real)std::sqrt(2.0 * (real)y) - 1.0f;
        else samples[i].y = 1.0 - (real)std::sqrt(2.0 - 2.0 * (real)y);
    }
}

//Resample from 0->1 to -0.5 -> 0.5 using cubic spline filter
void CubicSplineFilter(std::vector<glm::vec2>& samples, int numSamples) {
    for(int i=0; i<numSamples; i++) {
        real x = samples[i].x;
        real y = samples[i].y;

        samples[i].x = cubicFilter(x);
        samples[i].y = cubicFilter(y);
    }
}

void Random(std::vector<float>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    for(int i=0; i<numSamples; i++) {
        samples[i] = GetRand();
    }
}

void Jitter(std::vector<float>& samples, int numSamples) {
    if(samples.size() != numSamples) samples.resize(numSamples);

    for(int i=0; i<numSamples; i++) {
        samples[i] = ((real)i + GetRand()) / (real)numSamples;
    }
}

void Shuffle(std::vector<float>& samples, int numSamples) {
    for(int i=numSamples-2; i>=0; i--) {
        int target = (int)(GetRand() * (real)i);
        real temp =samples[i+1];

        samples[i+1] = samples[target];
        samples[target] = temp;
    }
}



