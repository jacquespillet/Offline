#pragma once

#include "Common/CommonIncludes.hpp"

void Random(std::vector<vector2>& samples, int numSamples);
void Jitter(std::vector<vector2>& samples, int numSamples);
void NRooks(std::vector<vector2>& samples, int numSamples);
void MultiJitter(std::vector<vector2>& samples, int numSamples);
void Shuffle(std::vector<vector2>& samples, int numSamples);

void BoxFilter(std::vector<vector2>& samples, int numSamples);
void TentFilter(std::vector<vector2>& samples, int numSamples);
void CubicSplineFilter(std::vector<vector2>& samples, int numSamples);

void Random(std::vector<real>& samples, int numSamples);
void Jitter(std::vector<real>& samples, int numSamples);
void Shuffle(std::vector<real>& samples, int numSamples);

inline real GetRand() {
    return ((real)std::rand() / (real)RAND_MAX);
}

inline real Solve(real r) {
    real u = r;
    for(int i=0; i<5; i++) {
        u = (11.0f * r + u * u * (6.0f + u * (8.0f - 9.0f * u))) / 
            (4.0f + 12.0f * u * (1.0f + u * (1.0f - u)));
    }

    return u;
}

inline real cubicFilter(real x) {
    if (x < 1.0f / 24.0f) {
        return std::pow(24 * x, 0.25f) - 2.0f;
    } else if (x < 0.5) {
        return Solve(24.0f * (x - 1.0f / 24.0f) / 11.0f) - 1.0f;
    } else if (x < 23.0f / 24.0f) {
        return 1.0f - Solve(24.0f * (23.0f / 24.0f - x) / 11.0f);
    } else {
        return 2 - std::pow(24.0f * (1.0f - x), 0.25f);
    }
}
