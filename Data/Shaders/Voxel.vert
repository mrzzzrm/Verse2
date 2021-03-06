#version 330

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Orientation;
uniform mat4 Transform;

in vec3 Position;
in vec3 Normal;
in uint ColorIndex;

out vec3 f_PositionVS;
out vec3 f_Normal;
flat out uint f_ColorIndex;

void main()
{
    vec4 positionVS = View * Transform * vec4(Position, 1.0f);

    gl_Position = Projection * positionVS;

    f_PositionVS = positionVS.xyz;
	f_Normal = (View * Orientation * vec4(Normal, 0.0f)).xyz;
    f_ColorIndex = ColorIndex;
}