precision highp float;

uniform vec2 resolution;
uniform sampler2D texture;
varying vec2 texCoordVarying;

#define R_LUMINANCE 0.298912
#define G_LUMINANCE 0.586611
#define B_LUMINANCE 0.114478


void main()
{
 
    vec4 color = texture2D(texture, texCoordVarying);
 
    float v = color.x * R_LUMINANCE + color.y * G_LUMINANCE + color.z * B_LUMINANCE;
 
    // color.x = v * 0.9;
    // color.y = v * 0.7;
    // color.z = v * 0.4;
 
    gl_FragColor = vec4(vec3(v), 1.0);
}
