#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include <vector>

ArduinoLEDMatrix matrix;

std::vector<int> UpdateToActiveX;
std::vector<int> UpdateToActiveY;
std::vector<int> UpdateToInactiveX;
std::vector<int> UpdateToInactiveY;

// defines the size of the LED matrix
const int maxX = 12;
const int maxY = 8;

void awakeCell(int x, int y)
{
    UpdateToActiveX.push_back(x);
    UpdateToActiveY.push_back(y);
}

void killCell(int x, int y)
{
    UpdateToInactiveX.push_back(x);
    UpdateToInactiveY.push_back(y);
}

bool isActive(int x, int y, uint8_t frame[maxY][maxX])
{
    return (frame[y][x]);
}

void borderCheck(int x, int y, bool *borderTop, bool *borderLeft, bool *borderRight, bool *borderBottom)
{
    if (x == 0)
    {
        *borderTop = true;
    }
    if (y == 0)
    {
        *borderLeft = true;
    }
    if (x == maxX)
    {
        *borderBottom = true;
    }
    if (y == maxY)
    {
        *borderRight = true;
    }
}

int neighborCheck(int x, int y, uint8_t frame[maxY][maxX])
{
    bool borderTop = false;
    bool borderLeft = false;
    bool borderBottom = false;
    bool borderRight = false;

    int activeNeighbors = 0;

    borderCheck(x, y, &borderTop, &borderLeft, &borderRight, &borderBottom);
    // printf("Coord:[%d, %d] %d %d %d %d\n", x, y, borderTop, borderLeft, borderRight, borderBottom);

    if (!borderTop)
    {
        if (frame[y - 1][x] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderTop && !borderLeft)
    {
        if (frame[y - 1][x - 1] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderLeft)
    {
        if (frame[y][x - 1] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderLeft && !borderBottom)
    {
        if (frame[y + 1][x - 1] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderBottom)
    {
        if (frame[y + 1][x] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderBottom && !borderRight)
    {
        if (frame[y + 1][x + 1] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderRight)
    {
        if (frame[y][x + 1] == 1)
        {
            activeNeighbors++;
        }
    }

    if (!borderRight && !borderTop)
    {
        if (frame[y - 1][x + 1] == 1)
        {
            activeNeighbors++;
        }
    }
    return (activeNeighbors);
}

void setup()
{
    Serial.begin(9600);
    matrix.begin();
}

void loop()
{
    uint8_t frame[maxY][maxX] = {
        // define your starting board
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    Serial.println("Startup finished");
    matrix.renderBitmap(frame, maxY, maxX);

    while (true)
    {
        delay(500);
        for (int x = 0; x < maxX; x++)
        {
            for (int y = 0; y < maxY; y++)
            {
                // checks active neighbors
                int activeNeighbors = neighborCheck(x, y, frame);
                bool cellState = isActive(x, y, frame);

                if (cellState)
                {
                    if (activeNeighbors == 2 || activeNeighbors == 3)
                    {
                        awakeCell(x, y);
                    }
                    else
                    {
                        killCell(x, y);
                    }
                }
                else
                {
                    if (activeNeighbors == 3)
                    {
                        awakeCell(x, y);
                    }
                }
            }
        }
        for (int i = 0; i < UpdateToActiveX.size(); i++)
        {
            frame[UpdateToActiveY[i]][UpdateToActiveX[i]] = 1;
        }
        for (int i = 0; i < UpdateToInactiveX.size(); i++)
        {
            frame[UpdateToInactiveY[i]][UpdateToInactiveX[i]] = 0;
        }
        UpdateToActiveX.clear();
        UpdateToActiveY.clear();
        UpdateToInactiveX.clear();
        UpdateToInactiveY.clear();
        matrix.renderBitmap(frame, maxY, maxX);
    }
}