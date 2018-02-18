precision highp float;

uniform vec2 resolution;
uniform sampler2D texture;
varying vec2 texCoordVarying;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.
    
    // float windowWidth = 1024.0;
    // float windowHeight = 768.0;
    
	// float r = gl_FragCoord.x / resolution.x;
	// float g = gl_FragCoord.y / resolution.y;
	// float b = 1.0;
	// float a = 1.0;
    vec4 tex = texture2D(texture, texCoordVarying);
	gl_FragColor = tex;
}
