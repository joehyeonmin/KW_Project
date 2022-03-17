#include "glSetup.h"

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtc/type_ptr.hpp>		//value_ptr()
using namespace glm;

#include <iostream>
#include <fstream>
using namespace std;

void init();
void quit();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);
void mouseButton(GLFWwindow* window, int button, int action, int mods);

// add
void mouseMove(GLFWwindow* window, double x, double y);


//Camera configuration
vec3 eyeTopView(0, 10, 0);		//Top view
vec3 upTopView(0, 0, -1);		//Top view

vec3 eyeFrontView(0, 0, 10);	//Front view
vec3 upFrontView(0, 1, 0);		//Front view

vec3 eyeBirdView(0, -10, 4);	//Bird-eye view
vec3 upBirdView(0, 1, 0);		//Bird-eye view
vec3 center(0, 0, 0);

//Light configuration
vec4 light(0.0, 0.0, 0.8, 1);	//Initial light position

//Global coordinate frame
bool axes = true;
float AXIS_LENGTH = 1.25;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };


// add
float point[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };

enum class InputMode
{
	NONE = 0,
	DRAGGING = 1,
	COMPLETE = 2,
};

InputMode inputMode = InputMode::NONE;


//control variable
int	view = 1; //Top, front, bird-eye veiw

// Picking 
int picked = -1;

int main(int argc, char* argv[]) {
	//Field of view of 85mm lens in degree
	fovy = 16.1f;

	// add
	perspectiveView = false;

	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//Callbacks
	glfwSetKeyCallback(window, keyboard);
	glfwSetMouseButtonCallback(window, mouseButton);

	// add 
	glfwSetCursorPosCallback(window, mouseMove);

	//Depth test
	glEnable(GL_DEPTH_TEST);

	//Normal vectors are normalized after transformation
	glEnable(GL_NORMALIZE);

	//Viewport and perspective setting
	reshape(window, windowW, windowH);

	//Initialization - Main loop - Finalizaion
	init();

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();			//Events

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

//Sphere, cylinder
GLUquadricObj* sphere = NULL;

void init()
{
	// Prepare quadric shapes
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricTexture(sphere, GL_FALSE);

	// Usage
	cout << endl;
	cout << "Keyboard Input: x for axes on/off" << endl;
	cout << "Keyboard Input: v for top, front, bird-eye view" << endl;
	cout << "Mouse button down, Select an object" << endl;
}

void quit()
{
	// Delete quadric shapes
	gluDeleteQuadric(sphere);
}

// Material
void setupColoredMaterial(const vec3& color)
{
	// Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { color[0], color[1], color[2], 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 100.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

// Draw a sphere using a GLU quadric
void drawSphere(float radius, int slices, int stacks)
{
	gluSphere(sphere, radius, slices, stacks);
}

// Light
void setupLight(const vec4& p)
{
	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(p));
}

// add
int sphere_arr[9] = { 0,1,2,3,4,5,6,7,8 };

void render(GLFWwindow* window)
{
	// Picking
	glInitNames();	// Initialize the name stack
	glPushName(-1);	// Push at least one name in the stack

	// Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	vec3	eye(0), up(0);
	switch (view)
	{
	case 0: eye = eyeTopView;		up = upTopView;		break;
	case 1: eye = eyeFrontView;		up = upFrontView;	break;
	case 2: eye = eyeBirdView;		up = upBirdView;	break;
	}
	
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	// Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH * dpiScaling);
	}

	// add
	if (inputMode == InputMode::DRAGGING) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(int(3 * dpiScaling), 0xcccc);
		glBegin(GL_LINE_LOOP);
		glVertex2f(point[0][0], point[0][1]);
		glVertex2f(point[0][0], point[2][1]);
		glVertex2f(point[2][0], point[2][1]);
		glVertex2f(point[2][0], point[0][1]);
		//cout << point[0][0] << "/////////////" << point[2][1]  << endl;

		glEnd();

	}
	else glDisable(GL_LINE_STIPPLE);

	// Smooth shading
	glShadeModel(GL_SMOOTH);

	// Lighting
	//
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	setupLight(light);

	// Draw objects
	//
	// 3x3 spheres or bunnies
	glScalef(0.4f, 0.4f, 0.4f);

	vec3	u[3];	//y-axis
	vec3	v[3];	//x-axis
	u[0] =  vec3(0, 1, 0) * 2.0f;	u[1] = vec3(0, 0, 0);	u[2] = -u[0];
	v[0] = -vec3(1, 0, 0) * 4.0f;	v[1] = vec3(0, 0, 0);	v[2] = -v[0];

	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(u[i].x, u[i].y, u[i].z);
		for (int j = 0; j < 3; j++) {
			glPushMatrix();
			glTranslatef(v[j].x, v[j].y, v[j].z);

			//Material
			if (sphere_arr[3 * i + j] == 9)	setupColoredMaterial(vec3(0, 0, 1)); // Selected
			else						setupColoredMaterial(vec3(1, 1, 1)); // Non-selected

			//Picking
			glLoadName(3 * i + j);	// Replace the name for the i-th row, j-th column

			// Draw a sphere
			drawSphere(0.7f, 64, 64);

			glPopMatrix();
		}
		glPopMatrix();
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

			//Axes on/off
		case GLFW_KEY_X:		axes = !axes;	break;


			// Top, front, bird-eye view
		case GLFW_KEY_V: view = (view + 1) % 3;	break;
		}
	}
}



int findNearestHits(int hits, GLuint selectBuffer[64])
{
	for (int i = 0; i < 9; i++) 
		sphere_arr[i] = i;

	bool	diagnosis = true;
	
	// axis include
	if (diagnosis )	cout << "hits = " << hits << endl;

	int		name = -1;
	float	nearest = 2.0;	// z1, z2 in [0, 1]
	
	int		index = 0;

	for (int i = 0; i < hits; i++) {
		int		n = selectBuffer[index];							//# of names
		

		if (diagnosis)
		{
			cout << "\t# of names = " << n << endl;
			//cout << "\tz1: " << z1 << endl;
			//cout << "\tz2: " << z2 << endl;
			cout << "\tnames: ";

			for (int j = 0; j < n; j++) {
				if (selectBuffer[index + 3 + j] > 9)
					continue;
				else
				{
					cout << selectBuffer[index + 3 + j] << " ";
					sphere_arr[selectBuffer[index + 3 + j]] = 9;
				}
			}
			cout << endl;
		}

		// To the next available one
		index += (3 + n);
	
	}
	if (diagnosis)	
		for (int i = 0; i < 9; i++) {
			if (sphere_arr[i] == 9)
				cout << "picked = " << i << endl;
		}

	return name;
}

// add
double click_point[2][2] = { {0, 0}, {0,0} };

int selectObjects(GLFWwindow* window, double x, double y)
{
	// Width and height of picking region in window coordinates
	//double delX = 2;
	//double delY = 2;

	// add
	double width;
	double height;

	if(click_point[1][0] > click_point[0][0])
		width = click_point[1][0] - click_point[0][0];
	else
		width = click_point[0][0] - click_point[1][0];

	if (click_point[1][0] > click_point[0][0])
		height = click_point[1][1] - click_point[0][1];
	else
		height = click_point[0][1] - click_point[1][1];


	x = (click_point[0][0] + click_point[1][0]) / 2;
	y = (click_point[0][1] + click_point[1][1]) / 2;


	// Maximum 64 selections
	GLuint	selectBuffer[64];
	glSelectBuffer(64, selectBuffer);

	// Current viewport
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Backup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	// Creates a projection matrix that can be used to restrict drawing to
	// a small region of the viewport
	gluPickMatrix(x, viewport[3] - y, width, height, viewport);	// y screen to viewport

	// Exploit the projection matrix for normal rendering
	setupProjectionMatrix();

	// Enter selection mode
	glRenderMode(GL_SELECT);

	// Render the objects for selection
	render(window);

	// Return to normal rendering mode and getting the picked object
	GLint	hits = glRenderMode(GL_RENDER);
	int	name = findNearestHits(hits, selectBuffer);


	// Restore the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	return	name;
}

void screen2world(float xs, float ys, float& xw, float& yw) {
	//In the world space, See reshape() in glSetup.cpp
	float aspect = (float)screenW / screenH;
	xw = 2.0f * (xs / (screenW - 1) - 0.5f) * aspect;
	yw = -2.0f * (ys / (screenH - 1) - 0.5f);
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	//Mouse cursor position in the screen coordinate system
	double xs, ys;
	glfwGetCursorPos(window, &xs, &ys);

	//Screen coordinate 2 world coordinate conversion
	float xw, yw;
	screen2world((float)xs, (float)ys, xw, yw);

	//The left button of the mouse is pressed
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		inputMode = InputMode::DRAGGING;

		point[0][0] = xw;   point[0][1] = yw;
		point[2][0] = xw;	point[2][1] = yw;
		//point[1][0] = xw;   point[1][1] = yw;
		//point[3][0] = xw;	point[3][1] = yw;
	

		click_point[0][0] = xs; 
		click_point[0][1] = ys;

		// Retrieve the selected object
		//picked = selectObjects(window, x, y);
		
	}

	else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {

		inputMode = InputMode::COMPLETE;
		point[2][0] = xw;   point[2][1] = yw;
		
		//point[1][0] = xw;  
		//point[3][1] = yw;

		click_point[1][0] = xs;
		click_point[1][1] = ys;

		// Retrieve the selected object
		picked = selectObjects(window, xw, yw);
	}
}

void mouseMove(GLFWwindow* window, double x, double y) {
	if (inputMode == InputMode::DRAGGING) {
		//Screen coordinate 2 world coordinate conversion
		screen2world((float)x, (float)y, point[2][0], point[2][1]);
	}
}
