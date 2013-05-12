#version 150

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;

uniform mat4 M; //modelview matrix
uniform mat4 P; //projection matrix
uniform mat3 M_n; //normal matrix

in VertexAttrib
{
  vec3 normal;
  vec4 color;
} vertex[];

out vec4 vertex_color;

void main()
{
	vec4 V1 = gl_PositionIn[0];
	vec4 V2 = gl_PositionIn[1];
	vec4 center = ( V1 + V2 ) / 2.0;
	gl_Position = P * M * center;
	vertex_color = vec4( 1.0, 0.0, 0.0, 1.0);//vertex[1].color;
	EmitVertex();
	gl_Position = P * M * (center + (vec4(vertex[1].normal, 1) * 100));
	vertex_color = vec4( 1.0, 0.0, 0.0, 1.0);//vertex[1].color;
	EmitVertex();
}