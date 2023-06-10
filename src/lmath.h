#ifndef LMATH_H
#define LMATH_H

#define PI 3.14159265359

float to_radians(const float degrees);
float to_degrees(const float radians);

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef float mat4x4[4][4];

void vec2_add(vec2 r, const vec2 a, const vec2 b);
void vec2_sub(vec2 r, const vec2 a, const vec2 b);
void vec2_mul(vec2 r, const vec2 v, const float s);
void vec2_div(vec2 r, const vec2 v, const float s);

float vec2_len(const vec2 v);
void vec2_norm(vec2 r, const vec2 v);

void vec3_add(vec3 r, const vec3 a, const vec3 b);
void vec3_sub(vec3 r, const vec3 a, const vec3 b);
void vec3_mul(vec3 r, const vec3 v, const float s);
void vec3_div(vec3 r, const vec3 v, const float s);

float vec3_len(const vec3 v);
void vec3_norm(vec3 r, const vec3 v);

void mat4x4_identity(mat4x4 m);
void mat4x4_mul(mat4x4 r, const mat4x4 a, const mat4x4 b);

void mat4x4_rotate_x(mat4x4 m, float angle);
void mat4x4_rotate_y(mat4x4 m, float angle);
void mat4x4_rotate_z(mat4x4 m, float angle);

void mat4x4_translate(mat4x4 m, float x, float y, float z);

void mat4x4_perspective(mat4x4 m, float fov, float aspect, float near, float far);

void mat4x4_mul_vec3(vec3 r, const mat4x4 m, const vec3 v);

#endif // LMATH_H