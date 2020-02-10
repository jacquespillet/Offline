#pragma once


// //cptl
// #include <ctpl_stl.h>

// //glm
#define GLM_FORCE_INLINE 
//#define GLM_FORCE_SSE2
#define GLM_FORCE_AVX
#include <glm/vec3.hpp> // vector3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_access.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

 //std lib
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <cstdio>
#include <limits>
#include <iomanip>
#include <numeric>
#include <random>


typedef double real;
typedef glm::dvec4 vector4;
typedef glm::dvec3 vector3;
typedef glm::dvec2 vector2;
typedef glm::dmat3 matrix3;
typedef glm::dmat4 matrix4;

typedef vector3  rgb;