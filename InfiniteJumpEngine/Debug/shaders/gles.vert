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
    
    vec3 L = normalize(M * vec4(lightPos, 1.0)).xyz;
    L = normalize(L - posT.xyz); 
	
    vec3 N = normalize(M_n * norm);
	
	float LDotN = dot( N, L ); 
	vec3 diff = vec3( 0.0, 0.0, 0.0 );
	if ( LDotN > 0.0 ) {
        diff = color * LDotN;
	} 
	
    vec4 newColor = vec4(diff, 1.0);
    frag_color = clamp(newColor, 0.0, 1.0);
	
    gl_Position = P * posT;
}