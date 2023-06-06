#include "lmath.h"
#include <math.h>

float to_radians(const float degrees)
{
    return degrees * (PI / 180);
}

float to_degrees(const float radians)
{
    return radians * (180 / PI);
}

vec2 vec2_create(float x, float y)
{
    vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

vec2 vec2_add(const vec2 a, const vec2 b)
{
    return vec2_create(a.x + b.x, a.y + b.y);
}

vec2 vec2_sub(const vec2 a, const vec2 b)
{
    return vec2_create(a.x - b.x, a.y - b.y);
}

vec2 vec2_mul(const vec2 v, const float s)
{
    return vec2_create(v.x * s, v.y * s);
}

vec2 vec2_div(const vec2 v, const float s)
{
    return vec2_create(v.x / s, v.y / s);
}

float vec2_length(const vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

vec2 vec2_normalize(const vec2 v)
{
    float len = vec2_length(v);
    return vec2_div(v, len);
}

vec3 vec3_create(float x, float y, float z)
{
    vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

vec3 vec3_add(const vec3 a, const vec3 b)
{
    return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 vec3_sub(const vec3 a, const vec3 b)
{
    return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 vec3_mul(const vec3 v, const float s)
{
    return vec3_create(v.x * s, v.y * s, v.z * s);
}

vec3 vec3_div(const vec3 v, const float s)
{
    return vec3_create(v.x / s, v.y / s, v.z / s);
}

float vec3_dot(const vec3 a, const vec3 b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_cross(const vec3 a, const vec3 b) 
{
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

float vec3_length(const vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec3_normalize(const vec3 v)
{
    float len = vec3_length(v);
    return vec3_div(v, len);
}