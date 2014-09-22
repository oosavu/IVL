attribute highp vec2 coord;
attribute highp vec2 texCoord;
varying vec2 textureCoordinate;
void main(void)
{
    gl_Position =  vec4(coord,0.0, 1.0);
    textureCoordinate = texCoord;
}
