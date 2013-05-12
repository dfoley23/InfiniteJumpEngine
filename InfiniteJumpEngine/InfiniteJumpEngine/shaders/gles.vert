#version 150

//These variables are constant for all vertices
uniform mat4 M; //modelview matrix
uniform mat4 P; //projection matrix
uniform mat3 M_n; //normal matrix
uniform vec3 lightPos;

//input variables from host
in vec3 pos; //vertex position
in vec3 norm; //vertex normal
in vec3 color; //vertex color 

//variables to be passed to the fragment shader
out vec4 frag_color;

void main() {
	vec4 posT = M * vec4(pos,1.0);
    	
    vec4 newColor = vec4(color, 1.0);
    frag_color = clamp(newColor, 0.0, 1.0);
	
    gl_Position = P * posT;
}