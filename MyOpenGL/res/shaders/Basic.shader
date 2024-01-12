#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float  a_TexIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	// gl_Position = u_MVP * position;
	// v_TexCoord = texCoord;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_MVP * vec4(a_Position, 1.0);
};


#shader fragment
#version 330 core

out vec4 o_Color;
// out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;


uniform vec4 u_Color; // 被用于调整颜色，如果没有用到，会被编译器优化掉，
uniform sampler2D u_Textures[2];


void main()
{	
	// vec4 texColor = texture(u_Texture, v_TexCoord);
	// color = texColor;
	int index = int(v_TexIndex);
	// o_Color = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0);
	o_Color = texture(u_Textures[index], v_TexCoord) * v_Color;
	// color = v_Color;
};