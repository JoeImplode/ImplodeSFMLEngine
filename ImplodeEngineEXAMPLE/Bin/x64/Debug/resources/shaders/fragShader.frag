varying in vec4 vert_pos;

uniform sampler2D texture;


void main()
{
	//Ambient light
	vec4 ambient = vec4(0.4, 0.4, 0.4, 1);

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	
	gl_FragColor = gl_Color * pixel * (clamp(ambient, 0, 1));
	
}