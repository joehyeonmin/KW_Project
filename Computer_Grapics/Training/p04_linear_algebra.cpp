#include <glm/glm.hpp>					//OpenGL Mathematics
#include <glm/gtx/string_cast.hpp>		//glm::to_string()
#include <glm/gtc/matrix_access.hpp>	//glm:column(), glm::row()
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <iostream>
using namespace std;

void part1() {
	cout << "Vector operations" << endl;

	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 2, 1);
	cout << "v1 = " << to_string(v1) << endl;
	cout << "v2 = " << to_string(v2) << endl << endl;

	cout << "v1 + v2 = " << to_string(v1 + v2) << endl;
	cout << "v1 - v2 = " << to_string(v1 - v2) << endl;
	cout << "-v1 = " << to_string(-v1) << endl;
	cout << "v1 - 2(v2) = " << to_string(v1 - 2.0f * v2) << endl;
	cout << "dot(v1, v2) = " << dot(v1, v2) << endl;
	cout << "cross(v1, v2) = " << to_string(cross(v1, v2)) << endl;
}

void part2() {
	cout << "Matrix operations" << endl;

	glm::mat3 A1(1.0, 2.0, 1.0, 2.0, 3.0, 1.0, 3.0, 2.0, 2.0);
	glm::mat3 A2(2.0, 2.0, 1.0, 1.0, 2.0, 1.0, 2.0, 1.0, 1.0);
	
	cout << "A1 = " << to_string(A1) << endl;
	cout << "A2 = " << to_string(A2) << endl << endl;

	cout << "A1 + A2 = " << to_string(A1 + A2) << endl;
	cout << "A1 - A2 = " << to_string(A1 - A2) << endl;
	cout << "-A1 = " << to_string(-A1) << endl;
	cout << "A1 - 2(A2) = " << to_string(A1 - 2.0f * A2) << endl;
	cout << "A1 x A2 = " << to_string(A1 * A2) << endl;
	cout << "A2 x A1 = " << to_string(A2 * A1) << endl;

	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 2, 1);

	cout << "A1 x v1 = " << to_string(A1 * v1) << endl;
	cout << "A2 x v2 = " << to_string(A2 * v2) << endl;
}

int main(int argc, char* argv[]) {
	int e = (argc < 2) ? 1 : atoi(argv[1]);

	switch (e) {
	case 1: part1(); break; //Vector operations
	case 2: part2(); break; //Matrix operations
	
	}

	return 0;
}

/*void part1() {
	cout << "3x1 vectors" << endl;

	//3D float vector with 0 values
	glm::vec3	a(0);
	cout << "a = " << to_string(a) << endl;
	

	//3D float vector with initial values
	glm::vec<3, float>	b(3, 2, 1);
	cout << "b = " << to_string(b) << endl;


	//3D vector assignment
	a = glm::vec3(1, 2, 3);
	cout << "a = " << to_string(a) << endl;

	//Componet_wise functions for setting and getting the x, y, z values
	a.z = 3;
	cout << "a[0] = " << a[0] << endl;
	cout << "a.z = " << a.z << endl;
	
}

void part2() {
	cout << "Vector operations" << endl;

	//Vectors
	glm::vec3 a(1, 2, 3);
	glm::vec3 b(3, 2, 1);
	cout << "a = " << to_string(a) << endl;
	cout << "b = " << to_string(b) << endl << endl;

	//Addition / subtraction
	cout << "a + b = " << to_string(a + b) << endl;
	cout << "a - b = " << to_string(a - b) << endl;

	//Negation
	cout << "-a = " << to_string(-a) << endl;

	//Scalar multiplication and subtraction
	cout << "1.5*a = " << to_string(1.5f * a) << endl;

	//Dot product
	cout << "dot(a, b) = " << dot(a, b) << endl;

	//Cross produect
	cout << "cross(a, b) = " << to_string(cross(a, b)) << endl;

	//Length produect
	cout << "length(a) = " << length(a) << endl;
}

void part3() {
	cout << "3x3 Matrix" << endl;

	//Zero Matrix
	glm::mat3 A(0);
	cout << "A = " << to_string(A) << endl;

	//Identity Matrix
	A = glm::mat3(1.0);
	cout << "A = " << to_string(A) << endl;

	//GLM employs column-major representation.
	//    B = 1.0 2.0 3.0
	//	      0.0 1.0 0.0
	//	      0.0 0.0 1.0
	glm::mat3 B(1.0, 0.0, 0.0, 2.0, 1.0, 0.0, 3.0, 0.0, 1.0);
	cout << "B = " << to_string(B) << endl;

	float B_data[9] = { 1.0, 0.0, 0.0, 2.0, 1.0, 0.0, 3.0, 0.0, 1.0 };
	B = glm::make_mat3(B_data);
	cout << "B = " << to_string(B) << endl;

	//Elemet indexing: B[column][row] in GLM. Be careful!
	cout << "3rd col of B = " << to_string(B[2]) << endl; //3rd column
	cout << "3rd col B = " << to_string(column(B, 2)) << endl; //Third column
	cout << "3rd row of B = " << to_string(row(B, 2)) << endl; //Third row
	cout << "1st row 3rd col of B = " << B[2][0] << endl; //B[column][row]
	cout << "1st row 3rd col of B = " << B[2].x << endl; //x, y, z, w
}

void part4() {
	cout << "Matrix operations" << endl;

	//Matrices
	glm::mat3 A(1.0);
	glm::mat3 B(1.0, 0.0, 0.0, 2.0, 1.0, 0.0, 3.0, 0.0, 1.0);
	
	cout << "A = " << to_string(A) << endl;
	cout << "B = " << to_string(B) << endl;

	//Addtion / Subtraction
	cout << "A + B = " << to_string(A + B) << endl;
	cout << "A - B = " << to_string(A - B) << endl;

	//Negation
	cout << "-A = " << to_string(-A) << endl;

	//Scalar multiplication
	cout << "1.5*A = " << to_string(1.5f *A) << endl;

	//Matrix multiplication
	cout << "A x B = " << to_string(A * B) << endl;
	
	//Matrix transpose
	cout << "transpose(B) = " << to_string(transpose(B)) << endl;

	//Matrix inverse
	cout << "inverse(B) = " << to_string(inverse(B)) << endl;

	//Check the inverse
	cout << "inverse(B) * B = " << to_string(inverse(B) * B) << endl;
	
}

void part5() {
	cout << "Matrix-vector multiplication and assembling" << endl;

	//Vectors
	glm::vec3 a(1, 2, 3);
	cout << "a = " << to_string(a) << endl;

	//Matrices
	glm::mat3 B(1.0, 0.0, 0.0, 2.0, 1.0, 0.0, 3.0, 0.0, 1.0);
	cout << "B = " << to_string(B) << endl;

	//Matrix-vector multiplication
	cout << "B x a = " << to_string(B * a) << endl;
	cout << "a x B = " << to_string(a * B) << endl;

	//Composition of a 4x1 vector from a 3x1 vector
	// 
	cout << "(a, 1.0) = " << to_string(glm::vec4(a, 1.0)) << endl;
	cout << "(1.0, a) = " << to_string(glm::vec4(1.0,a)) << endl;

	// Converting a 3x3 matrix into the corresponding homogeneous matrix
	glm::mat4	C = glm::mat4(B);
	cout << "C = " << to_string(C) << endl;



}
int main(int argc, char* argv[]) {
	int e = (argc < 2) ? 1 : atoi(argv[1]);
	
	switch (e) {
	case 1: part1(); break; //Vector operations
	case 2: part2(); break; //Matrix operations
	case 3: part3(); break; //Matrices
	case 4: part4(); break; //Matrix operations
	case 5: part5(); break; //Matrix-vector multiplication and assembling
	}

	return 0;
}*/