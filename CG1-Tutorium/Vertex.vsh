#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 v_normal;

void main(){
	gl_Position =  proj * view * model * vec4(pos, 1);
	v_normal = (model * vec4(normal, 1)).xyz;
}
