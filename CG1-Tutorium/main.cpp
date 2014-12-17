/** \file main.cpp OpenGL-Programm eines sich drehenden, von 2 Lampen angestrahlten, Würfels.
*
* Die 1. Lampe leuchtet rot und ist stationär. Die 2. Lampe leuctet blau und kreist um den Würfel.
* 
* \synopsis g++ *.cpp -I/usr/include/glm -I/usr/include/GL  -lGL -lGLEW -lGLU -lglut
*/

#include "main.h"
#include "Box.h"


GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);
GLuint programID;

float rotate = 0;

Box *box;

glm::vec3 redLightDirection(-1, 0, -1);
glm::vec3 blueLightDirection(1, 0, 0);

void init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	programID = loadShaders("Vertex.vsh", "Fragment.fsh");
	box = new Box();
	glUseProgram(programID);
	glEnable(GL_DEPTH_TEST);
}


void display(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glBindVertexArray(box->vaoID);

	glm::mat4 proj  = glm::perspective(20.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 view  = glm::lookAt(glm::vec3(10,10,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 model(1);

	model = glm::mat4(1);//glm::rotate(model, rotate, 0.0f, 1.0f, 0.0f);

	GLint projLoc = glGetUniformLocation(programID, "proj");
	GLint viewLoc = glGetUniformLocation(programID, "view");
	GLint modelLoc = glGetUniformLocation(programID, "model");

	GLint redLoc = glGetUniformLocation(programID, "redLightDir");
	glUniform3fv(redLoc, 1, &redLightDirection[0]);

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	glm::mat4 lightRotate = glm::mat4(1);//glm::rotate(rotate, 0.0f, 0.0f, 1.0f);
	glm::vec3 newBlueLightDirection = glm::vec3(lightRotate * glm::vec4(blueLightDirection, 1));
	GLint blueLightLoc = glGetUniformLocation(programID, "blueLightDir");
	glUniform3fv(blueLightLoc, 1, &newBlueLightDirection[0]);

	glDrawArrays(box->typeOfPrimitive, 0, box->getNumberOfVertices()*
		box->numVertsPerPrimitive);
	glutSwapBuffers();
}

void timer(int value){
	rotate += 1;
	if(rotate >= 360)
		rotate = 0;
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

int main (int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutMainLoop();
	return OK;
}
