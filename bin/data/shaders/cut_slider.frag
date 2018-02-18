precision highp float;

uniform vec2 resolution;
uniform sampler2D texture;
varying vec2 texCoordVarying;

uniform float rand;

void main (void)
{    
    float sin_value = sin(texCoordVarying.y / 0.01 * rand + rand * rand); //fix 0.01
    vec4 col = texture2D(texture, texCoordVarying + vec2(floor(sin_value) * 0.02 * rand, 0));
    
	gl_FragColor.rgba = col.rgba;
}

//TODO: 微調整難しいので時間あったらやる、、
// void main (void)
// {    
//     float sin_value = sin(texCoordVarying.y / 0.01 * rand + rand * rand); //fix 0.01
//     vec4 col = texture2D(texture, texCoordVarying + vec2(floor(sin_value) * sin(texCoordVarying.y) * 0.1 * rand, 0));
    
// 	gl_FragColor.rgba = col.rgba;
// }
