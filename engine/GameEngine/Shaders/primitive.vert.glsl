#version 150

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Pos;

out vec4 Color;
out vec4 position;

void main()
{
    position = vec4(Pos,1);
    
    position = View * World * position;
    
    Color = vec4(0,1,1,1); //R,G,B,_
    gl_Position = Projection * position;
}
