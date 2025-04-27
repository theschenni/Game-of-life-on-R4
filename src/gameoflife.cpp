#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include <Artic.h>
#include <vector>
// #include <LedMatrixStartup.h>

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
    if (x + 1 == maxX)
    {
        *borderBottom = true;
    }
    if (y + 1 == maxY)
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

void ledMatrixStartup()
{
    uint8_t frame[maxY][maxX] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    /*
        steps[
            [
            {0,0,1}
            {0,11,1}
            {7 ,0,1}
            {7 ,11,1}
            ]
        ]
    */

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][0] = 1;
    frame[0][11] = 1;
    frame[7][0] = 1;
    frame[7][11] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][1] = 1;
    frame[0][10] = 1;
    frame[7][1] = 1;
    frame[7][10] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][0] = 0;
    frame[0][11] = 0;
    frame[7][0] = 0;
    frame[7][11] = 0;

    frame[0][2] = 1;
    frame[0][9] = 1;
    frame[7][2] = 1;
    frame[7][9] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][1] = 0;
    frame[0][10] = 0;
    frame[7][1] = 0;
    frame[7][10] = 0;

    frame[0][3] = 1;
    frame[0][8] = 1;
    frame[7][3] = 1;
    frame[7][8] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][2] = 0;
    frame[0][9] = 0;
    frame[7][2] = 0;
    frame[7][9] = 0;

    frame[0][4] = 1;
    frame[0][7] = 1;
    frame[7][4] = 1;
    frame[7][7] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][3] = 0;
    frame[0][8] = 0;
    frame[7][3] = 0;
    frame[7][8] = 0;

    frame[0][5] = 1;
    frame[0][6] = 1;
    frame[7][5] = 1;
    frame[7][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][4] = 0;
    frame[0][7] = 0;
    frame[7][4] = 0;
    frame[7][7] = 0;

    frame[1][5] = 1;
    frame[1][6] = 1;
    frame[6][5] = 1;
    frame[6][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][5] = 0;
    frame[0][6] = 0;
    frame[7][5] = 0;
    frame[7][6] = 0;

    frame[2][5] = 1;
    frame[2][6] = 1;
    frame[5][5] = 1;
    frame[5][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[1][5] = 0;
    frame[1][6] = 0;
    frame[6][5] = 0;
    frame[6][6] = 0;

    frame[3][5] = 1;
    frame[3][6] = 1;
    frame[4][5] = 1;
    frame[4][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[2][5] = 0;
    frame[2][6] = 0;
    frame[5][5] = 0;
    frame[5][6] = 0;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[3][5] = 0;
    frame[3][6] = 0;
    frame[4][5] = 0;
    frame[4][6] = 0;

    frame[2][5] = 1;
    frame[2][6] = 1;
    frame[3][4] = 1;
    frame[3][7] = 1;
    frame[4][4] = 1;
    frame[4][7] = 1;
    frame[5][5] = 1;
    frame[5][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[2][5] = 0;
    frame[2][6] = 0;
    frame[3][4] = 0;
    frame[3][7] = 0;
    frame[4][4] = 0;
    frame[4][7] = 0;
    frame[5][5] = 0;
    frame[5][6] = 0;

    frame[1][5] = 1;
    frame[1][6] = 1;
    frame[2][4] = 1;
    frame[2][7] = 1;
    frame[3][3] = 1;
    frame[3][8] = 1;
    frame[4][3] = 1;
    frame[4][8] = 1;
    frame[5][4] = 1;
    frame[5][7] = 1;
    frame[6][5] = 1;
    frame[6][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[1][5] = 0;
    frame[1][6] = 0;
    frame[2][4] = 0;
    frame[2][7] = 0;
    frame[3][3] = 0;
    frame[3][8] = 0;
    frame[4][3] = 0;
    frame[4][8] = 0;
    frame[5][4] = 0;
    frame[5][7] = 0;
    frame[6][5] = 0;
    frame[6][6] = 0;

    frame[0][5] = 1;
    frame[0][6] = 1;
    frame[1][4] = 1;
    frame[1][7] = 1;
    frame[2][3] = 1;
    frame[2][8] = 1;
    frame[3][2] = 1;
    frame[3][9] = 1;
    frame[4][2] = 1;
    frame[4][9] = 1;
    frame[5][3] = 1;
    frame[5][8] = 1;
    frame[6][4] = 1;
    frame[6][7] = 1;
    frame[7][5] = 1;
    frame[7][6] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][5] = 0;
    frame[0][6] = 0;
    frame[1][4] = 0;
    frame[1][7] = 0;
    frame[2][3] = 0;
    frame[2][8] = 0;
    frame[3][2] = 0;
    frame[3][9] = 0;
    frame[4][2] = 0;
    frame[4][9] = 0;
    frame[5][3] = 0;
    frame[5][8] = 0;
    frame[6][4] = 0;
    frame[6][7] = 0;
    frame[7][5] = 0;
    frame[7][6] = 0;

    frame[0][4] = 1;
    frame[0][7] = 1;
    frame[1][3] = 1;
    frame[1][8] = 1;
    frame[2][2] = 1;
    frame[2][9] = 1;
    frame[3][1] = 1;
    frame[3][10] = 1;
    frame[4][1] = 1;
    frame[4][10] = 1;
    frame[5][2] = 1;
    frame[5][9] = 1;
    frame[6][3] = 1;
    frame[6][8] = 1;
    frame[7][4] = 1;
    frame[7][7] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][4] = 0;
    frame[0][7] = 0;
    frame[1][3] = 0;
    frame[1][8] = 0;
    frame[2][2] = 0;
    frame[2][9] = 0;
    frame[3][1] = 0;
    frame[3][10] = 0;
    frame[4][1] = 0;
    frame[4][10] = 0;
    frame[5][2] = 0;
    frame[5][9] = 0;
    frame[6][3] = 0;
    frame[6][8] = 0;
    frame[7][4] = 0;
    frame[7][7] = 0;

    frame[0][3] = 1;
    frame[0][8] = 1;
    frame[1][2] = 1;
    frame[1][9] = 1;
    frame[2][1] = 1;
    frame[2][10] = 1;
    frame[3][0] = 1;
    frame[3][11] = 1;
    frame[4][0] = 1;
    frame[4][11] = 1;
    frame[5][1] = 1;
    frame[5][10] = 1;
    frame[6][2] = 1;
    frame[6][9] = 1;
    frame[7][3] = 1;
    frame[7][8] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][3] = 0;
    frame[0][8] = 0;
    frame[1][2] = 0;
    frame[1][9] = 0;
    frame[2][1] = 0;
    frame[2][10] = 0;
    frame[5][1] = 0;
    frame[5][10] = 0;
    frame[6][2] = 0;
    frame[6][9] = 0;
    frame[7][3] = 0;
    frame[7][8] = 0;

    frame[0][2] = 1;
    frame[0][9] = 1;
    frame[1][1] = 1;
    frame[1][10] = 1;
    frame[2][0] = 1;
    frame[2][11] = 1;
    frame[5][0] = 1;
    frame[5][11] = 1;
    frame[6][1] = 1;
    frame[6][10] = 1;
    frame[7][2] = 1;
    frame[7][9] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][2] = 0;
    frame[0][9] = 0;
    frame[1][1] = 0;
    frame[1][10] = 0;
    frame[6][1] = 0;
    frame[6][10] = 0;
    frame[7][2] = 0;
    frame[7][9] = 0;

    frame[0][1] = 1;
    frame[0][10] = 1;
    frame[1][0] = 1;
    frame[1][11] = 1;
    frame[6][0] = 1;
    frame[6][11] = 1;
    frame[7][1] = 1;
    frame[7][10] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[0][1] = 0;
    frame[0][10] = 0;
    frame[7][1] = 0;
    frame[7][10] = 0;

    frame[0][0] = 1;
    frame[0][11] = 1;
    frame[7][0] = 1;
    frame[7][11] = 1;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[3][0] = 0;
    frame[3][11] = 0;
    frame[4][0] = 0;
    frame[4][11] = 0;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[2][0] = 0;
    frame[2][11] = 0;
    frame[5][0] = 0;
    frame[5][11] = 0;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[1][0] = 0;
    frame[1][11] = 0;
    frame[6][0] = 0;
    frame[6][11] = 0;

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    /*
    frame[0][1] = 1;
    frame[0][10] = 1;
    frame[1][0] = 1;
    frame[1][11] = 1;
    frame[6][0] = 1;
    frame[6][11] = 1;
    frame[7][1] = 1;
    frame[7][10] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(200);

    frame[0][1] = 0;
    frame[0][10] = 0;
    frame[1][0] = 0;
    frame[1][11] = 0;
    frame[6][0] = 0;
    frame[6][11] = 0;
    frame[7][1] = 0;
    frame[7][10] = 0;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);
    */

    frame[0][0] = 0;
    frame[0][11] = 0;
    frame[7][0] = 0;
    frame[7][11] = 0;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);
}

void ledMatrixStartupArc()
{
    uint8_t frame[8][12] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[4][2] = 0;
    frame[4][9] = 0;
    frame[5][3] = 0;
    frame[5][8] = 0;
    frame[6][4] = 0;
    frame[6][7] = 0;
    frame[7][5] = 0;
    frame[7][6] = 0;

    frame[3][2] = 1;
    frame[3][3] = 1;
    frame[3][4] = 1;
    frame[3][5] = 1;
    frame[3][6] = 1;
    frame[3][7] = 1;
    frame[3][8] = 1;
    frame[3][9] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[4][3] = 0;
    frame[4][8] = 0;
    frame[5][4] = 0;
    frame[5][7] = 0;
    frame[6][5] = 0;
    frame[6][6] = 0;

    frame[2][3] = 1;
    frame[2][4] = 1;
    frame[2][5] = 1;
    frame[2][6] = 1;
    frame[2][7] = 1;
    frame[2][8] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[4][4] = 0;
    frame[4][7] = 0;
    frame[5][5] = 0;
    frame[5][6] = 0;

    frame[1][4] = 1;
    frame[1][5] = 1;
    frame[1][6] = 1;
    frame[1][7] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);

    frame[4][5] = 0;
    frame[4][6] = 0;

    frame[0][5] = 1;
    frame[0][6] = 1;
    matrix.renderBitmap(frame, maxY, maxX);
    delay(100);
}

void setup()
{
    Serial.begin(9600);
    matrix.begin();
    /*
    uint8_t frame[8][12] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    matrix.renderBitmap(frame, maxY, maxX);
    arctic_boot();
    ledMatrixStartup();
    */
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