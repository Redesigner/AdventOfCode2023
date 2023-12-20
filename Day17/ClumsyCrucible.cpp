#include "ClumsyCrucible.h"

#include <fstream>
#include <string>
#include <queue>


using namespace std;

int64_t ClumsyCrucible::get()
{
    bool usingExample = false;

    fstream file = usingExample ? fstream("Day17/test.txt", ios::in) : fstream("Day17/input.txt", ios::in);
    if (!file.is_open())
    {
        return -1;
    }
    return 0;
}