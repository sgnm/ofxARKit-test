attribute vec4 position;
attribute vec2 texcoord;
// this is something we're creating for this shader
varying vec2 texCoordVarying;

uniform mat4 modelViewProjectionMatrix;

void main(){
	texCoordVarying = vec2(texcoord.x, texcoord.y);
	
	gl_Position = modelViewProjectionMatrix * position;
}
