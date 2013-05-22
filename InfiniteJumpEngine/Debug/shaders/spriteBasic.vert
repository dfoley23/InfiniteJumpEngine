#version 150

//These variables are constant for all vertices
uniform mat4 M; //modelview matrix
uniform mat4 V;
uniform mat4 P; //projection matrix
uniform mat3 M_n; //normal matrix
uniform vec3 lightPos;

//input variables from host
in vec3 pos; //vertex position
in vec3 norm; //vertex normal
in vec3 color; //vertex color 
in vec2 texCoord; //texture coord

//variables to be passed to the fragment shader
out vec4 frag_color;
out vec2 tex_coord;

void main() {
	vec4 posT = M * vec4(pos,1.0);

	vec3 diff = color;
	
    vec4 newColor = vec4(diff, 1.0);
    frag_color = clamp(newColor, 0.0, 1.0);
	
	tex_coord = texCoord;
	
    gl_Position = posT;
}