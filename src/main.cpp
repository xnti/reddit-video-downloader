#include <iostream>
#include "include/app.h"
#include "include/json.h"

int main(int argc, char *argv[])
{
    char *video_url = argv[1];
    xnti::pApp()->run(video_url);
    return 0;
}