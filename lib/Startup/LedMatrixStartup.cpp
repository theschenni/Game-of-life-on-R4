#include <Arduino.h>
#include <Arduino_LED_Matrix.h>

void Foobar(ArduinoLEDMatrix m)
{
    m.clear();
}

ArduinoLEDMatrix initMatrix()
{
    ArduinoLEDMatrix matrix;
    matrix.begin();
    return matrix;
}
