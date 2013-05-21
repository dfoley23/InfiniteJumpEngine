#version 150

in vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D tex0;

out vec4 end_color;

void main() {
    vec4 tex_color = vec4(texture2D(tex0, texCoord));
	vec4 final_color = frag_color;
	if ( texCoord.x > 0 || texCoord.y > 0 ) {
		final_color = final_color * tex_color;
	}
    end_color = final_color;
}