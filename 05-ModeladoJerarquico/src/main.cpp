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
/*Para el bob sponja*/
Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Sphere sphere4(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Box box1;
Box box2;
/************/
/*Para r2d2*/
Sphere sphere5(20, 20); //esfera negra
Cylinder  cylinder3(20, 20, 0.5, 0.5); //cilindro blanco
Box box3; //Caja azul
Box box4; //caja blanca
Box box5; //caja blanca

/******************/


bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;
float rot1 = 0.0, rot2 = 0.0, rot3=0.0, rot4=0.0;
float rot5 = 0.0, rot6 = 0.0, rot7 = 0.0, rot8 = 0.0;
float rot9 = 0.0, rot10 = 0.0, rot11 = 0.0, rot12 = 0.0;
float rot13 = 0.0, rot14 = 0.0, rot15 = 0.0, rot16 = 0.0;
float rot17 = 0.0, rot18 = 0.0, rot19 = 0.0, rot20 = 0.0;
float rot21 = 0.0, rot22 = 0.0, rot23 = 0.0;
float rot0 = 0.0, dz = 0.0;
float rotr0 = 0.0, dzr = 0.0;

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
	sphere2.setShader(&shader);
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphere3.init();
	sphere3.setShader(&shader);
	sphere3.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	sphere4.init();
	sphere4.setShader(&shader);
	sphere4.setColor(glm::vec4(0.75, 0.75, 0.75, 1.0));

	sphere5.init();
	sphere5.setShader(&shader);
	sphere5.setColor(glm::vec4(0.0, 0.0, 0.0, 0.0));

	cylinder1.init();
	cylinder1.setShader(&shader);
	cylinder1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shader);
	cylinder2.setColor(glm::vec4(0.35, 0.15, 0.16, 1.0));

	cylinder3.init();
	cylinder3.setShader(&shader);
	cylinder3.setColor(glm::vec4(1, 1, 1, 1.0));

	box1.init();
	box1.setShader(&shader);
	box1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));

	box2.init();
	box2.setShader(&shader);
	box2.setColor(glm::vec4(0.35, 0.15, 0.16, 1.0));

	box3.init();
	box3.setShader(&shader);
	box3.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	box4.init();
	box4.setShader(&shader);
	box4.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	box5.init();
	box5.setShader(&shader);
	box5.setColor(glm::vec4(0.75, 0.75, 0.75, 1.0));
	
	camera->setPosition(glm::vec3(2.0, 0.0, 4.0));
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
	sphere4.destroy();
	sphere5.destroy();

	cylinder1.destroy();
	cylinder2.destroy();
	cylinder3.destroy();

	box1.destroy();
	box2.destroy();
	box3.destroy();
	box4.destroy();
	box5.destroy();

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
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot15 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot15 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot16 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot16 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot17 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot17 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot18 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot18 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot19 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot19 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot20 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot20 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot21 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot21 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot22 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot22 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot23 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot23 -= 0.001;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		rot0 = 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		rot0 = -0.001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		dz = 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		dz = -0.001;
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rotr0 = 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rotr0 = -0.001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dzr = 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dzr = -0.001;
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model2 = glm::mat4(1.0f);


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
		sphere2.render(glm::scale(ojo, glm::vec3(0.3, 0.3, 0.1)));

		glm::mat4 ojoi = glm::translate(ojo, glm::vec3(0.0f, 0.0f, 0.03f));
		sphere3.enableFillMode();
		sphere3.render(glm::scale(ojoi, glm::vec3(0.15, 0.15, 0.1)));

		glm::mat4 ojoi12 = glm::translate(ojo, glm::vec3(0.0f, 0.0f, 0.04f));
		sphere5.enableFillMode();
		sphere5.render(glm::scale(ojoi12, glm::vec3(0.1, 0.1, 0.1)));

		//ojo2
		glm::mat4 ojo2 = glm::translate(model, glm::vec3(-0.25f, 0.20f, 0.05f));
		sphere2.enableFillMode();
		sphere2.render(glm::scale(ojo2, glm::vec3(0.3, 0.3, 0.1)));

		glm::mat4 ojoi2 = glm::translate(ojo2, glm::vec3(0.0f, 0.0f, 0.03f));
		sphere3.enableFillMode();
		sphere3.render(glm::scale(ojoi2, glm::vec3(0.15, 0.15, 0.1)));


		glm::mat4 ojoi22 = glm::translate(ojo2, glm::vec3(0.0f, 0.0f, 0.04f));
		sphere5.enableFillMode();
		sphere5.render(glm::scale(ojoi22, glm::vec3(0.1, 0.1, 0.1)));

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
		ap11 = glm::rotate(ap11, rot9, glm::vec3(0, 0, 1));
		ap11 = glm::rotate(ap11, rot10, glm::vec3(1, 0, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap11, glm::vec3(0.1, 0.1, 0.1)));
		//hueso1p1
		glm::mat4 hp11 = glm::translate(ap11, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp11, glm::vec3(0.1, 0.5, 0.1)));
		//art2p1
		glm::mat4 ap12 = glm::translate(ap11, glm::vec3(0.0f, -0.5f, 0.0f));
		ap12 = glm::rotate(ap12, rot11, glm::vec3(1, 0, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap12, glm::vec3(0.1, 0.1, 0.1)));
		//hueso2p1

		glm::mat4 hp12 = glm::translate(ap12, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp12, glm::vec3(0.1, 0.5, 0.1)));

		//zapato1
		glm::mat4 z1 = glm::translate(ap12, glm::vec3(0.0f, -0.5f, 0.05f));
		z1 = glm::rotate(z1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		z1 = glm::rotate(z1, glm::radians(90.0f), glm::vec3(1, 0, 0));
		cylinder2.render(glm::scale(z1, glm::vec3(0.15, 0.25, 0.1)));

		//articulaciónp2
		glm::mat4 ap21 = glm::translate(model, glm::vec3(0.25f, -0.65f, 0.0f));
		ap21 = glm::rotate(ap21, rot12, glm::vec3(0, 0, 1));
		ap21 = glm::rotate(ap21, rot13, glm::vec3(1, 0, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap21, glm::vec3(0.1, 0.1, 0.1)));
		//hueso1p2
		glm::mat4 hp21 = glm::translate(ap21, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp21, glm::vec3(0.1, 0.5, 0.1)));
		//art2p2
		glm::mat4 ap22 = glm::translate(ap21, glm::vec3(0.0f, -0.5f, 0.0f));
		ap22 = glm::rotate(ap22, rot14, glm::vec3(1, 0, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(ap22, glm::vec3(0.1, 0.1, 0.1)));
		//hueso2p2

		glm::mat4 hp22 = glm::translate(ap22, glm::vec3(0.0f, -0.25f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(hp22, glm::vec3(0.1, 0.5, 0.1)));

		//zapato2
		glm::mat4 z2 = glm::translate(ap22, glm::vec3(0.0f, -0.5f, 0.05f));
		z2 = glm::rotate(z2, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		z2 = glm::rotate(z2, glm::radians(90.0f), glm::vec3(1, 0, 0));
		cylinder2.render(glm::scale(z2, glm::vec3(0.15, 0.25, 0.1)));

		//pantalon
		glm::mat4 pan = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.05f));
		box2.enableFillMode();
		box2.render(glm::scale(pan, glm::vec3(1.0, 0.4, 0.1)));

		glm::mat4 pan2 = glm::translate(model, glm::vec3(-0.5f, -0.45f, 0.0f));
		box2.enableFillMode();
		box2.render(glm::scale(pan2, glm::vec3(0.05, 0.38, 0.2)));

		glm::mat4 pan3 = glm::translate(model, glm::vec3(0.5f, -0.45f, 0.0f));
		box2.enableFillMode();
		box2.render(glm::scale(pan3, glm::vec3(0.05, 0.38, 0.2)));

		glm::mat4 panp1 = glm::translate(ap11, glm::vec3(0.0f, -.025f, 0.0f));
		cylinder2.enableFillMode();
		cylinder2.render(glm::scale(panp1, glm::vec3(0.25, 0.15, 0.1)));

		glm::mat4 panp2 = glm::translate(ap21, glm::vec3(0.0f, -.025f, 0.0f));
		cylinder2.enableFillMode();
		cylinder2.render(glm::scale(panp2, glm::vec3(0.25, 0.15, 0.1)));

		/***********************Inicia el modelado del r2d2*************/
		model2 = glm::translate(model2, glm::vec3(0, 0, dzr));
		model2 = glm::rotate(model2, rotr0, glm::vec3(0, 1, 0));
	
		//torso
		glm::mat4 cuerpo = glm::translate(model2, glm::vec3(3, -.5, dz));
		cuerpo = glm::rotate(cuerpo, rot23, glm::vec3(0, 1, 0));
		cylinder3.enableFillMode();
		cylinder3.render(cuerpo);

		//cabeza
		glm::mat4 cabeza = glm::translate(cuerpo, glm::vec3(0, .5, 0));
		cabeza = glm::rotate(cabeza, rot21, glm::vec3(1, 0, 0));
		cabeza = glm::rotate(cabeza, rot22, glm::vec3(0, 1, 0));
		sphere4.enableFillMode();
		sphere4.render(cabeza);
		
		//ojo - cuadrado
		glm::mat4 ojoc = glm::translate(cabeza, glm::vec3(0, .3, 0.40));
		ojoc = glm::rotate(ojoc, glm::radians(-35.f), glm::vec3(1.0f, 0.0f, 0.0f));
		box3.render(glm::scale(ojoc, glm::vec3(0.25, 0.25, 0.05)));

		//ojo esfera
		glm::mat4 ojoe = glm::translate(ojoc, glm::vec3(0, 0, 0.02));
		sphere5.render(glm::scale(ojoe, glm::vec3(0.15, 0.15, 0.05)));

		//adorno cabeza 1
		glm::mat4 adorno1 = glm::translate(cabeza, glm::vec3(.025, .1, 0.5));
		adorno1 = glm::rotate(adorno1, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		box3.render(glm::scale(adorno1, glm::vec3(0.15, 0.1, 0.05)));
		//adorno cabeza2
		glm::mat4 adorno2 = glm::translate(cabeza, glm::vec3(-.1, .1, 0.5));
		adorno2 = glm::rotate(adorno2, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		box3.render(glm::scale(adorno2, glm::vec3(0.05, 0.1, 0.05)));
		
		//articulación
		glm::mat4 art1 = glm::translate(cuerpo, glm::vec3(0.5f, 0.25f, 0.0f));
		art1 = glm::rotate(art1, rot15, glm::vec3(0, 0, 1));
		art1 = glm::rotate(art1, rot16, glm::vec3(0, 1, 0));
		sphere2.render(glm::scale(art1, glm::vec3(0.1, 0.1, 0.1)));

		//brazo
		glm::mat4 br2d21 = glm::translate(art1, glm::vec3(0.25f, 0.0f, 0.0f));
		box4.render(glm::scale(br2d21, glm::vec3(0.7, .1, 0.1)));

		//articulacion mano
		glm::mat4 art12 = glm::translate(art1, glm::vec3(0.65f, 0.0f, 0.0f));
		art12 = glm::rotate(art12, rot19, glm::vec3(1, 0, 0));
		sphere3.render(glm::scale(art12, glm::vec3(0.1, 0.1, 0.1)));

		//mano
		glm::mat4 br2d212 = glm::translate(art12, glm::vec3(0.025f, 0.0f, 0.0f));
		box5.render(glm::scale(br2d212, glm::vec3(0.2, .3, 0.2)));

		//articulación2
		glm::mat4 art2 = glm::translate(cuerpo, glm::vec3(-0.5f, 0.25f, 0.0f));
		art2 = glm::rotate(art2, rot17, glm::vec3(0, 0, 1));
		art2 = glm::rotate(art2, rot18, glm::vec3(0, 1, 0));
		sphere2.render(glm::scale(art2, glm::vec3(0.1, 0.1, 0.1)));

		//brazo2
		glm::mat4 br2d22 = glm::translate(art2, glm::vec3(-0.25f, 0.0f, 0.0f));
		br2d22 = glm::rotate(br2d22, glm::radians(90.0f), glm::vec3(0, 0.0, 1.0));
		box4.render(glm::scale(br2d22, glm::vec3(0.1, .7, 0.1)));

		//articulacion mano2
		glm::mat4 art22 = glm::translate(art2, glm::vec3(-0.65f, 0.0f, 0.0f));
		art22 = glm::rotate(art22, rot20, glm::vec3(1, 0, 0));
		sphere3.render(glm::scale(art22, glm::vec3(0.1, 0.1, 0.1)));

		//mano2
		glm::mat4 br2d222 = glm::translate(art22, glm::vec3(-0.025f, 0.0f, 0.0f));
		box5.render(glm::scale(br2d222, glm::vec3(0.2, .3, 0.2)));

		/****************************************************************/
		shader.turnOff();
		dz = 0;
		rot0 = 0;
		dzr = 0;
		rotr0 = 0;
		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
