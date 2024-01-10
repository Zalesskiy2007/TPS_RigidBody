/* FILE NAME   : mth.h
 * PROGRAMMER  : MZ2.
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               General math module.
 */

#ifndef __mth_h_
#define __mth_h_

#include "mth_vec3.h"
#include "mth_matr.h"
#include "mth_vec2.h"
#include "mth_vec4.h"
#include "mth_camera.h"
#include "mth_ray.h"
#include "mth_tensor.h"

typedef mth::vec2<FLT> vec2;
typedef mth::vec3<FLT> vec3;
typedef mth::vec4<FLT> vec4;
typedef mth::matr<FLT> matr;
typedef mth::ray<FLT> ray;
typedef mth::camera<FLT> camera;
typedef mth::tensor<FLT> tensor;

#endif /* __mth_h_ */

 /* END OF 'mth.h' FILE */