#ifndef LMATH_H
#define LMATH_H

#define PI 3.14159265359

float to_radians(const float degrees);
float to_degrees(const float radians);

typedef struct
{
    float x;
    float y;

} vec2;

vec2 vec2_create(float x, float y);

vec2 vec2_add(const vec2 a, const vec2 b);
vec2 vec2_sub(const vec2 a, const vec2 b);
vec2 vec2_mul(const vec2 v, const float s);
vec2 vec2_div(const vec2 v, const float s);

float vec2_length(const vec2 v);
vec2 vec2_normalize(const vec2 v);

typedef struct 
{
    float x;
    float y;
    float z;
    
} vec3;

vec3 vec3_create(float x, float y, float z);

vec3 vec3_add(const vec3 a, const vec3 b);
vec3 vec3_sub(const vec3 a, const vec3 b);
vec3 vec3_mul(const vec3 v, const float s);
vec3 vec3_div(const vec3 v, const float s);

float vec3_dot(const vec3 a, const vec3 b);
vec3 vec3_cross(const vec3 a, const vec3 b);

float vec3_length(const vec3 v);
vec3 vec3_normalize(const vec3 v);

#endif