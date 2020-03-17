#include "exerciser.h"

void exercise(connection *C)
{
    query1(C, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 0, 35, 40, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 0, 35, 40, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 1, 0, 10);

    query2(C, "LightBlue");
    query2(C, "DarkBlue");

    query3(C, "BostonCollege");
    query3(C, "Duke");

    query4(C, "NC", "LightBlue");
    query4(C, "NC", "DarkBlue");

    query5(C, 5);
    query5(C, 10);
}
