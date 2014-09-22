#include "graphicline.h"

GraphicLine::GraphicLine(): GraphicObject()
{
    prevMin = 0;
    prevMax = 0;

    setMaxNegativeVal(0);
    setMaxPositiveVal(100);
}

