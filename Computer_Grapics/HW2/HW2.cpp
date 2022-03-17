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

//Camera configuration
vec3 eyeTopView(0, 10, 0);		//Top view
vec3 upTopView(0, 0, -1);		//Top view

vec3 eyeFrontView(0, 0, 10);	//Front view
vec3 upFrontView(0, 1, 0);		//Front view

vec3 eyeBirdView(0, -10, 4);	//Bird-eye view
vec3 upBirdView(0, 1, 0);		//Bird-eye view
//vec3 center(0, 0, 0);

//추가
vec3 eyeTemp(3.5, 3, 3.5);
vec3 upTemp(0, 1, 0);

//Light configuration
vec4 light(5.0, 5.0, 5.0, 1);		//Light position
 
//Light configuration
vec4 lightInitialP(0.0, 2.0, 0.0, 1);	//Initial light position

//Global coordinate frame
bool axes = true;

//Global coordinate frame
float AXIS_LENGTH = 3;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//control variable
int	view = 3; //Top, front, bird-eye veiw
int selection = 1; //Selected example

bool rotationObject = false; //Rotate the models
bool rotationLight = false;	//Rotate the lights

float thetaModel = 0; //Rotation angle around the y-axis
float thetaLight[3];

bool lightOn[3]; //Point = 0, distant = 1, spot = 2 lights
bool attenuation = false; //Attenuation for point light

bool exponent = false;
float exponentInitial = 0.0; //[0, 128]
float exponentValue = exponentInitial;
float exponentNorm = exponentValue / 128.0f; //[0, 1]

bool cutoff = false;
float cutoffMax = 60; //[0, 90] degree
float cutoffInitial = 30.0; //[0, cutoffMax] degree
float cutoffValue = cutoffInitial;
float cutoffNorm = cutoffValue / cutoffMax; //[0, 1]

int material = 0; //Predefined material paratmeters

//Paly configuration
bool pause = false;

float timeStep = 1.0f / 120; //120fps
float period = 4.0;

//Current frame
int frame = 0;

//********************************************


//Show nomral vectors
bool switchVnormal = false;


void reinitialize()
{
	frame = 0;

	lightOn[0] = true;	//Turn on only the point light
	lightOn[1] = false;
	lightOn[2] = false;

	thetaModel = 0;
	for (int i = 0; i < 3; i++)
		thetaLight[i] = 0;

	exponentValue = exponentInitial;
	exponentNorm = exponentValue / 128.0f;

	cutoffValue = cutoffInitial;
	cutoffNorm = cutoffValue / cutoffMax;
}

void animate()
{
	frame += 1;

	//Rotation angle of the light
	if (rotationLight) {
		for (int i = 0; i < 3; i++)
			if (lightOn[i]) thetaLight[i] += 4 / period;	//degree
	}

	//Rotate angle the models
	if (rotationObject) thetaModel += 4 / period;	//degree

	//Periodicallly change the exponent and/or cutoff value of the spot light
	if (lightOn[2] && exponent) {
		exponentNorm += float(radians(4.0 / period) / M_PI);
		exponentValue = float(128.0f * (acos(cos(exponentNorm * M_PI)) / M_PI));
	}
	if (lightOn[2] && cutoff) {
		cutoffNorm += float(radians(4.0 / period) / M_PI);
		cutoffValue = float(cutoffMax * (acos(cos(exponentNorm * M_PI)) / M_PI));
	}
}

int main(int argc, char* argv[]) 
{
	//vsync should be 0 for precise time stepping
	vsync = 0;	//0 for immediate mode(Tearing possible)

	//Field of view of 85mm lens in degree
	//fovy = 16.1f;

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
	while (!glfwWindowShouldClose(window)) 
	{
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
			if (!pause) animate();

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

//Sphere, cylinder
GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;
GLUquadricObj* cone = NULL;

//추가
int sweep = 0;

glm::vec4 p[36][18]; //point
glm::vec3 normal_vec[36][18]; //normal_vector
glm::vec3 centerPoint[36][18]; //center_point
glm::vec3 check_dir[36][18]; //방향벡터
glm::vec3 vnormal[36][18]; //vertext normal vectors

void init()
{
	//Animation system
	reinitialize();

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

	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluQuadricNormals(cone, GLU_SMOOTH);
	gluQuadricOrientation(cone, GLU_OUTSIDE);
	gluQuadricTexture(cone, GL_FALSE);

	//Prepare mesh
	//readMesh("m01_bunny.off");

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << "Keyboard Input: i for reinitialization" << endl;
	cout << "Keyboard Input: up for increasing period" << endl;
	cout << "Keyboard Input: down for decreasing period" << endl;
	cout << "Keyboard Input: v for the top, front, bird-eye view" << endl;

	// add
	cout << "Keyboard Input: n for draw the vertex normal vector" << endl;


	cout << endl;
	cout << "Keyboard Input: p for a point light" << endl;
	cout << "Keyboard Input: d for a distant light" << endl;
	cout << "Keyboard Input: s for a spot light" << endl;
	cout << "Keyboard Input: a for light attenuation" << endl;
	cout << "Keyboard Input: e for time dependent exponent of a spot light" << endl;
	cout << "Keyboard Input: c for time dependent cutoff of a spot light" << endl;
	cout << "Keyboard Input: m for predefined material parameters" << endl;
	cout << "Keyboard Input: l for rotation of lights" << endl;
	cout << "Keyboard Input: o for rotation of objects" << endl;
	
	cout << "Keyboard Input: shift + right for adjust the shininess coefficient of a point light" << endl;
	cout << "Keyboard Input: shift + left for adjust the shininess coefficient of a point light" << endl;
	
	cout << "Keyboard Input: 1 for draw a torus " << endl;
	cout << "Keyboard Input: 2 for control the sweep angle to demonstrate the two-sided lighting" << endl;
	
	//point
	// 1.2 -> 1.3
	// show shininess coefficient
	p[0][0] = vec4(1.3, 1, 0, 1.0f);

	glm::mat4 M = glm::mat4(1.0);
	glm::mat4 A = glm::mat4(1.0);
	glm::mat4 B = glm::mat4(1.0);
	glm::mat4 C = glm::mat4(1.0);

	vec3 pivot = { 1, 1, 0 };

	glm::vec3 z_axis(0, 0, 1);
	glm::vec3 y_axis(0, 1, 0);
	glm::vec3 x_axis(1, 0, 0);
	glm::vec4 axis(0.0, 0.0, 1.0, 1.0);

	// Set p[i][j]
	A = glm::translate(A, pivot);
	B = glm::translate(B, -pivot);

	for (int j = 0; j < 17; j++) {
		//M = glm::mat4(1.0);
		//M = glm::translate(M, pivot);
		M = glm::rotate(M, glm::radians(20.0f), z_axis);
		//M = glm::translate(M, -pivot);

		p[0][j + 1] = A * M * B * p[0][0];
	}

	//C = glm::mat4(1.0);
	for (int i = 0; i < 35; i++) {
		C = glm::rotate(C, glm::radians(10.0f), y_axis);

		for (int j = 0; j < 18; j++) {
			for (int j = 0; j < 18; j++) {
				p[i + 1][j] = C * p[0][j];
			}
		}
	}

	//Save all normal vector
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			vec3 a = p[(i + 1) % 36][j] - p[i][j];
			vec3 b = p[i][(j + 1) % 18] - p[i][j];
			vec3 result = glm::cross(a, b);
			normalize(result);

			normal_vec[i][j] = result;
		}
	}

	//Calculate all faces center point
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			vec3 center = p[i][j] + p[(i + 1) % 36][j] + p[(i + 1) % 36][(j + 1) % 18] + p[i][(j + 1) % 18];
			centerPoint[i][j] = { (center.x) / 4.0f, (center.y) / 4.0f, (center.z) / 4.0f };
			check_dir[i][j] = eye - centerPoint[i][j];
		}
	}
	
	// 추가
	//calculate all vertices normal vector
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			vnormal[i][j].x = p[i][j].x + normal_vec[i][j].x;
			vnormal[i][j].y = p[i][j].y + normal_vec[i][j].y;
			vnormal[i][j].z = p[i][j].z + normal_vec[i][j].z;

			vnormal[i][j] = normalize(normal_vec[i][j]);
			vnormal[i][j] = vnormal[i][j] * 0.1f;
		}
	}
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(cone);

	//Delete mesh
	//deleteMesh();
}


void setupColoredMaterial(const vec3& color)
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { color[0], color[1], color[2], 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setupWhiteShinyMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setupBrassMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.33f, 0.22f, 0.33f, 1.0f };
	GLfloat mat_diffuse[4] = { 0.78f, 0.57f, 0.11f, 1.0f };
	GLfloat mat_specular[4] = { 0.99f, 0.91f, 0.81f, 1.0f };
	GLfloat mat_shininess = 27.8f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setupRedPlasticMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.3f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[4] = { 0.6f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[4] = { 0.8f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_shininess = 32.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

//추가
//Only values in the range 0 128 are accepted.
GLfloat shininess = 0;

void setupShininessMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void drawSquare()
{
	//Square
	glBegin(GL_QUADS);

	//front
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glEnd();
}

//Draw a sphere using a GLU quadric
void drawSphere(float radius, int slices, int stacks)
{
	gluSphere(sphere, radius, slices, stacks);
}

//Draw a cylinder using a GLU quadric
void drawCylinder(float radius, float height, int slices, int stacks)
{
	gluCylinder(cylinder, radius, radius, height, slices, stacks);
}

//Draw a cone using a GLU quadric
void drawCone(float radius, float height, int slices, int stacks)
{
	gluCylinder(cone, 0, radius, height, slices, stacks);
}

//Compute the rotation axis and angle from a to b
//
//Axis is not normalized.
//theta is represented in degrees.
//
void computeRotation(const vec3& a, const vec3& b, float& theta, vec3& axis)
{
	axis = cross(a, b);
	float	sinTheta = length(axis);
	float	cosTheta = dot(a, b);
	theta = float(atan2(sinTheta, cosTheta) * 180.0 / M_PI);
}

//Light
void setupLight(const vec4& p, int i)
{
	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0 + i, GL_POSITION, value_ptr(p));

	//Attenuation for the point and spot light
	if ((i == 0 || i == 2) && attenuation)
	{
		glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1.0f);
		glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.1f);
		glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.05f);
	}
	else {		//Defalut value
		glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1.0f);
		glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.0f);
	}

	if (i == 2)		//Spot light
	{
		vec3 spotDirection = -vec3(p);
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, value_ptr(spotDirection));
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, cutoffValue);		//[0, 90]
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, exponentValue);	//[0, 128]
	}
	else {	//Point and distant light.
		// 180 to turn off cutoff when it has been used as a spot light
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180);	//uniform light distribution
	}
}

void drawArrow(const vec3& p, bool tailOnly)
{
	//Make it possible to change a subset of material parameters
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//Common material
	GLfloat mat_specular[4] = { 1, 1, 1, 1 };
	GLfloat mat_shininess = 25;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	//Transformation
	glPushMatrix();

	glTranslatef(p.x, p.y, p.z);

	if (!tailOnly)
	{
		float theta;
		vec3 axis;
		computeRotation(vec3(0, 0, 1), vec3(0, 0, 0) - vec3(p), theta, axis);
		glRotatef(theta, axis.x, axis.y, axis.z);
	}

	//Tail sphere
	float	arrowTailRadius = 0.05f;
	glColor3f(1, 0, 0);		//ambient and diffuse
	drawSphere(arrowTailRadius, 16, 16);

	if (!tailOnly)
	{
		float arrowShaftRadius = 0.02f;
		float arrowShaftLengh = 0.2f;
		glColor3f(0, 1, 0);
		drawCylinder(arrowShaftRadius, arrowShaftLengh, 16, 5);

		//Head cone
		float arrowheadHeight = 0.09f;
		float arrowheadRadius = 0.06f;
		glTranslatef(0, 0, arrowShaftLengh + arrowheadHeight);
		glRotatef(180, 1, 0, 0);
		glColor3f(0, 0, 1);
		drawCone(arrowheadRadius, arrowheadHeight, 16, 5);
	}

	glPopMatrix();

	//For convential material setting
	glDisable(GL_COLOR_MATERIAL);
}

void drawSpotLight(const vec3& p, float cutoff)
{
	glPushMatrix();

	glTranslatef(p.x, p.y, p.z);

	float theta;
	vec3 axis;
	computeRotation(vec3(0, 0, 1), vec3(0, 0, 0) - vec3(p), theta, axis);
	glRotatef(theta, axis.x, axis.y, axis.z);

	//Color
	setupColoredMaterial(vec3(0, 0, 1));

	//tan(cutoff) = r / h;
	float h = 0.15f;
	float r = h * tan(radians(cutoff));
	drawCone(r, h, 16, 5);

	//Color
	setupColoredMaterial(vec3(1, 0, 0));

	//Apex
	float apexRadius = 0.06f * (0.5f + exponentValue / 128.0f);
	drawSphere(apexRadius, 16, 16);

	glPopMatrix();
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

void drawVnormal()
{
	vec3 temp[36][18];

	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			temp[i][j].x = p[i][j].x + vnormal[i][j].x;
			temp[i][j].y = p[i][j].y + vnormal[i][j].y;
			temp[i][j].z = p[i][j].z + vnormal[i][j].z;
		}
	}

	glBegin(GL_LINES);
	setDiffuseColor(glm::vec3(1, 0, 0));	//Material //red
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			glVertex3fv(value_ptr(p[i][j]));
			glVertex3fv(value_ptr(temp[i][j]));
		}
	}
	glEnd();
}

void draw_All()
{
	
	//프레임 그리기
	glEnable(GL_POLYGON_OFFSET_FILL); //depth

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Draw wireframe only

	setDiffuseColor(glm::vec3(0, 0, 0));

	//그리기
	glBegin(GL_QUADS);
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
			glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_LINE);

	//파란색 사각형 그리기
	glEnable(GL_POLYGON_OFFSET_FILL); //depth

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Overlay wireframe on quads

	setDiffuseColor(glm::vec3(0, 0, 1));

	//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
	glPolygonOffset(1.0f, 1.0f);

	glBegin(GL_QUADS);
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {

			glNormal3fv(value_ptr(normal_vec[i][j]));
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
			glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);

	
}

void color_Shading()
{
	//처음 원 그리기 시작
	if (sweep == 0)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		setDiffuseColor(glm::vec3(0, 0, 0));

		//
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 18; j++) {
			glVertex3fv(value_ptr(p[0][j]));
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_LINE);
	}

	else if (sweep > 0)
	{
		//프레임 그리기 시작
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		setDiffuseColor(glm::vec3(0, 0, 0));

		//프레임 그리기
		glBegin(GL_QUADS);
		//움직인 만큼 그리기
		for (int i = 0; i < sweep; i++) {
			for (int j = 0; j < 18; j++) {
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
				glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
				glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
				glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_LINE);

		//사각형 그리기 시작

		//추가 Two-Sided Lighting
		glDisable(GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

		
		//추가
		GLfloat mat_blue[4] = { 0, 0, 1, 1 };
		GLfloat mat_red[4] = { 1, 0, 0, 1 };

		//사각형 그리기
		glBegin(GL_QUADS);
		//움직인 만큼 그리기
		for (int i = 0; i < sweep; i++) {
			for (int j = 0; j < 18; j++) {

				// 앞면인지 뒷면인지 내적연산을 통해 판단 
				if (dot(normal_vec[i][j], check_dir[i][j]) > 0) // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 크면 바깥면
				{
					//setDiffuseColor(glm::vec3(0, 0, 1)); //파랑
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue); //파랑
					//GL_FRONT는 점을 찍는 방향으로 판단
					//노말벡터로 판단 가능
					glNormal3fv(value_ptr(normal_vec[i][j]));

					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
					
				}
				else
				{ // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 작으면 안쪽면
					//setDiffuseColor(glm::vec3(1, 0, 0)); //빨강

					glMaterialfv(GL_BACK, GL_DIFFUSE, mat_red); //빨강
					//GL_FRONT는 점을 찍는 방향으로 판단
					//노말벡터로 판단 가능

					glNormal3fv(value_ptr(normal_vec[i][j]));
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);

				}

			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else if (sweep < 0)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		setDiffuseColor(glm::vec3(0, 0, 0));

		//프레임 그리기
		glBegin(GL_QUADS);
		for (int i = 36 + sweep; i < 36; i++) {
			for (int j = 0; j < 18; j++) {
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
				glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
				glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
				glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_LINE);

		// 사각형 그리기
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

		//추가
		glDisable(GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		//추가
		GLfloat mat_blue[4] = {0.0, 0.0, 1.0, 1.0};
		GLfloat mat_red[4] = { 1.0, 0.0, 0.0, 1.0 };


		// 현재 점에서 끝 점까지 그림
		glBegin(GL_QUADS);
		for (int i = 36 + sweep; i < 36; i++) {
			for (int j = 0; j < 18; j++) {
				
				// 1차과제 코드
				// 앞면인지 뒷면인지 내적연산을 통해 판단 
				/*if (dot(normal_vec[i][j], check_dir[i][j]) > 0) // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 크면 바깥면
				{
					//setDiffuseColor(glm::vec3(0, 0, 1)); //파랑
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue); //blue
					//GL_FRONT는 점을 찍는 방향으로 판단
					//노말벡터로 판단 가능

					glNormal3fv(value_ptr(normal_vec[i][j]));
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
				}
				else
				{ // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 작으면 안쪽면
					//setDiffuseColor(glm::vec3(1, 0, 0)); //빨강
					glMaterialfv(GL_BACK, GL_DIFFUSE, mat_red); //red
					//GL_FRONT는 점을 찍는 방향으로 판단
					//노말벡터로 판단 가능*/

				// change
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue); //blue
				glMaterialfv(GL_BACK, GL_DIFFUSE, mat_red); //red

				glNormal3fv(value_ptr(normal_vec[i][j]));
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
				glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
				glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
				glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);

				
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}


void render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//vec3	eye(0), up(0);
	switch (view)
	{
	case 0: eye = eyeTopView;		up = upTopView;		break;
	case 1: eye = eyeFrontView;		up = upFrontView;	break;
	case 2: eye = eyeBirdView;		up = upBirdView;	break;

	//추가
	case 3: eye = eyeTemp;	up = upTemp;	break;
	}
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH * dpiScaling);
	}

	//Rotation of the light or 3x3 models
	vec3 axis(1, 0, 1);
	axis = normalize(axis);

	//Lighting
	//
	glEnable(GL_LIGHTING);

	//Set up the lights
	vec4 lightP[3];
	for (int i = 0; i < 3; i++)
	{
		//Just turn off the i-th light, if not lit
		if (!lightOn[i]) { glDisable(GL_LIGHT0 + i); continue; }

		//Turn on the i-th light
		glEnable(GL_LIGHT0 + i);

		//Dealing with the distant light
		lightP[i] = lightInitialP;
		if (i == 1) lightP[i].w = 0;

		//Lights rotate around the center of the world coordinate system
		mat4	R = rotate(mat4(1.0), radians(thetaLight[i]), axis);
		lightP[i] = R * lightP[i];

		//Set up the i-th light
		setupLight(lightP[i], i);
	}

	//Draw the geometries of the lights
	for (int i = 0; i < 3; i++)
	{
		if (!lightOn[i])		continue;

		if (i == 2)	drawSpotLight(lightP[i], cutoffValue);
		else
		{
			drawArrow(lightP[i], i == 0);	//Tail only for a point light
		}
	}

	//Material
	//setupMaterial();
	setupShininessMaterial();

	switch (selection)
	{
	case 1: draw_All();			break;
	case 2: color_Shading();	break;
	}

	if (switchVnormal)
		drawVnormal();
}

void keyboard(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT && !(mods & GLFW_MOD_SHIFT)) 
	{
		switch (key)
		{
		//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

		//Axes
		case GLFW_KEY_X:		axes = !axes; break;

		//Initialization
		case GLFW_KEY_I: reinitialize(); break;

		//play on/off
		case GLFW_KEY_SPACE:	pause = !pause; break;

		//Period control
		case GLFW_KEY_UP:	period += 0.1f; break;
		case GLFW_KEY_DOWN: period = (float)std::max(period - 0.1, 0.1); break;

		//Top, front, bird-eye view
		case GLFW_KEY_V:	
			view = (view + 1) % 4; break;
			//view = 3;

		//Turn on/off the point, distant, spot light
		//2번문제(s 클릭)
		case GLFW_KEY_P: lightOn[0] = !lightOn[0];	break;
		case GLFW_KEY_D: lightOn[1] = !lightOn[1];	break;
		case GLFW_KEY_S: lightOn[2] = !lightOn[2];	break;

		//Light attenuation
		case GLFW_KEY_A: attenuation = !attenuation; break;

		//Light: point, direction, spot
		//3번문제(l 클릭)
		case GLFW_KEY_L: rotationLight = !rotationLight; break;

		//Rotation: light position/direction, models
		case GLFW_KEY_O: rotationObject = !rotationObject; break;

		//Time dependent exponent of a spot light
		case GLFW_KEY_E: exponent = !exponent; break;

		//Time dependent cutoff of a spot light
		case GLFW_KEY_C: cutoff = !cutoff; break;

		//Predefined material parameters
		case GLFW_KEY_M: material = (material + 1) % 3; break;

			

		//1번문제 draw the vertex normal vectors
		case GLFW_KEY_N: switchVnormal = !switchVnormal;	break;

		//5번문제 Control the sweep angle to demonstrate the two-sided lighting(2번 클릭)
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;

		case GLFW_KEY_RIGHT:
			if (sweep < 36)
				sweep++;
			else
				sweep = sweep;
			break;

		case GLFW_KEY_LEFT:
			if (sweep > -36)
				sweep--;
			else
				sweep = sweep;
			break;
		}
	}

	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (mods & GLFW_MOD_SHIFT))
	{
		switch (key)
		{
		//4번문제
		//추가
		//0~128 값을 가질 수 있음
		case GLFW_KEY_LEFT: 
			if (shininess <= 0)
				shininess = 0;
			else
				shininess = shininess - 1;
			break;
		
		case GLFW_KEY_RIGHT: 
			if (shininess >= 128)
				shininess = 128;
			else
				shininess = shininess + 1;
			break;
		

		//case GLFW_KEY_UP:
			
		//case GLFW_KEY_DOWN:
		
		}
	}
}