#version 150

//These variables are constant for all vertices
uniform vec3 lightPos;

//input variables from host
in vec3 pos; //vertex position
in vec3 norm; //vertex normal
in vec3 color; //vertex color 

//variables to be passed to the fragment shader
out VertexAttrib
{
  vec3 normal;
  vec4 color;
} vertex;      
 
void main(void)
{
    gl_Position = vec4(pos.xyz, 1.0);
    vertex.normal = norm;
    vertex.color = vec4(norm.xyz, 1.0);
}