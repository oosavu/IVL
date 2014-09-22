#include "graphicloop.h"

GraphicLoop::GraphicLoop(): GraphicObject()
{
    prevXpix = 0;
    prevYpix = 0;
    setMaxNegativeValX(-10);
    setMaxPositiveValX(100);
    setMaxNegativeValY(-10);
    setMaxPositiveValY(100);
}
