//頂点シェーダ
attribute vec4 position;
attribute vec2 texcoord;

varying vec2 texCoordVarying;
uniform mat4 modelViewProjectionMatrix;

void main(void)
{
    texCoordVarying = vec2(texcoord.x, texcoord.y);
	
	gl_Position = modelViewProjectionMatrix * position;
}