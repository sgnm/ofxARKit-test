precision highp float;

uniform vec2 resolution;
uniform sampler2D texture;
varying vec2 texCoordVarying;

uniform float rand;

void main (void)
{
    vec4 tex = texture2D(texture, texCoordVarying);
    //x軸、横軸がランダムにoffset決まって、そこのピクセル取得しにいくみたいな
    vec4 col_r = texture2D(texture, texCoordVarying + vec2(-0.046 * rand, 0.0));
    vec4 col_l = texture2D(texture, texCoordVarying + vec2(0.046 * rand, 0.0));
    vec4 col_g = texture2D(texture, texCoordVarying + vec2(-0.01 * rand, 0.0));
    
    //今現在見てるピクセルに対して加算するようなイメージ
    //y座標に応じて、あ
    tex.b = tex.b + col_r.b * max(1.0, sin(texCoordVarying.y * 1.2) * 2.5) * rand;
    tex.r = tex.r + col_l.r * max(1.0, sin(texCoordVarying.y * 1.2) * 2.5) * rand;
    tex.g = tex.g + col_g.g * max(1.0, sin(texCoordVarying.y * 1.2) * 2.5) * rand;

    gl_FragColor.rgba = tex.rgba;
}
