//uniform sampler2D qt_Texture0;
//varying highp vec4 qt_TexCoord0;

//void main(void)
//{
//    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
//}
void main(void)
{
    gl_FragColor = vec4(1.0,1.0,1.0,1.0);
//    if(gl_PointCoord.x > 0.0 && gl_PointCoord.y > 0.0)
//     discard;
}
