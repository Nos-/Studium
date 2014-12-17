#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H


#include "main.h"

class BasicObject {
public:
		BasicObject(GLuint typeOfPrimitive){
			this->typeOfPrimitive = typeOfPrimitive;
			switch (this->typeOfPrimitive){
			case GL_QUADS:		numVertsPerPrimitive = 4; break;
			case GL_TRIANGLES:	numVertsPerPrimitive = 3; break;
			case GL_LINES:		numVertsPerPrimitive = 2; break;
			case GL_POINTS:		numVertsPerPrimitive = 1; break;
			default:			numVertsPerPrimitive = 0; break;
			}
		};

		struct vertexAttributes{
			glm::vec3 pos;
			glm::vec3 normal;
			glm::vec4 color;
			glm::vec2 texCoord;
		};

		void allocateMemory(){
			glGenVertexArrays(1, &vaoID);
			glBindVertexArray(vaoID);

			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertexAttributes), &vertices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48, (const void*) 0);	// 48= sizeof(VertexAttributes); 0= Anfang des Arrays
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48, (const void*) 12);	// 12=      3 * sizeof(GL_FLOAT)
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 48, (const void*) 24);	// 24= 12 + 4 * sizeof(GL_FLOAT)
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 48, (const void*) 40);	// 40= 24 + 4 * sizeof(GL_FLOAT)

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

		};

		int getNumberOfVertices(){
				return vertices.size();
		};

		GLuint vboID;
		GLuint vaoID;
		GLuint typeOfPrimitive;
		GLuint numVertsPerPrimitive;
		std::vector<vertexAttributes> vertices;

};

#endif
