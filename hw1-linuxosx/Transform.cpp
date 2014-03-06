// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // Use degrees and axis to return rotation matrix
  // Use axis-angle formula
  float radians = degrees * pi / 180;
  
  // get axis' components along X, Y, Z
  const float x = axis.x;
  const float y = axis.y;
  const float z = axis.z;
  
  const mat3 identity = mat3(1.0);
  mat3 matrix1 = mat3(x*x, x*y, x*z, y*x, y*y, y*z, z*x, z*y, z*z);
  mat3 matrix2 = mat3(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);
  
  // use matrix from axis-angle formula
  return mat3(cos(radians)*identity + (1-cos(radians))*matrix1 + sin(radians)*matrix2);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // this is a rotation about the Y-axis
  const vec3 yAxis = vec3(0.0, 1.0, 0.0);
  mat3 rot_matrix = Transform::rotate(degrees, yAxis);
  
  // modify eye and up vector accordingly
  // eye = Rot * eye
  eye = rot_matrix * eye;
  up = rot_matrix * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  const vec3 xAxis = vec3(1.0, 0.0, 0.0);
  mat3 rot_matrix = Transform::rotate(degrees, xAxis);
  
  // modify eye and up vector accordingly
  // eye = Rot * eye
  eye = rot_matrix * eye;
  up = rot_matrix * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);
  
  mat4 lookAtMatrix = mat4(u.x, v.x, w.x, 0.0,
					   u.y, v.y, w.y, 0.0,
					   u.z, v.z, w.z, 0.0,
					   -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1.0);

  
  return lookAtMatrix;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
