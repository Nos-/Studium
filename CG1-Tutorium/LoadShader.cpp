#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>

#include <glew.h>

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>


GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath){
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if(vertexShaderStream.is_open()){
		std::string line = "";
		while( std::getline( vertexShaderStream, line))
			vertexShaderCode += "\n"+line;
		vertexShaderStream.close();
	}else{
		printf("Failed to open vertexShader source!\n");
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::string line = "";
		while( std::getline( fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close();
	}else{
		printf("Failed to open fragmentShader source!\n");
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	printf("compiling vertex shader:\n   %s\n", vertexFilePath);
	char const* vertexShaderPointer = vertexShaderCode.c_str();
	const GLint vertexSourceLength = vertexShaderCode.size();
	glShaderSource(vertexShaderID, 1, & vertexShaderPointer, &vertexSourceLength);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		printf("shader putt\n");
	}
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> vertexShaderErrorMsg(infoLogLength);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
		printf("%s\n", &vertexShaderErrorMsg[0]);
	}


	printf("compiling fragment shader:\n  %s\n", fragmentFilePath);
	char const* fragmentShaderPointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> fragmentShaderErrorMsg(infoLogLength);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMsg[0]);
		printf("%s\n", &fragmentShaderErrorMsg[0]);
	}


	printf("linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> progErrorMsg(infoLogLength);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &progErrorMsg[0]);
		printf("%s\n", &progErrorMsg[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
