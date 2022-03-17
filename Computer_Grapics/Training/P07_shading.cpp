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

bool readMesh(const char* filename);
void deleteMesh();

//Camera configuration
vec3 eye(3, 3, 3);
vec3 center(0, 0, 0);
vec3 up(0, 1, 0);

//Light configuration
vec4 light(5.0, 5.0, 0.0, 1);		//Light position

//Global coordinate frame
bool axes = true;

float AXIS_LENGTH = 3;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//control variable
bool smooth = true;

//Selected example
int selection = 1;

//Sphere
GLUquadricObj* sphere = NULL;

//Paly configuration
bool pause = true;

float timeStep = 1.0f / 120; //120fps
float period = 4.0;

//Drawing parameters
bool polygonFill = true;	//Polygon mode

//Current frame
int frame = 0;

int main(int argc, char* argv[]) {
	//FPS control: vsync should be 0 for precise time stepping
	vsync = 0;

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
			//Animate 1 frame
			if (!pause)	frame += 1;

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

	//Prepare mesh
	readMesh("m01_bunny.off");

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << "Keyboard Input: s for turn on/off smooth shading" << endl;
	cout << "Keyboard Input: f for polygon fill on/off" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for Draw normal vectors of triangles of the bunny model" << endl;
	cout << "Keyboard Input: 2 for Draw normal vectors of vertices of the bunny model" << endl;

	
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);

	//Delete mesh
	deleteMesh();
}

//Light
void setupLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
void drawSphere(float radius, int slices, int stacks, const vec3& color)
{
	//Material
	setDiffuseColor(color);

	//Sphere using GLU quadrices
	gluSphere(sphere, radius, slices, stacks);
}

//Read a mesh from a given OFF file
int		nVertices = 0, nFaces = 0, nEdges = 0;
glm::vec3* vertex = NULL;
glm::vec3* vnormal = NULL;		//Vertex normal
glm::vec3* fnormal = NULL;		//Face normal
int* face[3] = { NULL, NULL, NULL };

bool readMesh(const char* filename)
{
	ifstream is(filename);
	if (is.fail()) return false;

	char magicNumber[256];
	is >> magicNumber;

	// # vertices, # faces, # edges
	is >> nVertices >> nFaces >> nEdges;
	cout << "# vertices = " << nVertices << endl;
	cout << "# faces = " << nFaces << endl;

	//Vertices
	vertex = new vec3[nVertices];
	for (int i = 0; i < nVertices; i++)
		is >> vertex[i].x >> vertex[i].y >> vertex[i].z;

	//Vertex normals
	vnormal = new glm::vec3[nVertices];
	for (int i = 0; i < nVertices; i++)
		vnormal[i] = glm::vec3(0, 0, 0);

	//Face normals
	fnormal = new glm::vec3[nFaces];

	//Faces
	face[0] = new int[nFaces];	//Only support triangles
	face[1] = new int[nFaces];
	face[2] = new int[nFaces];

	int n;
	for (int i = 0; i < nFaces; i++) {
		is >> n >> face[0][i] >> face[1][i] >> face[2][i];
		if (n != 3) cout << "# vertices of the " << i << "-th faces = " << n << endl;

		//Normal vector of the face
		glm::vec3 v1 = vertex[face[1][i]] - vertex[face[0][i]];
		glm::vec3 v2 = vertex[face[2][i]] - vertex[face[0][i]];
		glm::vec3 v = normalize(cross(v1, v2));

		fnormal[i] = v;

		// 크기 줄이기
		fnormal[i] = fnormal[i] * 0.1f;
		
		//Add it to the normal vector of each vertex
		vnormal[face[0][i]] += v;
		vnormal[face[1][i]] += v;
		vnormal[face[2][i]] += v;
	}

	//Normalize of the normal vectors
	for (int i = 0; i < nVertices; i++) {
		vnormal[i] = normalize(vnormal[i]);
		
		// 크기 줄이기
		vnormal[i] = vnormal[i] * 0.1f;
	}

	return true;
}

//Delete the vertices and faces of the mesh
void deleteMesh()
{
	if (vertex) { delete[] vertex; vertex = NULL; }
	if (vnormal) { delete[] vnormal; vnormal = NULL; }
	if (fnormal) { delete[] fnormal; fnormal = NULL; }
	if (face[0]) { delete[] face[0]; face[0] = NULL; }
	if (face[1]) { delete[] face[1]; face[1] = NULL; }
	if (face[2]) { delete[] face[2]; face[2] = NULL; }
}


//ex01 ( 개수 : 4320 ) 
void normalV_triangles()
{
	vec3* center_point = new vec3[nFaces];

	// 삼각형의 중심점 구하기
	for (int i = 0; i < nFaces; i++) {
		center_point[i] = vertex[face[0][i]] + vertex[face[1][i]] + vertex[face[2][i]];
		center_point[i].x = center_point[i].x / 3.0f;	
		center_point[i].y = center_point[i].y / 3.0f;	
		center_point[i].z = center_point[i].z / 3.0f;
	}

	vec3* temp = new vec3[nFaces];

	//중심점 + 법선벡터
	for (int i = 0; i < nFaces; i++) {
		temp[i] = center_point[i] + fnormal[i];
	}

	glBegin(GL_LINES);
	for (int i = 0; i < nFaces; i++) {
		glVertex3fv(value_ptr(center_point[i]));
		glVertex3fv(value_ptr(temp[i]));
	}
	glEnd();
}

//ex02 ( 개수 : 2162 ) 
void normalV_vertices()
{
	vec3* temp = new vec3[nVertices];

	//정점 + 법선벡터
	for (int i = 0; i < nVertices; i++) {
		
		temp[i] = vertex[i] + vnormal[i];
	}

	glBegin(GL_LINES);
	for (int i = 0; i < nVertices; i++) {
		glVertex3fv(value_ptr(vertex[i]));
		glVertex3fv(value_ptr(temp[i]));
	}
	glEnd();
}

void render(GLFWwindow* window)
{
	//Polygon mode
	if (polygonFill) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH * dpiScaling);
	}

	//Lighting
	setupLight();

	//Smooth shading
	if (smooth) glShadeModel(GL_SMOOTH);
	else        glShadeModel(GL_FLAT);	//Use the normal of the last vertex of a polygon

	//Material
	setupMaterial();

	//Rotation
	float theta = frame * 4 / period;
	glm::vec3 axis(0, 1, 0);
	glRotatef(theta, axis.x, axis.y, axis.z);

	//Draw sphere using gluSphere() after setting up the material
	switch (selection)
	{
	case 1: normalV_triangles();	break;
	case 2: normalV_vertices();	break;
	
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

			//Axes
		case GLFW_KEY_X:		axes = !axes; break;

			//play on/off
		case GLFW_KEY_SPACE:	pause = !pause; break;

			//Control for changing smooth/flat shading
		case GLFW_KEY_S: smooth = !smooth; break;

			//Polygon fill on/off
		case GLFW_KEY_F: polygonFill = !polygonFill; break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;
		
		
		}
	}
}