// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // axis angle formula
  const float radians = degrees * pi / 180;

  const float x = axis.x;
  const float y = axis.y;
  const float z = axis.z;

  mat3 identity = mat3(1.0);
  mat3 matrix1 = mat3(x*x, x*y, x*z, x*y, y*y, y*z, x*z, y*z, z*z);
  mat3 matrix2 = mat3(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);

  return mat3(cos(radians)*identity + (1-cos(radians))*matrix1 + sin(radians)*matrix2);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// transform about the y axis
	vec3 y_axis = vec3(0.0, 1.0, 0.0);
	mat3 R_transpose = glm::transpose(rotate(degrees, y_axis));

	eye = eye * R_transpose;
	up = up * R_transpose;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
 	// transform about x-axis
	vec3 x_axis = vec3(0.0, 1.0, 0.0);
	mat3 R_transpose = glm::transpose(rotate(degrees, x_axis));

	eye = eye * R_transpose;
	up = up * R_transpose;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  	/* personal implementation of GluLookat */

  	// Step 1: Create coordinate frame for camera
  	vec3 w = glm::normalize(eye);	// w = normalize(eye-center)
  	vec3 u = glm::normalize(glm::cross(up, w));
  	vec3 v = glm::cross(w, u);	// already normalized

  	// Step 2: Define a rotation matrix (column-major form for GLM)
  	mat4 rot = mat4(u.x, v.x, w.x, 0.0,
  					u.y, v.y, w.y, 0.0,
  					u.z, v.z, w.z, 0.0,
  					0.0, 0.0, 0.0, 1.0);
  	mat4 translation = mat4(1.0, 0.0, 0.0, 0.0,
  							0.0, 1.0, 0.0, 0.0,
  							0.0, 0.0, 1.0, 0.0,
  							-eye.x, -eye.y, -eye.z, 1);

  	// Step 3: Apply transformations (translation followed by rotation)
  	mat4 combinedTransformation = glm::transpose(glm::transpose(translation) * glm::transpose(rot));
  	return combinedTransformation;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
