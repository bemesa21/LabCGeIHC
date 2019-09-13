//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes

#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int screenWidth;
int screenHeight;

GLFWwindow * window;

Shader shader;
//crea un apuntador
std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());
Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Box box1;
Box box2;

bool exitApp = false;
int lastMousePosX = 0;
int lastMousePosY = 0;
int offsetX = 0;
int offsetY = 0;

double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {
	
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.85f, 0.89f, 0.94f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	//inicializar los buffers VAO, VBO, EBO

	sphere1.init();
	//METODO SETTER QUE COLOCA EL APUNTADOR AL SHADER
	sphere1.setShader(&shader);
	//Setter para poner el color a la geometría
	sphere1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));

	sphere2.init();
	//METODO SETTER QUE COLOCA EL APUNTADOR AL SHADER
	sphere2.setShader(&shader);
	//Setter para poner el color a la geometría
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphere3.init();
	//METODO SETTER QUE COLOCA EL APUNTADOR AL SHADER
	sphere3.setShader(&shader);
	//Setter para poner el color a la geometría
	sphere3.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shader);
	cylinder1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shader);
	cylinder2.setColor(glm::vec4(0.35, 0.15, 0.16, 1.0));

	box1.init();
	box1.setShader(&shader);
	box1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));
	camera->setPosition(glm::vec3(2.0, 0.0, 4.0));

	box2.init();
	box2.setShader(&shader);
	box2.setColor(glm::vec4(0.35, 0.15, 0.16, 1.0));
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.
	//elimina los VAO VBO Y EBO
	sphere1.destroy();
	sphere2.destroy();
	sphere3.destroy();

	cylinder1.destroy();
	cylinder2.destroy();

	box1.destroy();
	box2.destroy();

	shader.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication){
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	//offsetX = 0;
	//offsetY = 0;
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 view = camera->getViewMatrix();
		shader.turnOn();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1.0f);

		/*sphere1.enableWireMode();
		sphere1.render(model);*/
		//Dibujado de la geometría y recibe la matriz de transformación
		/*cylinder1.render(model);
		cylinder1.enableWireMode();
		*/
		//box1.enableWireMode();
		box1.render(glm::scale(model, glm::vec3(1.0,1.25,0.1)));
		//articulación
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1,0.1,0.1)));
		//brazo
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0f, 0.0f));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));
		//art2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1,0.1,0.1)));
		//hueso2

		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.25f, 0.0f, 0.0f));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.5, 0.1)));

		//ojo
		glm::mat4 ojo = glm::translate(model, glm::vec3(0.25f, 0.20f, 0.05f));
		sphere2.enableFillMode();
		sphere2.render(glm::scale(ojo, glm::vec3(0.2, 0.2, 0.1)));

		glm::mat4 ojoi = glm::translate(ojo, glm::vec3(0.0f, 0.0f, 0.05f));
		sphere3.enableFillMode();
		sphere3.render(glm::scale(ojoi, glm::vec3(0.09, 0.09, 0.1)));

		//ojo2
		glm::mat4 ojo2 = glm::translate(model, glm::vec3(-0.25f, 0.20f, 0.05f));
		sphere2.enableFillMode();
		sphere2.render(glm::scale(ojo2, glm::vec3(0.2, 0.2, 0.1)));

		glm::mat4 ojoi2 = glm::translate(ojo2, glm::vec3(0.0f, 0.0f, 0.05f));
		sphere3.enableFillMode();
		sphere3.render(glm::scale(ojoi2, glm::vec3(0.09, 0.09, 0.1)));
		//articulaciónb2
		glm::mat4 j3 = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j3, glm::vec3(0.1, 0.1, 0.1)));
		//brazo2
		glm::mat4 l3 = glm::translate(j3, glm::vec3(-0.25f, 0.0f, 0.0f));
		l3 = glm::rotate(l3, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l3, glm::vec3(0.1, 0.5, 0.1)));
		//art2b2
		glm::mat4 j4 = glm::translate(j3, glm::vec3(-0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j4, glm::vec3(0.1, 0.1, 0.1)));
		//hueso2b2

		glm::mat4 l4 = glm::translate(j4, glm::vec3(-0.25f, 0.0f, 0.0f));
		l4 = glm::rotate(l4, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l4, glm::vec3(0.1, 0.5, 0.1)));

		//articulaciónp1
		glm::mat4 ap11 = glm::translate(model, glm::vec3(-0.25f, -0.65f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap11, glm::vec3(0.1, 0.1, 0.1)));
		//hueso1p1
		glm::mat4 hp11 = glm::translate(ap11, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp11, glm::vec3(0.1, 0.5, 0.1)));
		//art2p1
		glm::mat4 ap12 = glm::translate(ap11, glm::vec3(0.0f, -0.5f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap12, glm::vec3(0.1, 0.1, 0.1)));
		//hueso2p1

		glm::mat4 hp12 = glm::translate(ap12, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp12, glm::vec3(0.1, 0.5, 0.1)));

		//articulaciónp2
		glm::mat4 ap21 = glm::translate(model, glm::vec3(0.25f, -0.65f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap21, glm::vec3(0.1, 0.1, 0.1)));
		//hueso1p2
		glm::mat4 hp21 = glm::translate(ap21, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp21, glm::vec3(0.1, 0.5, 0.1)));
		//art2p2
		glm::mat4 ap22 = glm::translate(ap21, glm::vec3(0.0f, -0.5f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap22, glm::vec3(0.1, 0.1, 0.1)));
		//hueso2p2

		glm::mat4 hp22 = glm::translate(ap22, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp22, glm::vec3(0.1, 0.5, 0.1)));

		glm::mat4 pan = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.05f));
		box2.enableFillMode();
		box2.render(glm::scale(pan, glm::vec3(1.0, 0.4,0.1)));

		glm::mat4 pan2 = glm::translate(model, glm::vec3(-0.5f, -0.45f, 0.0f));
		box2.enableFillMode();
		box2.render(glm::scale(pan2, glm::vec3(0.05, 0.38, 0.2)));

		glm::mat4 pan3 = glm::translate(model, glm::vec3(0.5f, -0.45f, 0.0f));
		box2.enableFillMode();
		box2.render(glm::scale(pan3, glm::vec3(0.05, 0.38, 0.2)));

		glm::mat4 panp1 = glm::translate(model, glm::vec3(-0.25f, -.73f, 0.0f));
		cylinder2.enableFillMode();
		cylinder2.render(glm::scale(panp1, glm::vec3(0.25, 0.15, 0.1)));

		glm::mat4 panp2 = glm::translate(model, glm::vec3(0.25f, -.73f, 0.0f));
		cylinder2.enableFillMode();
		cylinder2.render(glm::scale(panp2, glm::vec3(0.25, 0.15, 0.1)));

		shader.turnOff();

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
