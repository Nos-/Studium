#version 300 es

precision float mediump;
/*precision vec3 mediump;
precision vec4 mediump;
precision vec2 mediump;*/

out vec4 outColor;

uniform vec3 redLightDir;
uniform vec3 blueLightDir;

in vec3 v_normal;


void main(){
	vec3 ambientColor = vec3(0.1, 0.1, 0.1);
	float redDiffuseIntensity = 0.5 * max(dot(normalize(-redLightDir), v_normal), 0);
	float blueDiffuseIntensity = 0.5 * max(dot(normalize(-blueLightDir), v_normal), 0);
	vec3 mixedColor = ambientColor + redDiffuseIntensity * vec3(1, 0, 0) + blueDiffuseIntensity * vec3(0, 0, 1);
	outColor = vec4(mixedColor, 1);
}
