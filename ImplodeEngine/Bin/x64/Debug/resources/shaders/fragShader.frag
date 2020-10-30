varying in vec4 vert_pos;

uniform sampler2D texture;


void main()
{
	//Ambient light
	vec4 ambient = vec4(0.02, 0.02, 0.02, 1.0);
	
	//Convert light to view coords
	lightPos = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular)
	vec2 lightToFrag = lightPos - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance)
	float vecLength = clamp(length(lightToFrag) * 2, 0, 1);

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	
	gl_FragColor = gl_Color * pixel * (clamp(ambient, 0, 1));
	
}