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
std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Box box1;
Box box2;


bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;
float rot1 = 0.0, rot2 = 0.0, rot3=0.0, rot4=0.0;
float rot5 = 0.0, rot6 = 0.0, rot7 = 0.0, rot8 = 0.0;
float rot9 = 0.0, rot10 = 0.0, rot11 = 0.0, rot12 = 0.0;
float rot13 = 0.0, rot14 = 0.0, rot15 = 0.0, rot16 = 0.0;
float rot0 = 0.0, dz = 0.0;

bool sentido = true;
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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");

	// Inicializar los buffers VAO, VBO, EBO

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

	// Destrucción de los VAO, EBO, VBO
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

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
	offsetX = 0;
	offsetY = 0;
	//release


	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
		sentido = false;
	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot1 += 0.001;
	else if((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot1 -= 0.001;
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot2 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot3 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot3 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot4 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot4 -= 0.001;

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot5 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot5 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot6 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot6 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot7 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot7 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot8 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot8 -= 0.01;
	

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot9 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot9 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot10 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot10 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot11 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot11 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot12 += 0.01;
	else if ((glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot12 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot13 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot13 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot14 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot14 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot15 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot15 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot16 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot16 -= 0.001;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot0 = 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot0 = -0.001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		dz = 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		dz = -0.001;
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	glm::mat4 model = glm::mat4(1.0f);

	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));
		
		box1.render(glm::scale(model, glm::vec3(1.0, 1.25, 0.1)));
		//articulación
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		j1 = glm::rotate(j1, rot1, glm::vec3(0, 0, 1));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0));
		//brazo
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0f, 0.0f));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));
		//art2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5f, 0.0f, 0.0f));
		j2 = glm::rotate(j2, rot3, glm::vec3(0, 0, 1));
		j2 = glm::rotate(j2, rot4, glm::vec3(0, 1, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));
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
		j3 = glm::rotate(j3, rot5, glm::vec3(0, 0, 1));
		j3 = glm::rotate(j3, rot6, glm::vec3(0, 1, 0));
		//brazo2
		glm::mat4 l3 = glm::translate(j3, glm::vec3(-0.25f, 0.0f, 0.0f));
		l3 = glm::rotate(l3, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l3, glm::vec3(0.1, 0.5, 0.1)));
		//art2b2
		glm::mat4 j4 = glm::translate(j3, glm::vec3(-0.5f, 0.0f, 0.0f));
		j4 = glm::rotate(j4, rot7, glm::vec3(0, 0, 1));
		j4 = glm::rotate(j4, rot8, glm::vec3(0, 1, 0));
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
		box2.render(glm::scale(pan, glm::vec3(1.0, 0.4, 0.1)));

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
		dz = 0;
		rot0 = 0;
		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
