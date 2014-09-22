attribute highp float x_index;  //координата графика по x
attribute highp float y_cord;   //координата графика по у
uniform highp float pos;        //позиция буфера
uniform highp float buff_size;  //размер буфера
void main(void)
{
    float temp = buff_size/2.0;
    if (x_index > pos )
        gl_Position = vec4((x_index - pos)/temp - 1.0, y_cord,0.0,1.0);
    else
        gl_Position = vec4((x_index + buff_size - pos)/temp - 1.0, y_cord,0.0,1.0);
    //gl_PointSize = 2.0;

}
