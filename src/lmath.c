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

void vec2_add(vec2 r, const vec2 a, const vec2 b)
{
    r[0] = a[0] + b[0];
    r[1] = a[1] + b[1];
}

void vec2_sub(vec2 r, const vec2 a, const vec2 b)
{
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
}

void vec2_mul(vec2 r, const vec2 v, const float s)
{
    r[0] = v[0] * s;
    r[1] = v[1] * s;
}

void vec2_div(vec2 r, const vec2 v, const float s)
{
    r[0] = v[0] / s;
    r[1] = v[1] / s;
}

float vec2_len(const vec2 v)
{
    return sqrtf(v[0] * v[0] + v[1] * v[1]);
}

void vec2_norm(vec2 r, const vec2 v)
{
    const float len = vec2_len(v);
    vec2_div(r, r, len);
}

void vec3_add(vec3 r, const vec3 a, const vec3 b)
{
    r[0] = a[0] + b[0];
    r[1] = a[1] + b[1];
    r[2] = a[2] + b[2];
}

void vec3_sub(vec3 r, const vec3 a, const vec3 b)
{
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
    r[2] = a[2] - b[2];
}

void vec3_mul(vec3 r, const vec3 v, const float s)
{
    r[0] = v[0] * s;
    r[1] = v[1] * s;
    r[2] = v[2] * s;
}

void vec3_div(vec3 r, const vec3 v, const float s)
{
    r[0] = v[0] / s;
    r[1] = v[1] / s;
    r[2] = v[2] / s;
}

float vec3_len(const vec3 v)
{
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vec3_norm(vec3 r, const vec3 v)
{
    const float len = vec3_len(v);
    vec2_div(r, r, len);
}

void mat4x4_identity(mat4x4 m)
{
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}

void mat4x4_mul(mat4x4 o, const mat4x4 a, const mat4x4 b)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            o[j][i] = a[j][0] * b[0][i] + a[j][1] * b[1][i] + a[j][2] * b[2][i] + a[j][3] * b[3][i];
        }
    }
}

void mat4x4_rotate_x(mat4x4 m, float angle)
{
    m[0][0] =  1.0f;
    m[1][1] =  cosf(angle);
    m[1][2] =  sinf(angle);
    m[2][1] = -sinf(angle);
    m[2][2] =  cosf(angle);
    m[3][3] =  1.0f;
}

void mat4x4_rotate_y(mat4x4 m, float angle)
{
    m[0][0] =  cosf(angle);
    m[0][2] =  sinf(angle);
    m[2][0] = -sinf(angle);
    m[1][1] =  1.0f;
    m[2][2] =  cosf(angle);
    m[3][3] =  1.0f;
}

void mat4x4_rotate_z(mat4x4 m, float angle)
{
    m[0][0] =  cosf(angle);
    m[0][1] =  sinf(angle);
    m[1][0] = -sinf(angle);
    m[1][1] =  cosf(angle);
    m[2][2] =  1.0f;
    m[3][3] =  1.0f;
}

void mat4x4_translate(mat4x4 m, float x, float y, float z)
{
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

void mat4x4_perspective(mat4x4 m, float fov, float aspect, float near, float far)
{
    float a = 1.0f / tanf(fov * 0.5f);

    m[0][0] = aspect * a;
    m[1][1] = a;
    m[2][2] = far / (far - near);
    m[3][2] = (-far * near) / (far - near);
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
}

void mat4x4_mul_vec3(vec3 r, const mat4x4 m, const vec3 v)
{
    r[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + m[3][0];
    r[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[3][1];
    r[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[3][2];

    float w = v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + m[3][3];

    if (w != 0.0f)
    {
        r[0] /= w; r[1] /= w; r[2] /= w;
    }
}