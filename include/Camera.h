#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>

class Camera{
public:
    glm::vec3 position;
    glm::vec3 target;

    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 up;

    glm::mat4 view;
    
    float speed        = 10.0f;
    float fovInDegrees = 90.0f;

    const float fovInDegreesWhileRunning = fovInDegrees + 10.0f;
    const float fovInDegreesWhileWalking = fovInDegrees;

    float yaw         = -90.0f;
    float pitch       =  0.0f;
    float sensitivity =  0.1f;

    Camera(glm::vec3 position, glm::vec3 target);
};

#endif