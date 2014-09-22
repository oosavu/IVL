uniform sampler2D colorTexture;
varying highp vec2 textureCoordinate;
//uniform highp float w_pix;
//uniform highp float h_pix;
void main(void)
{
    gl_FragColor = texture2D(colorTexture, textureCoordinate);
}
