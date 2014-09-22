uniform sampler2D colorTexture;
varying highp vec2 textureCoordinate;
void main(void)
{
    gl_FragColor = texture2D(colorTexture, textureCoordinate);//vec4(0.9,0.1,0.1,0.5);
}
