#include "glSetup.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES		//To include the definition of M_PI in math.h
#endif

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtx/string_cast.hpp>	//glm::to_string()
#include <glm/gtc/type_ptr.hpp>		//glm::value_ptr()
using namespace glm;

#include <iostream>
using namespace std;

void init();
void quit();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

//Camera configuration
vec3 eye(3.5, 3, 3.5);
vec3 center(0, 0, 0);
vec3 up(0, 1, 0);

//Light configuration
vec4 light(5.0, 5.0, 5.0, 1);		//Light position

//Global coordinate frame
float AXIS_LENGTH = 3;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//Selected example
int selection = 1;

//Sphere, cylinder
GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;
GLUquadricObj* disk = NULL;

//Paly configuration
bool pause = false;

float timeStep = 1.0f / 120; //120fps
float period = 4.0;

//Current frame
int frame = 0;

int main(int argc, char* argv[]) {
	//FPS control: vsync should be 0 for precise time stepping
	vsync = 0;	//0 for immediate mode(Tearing possible)

	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//Callbacks
	glfwSetKeyCallback(window, keyboard);

	//Depth test
	glEnable(GL_DEPTH_TEST);

	//Normal vectors are normalized after transformation
	glEnable(GL_NORMALIZE);

	//Viewport and perspective setting
	reshape(window, windowW, windowH);

	//Initialization - Main loop - Finalizaion
	//
	init();

	//Main loop
	float previous = (float)glfwGetTime();
	float elapsed = 0;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();		//Events

		//Time passed during a single loop
		float now = (float)glfwGetTime();
		float delta = now - previous;
		previous = now;

		//Time passed after the previous frame
		elapsed += delta;

		//Deal with the current frame
		if (elapsed > timeStep) {
			//Rotate the line segment if not paused
			if (!pause) frame += 1;

			elapsed = 0;	//Reset the elapsed time
		}

		render(window);				//Draw one frame
		glfwSwapBuffers(window);	//Swap buffers
	}

	//Finalization
	quit();

	//Terminate the glfw system
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void init()
{
	//Prepare quadric shapes
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricTexture(sphere, GL_FALSE);

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricOrientation(cylinder, GLU_OUTSIDE);
	gluQuadricTexture(cylinder, GL_FALSE);

	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_FILL);
	gluQuadricNormals(disk, GLU_SMOOTH);
	gluQuadricOrientation(disk, GLU_OUTSIDE);
	gluQuadricTexture(disk, GL_FALSE);

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for scaling wrt a pivot example using GLM" << endl;
	cout << "Keyboard Input: 2 for scaling wrt a direction example using GLM" << endl;
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(disk);
}

//Light
void setupLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(light));
}

//Material
void setupMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 128;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setDiffuseColor(const vec3& color)
{
	GLfloat mat_diffuse[4] = { color[0],color[1], color[2], 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
}

//Draw a sphere after setting up its material
void drawSphere(float radius, const vec3& color)
{
	//Material
	setDiffuseColor(color);

	//Sphere using GLU quadrices
	gluSphere(sphere, radius, 72, 72);
}

//Draw a cylinder after setting up its material
void drawCylinder(float radius, float height, const vec3& color)
{
	//Material
	setDiffuseColor(color);

	//Cylinder using GLU quadrics
	gluCylinder(cylinder, radius, radius, height, 72, 5);
}

//Draw a disk after setting up its material
void drawDisk(float inner_radius, float outer_radius, const vec3& color)
{
	//Material
	setDiffuseColor(color);

	//Disk using GLU quadrics
	gluDisk(disk, inner_radius, outer_radius, 72, 5);
}

//Draw a unit cube
void drawCube()
{
	//Cube
	glBegin(GL_QUADS);

	//Front
	glNormal3f(0, 0, 1);

	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	//Back
	glNormal3f(0, 0, -1);

	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	//Right
	glNormal3f(1, 0, 0);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);

	//Left
	glNormal3f(-1, 0, 0);

	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	//Top
	glNormal3f(0, 1, 0);

	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);

	//Bottom
	glNormal3f(0, -1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);

	glEnd();
}

//추가
void scalingPivotExampleGLM()
{
	float s = 1.0f + 0.95f * sin(frame * 0.1f / period);
	glm::vec3 pivot(0.5, 0.5, 0.5);
	glm::vec3 temp(s, 1, 1);

	//Identity matrix
	glm::mat4 M(1.0);

	//M = M * translate(pivot)
	M = glm::translate(M, pivot);

	//M = M * scale(vec3)
	M = glm::scale(M, temp);

	//M = M * translate(-pivot)
	M = glm::translate(M, -pivot);

	glMultMatrixf(value_ptr(M));

	setDiffuseColor(glm::vec3(1, 1, 1));	//Material
	drawCube();
}

//추가
void scalingDirectionExampleGLM()
{
	float s = 1.0f + 0.95f * sin(frame * 0.1f / period);
	glm::vec3 direction(1, 1, 0);
	direction = normalize(direction);	//Unit vector
	glm::vec3 temp(s, 1, 1);

	//Identity matrix
	glm::mat4 M(1.0);

	//Compute the rotation axis and angle between the x-aixs and the given direction
	glm::vec3 axis = cross(glm::vec3(1, 0, 0), direction);
	float	  sinTheta = length(axis);
	float	  cosTheta = dot(glm::vec3(1, 0, 0), direction);
	float	  theta = (float)atan2(sinTheta, cosTheta) * float(180.0 / M_PI);
	axis /= sinTheta;	//Unit axis

	//M = M * rotate(angle, axis)
	M = glm::rotate(M, glm::radians(theta), axis);

	//M = M * scale(vec3)
	M = glm::scale(M, temp);

	//M = M * rotate(angle, axis)
	M = glm::rotate(M, -glm::radians(theta), axis);

	glMultMatrixf(value_ptr(M));

	setDiffuseColor(glm::vec3(1, 1, 1));	//Material
	drawCube();
}

void render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	glDisable(GL_LIGHTING);
	drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH * dpiScaling);

	//Lighting
	setupLight();

	//Material
	setupMaterial();

	//Draw sphere using gluSphere() after setting up the material
	switch (selection)
	{
	case 1: scalingPivotExampleGLM();		break;
	case 2: scalingDirectionExampleGLM();	break;
	}
}

void keyboard(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key)
		{
			//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

			//Play on/off
		case GLFW_KEY_SPACE: pause = !pause; break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;
		}
	}
}