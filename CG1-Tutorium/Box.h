#include "main.h"
#include "basic_object.h"


class Box : public BasicObject {
public:

	Box(float width = 1, float height = 1, float length = 1) : BasicObject(GL_QUADS) {
		
		float wHalf = width / 2.0f;
		float hHalf = height / 2.0f;
		float lHalf = length / 2.0f;
		vertexAttributes va;
		glm::vec3 corners[8];
		corners[0] = glm::vec3(-wHalf, -hHalf, lHalf);
		corners[1] = glm::vec3(wHalf, -hHalf, lHalf);
		corners[2] = glm::vec3(wHalf, hHalf, lHalf);
		corners[3] = glm::vec3(-wHalf, hHalf, lHalf);
		corners[4] = glm::vec3(wHalf, -hHalf, -lHalf);
		corners[5] = glm::vec3(wHalf, hHalf, -lHalf);
		corners[6] = glm::vec3(-wHalf, -hHalf, -lHalf);
		corners[7] = glm::vec3(-wHalf, hHalf, -lHalf);
		
		glm::vec3 normals[6];
		normals[0] = glm::vec3(0,0,1); // front
		normals[1] = glm::vec3(0,0,-1); // back
		normals[2] = glm::vec3(1,0,0); // right
		normals[3] = glm::vec3(-1,0,0); // left
		normals[4] = glm::vec3(0,1,0); // top 
		normals[5] = glm::vec3(0,-1,0); // bottom
		
		//////////// FRONT
		va.pos = corners[0];
		va.normal = normals[0];
		vertices.push_back(va);
		
		va.pos = corners[1];
		va.normal = normals[0];
		vertices.push_back(va);
		
		va.pos = corners[2];
		va.normal = normals[0];
		vertices.push_back(va);
		
		va.pos = corners[3];
		va.normal = normals[0];
		vertices.push_back(va);
		
		/////////// BACK
		va.pos = corners[4];
		va.normal = normals[1];
		vertices.push_back(va);
		
		va.pos = corners[5];
		va.normal = normals[1];
		vertices.push_back(va);
		
		va.pos = corners[7];
		va.normal = normals[1];
		vertices.push_back(va);
		
		va.pos = corners[6];
		va.normal = normals[1];
		vertices.push_back(va);
		
		/////////// RIGHT
		va.pos = corners[1];
		va.normal = normals[2];
		vertices.push_back(va);
		
		va.pos = corners[4];
		va.normal = normals[2];
		vertices.push_back(va);
		
		va.pos = corners[5];
		va.normal = normals[2];
		vertices.push_back(va);
		
		va.pos = corners[2];
		va.normal = normals[2];
		vertices.push_back(va);
		
		/////////// LEFT
		va.pos = corners[0];
		va.normal = normals[3];
		vertices.push_back(va);
		
		va.pos = corners[3];
		va.normal = normals[3];
		vertices.push_back(va);
		
		va.pos = corners[7];
		va.normal = normals[3];
		vertices.push_back(va);
		
		va.pos = corners[6];
		va.normal = normals[3];
		vertices.push_back(va);
		
		/////////// TOP
		va.pos = corners[3];
		va.normal = normals[4];
		vertices.push_back(va);
		
		va.pos = corners[2];
		va.normal = normals[4];
		vertices.push_back(va);
		
		va.pos = corners[5];
		va.normal = normals[4];
		vertices.push_back(va);
		
		va.pos = corners[7];
		va.normal = normals[4];
		vertices.push_back(va);
		
		/////////// BOTTOM
		va.pos = corners[0];
		va.normal = normals[5];
		vertices.push_back(va);
		
		va.pos = corners[6];
		va.normal = normals[5];
		vertices.push_back(va);
		
		va.pos = corners[4];
		va.normal = normals[5];
		vertices.push_back(va);
		
		va.pos = corners[1];
		va.normal = normals[5];
		vertices.push_back(va);
		
		allocateMemory();
	}
	

};
