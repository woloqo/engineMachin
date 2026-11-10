#include "../include/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target){
    this->position  = position;
    this->target    = target;
    
    this->view      = glm::mat4(1.0f);

    this->up        = glm::vec3(0.0f, 1.0f, 0.0f); 
    this->front     = glm::normalize(this->target - this->position);

    this->pitch     = glm::degrees(asin(this->front.y));
    this->yaw       = glm::degrees(atan2(this->front.z, this->front.x));

    this->view      = glm::lookAt(this->position, this->position + this->front, this->up);
}