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

//Paly configuration
bool pause = false;

float timeStep = 1.0f / 120; //120fps
float period = 4.0;

//Current frame
int frame = 0;



int main(int argc, char* argv[])
{
	//vsync should be 0 for precise time stepping
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

//추가
int sweep = 0;

glm::vec4 p[36][18]; //point
glm::vec3 normal_vec[36][18]; //normal_vector
glm::vec3 centerPoint[36][18]; //center_point
glm::vec3 check_dir[36][18]; //방향벡터

void init()
{
	p[0][0] = vec4(1.2, 1, 0, 1.0f);
	
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

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for Draw the wireframe only" << endl;
	cout << "Keyboard Input: 2 for Draw the quads and the wireframe" << endl;
	cout << "Keyboard Input: 3 for Sweep angle control around the y-axis" << endl;
	cout << "Keyboard Input: 4 for Two-sided constant shading" << endl;
	//cout << "Keyboard Input: 5 for test" << endl;
}

void quit()
{
	
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


//프레임 그리기
void draw_Wireframe()
{
	glEnable(GL_POLYGON_OFFSET_FILL); //depth
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Draw wireframe only
	
	setDiffuseColor(glm::vec3(0, 0, 0));

	//그리기
	glBegin(GL_QUADS);
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			// i의  max 값 36과 j의 max 값 18은 0으로 바꿔서 계산
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
			glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_LINE);
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
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
			glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
			glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void draw_Sweep()
{
	//처음 원 그리기
	if (sweep == 0)
	{
		glEnable(GL_POLYGON_OFFSET_FILL); //depth

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		setDiffuseColor(glm::vec3(0, 0, 0));	
		
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 18; j++) {
			glVertex3fv(value_ptr(p[0][j]));
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_LINE);
	}

	//증가 방향
	else if (sweep > 0)
	{
		glEnable(GL_POLYGON_OFFSET_FILL); //depth

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

		//파란색 사각형 그리기
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

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
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	//감소 방향
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

		setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

		// 현재 점에서 끝 점까지 그림
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
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
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
		glEnable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

		//사각형 그리기
		glBegin(GL_QUADS);
		//움직인 만큼 그리기
		for (int i = 0; i < sweep; i++) {
			for (int j = 0; j < 18; j++) {

				// 앞면인지 뒷면인지 내적연산을 통해 판단 
				if (dot(normal_vec[i][j], check_dir[i][j]) > 0) // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 크면 바깥면
				{ 
					setDiffuseColor(glm::vec3(0, 0, 1)); //파랑
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
				}
				else 
				{ // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 작으면 안쪽면
					setDiffuseColor(glm::vec3(1, 0, 0)); //빨강
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
					
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

		setDiffuseColor(glm::vec3(0, 0, 1));

		//파란색 사각형이랑 프레임을 같이 그리기 위해 사용
		glPolygonOffset(1.0f, 1.0f);

		// 현재 점에서 끝 점까지 그림
		glBegin(GL_QUADS);
		for (int i = 36 + sweep; i < 36; i++) {
			for (int j = 0; j < 18; j++) {
				// 앞면인지 뒷면인지 내적연산을 통해 판단 
				if (dot(normal_vec[i][j], check_dir[i][j]) > 0) // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 크면 바깥면
				{
					setDiffuseColor(glm::vec3(0, 0, 1)); //파랑
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);
				}
				else
				{ // 법선 벡터와 centerPoint -> eye 벡터의 내적 값이 0보다 작으면 안쪽면
					setDiffuseColor(glm::vec3(1, 0, 0)); //빨강
					glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
					glVertex3f(p[i][(j + 1) % 18].x, p[i][(j + 1) % 18].y, p[i][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][(j + 1) % 18].x, p[(i + 1) % 36][(j + 1) % 18].y, p[(i + 1) % 36][(j + 1) % 18].z);
					glVertex3f(p[(i + 1) % 36][j].x, p[(i + 1) % 36][j].y, p[(i + 1) % 36][j].z);

				}
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}

//점 확인 파트
void drawPoints() {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 18; j++) {
			glPointSize(6.0);
			glBegin(GL_POINTS);
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
		}
	}
	glEnd();
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

	switch (selection)
	{
	case 1: draw_Wireframe(); break;
	case 2: draw_All(); break;
	case 3: draw_Sweep(); break;
	case 4: color_Shading(); break;
	//case 5: drawPoints(); break;
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
		case GLFW_KEY_3: selection = 3; break;
		case GLFW_KEY_4: selection = 4; break;
		//case GLFW_KEY_5: selection = 5; break;

		case GLFW_KEY_RIGHT: 
			if(sweep < 36)
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
}