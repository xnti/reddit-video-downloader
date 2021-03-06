/*
 *      author  : xnti (https://github.com/xnti)
 *      license : MIT
 */

#include <iostream>
#include "include/app.h"
#include "include/json.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::system("clear");
        printf("\033[1;31m\n[ ! ] Missing argument, please provide a http(s) url. \n\033[0m\n");
        printf("\033[1;31mUsage: $ %s <url> \n\033[0m\n", argv[0]);
        return 1;
    }

    const char *video_url = argv[1];
    std::string video_url_str = video_url;

    if (video_url_str.substr(0, 4) != "http")
    {
        std::system("clear");
        printf("\033[1;31m\n[ ! ] Please provide a valid http(s) url. \n\033[0m\n");
        printf("\033[1;31mUsage: $ %s <url> \n\033[0m\n", argv[0]);
        return 1;
    }

    xnti::pApp()->run(video_url);
    return 0;
}