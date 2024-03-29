attribute vec2 a_texCoord0;
varying out vec4 vert_pos;
varying out vec2 vTexCoord0;

uniform vec2 texCoord;
void main()
{
    // transform the vertex position
	vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
    vTexCoord0 = gl_TexCoord[0];

}