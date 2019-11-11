#define _USE_MATH_DEFINES
#include <cmath>
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

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

GLFWwindow* window;

Shader shader;
//Shader de texturizado
Shader shaderTexture;
//Shader con iluminacion solo color
Shader shaderColorLighting;
//Shader con iluminacion y textura
Shader shaderTextureLighting;
// Descomentar
//Shader con materiales
Shader shaderMaterialLighting;
// Descomentar
//Shader con skybox
Shader shaderSkybox;
// Shader con multiples luces
Shader shaderMulLighting;

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Sphere sphere4(20, 20);
Sphere sphere5(20, 20);
Sphere sphereLamp(20, 20);
// Descomentar
Sphere skyboxSphere(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Cylinder cylinder3(20, 20, 0.5, 0.5);

Cylinder cylinderMaterials(20, 20, 0.5, 0.5);
Box boxMaterials;
Box box1;
Box box2;
Box box3;
Box box4;
Box box5;
Box boxParedes;
Box boxPiso;
Box boxCesped;
Box boxCarretera;
// Models complex instances
//Model modelRock;
//Model modelRailRoad;
//Model modelAircraft;
Model modelCar;
Model modelEclipseWheelsFrontal;
Model modelEclipseWheelsRear;

Model modelRosa;
Model modelMaceta;
Model modelJardinera;
Model modelMueble;
Model modelSala;
Model modelSalap;
Model modelToilet;
Model modelHandWash;
Model modelTable;
Model modelLampara;

Model modelHeliChasis;
Model modelHeliHeliMeid;
Model modelHeliHeliCh;

Model modelLambo;
Model modelLamboLeftDor;
Model modelLamboRightDoor;

Model modelLamboFrontWheels;
Model modelLamboBackWheels;

Model modelTree;
Model modelStar;
Model modelSerie;
Model modelChBall1;
Model modelChBall2;
Model modelChBall3;
Model modelChBall4;
Model modelChBall5;

GLuint textureID1, textureID2, textureID3, textureID4, textureID5, textureID6, textureID7, textureID8, textureID9;
GLuint textureID10, textureID11, textureID12, textureID13, textureID14, textureID15, textureID16, textureID17;
GLuint textureID18, textureID19, textureID20, textureID21, textureID22, textureID23, textureID24, textureID25;
GLuint skyboxTextureID;
int offset1 = 1;
int offset2 = 4;
int offset3 = 7;
int offset4 = 7;
int offset5 = 4;

int offsetc1 = 0;
int offsetc2 = 0;
int offsetc3 = 0;

float offsetState = 0.0;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/ely_hills/hills_ft.tga",
		"../Textures/ely_hills/hills_bk.tga",
		"../Textures/ely_hills/hills_up.tga",
		"../Textures/ely_hills/hills_dn.tga",
		"../Textures/ely_hills/hills_rt.tga",
		"../Textures/ely_hills/hills_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
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
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode);
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
	shaderTexture.initialize("../Shaders/texturizado_res.vs",
		"../Shaders/texturizado_res.fs");
	shaderColorLighting.initialize("../Shaders/iluminacion_color_res.vs",
		"../Shaders/iluminacion_color_res.fs");
	shaderTextureLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/iluminacion_texture_res.fs");
	shaderMaterialLighting.initialize("../Shaders/iluminacion_material.vs",
		"../Shaders/iluminacion_material_res.fs");
	shaderSkybox.initialize("../Shaders/cubeTexture.vs",
		"../Shaders/cubeTexture.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/multipleLights.fs");

	// Inicializar los buffers VAO, VBO, EBO
	sphere1.init();
	// Método setter que colocar el apuntador al shader
	sphere1.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphere2.init();
	// Método setter que colocar el apuntador al shader
	sphere2.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphere3.init();
	sphere3.setShader(&shaderColorLighting);
	sphere3.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	sphere4.init();
	sphere4.setShader(&shaderColorLighting);
	sphere4.setColor(glm::vec4(0.75, 0.75, 0.75, 1.0));

	sphere5.init();
	sphere5.setShader(&shaderColorLighting);
	sphere5.setColor(glm::vec4(0.0, 0.0, 0.0, 0.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphereLamp.init();
	// Método setter que colocar el apuntador al shader
	sphereLamp.setShader(&shader);
	//Setter para poner el color de la geometria
	sphereLamp.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shaderColorLighting);
	cylinder1.setColor(glm::vec4(0.99, 0.9, 0.05, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shaderMulLighting);

	cylinder3.init();
	cylinder3.setShader(&shader);
	cylinder3.setColor(glm::vec4(1, 1, 1, 1.0));

	cylinderMaterials.init();
	cylinderMaterials.setShader(&shaderMaterialLighting);
	cylinderMaterials.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	boxMaterials.init();
	boxMaterials.setShader(&shaderMaterialLighting);

	// Inicializacion de la esfera del skybox
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	box1.init();
	// Settea el shader a utilizar
	box1.setShader(&shaderMulLighting);

	box2.init();
	box2.setShader(&shaderColorLighting);
	box2.setColor(glm::vec4(0.35, 0.15, 0.16, 1.0));


	box3.init();
	box3.setShader(&shaderColorLighting);
	box3.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));


	box4.init();
	box4.setShader(&shader);
	box4.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	box5.init();
	box5.setShader(&shader);
	box5.setColor(glm::vec4(0.75, 0.75, 0.75, 1.0));

	boxParedes.init();
	boxParedes.setShader(&shaderMulLighting);

	boxPiso.init();
	boxPiso.setShader(&shaderMaterialLighting);

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxCarretera.init();
	boxCarretera.setShader(&shaderMulLighting);

	/*modelRock.loadModel("../models/rock/rock.obj");
	modelRock.setShader(&shaderMulLighting);

	modelRailRoad.loadModel("../models/railroad/railroad_track.obj");
	modelRailRoad.setShader(&shaderMulLighting);

	modelAircraft.loadModel("../models/Aircraft_obj/E 45 Aircraft_obj.obj");
	modelAircraft.setShader(&shaderMulLighting);*/

	/////////////////////
	/////eclipse car/////
	/////////////////////
	modelCar.loadModel("../models/Eclipse/2003eclipse_chasis.obj");
	modelCar.setShader(&shaderMulLighting);

	modelEclipseWheelsFrontal.loadModel("../models/Eclipse/2003eclipse_frontal_wheels.obj");
	modelEclipseWheelsFrontal.setShader(&shaderMulLighting);

	modelEclipseWheelsRear.loadModel("../models/Eclipse/2003eclipse_rear_wheels.obj");
	modelEclipseWheelsRear.setShader(&shaderMulLighting);

	/////////////////////
	/////Helicoptero/////
	/////////////////////
	modelHeliChasis.loadModel("../models/Helicopter/Mi_24_chasis.obj");
	modelHeliChasis.setShader(&shaderMulLighting);

	modelHeliHeliMeid.loadModel("../models/Helicopter/Mi_24_heli.obj");
	modelHeliHeliMeid.setShader(&shaderMulLighting);

	modelHeliHeliCh.loadModel("../models/Helicopter/Mi_24_heli2.obj");
	modelHeliHeliCh.setShader(&shaderMulLighting);
	/////////////////////
	/////Lambo car/////
	/////////////////////
	modelLambo.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_chasis.obj");
	modelLambo.setShader(&shaderMulLighting);
	modelLamboLeftDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_left_dor.obj");
	modelLamboLeftDor.setShader(&shaderMulLighting);
	modelLamboRightDoor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_door2.obj");
	modelLamboRightDoor.setShader(&shaderMulLighting);
	modelLamboFrontWheels.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_wheels.obj");
	modelLamboFrontWheels.setShader(&shaderMulLighting);
	modelLamboBackWheels.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_wheels2.obj");
	modelLamboBackWheels.setShader(&shaderMulLighting);


	/////////////////////
	/////Muebles/////////
	/////////////////////
	/*modelMueble.loadModel("../models/Wood_Table/\Wood_Table.obj");
	modelMueble.setShader(&shaderMulLighting);

	modelTable.loadModel("../models/table/table.obj");
	modelTable.setShader(&shaderMulLighting);

	modelSala.loadModel("../models/sofa/sofa.obj");
	modelSala.setShader(&shaderMulLighting);

	modelRosa.loadModel("../models/rosa/rosa.obj");
	modelRosa.setShader(&shaderMulLighting);

	modelMaceta.loadModel("../models/plantamaceta/plantamaceta.obj");
	modelMaceta.setShader(&shaderMulLighting);

	modelJardinera.loadModel("../models/jardinera/jardinera.obj");
	modelJardinera.setShader(&shaderMulLighting);


	modelSalap.loadModel("../models/sofap/sofap.obj");
	modelSalap.setShader(&shaderMulLighting);

	
	modelToilet.loadModel("../models/toilet/toilet.obj");
	modelToilet.setShader(&shaderMulLighting);

	modelHandWash.loadModel("../models/lavamanos/bathroom_vanity.obj");
	modelHandWash.setShader(&shaderMulLighting);*/

	modelLampara.loadModel("../models/lampara1/lampara.obj");
	modelLampara.setShader(&shaderMulLighting);

	////////////////////////
	/////Decoración/////////
	////////////////////////
	modelTree.loadModel("../models/christmas_tree/Christmas+tree.obj");
	modelTree.setShader(&shaderMulLighting);

	modelStar.loadModel("../models/star_obj/gold_star.obj");
	modelStar.setShader(&shaderMulLighting);

	modelSerie.loadModel("../models/serie/jugando.obj");
	modelSerie.setShader(&shaderMulLighting);

	modelChBall1.loadModel("../models/Christmas_Bells_obj/ball1.obj");
	modelChBall1.setShader(&shaderMulLighting);

	modelChBall2.loadModel("../models/Christmas_Bells_obj/ball2.obj");
	modelChBall2.setShader(&shaderMulLighting);

	modelChBall3.loadModel("../models/Christmas_Bells_obj/ball3.obj");
	modelChBall3.setShader(&shaderMulLighting);

	modelChBall4.loadModel("../models/Christmas_Bells_obj/ball4.obj");
	modelChBall4.setShader(&shaderMulLighting);

	modelChBall5.loadModel("../models/Christmas_Bells_obj/ball5.obj");
	modelChBall5.setShader(&shaderMulLighting);

	camera->setPosition(glm::vec3(-4.5, 4.8, 10.0));

	// Descomentar
	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	// Definiendo la textura a utilizar
	Texture texture1("../Textures/sponge.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	FIBITMAP* bitmap = texture1.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	unsigned char* data = texture1.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID1);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture1.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture2("../Textures/water.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texture2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID2);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture2.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture3("../Textures/goku.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture3.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture3.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID3);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID3);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture3.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture4("../Textures/texturaLadrillos.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture4.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture4.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID4);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture4.freeImage(bitmap);
	Texture texture5("../Textures/duela.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture5.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture5.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID5);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID5);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture5.freeImage(bitmap);

	Texture texture6("../Textures/madera_cherry.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture6.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID6);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID6);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture6.freeImage(bitmap);

	Texture texture7("../Textures/cortina.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture7.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture7.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID7);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID7);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture7.freeImage(bitmap);
	Texture texture8("../Textures/Netflix.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture8.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture8.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID8);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID8);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture8.freeImage(bitmap);

	Texture texture9("../Textures/madera.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture9.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID9);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID9);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture9.freeImage(bitmap);

	Texture texture10("../Textures/pared1.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture10.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID10);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID10);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture10.freeImage(bitmap);

	Texture texture11("../Textures/colcha.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture11.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID11);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID11);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture11.freeImage(bitmap);

	Texture texture12("../Textures/almohada.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture12.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture12.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID12);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID12);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture12.freeImage(bitmap);

	Texture texture13("../Textures/zaguan.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture13.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture13.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID13);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID13);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture13.freeImage(bitmap);

	Texture texture14("../Textures/puerta_sala.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture14.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture14.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID14);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID14);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture14.freeImage(bitmap);

	Texture texture15("../Textures/probando.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture15.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture15.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID15);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID15);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture15.freeImage(bitmap);

	Texture texture16("../Textures/ventanal_arriba.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture16.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture16.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID16);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID16);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture16.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture17("../Textures/cesped.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture17.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture17.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID17);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID17);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture17.freeImage(bitmap);

	Texture texture18("../Textures/carretera.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture18.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture18.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID18);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID18);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture18.freeImage(bitmap);

	Texture texture19("../Textures/pared_naranja.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture19.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture19.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID19);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID19);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture19.freeImage(bitmap);

	Texture texture20("../Textures/pared_azul.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture20.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture20.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID20);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID20);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture20.freeImage(bitmap);

	Texture texture21("../Textures/piso_piedra.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture21.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture21.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID21);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID21);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture21.freeImage(bitmap);

	Texture texture22("../Textures/piso_gris.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture22.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture22.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID22);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID22);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture22.freeImage(bitmap);
	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP* bitmap = skyboxTexture.loadImage(true);
		unsigned char* data = skyboxTexture.convertToData(bitmap, imageWidth,
			imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}


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
	sphereLamp.destroy();


	cylinder1.destroy();
	cylinder2.destroy();
	cylinder3.destroy();
	cylinderMaterials.destroy();

	box1.destroy();
	box2.destroy();
	box3.destroy();
	box4.destroy();
	box5.destroy();
	boxMaterials.destroy();
	boxParedes.destroy();
	shader.destroy();
	shaderColorLighting.destroy();
	shaderMaterialLighting.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTexture.destroy();
	shaderTextureLighting.destroy();

	modelCar.destroy();
	modelEclipseWheelsFrontal.destroy();
	modelEclipseWheelsRear.destroy();

	modelHeliChasis.destroy();
	modelHeliHeliMeid.destroy();
	modelHeliHeliCh.destroy();

	modelLambo.destroy();
	modelLamboLeftDor.destroy();
	modelLamboRightDoor.destroy();
	modelLamboBackWheels.destroy();
	modelLamboFrontWheels.destroy();

	modelMueble.destroy();
	modelSala.destroy();
	modelRosa.destroy();
	modelMaceta.destroy();
	modelJardinera.destroy();
	modelLampara.destroy();
	modelSalap.destroy();
	modelToilet.destroy();
	modelTable.destroy();
	modelHandWash.destroy();

	modelTree.destroy();
	modelStar.destroy();

	modelChBall1.destroy();
	modelChBall2.destroy();
	modelChBall3.destroy();
	modelChBall4.destroy();
	modelChBall5.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode) {
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

bool processInput(bool continueApplication) {
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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
	offsetX = 0;
	offsetY = 0;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot1 += 0.001;
	else if ((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))
		rot1 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
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

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rotr0 = 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rotr0 = -0.001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dzr = 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dzr = -0.001;
	glfwPollEvents();
	sentido = true;
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 model2 = glm::mat4(1.0f);
	float offX = 0.0;
	float angle = 0.0;
	float ratio = 30.0;
	float rotHeliHeliy = 0.0;
	float rotHeliHeliz = 0.0;
	float rotWheelx = 0.0;
	float rotWheely = 0.0;
	float rotWheelLamboX = 0.0;
	float rotWheelLamboY = 0.0;
	float dorRotCount = 0.0;
	int stateDoor = 0;



	glm::mat4 matrixModelAircraft = glm::mat4(1.0);
	matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(8.0, 2.0, -10.0));
	glm::mat4 matrixModelCar = glm::mat4(1.0);
	matrixModelCar = glm::translate(matrixModelCar, glm::vec3(-10, -1.6, -12.0));
	matrixModelCar = glm::scale(matrixModelCar, glm::vec3(0.65, 0.65, 0.65));

	glm::mat4 modelMatrixLambo = glm::mat4(1.0);
	modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(-15.0, -1.6, -15.0));
	modelMatrixLambo = glm::scale(modelMatrixLambo, glm::vec3(2.0, 2.0, 2.0));


	glm::mat4 modelMatrixHeliChasis = glm::mat4(1.0);
	modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(20, 20, 0));

	int state = 0;
	int stateheli = 0;

	float offsetAircraftAdvance = 0.0;
	float  offsetLamboAdvance = 0.0;
	float offsetLamboRot = 0.0;
	float offsetAircraftRot = 0.0;

	float offsetHeliAdvance = 0.0;

	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));
		// Settea la matriz de vista y projection al shader con solo textura
		shaderTexture.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion solo color
		shaderColorLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderColorLighting.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con textura
		shaderTextureLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTextureLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con material
		shaderMaterialLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMaterialLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
			glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Propiedades de la luz para objetos con color
		shaderColorLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderColorLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderColorLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));


		// Propiedades de la luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderTextureLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

		// Propiedades de la luz para objetos con multiples luces
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
		// Esto es para la luz spotlight
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camera->getFront()));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.001);

		// Esto es para la luces pointlights
		shaderMulLighting.setInt("pointLightCount", 14);
		shaderMulLighting.setVectorFloat3("pointLights[0].position", glm::value_ptr((glm::vec3(-3.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[0].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[0].linear", offset1);
		shaderMulLighting.setFloat("pointLights[0].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[1].position", glm::value_ptr((glm::vec3(-4.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
		shaderMulLighting.setFloat("pointLights[1].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[1].linear", offset2);
		shaderMulLighting.setFloat("pointLights[1].quadratic", 0.004);

		//luz azul
		shaderMulLighting.setVectorFloat3("pointLights[2].position", glm::value_ptr((glm::vec3(-5.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
		shaderMulLighting.setFloat("pointLights[2].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[2].linear", offset3);
		shaderMulLighting.setFloat("pointLights[2].quadratic", 0.004);

		//luz extra amarilla
		shaderMulLighting.setVectorFloat3("pointLights[3].position", glm::value_ptr((glm::vec3(-2.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[3].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[3].linear", offset4);
		shaderMulLighting.setFloat("pointLights[3].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[4].position", glm::value_ptr((glm::vec3(-1.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.specular", glm::value_ptr(glm::vec3(0.34, 0.13, 0.39)));
		shaderMulLighting.setFloat("pointLights[4].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[4].linear", offset5);
		shaderMulLighting.setFloat("pointLights[4].quadratic", 0.004);

		//luz del baño
		shaderMulLighting.setVectorFloat3("pointLights[5].position", glm::value_ptr((glm::vec3(-1.0, 1.3, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[5].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[5].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[5].quadratic", 0.004);

		//luz comedor
		shaderMulLighting.setVectorFloat3("pointLights[6].position", glm::value_ptr((glm::vec3(2.5, 1.12, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[6].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[6].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[6].quadratic", 0.004);


		//luz cocina
		shaderMulLighting.setVectorFloat3("pointLights[7].position", glm::value_ptr((glm::vec3(6.0, 1.12, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[7].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[7].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[7].quadratic", 0.004);

		//luces sala
		shaderMulLighting.setVectorFloat3("pointLights[8].position", glm::value_ptr((glm::vec3(0.0, 1.0, 3.0))));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[8].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[8].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[8].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[9].position", glm::value_ptr((glm::vec3(2.0, 1.0, 3.0))));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[9].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[9].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[9].quadratic", 0.004);

		//luz recamara abajo
		shaderMulLighting.setVectorFloat3("pointLights[10].position", glm::value_ptr((glm::vec3(7.5, 1.0, 4.0))));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[10].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[10].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[10].quadratic", 0.004);

		//luz recamara 1
		shaderMulLighting.setVectorFloat3("pointLights[11].position", glm::value_ptr((glm::vec3(7.5, 4.65, 4.0))));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[11].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[11].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[11].quadratic", 0.004);

		//luz recamara 2
		shaderMulLighting.setVectorFloat3("pointLights[12].position", glm::value_ptr((glm::vec3(7.5, 4.65, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[12].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[12].linear", 0.1);
		shaderMulLighting.setFloat("pointLights[12].quadratic", 0.004);

		//luz estrella
		shaderMulLighting.setVectorFloat3("pointLights[13].position", glm::value_ptr((glm::vec3(-4.1, 4.5, 5.0))));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[13].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[13].linear", offset1);
		shaderMulLighting.setFloat("pointLights[13].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[14].position", glm::value_ptr((glm::vec3(-4.1, 2.8, 5.0))));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[14].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[14].linear", offset2);
		shaderMulLighting.setFloat("pointLights[14].quadratic", 0.004);

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-3.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, offsetc1));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-4.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, offsetc2));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-5.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, offsetc3));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-2.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-1.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		glm::mat4 lightModelmatrix = glm::rotate(glm::mat4(1.0f), angle,
			glm::vec3(1.0f, 0.0f, 0.0f));
		lightModelmatrix = glm::translate(lightModelmatrix,
			glm::vec3(0.0f, 0.0f, -ratio));
		// Posicion luz para objetos con color
		shaderColorLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con materiales
		shaderMaterialLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));
		sphereLamp.setScale(glm::vec3(1, 1, 1));
		sphereLamp.setPosition(glm::vec3(0, 0, 0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		sphereLamp.render(lightModelmatrix);


		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));

		glBindTexture(GL_TEXTURE_2D, textureID1);
		box1.render(glm::scale(model, glm::vec3(1.0, 1.25, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

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

		//adornos torso
		glm::mat4 adornot = glm::translate(cuerpo, glm::vec3(0, .4, .85));
		box3.render(glm::scale(adornot, glm::vec3(0.25, 0.05, 0.05)));

		glm::mat4 adornot2 = glm::translate(cuerpo, glm::vec3(0, .3, .85));
		box3.render(glm::scale(adornot2, glm::vec3(0.25, 0.05, 0.05)));

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


		/*glm::mat4 modelAgua = glm::mat4(1.0);
		modelAgua = glm::translate(modelAgua, glm::vec3(5.0, 0.01, 5.0));
		modelAgua = glm::scale(modelAgua, glm::vec3(5.0, 0.01, 5.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID2);
		// Le cambiamos el shader con multiples luces NO OLVIDAR
		shaderMulLighting.setFloat("offsetX", offX);
		box2.render(modelAgua);
		glBindTexture(GL_TEXTURE_2D, 0);
		shaderMulLighting.setFloat("offsetX", 0);*/

		glm::mat4 modelCesped = glm::mat4(1.0);
		modelCesped = glm::translate(modelCesped, glm::vec3(2.25, -1.6, 0.0));
		modelCesped = glm::scale(modelCesped, glm::vec3(20.0, 0.001, 20.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID17);
		boxCesped.render(modelCesped);
		glBindTexture(GL_TEXTURE_2D, 0);

		/*glm::mat4 modelSphere = glm::mat4(1.0);
		modelSphere = glm::translate(modelSphere, glm::vec3(10.0, 0.5, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID3);
		sphere3.render(modelSphere);
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 modelCylinder = glm::mat4(1.0);
		modelCylinder = glm::translate(modelCylinder,
				glm::vec3(-3.0, 0.5, 0.0));
		// Envolvente desde el indice 0, el tamanio es 20 * 20 * 6
		// Se usa la textura 1 ( Bon sponja)
		glBindTexture(GL_TEXTURE_2D, textureID1);
		cylinder2.render(0, cylinder2.getSlices() * cylinder2.getStacks() * 6,
				modelCylinder);
		// Tapa Superior desde el indice : 20 * 20 * 6, el tamanio de indices es 20 * 3
		// Se usa la textura 2 ( Agua )
		glBindTexture(GL_TEXTURE_2D, textureID2);
		cylinder2.render(cylinder2.getSlices() * cylinder2.getStacks() * 6,
				cylinder2.getSlices() * 3, modelCylinder);
		// Tapa inferior desde el indice : 20 * 20 * 6 + 20 * 3, el tamanio de indices es 20 * 3
		// Se usa la textura 3 ( Goku )
		glBindTexture(GL_TEXTURE_2D, textureID3);
		cylinder2.render(
				cylinder2.getSlices() * cylinder2.getStacks() * 6
						+ cylinder2.getSlices() * 3, cylinder2.getSlices() * 3,
				modelCylinder);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Render del cubo con textura de ladrillos y con repeticion en x
		glm::mat4 cubeTextureModel = glm::mat4(1.0);
		cubeTextureModel = glm::translate(cubeTextureModel,
				glm::vec3(-5.0, 0.5, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderMulLighting.setVectorFloat2("scaleUV",
				glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(cubeTextureModel);
		shaderMulLighting.setVectorFloat2("scaleUV",
				glm::value_ptr(glm::vec2(0.0, 0.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		// Render del cyindro con materiales
		glm::mat4 cylinderMaterialModel = glm::mat4(1.0);
		cylinderMaterialModel = glm::translate(cylinderMaterialModel,  glm::vec3(3.0, 0.5, -3.0));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		cylinderMaterials.render(cylinderMaterialModel);

		glm::mat4 boxMaterialModel = glm::mat4(1.0f);
		boxMaterialModel = glm::translate(boxMaterialModel, glm::vec3(-3.0, 0.5, -3.0));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		boxMaterials.render(boxMaterialModel);

		//Models complex render
		glm::mat4 matrixModelRock = glm::mat4(1.0);
		matrixModelRock = glm::translate(matrixModelRock, glm::vec3(-3.0, 0.0, 6.0));
		modelRock.render(matrixModelRock);
		// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
		glActiveTexture(GL_TEXTURE0);
		// Esto es para las vias del tren
		glm::mat4 matrixModelRailroad = glm::mat4(1.0);
		matrixModelRailroad = glm::translate(matrixModelRailroad, glm::vec3(3.0, 0.0, 10.0));
		modelRailRoad.render(matrixModelRailroad);
		// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
		glActiveTexture(GL_TEXTURE0);
		*/
		//////////////////////////////////////////////////////////////
//////////////////////RENDER CASA ////////////////////////////
//////////////////////////////////////////////////////////////

///////////////////////PLANTA BAJA///////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID13);
		glm::mat4 zaguan = glm::mat4(1.0);
		zaguan = glm::translate(zaguan, glm::vec3(-4.1, 0.0, 5.8));
		boxParedes.render(glm::scale(zaguan, glm::vec3(3.4, 3.0, 0.2)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////PAREDES COCHERA//////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredizquierdapb = glm::mat4(1.0);
		paredizquierdapb = glm::translate(paredizquierdapb, glm::vec3(-6.0, 0.0, 0.0));
		boxParedes.render(glm::scale(paredizquierdapb, glm::vec3(0.4, 3.0, 12.0)));

		glm::mat4 paredpuerta = glm::mat4(1.0);
		paredpuerta = glm::translate(paredpuerta, glm::vec3(-2.3, 0.0, 5.25));
		boxParedes.render(glm::scale(paredpuerta, glm::vec3(0.2, 3.0, 1.5)));

		glm::mat4 paredicochera = glm::mat4(1.0);
		paredicochera = glm::translate(paredicochera, glm::vec3(-2.3, 0.0, -3));
		boxParedes.render(glm::scale(paredicochera, glm::vec3(0.2, 3.0, 6.0)));

		glm::mat4 paredventana = glm::mat4(1.0);
		paredventana = glm::translate(paredventana, glm::vec3(-2.3, -1.0, 1.55));
		boxParedes.render(glm::scale(paredventana, glm::vec3(0.2, 1.0, 3.0)));
		//////////////////PUERTA SALA////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID14);
		glm::mat4 puertasala = glm::mat4(1.0);
		puertasala = glm::translate(puertasala, glm::vec3(-2.3, 0.0, 3.75));
		boxParedes.render(glm::scale(puertasala, glm::vec3(0.2, 3.0, 1.5)));
		////////////////VENATNA SALA COCHERA/////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanasala = glm::mat4(1.0);
		ventanasala = glm::translate(ventanasala, glm::vec3(-2.3, 0.5, 1.55));
		boxParedes.render(glm::scale(ventanasala, glm::vec3(0.2, 2.0, 3.0)));
		//////////////////BAÑO////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertabanio = glm::mat4(1.0);
		puertabanio = glm::translate(puertabanio, glm::vec3(-1.8, -0.2, 0.0));
		boxParedes.render(glm::scale(puertabanio, glm::vec3(1.0, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredbanio1 = glm::mat4(1.0);
		paredbanio1 = glm::translate(paredbanio1, glm::vec3(-1.8, 1.3, 0.0));
		boxParedes.render(glm::scale(paredbanio1, glm::vec3(1.0, 0.4, 0.2)));

		glm::mat4 paredbanio2 = glm::mat4(1.0);
		paredbanio2 = glm::translate(paredbanio2, glm::vec3(-0.75, 0, 0.0));
		boxParedes.render(glm::scale(paredbanio2, glm::vec3(2.5, 3.0, 0.2)));

		glm::mat4 paredbanio3 = glm::mat4(1.0);
		paredbanio3 = glm::translate(paredbanio3, glm::vec3(0.4, 0, -3.0));
		boxParedes.render(glm::scale(paredbanio3, glm::vec3(0.2, 3.0, 6.0)));


		glm::mat4 paredbanio4 = glm::mat4(1.0);
		paredbanio4 = glm::translate(paredbanio4, glm::vec3(-0.9, 0, -6.0));
		boxParedes.render(glm::scale(paredbanio4, glm::vec3(3, 3.0, 0.2)));

		///////////////////COMEDOR/////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID14);
		glm::mat4 puertacomedor = glm::mat4(1.0);
		puertacomedor = glm::translate(puertacomedor, glm::vec3(1.1, 0.0, -6.0));
		boxParedes.render(glm::scale(puertacomedor, glm::vec3(1.0, 3.0, 0.2)));
		////////////////VENTANA COMEDOR/////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanacomedor = glm::mat4(1.0);
		ventanacomedor = glm::translate(ventanacomedor, glm::vec3(2.6, 0.5, -6.0));
		boxParedes.render(glm::scale(ventanacomedor, glm::vec3(2.0, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredcomedor = glm::mat4(1.0);
		paredcomedor = glm::translate(paredcomedor, glm::vec3(2.6, -1.0, -6.0));
		boxParedes.render(glm::scale(paredcomedor, glm::vec3(2, 1.0, 0.2)));

		glm::mat4 paredcomedor2 = glm::mat4(1.0);
		paredcomedor2 = glm::translate(paredcomedor2, glm::vec3(4, 0, -6.0));
		boxParedes.render(glm::scale(paredcomedor2, glm::vec3(1, 3.0, 0.2)));

		//////////////////COCINA/////////////////////
		glm::mat4 paredcocina1 = glm::mat4(1.0);
		paredcocina1 = glm::translate(paredcocina1, glm::vec3(5.25, 0, -6.0));
		boxParedes.render(glm::scale(paredcocina1, glm::vec3(1.5, 3.0, 0.2)));

		glm::mat4 paredcocina2 = glm::mat4(1.0);
		paredcocina2 = glm::translate(paredcocina2, glm::vec3(7.0, -1.0, -6.0));
		boxParedes.render(glm::scale(paredcocina2, glm::vec3(2, 1.0, 0.2)));

		glm::mat4 paredcocina3 = glm::mat4(1.0);
		paredcocina3 = glm::translate(paredcocina3, glm::vec3(9.25, 0.0, -6.0));
		boxParedes.render(glm::scale(paredcocina3, glm::vec3(2.5, 3.0, 0.2)));


		glm::mat4 paredcocina5 = glm::mat4(1.0);
		paredcocina5 = glm::translate(paredcocina5, glm::vec3(7.5, 0, 0.0));
		boxParedes.render(glm::scale(paredcocina5, glm::vec3(6, 3.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanacocina = glm::mat4(1.0);
		ventanacocina = glm::translate(ventanacocina, glm::vec3(7, 0.5, -6.0));
		boxParedes.render(glm::scale(ventanacocina, glm::vec3(2.0, 2.0, 0.2)));

		////////////////////////SALA///////////////
		glm::mat4 ventanasala2 = glm::mat4(1.0);
		ventanasala2 = glm::translate(ventanasala2, glm::vec3(.95, 0.5, 5.9));
		boxParedes.render(glm::scale(ventanasala2, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredsala1 = glm::mat4(1.0);
		paredsala1 = glm::translate(paredsala1, glm::vec3(-1.3, 0.0, 5.9));
		boxParedes.render(glm::scale(paredsala1, glm::vec3(2, 3.0, 0.2)));

		glm::mat4 paredsala2 = glm::mat4(1.0);
		paredsala2 = glm::translate(paredsala2, glm::vec3(0.95, -1.0, 5.9));
		boxParedes.render(glm::scale(paredsala2, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredsala3 = glm::mat4(1.0);
		paredsala3 = glm::translate(paredsala3, glm::vec3(3.7, 0.0, 5.9));
		boxParedes.render(glm::scale(paredsala3, glm::vec3(3, 3.0, 0.2)));

		//////////////////RECAMARA INFERIOR///////////////////////////
		glm::mat4 paredrecamarai = glm::mat4(1.0);
		paredrecamarai = glm::translate(paredrecamarai, glm::vec3(6.4, -1.0, 5.9));
		boxParedes.render(glm::scale(paredrecamarai, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredrecamarai2 = glm::mat4(1.0);
		paredrecamarai2 = glm::translate(paredrecamarai2, glm::vec3(9.15, 0.0, 5.9));
		boxParedes.render(glm::scale(paredrecamarai2, glm::vec3(3, 3.0, 0.2)));

		glm::mat4 paredrecamarai3 = glm::mat4(1.0);
		paredrecamarai3 = glm::translate(paredrecamarai3, glm::vec3(8, 0, 2.0));
		boxParedes.render(glm::scale(paredrecamarai3, glm::vec3(5, 3.0, 0.2)));

		glm::mat4 paredrecamarai4 = glm::mat4(1.0);
		paredrecamarai4 = glm::translate(paredrecamarai4, glm::vec3(4.5, 0, 3.9));
		boxParedes.render(glm::scale(paredrecamarai4, glm::vec3(0.2, 3.0, 3.9)));

		glm::mat4 paredrecamarai5 = glm::mat4(1.0);
		paredrecamarai5 = glm::translate(paredrecamarai5, glm::vec3(5, 1.3, 2.0));
		boxParedes.render(glm::scale(paredrecamarai5, glm::vec3(1.0, 0.4, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertarecamarai = glm::mat4(1.0);
		puertarecamarai = glm::translate(puertarecamarai, glm::vec3(5, -0.2, 2.0));
		boxParedes.render(glm::scale(puertarecamarai, glm::vec3(1, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamarai = glm::mat4(1.0);
		ventanarecamarai = glm::translate(ventanarecamarai, glm::vec3(6.4, 0.5, 5.9));
		boxParedes.render(glm::scale(ventanarecamarai, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredderechapb = glm::mat4(1.0);
		paredderechapb = glm::translate(paredderechapb, glm::vec3(10.4, 0.0, 0.0));
		boxParedes.render(glm::scale(paredderechapb, glm::vec3(0.4, 3.0, 12.0)));

		////////PISOS PLANTA BAJA//////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID21);
		glm::mat4 pisocochera = glm::mat4(1.0);
		pisocochera = glm::translate(pisocochera, glm::vec3(-4.1, -1.5, -0.2));
		boxParedes.render(glm::scale(pisocochera, glm::vec3(3.4, 0.1, 12)));

		glBindTexture(GL_TEXTURE_2D, textureID22);

		glm::mat4 pisopb = glm::mat4(1.0);
		pisopb = glm::translate(pisopb, glm::vec3(4.0, -1.5, -0.2));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		boxParedes.render(glm::scale(pisopb, glm::vec3(13, 0.1, 12)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		/////TECHO PLANTA BAJA
		glm::mat4 techopb = glm::mat4(1.0);
		techopb = glm::translate(techopb, glm::vec3(2.25, 1.8, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID5);
		boxParedes.render(24, 6, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(0, 24, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));
		boxParedes.render(30, 6, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));

		//////////////////FIN PLANTA BAJA///////////////////////////////

		//////////////////////////////////////////////////////////////
		///////////////////PRIMER PISO/////////////////////
		//////////////////////////////////////////////////////////////

		////////////PAREDES RECAMARA 1///////////
		glm::mat4 paredrecamara1 = glm::mat4(1.0);
		paredrecamara1 = glm::translate(paredrecamara1, glm::vec3(6.4, 2.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara1, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredrecamara12 = glm::mat4(1.0);
		paredrecamara12 = glm::translate(paredrecamara12, glm::vec3(9.15, 3.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara12, glm::vec3(3, 3.0, 0.2)));

		glm::mat4 paredrecamara13 = glm::mat4(1.0);
		paredrecamara13 = glm::translate(paredrecamara13, glm::vec3(8, 3.6, 2.0));
		boxParedes.render(glm::scale(paredrecamara13, glm::vec3(5, 3.0, 0.2)));

		glm::mat4 paredrecamara14 = glm::mat4(1.0);
		paredrecamara14 = glm::translate(paredrecamara14, glm::vec3(4.5, 3.6, 3.9));
		boxParedes.render(glm::scale(paredrecamara14, glm::vec3(0.2, 3.0, 3.9)));

		glm::mat4 paredrecamara15 = glm::mat4(1.0);
		paredrecamara15 = glm::translate(paredrecamara15, glm::vec3(5, 4.9, 2.0));
		boxParedes.render(glm::scale(paredrecamara15, glm::vec3(1.0, 0.4, 0.2)));

		glm::mat4 paredrecamara16 = glm::mat4(1.0);
		paredrecamara16 = glm::translate(paredrecamara16, glm::vec3(4.8, 3.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara16, glm::vec3(0.8, 3.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertarecamara1 = glm::mat4(1.0);
		puertarecamara1 = glm::translate(puertarecamara1, glm::vec3(5, 3.4, 2.0));
		boxParedes.render(glm::scale(puertarecamara1, glm::vec3(1, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamara1 = glm::mat4(1.0);
		ventanarecamara1 = glm::translate(ventanarecamara1, glm::vec3(6.4, 4.1, 5.9));
		boxParedes.render(glm::scale(ventanarecamara1, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredderechap1 = glm::mat4(1.0);
		paredderechap1 = glm::translate(paredderechap1, glm::vec3(10.4, 3.6, 0.0));
		//boxParedes.render(glm::scale(paredderechap1, glm::vec3(0.4, 3.0, 12.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////////////RECAMARA DOSSS/////////////////
		glm::mat4 modelCasa = glm::mat4(1.0f);
		modelCasa = glm::translate(modelCasa, glm::vec3(4.5, 3.6, -3));
		modelCasa = glm::rotate(modelCasa, glm::radians(90.0f), glm::vec3(0, 1, 0.0));

		glm::mat4 paredFrontal = glm::scale(modelCasa, glm::vec3(6.0, 3.0, 0.3));
		glBindTexture(GL_TEXTURE_2D, textureID10);

		boxParedes.render(paredFrontal);

		glm::mat4 plafonf = glm::translate(modelCasa, glm::vec3(0, 1.2, 0.3));
		boxParedes.render(glm::scale(plafonf, glm::vec3(6.0, 0.1, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);

		glBindTexture(GL_TEXTURE_2D, textureID8);
		glm::mat4 pantalla = glm::translate(plafonf, glm::vec3(0.35, -1.0, 0.0));
		boxParedes.render(glm::scale(pantalla, glm::vec3(1.5, 1.0, 0.3)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 repisaVertical1 = glm::translate(modelCasa, glm::vec3(-1.5, -0.2, 0.3));
		boxParedes.render(glm::scale(repisaVertical1, glm::vec3(0.05, 2.65, 0.3)));

		glm::mat4 repisaHorizontal1 = glm::translate(repisaVertical1, glm::vec3(0.4, 0.45, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal1, glm::vec3(0.75, 0.05, 0.3)));


		glm::mat4 repisaHorizontal2 = glm::translate(repisaHorizontal1, glm::vec3(0.0, -0.75, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal2, glm::vec3(0.75, 0.05, 0.3)));

		glm::mat4 repisaVertical2 = glm::translate(repisaVertical1, glm::vec3(0.8, 0.0, 0.0));
		boxParedes.render(glm::scale(repisaVertical2, glm::vec3(0.05, 2.65, 0.3)));


		////////////repisas tele/////////////
		glm::mat4 repisaHorizontal3 = glm::translate(repisaVertical2, glm::vec3(1, -0.5, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal3, glm::vec3(2, 0.05, 0.3)));
		glm::mat4 repisaHorizontal4 = glm::translate(repisaHorizontal3, glm::vec3(0.0, -0.4, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal4, glm::vec3(2, 0.05, 0.3)));

		glm::mat4 repisaVertical3 = glm::translate(repisaVertical2, glm::vec3(2.0, 0.0, 0.0));
		boxParedes.render(glm::scale(repisaVertical3, glm::vec3(0.05, 2.65, 0.3)));

		glm::mat4 repisaHorizontal5 = glm::translate(repisaVertical3, glm::vec3(0.8, -.7, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal5, glm::vec3(1.6, 0.05, 0.3)));

		glm::mat4 repisaHorizontal6 = glm::translate(repisaHorizontal5, glm::vec3(0.0, 0.66, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal6, glm::vec3(1.6, 0.05, 0.3)));

		glm::mat4 repisaHorizontal7 = glm::translate(repisaHorizontal6, glm::vec3(0.0, 0.66, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal7, glm::vec3(1.6, 0.05, 0.3)));


		//////////////////Pared closet/////////////////////
		glm::mat4 paredCloset = glm::translate(modelCasa, glm::vec3(-3, 0.0, 3.5));
		boxParedes.render(glm::scale(paredCloset, glm::vec3(0.2, 3.0, 5.0)));

		glm::mat4 paredCloset2 = glm::translate(modelCasa, glm::vec3(-3, 1.25, 0.6));
		boxParedes.render(glm::scale(paredCloset2, glm::vec3(0.2, 0.4, 1)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puerta = glm::translate(paredCloset, glm::vec3(0.0, -0.25, -3.0));
		boxParedes.render(glm::scale(puerta, glm::vec3(0.2, 2.6, 1)));

		glBindTexture(GL_TEXTURE_2D, textureID6);
		glm::mat4 closetArriba = glm::translate(paredCloset, glm::vec3(0.3, 1.5, 0.0));
		boxParedes.render(glm::scale(closetArriba, glm::vec3(0.8, 0.2, 5.0)));

		glm::mat4 closetAbajo11 = glm::translate(paredCloset, glm::vec3(0.3, 0.0, 0.0));
		boxParedes.render(glm::scale(closetAbajo11, glm::vec3(0.6, 3.0, 5.0)));


		////////////Pared ventana/////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamara2 = glm::mat4(1.0);
		ventanarecamara2 = glm::translate(ventanarecamara2, glm::vec3(6.4, 4.1, -6.0));
		boxParedes.render(glm::scale(ventanarecamara2, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredventana1 = glm::mat4(1.0);
		paredventana1 = glm::translate(paredventana1, glm::vec3(4.8, 3.6, -6));
		boxParedes.render(glm::scale(paredventana1, glm::vec3(0.8, 3.0, 0.2)));

		glm::mat4 paredventana2 = glm::mat4(1.0);
		paredventana2 = glm::translate(paredventana2, glm::vec3(6.4, 2.6, -6));
		boxParedes.render(glm::scale(paredventana2, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredventana3 = glm::mat4(1.0);
		paredventana3 = glm::translate(paredventana3, glm::vec3(9.15, 3.6, -6));
		boxParedes.render(glm::scale(paredventana3, glm::vec3(3, 3.0, 0.2)));

		////////pared superior derecha/////////
		glm::mat4 paredderechas = glm::mat4(1.0);
		paredderechas = glm::translate(paredderechas, glm::vec3(10.4, 3.6, 0.0));
		boxParedes.render(glm::scale(paredderechas, glm::vec3(0.4, 3.0, 12.0)));
		/*

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredVentana = glm::translate(modelCasa, glm::vec3(3, 0.0, 2.5));
		boxParedes.render(glm::scale(paredVentana, glm::vec3(0.2, 3.0, 6.0)));

		glm::mat4 plafond = glm::translate(paredVentana, glm::vec3(-0.3, 3.0, 0.0));
		boxParedes.render(glm::scale(plafond, glm::vec3(0.3, 0.1, 9.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 ventana = glm::translate(paredVentana, glm::vec3(0.0, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		boxParedes.render(glm::scale(ventana, glm::vec3(0.5, 4.0, 6.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		/***********************************/

		/*****************Pared cama*********************/
		//glm::mat4 paredCama = glm::translate(modelCasa, glm::vec3(0.0, 0.0, 9.0));
		//boxParedes.render(glm::scale(paredCama, glm::vec3(12.0, 7.5, 0.3)));

	   /* glBindTexture(GL_TEXTURE_2D, textureID11);
		glm::mat4 cama = glm::translate(modelCasa, glm::vec3(0.0, -3.0, 6.0));
		boxParedes.render(glm::scale(cama, glm::vec3(3.5, 2.0, 6.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, textureID12);
		glm::mat4 almohada = glm::translate(modelCasa, glm::vec3(0.0, -1.8, 8.3));
		boxParedes.render(glm::scale(almohada, glm::vec3(2.5, 0.4, 1.5)));
		glBindTexture(GL_TEXTURE_2D, 0);*/

		/***************************************************/
		/*Piso*/
   /* glBindTexture(GL_TEXTURE_2D, textureID5);
		glm::mat4 piso = glm::translate(modelCasa, glm::vec3(0.0, -4.0, 4.3));
		boxPiso.render(glm::scale(piso, glm::vec3(12.0, 0.3, 9.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 techo = glm::translate(piso, glm::vec3(0.0, 7.8, 0.0));
		boxPiso.render(glm::scale(techo, glm::vec3(12.0, 0.3, 9.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/

		////////////////Fachada parte 1 ///////////////

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 paredizquierdap1 = glm::mat4(1.0);
		paredizquierdap1 = glm::translate(paredizquierdap1, glm::vec3(-6.0, 3.6, 0.3));
		boxParedes.render(0, 6, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));
		boxParedes.render(30, 6, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 fachada1 = glm::mat4(1.0);
		fachada1 = glm::translate(fachada1, glm::vec3(-4.1, 2.4, 6.25));
		//boxParedes.render(12, 12, glm::scale(fachada1, glm::vec3(3.4, 0.6, 1.2)));
		boxParedes.render(0, 6, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));
		boxParedes.render(30, 6, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));

		glm::mat4 fachada2 = glm::mat4(1.0);
		glBindTexture(GL_TEXTURE_2D, textureID19);
		fachada2 = glm::translate(fachada2, glm::vec3(-2.3, 3.6, 6.25));
		boxParedes.render(0, 12, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));
		boxParedes.render(30, 6, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(12, 18, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));



		glBindTexture(GL_TEXTURE_2D, textureID16);
		glm::mat4 fachada4 = glm::mat4(1.0);
		fachada4 = glm::translate(fachada4, glm::vec3(-4.1, 3.9, 6.25));
		boxParedes.render(glm::scale(fachada4, glm::vec3(3.4, 2.4, 0.7)));
		///////////////fachada en medio arriba///////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanafachada = glm::mat4(1.0);
		ventanafachada = glm::translate(ventanafachada, glm::vec3(.95, 4.1, 6.1));
		boxParedes.render(glm::scale(ventanafachada, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID20);
		glm::mat4 paredfachada1 = glm::mat4(1.0);
		paredfachada1 = glm::translate(paredfachada1, glm::vec3(-1.3, 3.6, 6.1));
		boxParedes.render(0, 12, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));


		glm::mat4 paredfachada2 = glm::mat4(1.0);
		paredfachada2 = glm::translate(paredfachada2, glm::vec3(0.95, 2.6, 6.1));
		glBindTexture(GL_TEXTURE_2D, textureID20);
		boxParedes.render(0, 12, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 paredfachada3 = glm::mat4(1.0);
		paredfachada3 = glm::translate(paredfachada3, glm::vec3(3.3, 3.6, 6.1));
		glBindTexture(GL_TEXTURE_2D, textureID20);
		boxParedes.render(0, 12, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3))); //vemos

		glBindTexture(GL_TEXTURE_2D, textureID20);
		glm::mat4 paredfachada4 = glm::mat4(1.0);
		paredfachada4 = glm::translate(paredfachada4, glm::vec3(1.1, 5.2, 6.1));
		boxParedes.render(glm::scale(paredfachada4, glm::vec3(6.75, 0.4, 0.4)));

		////////////////////////Techo segundo piso////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID19);

		glm::mat4 techo1 = glm::mat4(1.0);
		techo1 = glm::translate(techo1, glm::vec3(-4.1, 5.2, 0.3));
		boxParedes.render(0, 12, glm::scale(techo1, glm::vec3(4.2, 0.4, 12.6)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(12, 24, glm::scale(techo1, glm::vec3(4.2, 0.4, 12.6)));


		glm::mat4 techo2 = glm::mat4(1.0);
		techo2 = glm::translate(techo2, glm::vec3(4.2, 5.2, 0.0));
		boxParedes.render(glm::scale(techo2, glm::vec3(13, 0.4, 12)));
		///////////////////////////////////////////
		/////////////Carretera/////////////////////
		///////////////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, textureID18);
		glm::mat4 carretera1 = glm::mat4(1.0);
		carretera1 = glm::translate(carretera1, glm::vec3(2.25, -1.6, 14.5));
		boxCarretera.render(glm::scale(carretera1, glm::vec3(20, 0.0, 10)));

		glm::mat4 carretera2 = glm::mat4(1.0);
		carretera2 = glm::translate(carretera2, glm::vec3(-12.7, -1.6, 4.4));
		boxCarretera.render(glm::scale(carretera2, glm::vec3(10, 0.0, 30)));

		glm::mat4 carretera3 = glm::mat4(1.0);
		carretera3 = glm::translate(carretera3, glm::vec3(16.8, -1.6, 4.4));
		boxCarretera.render(glm::scale(carretera3, glm::vec3(10, 0.0, 30)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////
		/////////////MUEBLES/////////////////////
		///////////////////////////////////////////
		/*glm::mat4 matrixModelMueble = glm::mat4(1.0);
		matrixModelMueble = glm::translate(matrixModelMueble, glm::vec3(1.0, -1.6, 3.0));
		matrixModelMueble = glm::scale(matrixModelMueble, glm::vec3(1.5, 1.5, 1.5));
		modelMueble.render(matrixModelMueble);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelTable = glm::mat4(1.0);
		matrixModelTable = glm::translate(matrixModelTable, glm::vec3(2.5, -1.6, -2.5));
		matrixModelTable = glm::scale(matrixModelTable, glm::vec3(2, 2, 2));
		modelTable.render(matrixModelTable);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelRosa = glm::mat4(1.0);
		matrixModelRosa = glm::translate(matrixModelRosa, glm::vec3(1.0, -1.0, 3.0));
		matrixModelRosa = glm::scale(matrixModelRosa, glm::vec3(0.3, 0.3, 0.3));
		modelRosa.render(matrixModelRosa);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelMaceta = glm::mat4(1.0);
		matrixModelMaceta = glm::translate(matrixModelMaceta, glm::vec3(1.0, -1.6, 6.8));
		matrixModelMaceta = glm::rotate(matrixModelMaceta, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelMaceta = glm::scale(matrixModelMaceta, glm::vec3(0.2, 0.2, 0.2));
		modelMaceta.render(matrixModelMaceta);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelJardinera = glm::mat4(1.0);
		matrixModelJardinera = glm::translate(matrixModelJardinera, glm::vec3(10.0, -1.6, 8));
		matrixModelJardinera = glm::rotate(matrixModelJardinera, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelJardinera = glm::scale(matrixModelJardinera, glm::vec3(0.3, 0.3, 0.3));
		modelJardinera.render(matrixModelJardinera);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelSala= glm::mat4(1.0);
		matrixModelSala = glm::translate(matrixModelSala, glm::vec3(1.0, -1.0, 5.0));
		matrixModelSala = glm::rotate(matrixModelSala, glm::radians(180.0f), glm::vec3(0, 1, 0));
		matrixModelSala = glm::scale(matrixModelSala, glm::vec3(0.5, 0.5, 0.5));
		modelSala.render(matrixModelSala);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelSalap = glm::mat4(1.0);
		matrixModelSalap = glm::translate(matrixModelSalap, glm::vec3(-1.0, -1.5, 3.5));
		matrixModelSalap = glm::rotate(matrixModelSalap, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelSalap = glm::scale(matrixModelSalap, glm::vec3(0.3, 0.3, 0.3));
		modelSalap.render(matrixModelSalap);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelToilet = glm::mat4(1.0);
		matrixModelToilet = glm::translate(matrixModelToilet, glm::vec3(-0.2, -1.6, -1.0));
		matrixModelToilet = glm::rotate(matrixModelToilet, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelToilet = glm::scale(matrixModelToilet, glm::vec3(0.3, 0.3, 0.3));
		modelToilet.render(matrixModelToilet);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelHandWash = glm::mat4(1.0);
		matrixModelHandWash = glm::translate(matrixModelHandWash, glm::vec3(-0.2, -1.6, -2.5));
		matrixModelHandWash = glm::rotate(matrixModelHandWash, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelHandWash.render(matrixModelHandWash);
		glActiveTexture(GL_TEXTURE0);*/

		//lampara del baño
		glm::mat4 matrixModelLamp1 = glm::mat4(1.0);
		matrixModelLamp1 = glm::translate(matrixModelLamp1, glm::vec3(-1.0, 1.12, -2.5));
		matrixModelLamp1 = glm::rotate(matrixModelLamp1, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp1, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara comedor
		glm::mat4 matrixModelLamp2 = glm::mat4(1.0);
		matrixModelLamp2 = glm::translate(matrixModelLamp2, glm::vec3(2.5, 1.12, -2.5));
		matrixModelLamp2 = glm::rotate(matrixModelLamp2, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp2, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara cocina
		glm::mat4 matrixModelLamp3 = glm::mat4(1.0);
		matrixModelLamp3 = glm::translate(matrixModelLamp3, glm::vec3(6.0, 1.12, -2.5));
		matrixModelLamp3 = glm::rotate(matrixModelLamp3, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp3, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);


		//lampara sala 1
		glm::mat4 matrixModelLamp4 = glm::mat4(1.0);
		matrixModelLamp4 = glm::translate(matrixModelLamp4, glm::vec3(0.0, 1.0, 3.0));
		matrixModelLamp4 = glm::rotate(matrixModelLamp4, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp4, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);
		
		//lampara sala 2
		glm::mat4 matrixModelLamp5 = glm::mat4(1.0);
		matrixModelLamp5 = glm::translate(matrixModelLamp5, glm::vec3(2.0, 1.0, 3.0));
		matrixModelLamp5 = glm::rotate(matrixModelLamp5, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp5, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara recamara abajo
		glm::mat4 matrixModelLamp6 = glm::mat4(1.0);
		matrixModelLamp6 = glm::translate(matrixModelLamp6, glm::vec3(7.5, 1.0, 4.0));
		matrixModelLamp6 = glm::rotate(matrixModelLamp6, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp6, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara recamara arriba
		glm::mat4 matrixModelLamp7 = glm::mat4(1.0);
		matrixModelLamp7 = glm::translate(matrixModelLamp7, glm::vec3(7.5, 4.65, 4.0));
		matrixModelLamp7 = glm::rotate(matrixModelLamp7, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp7, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//recamara arriba2
		glm::mat4 matrixModelLamp8 = glm::mat4(1.0);
		matrixModelLamp8 = glm::translate(matrixModelLamp8, glm::vec3(7.5, 4.65, -2.5));
		matrixModelLamp8 = glm::rotate(matrixModelLamp8, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelLampara.render(glm::scale(matrixModelLamp8, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);
		

		/////////////////////////////////////////
		/////////////Decoraciones////////////////
		/////////////////////////////////////////
		glm::mat4 matrixModelTree = glm::mat4(1.0);
		matrixModelTree = glm::translate(matrixModelTree, glm::vec3(-4.1, 2.1, 5.0));
		matrixModelTree = glm::scale(matrixModelTree, glm::vec3(0.6, 0.6, 0.6));
		modelTree.render(matrixModelTree);

		glm::mat4 matrixModelStar = glm::mat4(1.0);
		matrixModelStar = glm::translate(matrixModelStar, glm::vec3(-4.1, 4.8, 5.0));
		matrixModelStar = glm::scale(matrixModelStar, glm::vec3(0.15, 0.15, 0.15));
		modelStar.render(matrixModelStar);

		glm::mat4 matrixModelSerie = glm::mat4(1.0);
		matrixModelSerie = glm::translate(matrixModelSerie, glm::vec3(-2.0, 4.5, 5.6));
		modelSerie.render(glm::scale(matrixModelSerie, glm::vec3(0.15, 0.15, 0.15)));

		glm::mat4 matrixModelChBall1 = glm::mat4(1.0);
		matrixModelChBall1 = glm::translate(matrixModelChBall1, glm::vec3(-4.0, 4.4, 4.8));
		modelChBall1.render(glm::scale(matrixModelChBall1, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall2 = glm::mat4(1.0);
		matrixModelChBall2 = glm::translate(matrixModelChBall2, glm::vec3(-4.3, 4.4, 4.9));
		modelChBall2.render(glm::scale(matrixModelChBall2, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall3 = glm::mat4(1.0);
		matrixModelChBall3 = glm::translate(matrixModelChBall3, glm::vec3(-4.3, 4.0, 4.8));
		modelChBall3.render(glm::scale(matrixModelChBall3, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall4 = glm::mat4(1.0);
		matrixModelChBall4 = glm::translate(matrixModelChBall4, glm::vec3(-4.0, 4.0, 4.7));
		modelChBall5.render(glm::scale(matrixModelChBall4, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall5 = glm::mat4(1.0);
		matrixModelChBall5 = glm::translate(matrixModelChBall5, glm::vec3(-3.8, 4.0, 5.0));
		modelChBall4.render(glm::scale(matrixModelChBall5, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall6 = glm::mat4(1.0);
		matrixModelChBall6 = glm::translate(matrixModelChBall6, glm::vec3(-4.3, 4.0, 5.1));
		modelChBall1.render(glm::scale(matrixModelChBall6, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall7 = glm::mat4(1.0);
		matrixModelChBall7 = glm::translate(matrixModelChBall7, glm::vec3(-4.0, 4.0, 5.1));
		modelChBall2.render(glm::scale(matrixModelChBall7, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall8 = glm::mat4(1.0);
		matrixModelChBall8 = glm::translate(matrixModelChBall8, glm::vec3(-3.8, 3.6, 5.1));
		modelChBall3.render(glm::scale(matrixModelChBall8, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall9 = glm::mat4(1.0);
		matrixModelChBall9 = glm::translate(matrixModelChBall9, glm::vec3(-4.1, 3.6, 5.2));
		modelChBall1.render(glm::scale(matrixModelChBall9, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall10 = glm::mat4(1.0);
		matrixModelChBall10 = glm::translate(matrixModelChBall10, glm::vec3(-4.4, 3.6, 5.3));
		modelChBall4.render(glm::scale(matrixModelChBall10, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall11 = glm::mat4(1.0);
		matrixModelChBall11 = glm::translate(matrixModelChBall11, glm::vec3(-3.8, 3.6, 4.7));
		modelChBall2.render(glm::scale(matrixModelChBall11, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall12 = glm::mat4(1.0);
		matrixModelChBall12 = glm::translate(matrixModelChBall12, glm::vec3(-4.1, 3.6, 4.6));
		modelChBall4.render(glm::scale(matrixModelChBall12, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall13 = glm::mat4(1.0);
		matrixModelChBall13 = glm::translate(matrixModelChBall13, glm::vec3(-4.4, 3.6, 4.7));
		modelChBall5.render(glm::scale(matrixModelChBall13, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall14 = glm::mat4(1.0);
		matrixModelChBall14 = glm::translate(matrixModelChBall14, glm::vec3(-3.7, 3.2, 5.3));
		modelChBall2.render(glm::scale(matrixModelChBall14, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall15 = glm::mat4(1.0);
		matrixModelChBall15 = glm::translate(matrixModelChBall15, glm::vec3(-4.1, 3.2, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall15, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall16 = glm::mat4(1.0);
		matrixModelChBall16 = glm::translate(matrixModelChBall16, glm::vec3(-4.5, 3.2, 5.4));
		modelChBall5.render(glm::scale(matrixModelChBall16, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall17 = glm::mat4(1.0);
		matrixModelChBall17 = glm::translate(matrixModelChBall17, glm::vec3(-3.7, 3.2, 4.5));
		modelChBall4.render(glm::scale(matrixModelChBall17, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall18 = glm::mat4(1.0);
		matrixModelChBall18 = glm::translate(matrixModelChBall18, glm::vec3(-4.1, 3.2, 4.4));
		modelChBall3.render(glm::scale(matrixModelChBall18, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall19 = glm::mat4(1.0);
		matrixModelChBall19 = glm::translate(matrixModelChBall19, glm::vec3(-4.5, 3.2, 4.5));
		modelChBall2.render(glm::scale(matrixModelChBall19, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall20 = glm::mat4(1.0);
		matrixModelChBall20 = glm::translate(matrixModelChBall20, glm::vec3(-3.7, 2.8, 5.4));
		modelChBall4.render(glm::scale(matrixModelChBall20, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall26 = glm::mat4(1.0);
		matrixModelChBall26 = glm::translate(matrixModelChBall26, glm::vec3(-3.5, 2.8, 5.0));
		modelChBall3.render(glm::scale(matrixModelChBall26, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall27 = glm::mat4(1.0);
		matrixModelChBall27 = glm::translate(matrixModelChBall27, glm::vec3(-3.6, 3.2, 4.8));
		modelChBall5.render(glm::scale(matrixModelChBall27, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall28 = glm::mat4(1.0);
		matrixModelChBall28 = glm::translate(matrixModelChBall28, glm::vec3(-3.5, 2.4, 5.0));
		modelChBall1.render(glm::scale(matrixModelChBall28, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall21 = glm::mat4(1.0);
		matrixModelChBall21 = glm::translate(matrixModelChBall21, glm::vec3(-4.1, 2.8, 5.6));
		modelChBall2.render(glm::scale(matrixModelChBall21, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall22 = glm::mat4(1.0);
		matrixModelChBall22 = glm::translate(matrixModelChBall22, glm::vec3(-4.5, 2.8, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall22, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall23 = glm::mat4(1.0);
		matrixModelChBall23 = glm::translate(matrixModelChBall23, glm::vec3(-3.7, 2.8, 4.5));
		modelChBall1.render(glm::scale(matrixModelChBall23, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall24 = glm::mat4(1.0);
		matrixModelChBall24 = glm::translate(matrixModelChBall24, glm::vec3(-4.1, 2.8, 4.4));
		modelChBall5.render(glm::scale(matrixModelChBall24, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall25 = glm::mat4(1.0);
		matrixModelChBall25 = glm::translate(matrixModelChBall25, glm::vec3(-4.5, 2.8, 4.5));
		modelChBall3.render(glm::scale(matrixModelChBall25, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall29 = glm::mat4(1.0);
		matrixModelChBall29 = glm::translate(matrixModelChBall29, glm::vec3(-3.7, 2.4, 5.3));
		modelChBall2.render(glm::scale(matrixModelChBall29, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall30 = glm::mat4(1.0);
		matrixModelChBall30 = glm::translate(matrixModelChBall30, glm::vec3(-4.1, 2.4, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall30, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall31 = glm::mat4(1.0);
		matrixModelChBall31 = glm::translate(matrixModelChBall31, glm::vec3(-4.5, 2.4, 5.4));
		modelChBall5.render(glm::scale(matrixModelChBall31, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall32 = glm::mat4(1.0);
		matrixModelChBall32 = glm::translate(matrixModelChBall32, glm::vec3(-3.7, 2.4, 4.5));
		modelChBall4.render(glm::scale(matrixModelChBall32, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall33 = glm::mat4(1.0);
		matrixModelChBall33 = glm::translate(matrixModelChBall33, glm::vec3(-4.1, 2.4, 4.4));
		modelChBall3.render(glm::scale(matrixModelChBall33, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall34 = glm::mat4(1.0);
		matrixModelChBall34 = glm::translate(matrixModelChBall34, glm::vec3(-4.5, 2.4, 4.5));
		modelChBall2.render(glm::scale(matrixModelChBall34, glm::vec3(0.5, 0.5, 0.5)));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////RENDER ANIMACIONES/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////
		/////Render eclipse//////////////////////
		/////////////////////////////////////////
		//Chasis
		modelCar.render(matrixModelCar);
		glActiveTexture(GL_TEXTURE0);
		//Llantas delanteras
		// Render for the eclipse car llantas delanteras
		glm::mat4 modelMatrixEclipseFrontalWheels = glm::mat4(matrixModelCar);
		modelMatrixEclipseFrontalWheels = glm::translate(modelMatrixEclipseFrontalWheels, glm::vec3(0.0, 1.06285, 4.11795));
		//Rotacion de llanata cuando da vuelta
		modelMatrixEclipseFrontalWheels = glm::rotate(modelMatrixEclipseFrontalWheels, rotWheely, glm::vec3(0, 1, 0));
		modelMatrixEclipseFrontalWheels = glm::rotate(modelMatrixEclipseFrontalWheels, rotWheelx, glm::vec3(1, 0, 0));
		modelMatrixEclipseFrontalWheels = glm::translate(modelMatrixEclipseFrontalWheels, glm::vec3(0.0, -1.06285, -4.11795));
		modelEclipseWheelsFrontal.render(modelMatrixEclipseFrontalWheels);
		glActiveTexture(GL_TEXTURE0);

		// Render for the eclipse car llantas atras
		glm::mat4 modelMatrixEclipseRealWheels = glm::mat4(matrixModelCar);
		modelMatrixEclipseRealWheels = glm::translate(modelMatrixEclipseRealWheels, glm::vec3(0.0, 1.05128, -4.34651));
		modelMatrixEclipseRealWheels = glm::rotate(modelMatrixEclipseRealWheels, rotWheelx, glm::vec3(1, 0, 0));
		modelMatrixEclipseRealWheels = glm::translate(modelMatrixEclipseRealWheels, glm::vec3(0.0, -1.05128, 4.34651));
		modelEclipseWheelsRear.render(modelMatrixEclipseRealWheels);
		glActiveTexture(GL_TEXTURE0);


		/////////////////////////////////////////
		//////////RENDER HELICOPTERO/////////////
		/////////////////////////////////////////
		modelHeliChasis.render(modelMatrixHeliChasis);
		glActiveTexture(GL_TEXTURE0);

		// Helices Helicoptero
		glm::mat4 modelMatrixHeliHeli = glm::mat4(modelMatrixHeliChasis);
		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(-0.003344, 1.88318, -0.254566));
		modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHeliHeliy, glm::vec3(0, 1, 0));
		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.003344, -1.88318, 0.254566));
		modelHeliHeliMeid.render(modelMatrixHeliHeli);
		glActiveTexture(GL_TEXTURE0);
		//Helice chica
		glm::mat4 modelMatrixHeliHeli2 = glm::mat4(modelMatrixHeliChasis);
		modelMatrixHeliHeli2 = glm::translate(modelMatrixHeliHeli2, glm::vec3(0.4685, 2.099, -5.645));
		modelMatrixHeliHeli2 = glm::rotate(modelMatrixHeliHeli2, rotHeliHeliz, glm::vec3(1, 0, 0));
		modelMatrixHeliHeli2 = glm::translate(modelMatrixHeliHeli2, glm::vec3(-0.4685, -2.099, 5.645));
		modelHeliHeliCh.render(modelMatrixHeliHeli2);
		glActiveTexture(GL_TEXTURE0);

		/////////////////////////////////////////
		//////////RENDER Lambo/////////////
		/////////////////////////////////////////

		//chasis
		modelLambo.render(modelMatrixLambo);
		glActiveTexture(GL_TEXTURE0);

		//puertas
		glm::mat4 modelMatrixLamboLeftDor = glm::mat4(modelMatrixLambo);
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(1.08676, 0.707316, 0.982601));
		modelMatrixLamboLeftDor = glm::rotate(modelMatrixLamboLeftDor, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(-1.08676, -0.707316, -0.982601));
		modelLamboLeftDor.render(modelMatrixLamboLeftDor);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixLamboLeftDoor2 = glm::mat4(modelMatrixLambo);
		modelMatrixLamboLeftDoor2 = glm::translate(modelMatrixLamboLeftDoor2, glm::vec3(-1.113, 0.707316, 0.982601));
		modelMatrixLamboLeftDoor2 = glm::rotate(modelMatrixLamboLeftDoor2, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboLeftDoor2 = glm::translate(modelMatrixLamboLeftDoor2, glm::vec3(1.113, -0.707316, -0.982601));
		modelLamboRightDoor.render(modelMatrixLamboLeftDoor2);
		glActiveTexture(GL_TEXTURE0);

		//llantas enfrente
		glm::mat4 modelMatrixLamboFrontalWheels = glm::mat4(modelMatrixLambo);
		modelMatrixLamboFrontalWheels = glm::translate(modelMatrixLamboFrontalWheels, glm::vec3(0.0, 0.3722, 1.409));
		//Rotacion de llanata cuando da vuelta
		//modelMatrixLamboFrontalWheels = glm::rotate(modelMatrixLamboFrontalWheels, rotWheelLamboY, glm::vec3(0, 1, 0));
		modelMatrixLamboFrontalWheels = glm::rotate(modelMatrixLamboFrontalWheels, rotWheelLamboX, glm::vec3(1, 0, 0));
		modelMatrixLamboFrontalWheels = glm::translate(modelMatrixLamboFrontalWheels, glm::vec3(0.0, -0.3722, -1.409));
		modelLamboFrontWheels.render(modelMatrixLamboFrontalWheels);
		glActiveTexture(GL_TEXTURE0);


		//llantas atras
		glm::mat4 modelMatrixLamboRealWheels = glm::mat4(modelMatrixLambo);
		modelMatrixLamboRealWheels = glm::translate(modelMatrixLamboRealWheels, glm::vec3(0.0, 0.3722, -1.609));
		modelMatrixLamboRealWheels = glm::rotate(modelMatrixLamboRealWheels, rotWheelLamboX, glm::vec3(1, 0, 0));
		modelMatrixLamboRealWheels = glm::translate(modelMatrixLamboRealWheels, glm::vec3(0.0, -0.3722, 1.609));
		modelLamboBackWheels.render(modelMatrixLamboRealWheels);
		glActiveTexture(GL_TEXTURE0);

		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.0001;

		// Se Dibuja el Skybox
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);


		dz = 0;
		rot0 = 0;
		offX += 0.001;

		/*switch (state)
		{
		case 0:
			std::cout << "Advance:" << std::endl;
			matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(0.0, 0.0, -0.1));
			offsetAircraftAdvance += 0.1;
			if (offsetAircraftAdvance > 3.0) {
				offsetAircraftAdvance = 0.0;
				state = 1;
			}
		break;
		case 1:
			std::cout << "Turn:" << std::endl;
			matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(0.0, 0.0, -0.01));
			matrixModelAircraft = glm::rotate(matrixModelAircraft, glm::radians(0.05f),glm::vec3(0.0, 0.1, 0.0));
			offsetAircraftRot += 0.05;
			if (offsetAircraftRot > 90) {
				offsetAircraftRot = 0.0;
				state = 0;
			}
			break;
		default:
			break;
		}*/

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////MAQUINAS DE ESTADOS/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////
		/////////////////STATE MACHINE Eclipse car/////////////////////////
		///////////////////////////////////////////////////////////////////
		switch (state)
		{
		case 0:
			matrixModelCar = glm::translate(matrixModelCar, glm::vec3(0.0, 0.0, 0.1));
			offsetAircraftAdvance += 0.1;
			rotWheely -= 0.01;
			if (rotWheely < 0)
				rotWheely = 0;
			if (offsetAircraftAdvance > 30.0) {
				offsetAircraftAdvance = 0.0;
				state = 1;
			}
			break;
		case 1:
			matrixModelCar = glm::translate(matrixModelCar, glm::vec3(0.0, 0.0, 0.01));
			matrixModelCar = glm::rotate(matrixModelCar, glm::radians(0.05f), glm::vec3(0.0, 1.0, 0.0));
			offsetAircraftRot += 0.05;
			rotWheely += 0.0001;
			if (rotWheely < glm::radians(15.0))
				rotWheely = glm::radians(15.0);
			if (offsetAircraftRot > 90) {
				offsetAircraftRot = 0.0;
				state = 0;
			}
			break;
		default:
			break;
		}

		///////////////////////////////////////////////////////////////////
		/////////////////STATE MACHINE HELICOPTERO/////////////////////
		///////////////////////////////////////////////////////////////////
		switch (stateheli) {
		case 0:
			modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(-0.1, -0.1, 0.0));
			offsetHeliAdvance += 0.1;
			if (offsetHeliAdvance > 14.7) {
				offsetHeliAdvance = 0.0;
				stateheli = 2;
			}
			break;
		case 1:
			modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(0.1, 0.1, 0));
			offsetHeliAdvance += 0.1;
			if (offsetHeliAdvance > 14.7) {
				offsetHeliAdvance = 0.0;
				stateheli = 0;
			}

			break;
		case 2:
			offsetState += 0.2;
			if (offsetState > 18.0) {
				offsetState = 0;
				stateheli = 1;
			}
			break;
		default:
			break;
		}

		/////////////////////////////////////////////////////
		/////////////////State machine lambo/////////////////////
		/////////////////////////////////////////////////////
		switch (stateDoor) {
		case 0:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, 0.1));
			offsetLamboAdvance += 0.1;
			rotWheelLamboX += 0.1;

			if (offsetLamboAdvance > 10.0) {
				offsetLamboAdvance = 0.0;
				stateDoor = 1;
			}
		
			break;
		case 1:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, 0.1));
			modelMatrixLambo = glm::rotate(modelMatrixLambo, glm::radians(0.4f), glm::vec3(0.0, 1.0, 0.0));
			rotWheelLamboX += 0.1;
			offsetLamboRot += 0.4;
			if (offsetLamboRot > 25) {
				offsetLamboRot = 0.0;
				stateDoor = 2;
			}
			break;
		case 2:
			dorRotCount += 0.5;
			if (dorRotCount > 75)
				stateDoor = 3;
			break;
		case 3:
			dorRotCount -= 0.5;
			if (dorRotCount < 0) {
				dorRotCount = 0.0;
				stateDoor = 4;
			}
			break;
		case 4:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, -0.1));
			modelMatrixLambo = glm::rotate(modelMatrixLambo, glm::radians(-0.4f), glm::vec3(0.0, 1.0, 0.0));
			rotWheelLamboX -= 0.1;
			offsetLamboRot += 0.4;
			if (offsetLamboRot > 25) {
				offsetLamboRot = 0.0;
				stateDoor = 5;
			}
			break;
		case 5:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, -0.1));
			offsetLamboAdvance += 0.1;
			rotWheelLamboX -= 0.1;
			if (offsetLamboAdvance > 10.0) {
				offsetLamboAdvance = 0.0;
				stateDoor = 0;
			}
			break;
		}

		offset1 += 1;
		offset2 += 1;
		offset3 += 1;
		offset4 += 1;
		offset5 += 1;
		offsetc1 += 0.05;
		offsetc2 += 0.05;
		offsetc3 += 0.05;
		if (offset1 > 7) { offset1 = 0.0; }
		if (offset2 > 7) { offset2 = 0.0; }
		if (offset3 > 7) { offset3 = 0.0; }
		if (offset4 > 7) { offset4 = 0.0; }
		if (offset5 > 7) { offset5 = 0.0; }
		if (offsetc1 > 1) { offsetc1 = 0.0; }
		if (offsetc2 > 1) { offsetc2 = 0.0; }
		if (offsetc3 > 1) { offsetc3 = 0.0; }
		rotHeliHeliy += 0.1;
		rotHeliHeliz += 0.1;
		rotWheelx += 0.1;
		glfwSwapBuffers(window);
	}
}

int main(int argc, char** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
