#include<string>
#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"../include/shaderClass.h"
#include"../include/VAO.h"
#include"../include/VBO.h"
#include"../include/EBO.h"
#include"../include/colors.h"
#include"../include/textures.h"
#include"../include/TextRenderer.h"
#include"../include/camera.h"
#include"../include/Atlas.h"
#include"../include/Block.h"
#include"../include/MeshBuilder.h"

const char *defaultVertPath		= RES_PATH "/shaders/default.vert";
const char *defaultFragPath 	= RES_PATH "/shaders/default.frag";

const char *textVertPath 		= RES_PATH "/shaders/text.vert";
const char *textFragPath 		= RES_PATH "/shaders/text.frag";

const char *grassTextPath 		= RES_PATH "/textures/grass_side.png";
const char *atlasPath 			= RES_PATH "/textures/atlas.png";
const char *fontPath     		= RES_PATH "/fonts/minecraft_font.ttf";

//Variables del programa

const char *windowTitle = "engineMachin";

int windowWidth 		= 800;
int windowHeight 		= 800;

bool isDebugActive 		= true;
bool firstMouse 		= true;
bool constrainPitch		= true;

float deltaTime 		= 0.0f;
float lastX = windowWidth/2, lastY = windowHeight/2;

Camera camera = Camera(glm::vec3(12.0f, 2.0f, 0.5f));

void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
		std::cout<<"Tecla [esc] presionada... Cerrando ventana\n";
		glfwSetWindowShouldClose(w, true);
	}
	if(key == GLFW_KEY_F1 && action == GLFW_RELEASE){
		std::cout<<"Debug toggled\n";
		isDebugActive = isDebugActive ? 0 : 1;
		glfwWaitEventsTimeout(0.7);
	}
}

void processInput(GLFWwindow *w, Camera *c){
	if(glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) c->position += c->speed * c->front * deltaTime;
	if(glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) c->position -= c->speed * c->front * deltaTime;
	if(glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) c->position += glm::normalize(glm::cross(c->front, c->up)) * c->speed * deltaTime;
	if(glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) c->position -= glm::normalize(glm::cross(c->front, c->up)) * c->speed * deltaTime;
	if(glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS) c->position.y += c->speed * deltaTime;
	if(glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) c->position.y -= c->speed * deltaTime;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw   += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.0f) camera.pitch = 89.0f;
    if(camera.pitch < -89.0f) camera.pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    direction.y = sin(glm::radians(camera.pitch));
    direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.front = glm::normalize(direction);
}  

void framebuffer_size_callback(GLFWwindow *w, int width, int height){
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

int main(){
	glfwInit();
	std::cout<<"engineMachin log:\n";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (window == NULL){
		std::cout << "Error al crear ventana\n";
		glfwTerminate();
		return -1;
	} else std::cout<<"Ventana creada correctamente\n";

	//Window settings
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval( 0 );

	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST); 

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback); 

	Shader shaderProgram(defaultVertPath, defaultFragPath);

	std::vector<float> vertices;
  	std::vector<unsigned int> indices;
  	addCube(vertices, indices, {0, 1, -1}, GRASS);
	addCube(vertices, indices, {0, 1,  1}, GRASS);
	addCube(vertices, indices, {0, 2, -1}, GRASS);
	addCube(vertices, indices, {0, 2,  1}, GRASS);

	addCube(vertices, indices, {0, -2,  0}, GRASS);
	addCube(vertices, indices, {0, -2, -1}, GRASS);
	addCube(vertices, indices, {0, -2,  1}, GRASS);
	addCube(vertices, indices, {0, -1, -2}, GRASS);
	addCube(vertices, indices, {0, -1,  2}, GRASS);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices.data(), vertices.size() * sizeof(float));
	EBO EBO1(indices.data(),  indices.size()  * sizeof(unsigned int));

	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Texture grassTexture("grassTexture", grassTextPath);
	Texture atlas("atlas", atlasPath);

	unsigned int tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.use();
	glUniform1i(tex0Uni, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	TextRenderer text(textVertPath, textFragPath);
	if (!text.Load(fontPath, 48)) return -1;

	double lastTime = glfwGetTime();
	float lastFrame = 0.0f;
	int frames = 0;
	std::string fpsText = std::to_string(frames) + " FPS (" + std::to_string(1000.0 / frames).substr(0, 4) + " ms)";

	// Main loop
	while (!glfwWindowShouldClose(window)){
		glClearColor(COLOR_WHITE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		processInput(window, &camera);

		//Transformaciones
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4  proj = glm::mat4(1.0f);

		VAO1.Bind();
		atlas.bind();

		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
		camera.view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
		proj = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		double currentTime = glfwGetTime();
		frames++;
		double elapsed = currentTime - lastTime;
		if (elapsed >= 0.5) {
			double fps = frames / elapsed;
			fpsText = std::format("{:.0f} FPS ({:.2f} ms)", fps, 1000.0 / fps);
			frames = 0; lastTime = currentTime;
		}

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;  
		
		if(isDebugActive){
			text.Draw(fpsText, 10.0f, windowHeight - 25.0f, 0.4f, glm::vec3(0.0f, 0.0f, 0.0f), windowWidth, windowHeight);

			std::string cameraText = "Camera pos: " + std::format("{:.2f}", camera.position.x) + ", " + std::format("{:.2f}", camera.position.y) + ", " + std::format("{:.2f}", camera.position.z);
			text.Draw(cameraText, 10.0f, windowHeight - 45.0f, 0.4f, glm::vec3(0.0f, 0.0f, 0.0f), windowWidth, windowHeight);

			std::string viewText = "(looking at : " + std::format("{:.2f}", camera.front.x) + ", " + std::format("{:.2f}", camera.front.y) + ", " + std::format("{:.2f}", camera.front.z) + ")";
			text.Draw(viewText, 5.0f, windowHeight - 65.0f, 0.35f, glm::vec3(0.0f, 0.0f, 0.0f), windowWidth, windowHeight);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	grassTexture.Delete();
	text.Delete();

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}