#include <iostream>
#include "include/app.h"
#include "include/json.h"

int main(int argc, char *argv[])
{

    // ./reddit-video-downloader video_url
    char *video_url = argv[1];
    // std::cout << video_url << "\n";
    // auto pJson = xnti::pJson();

    // nlohmann::json j = xnti::pJson()->get_json(video_url);
    // const char* fallback_url = xnti::pJson()->get_fallback_url(j);
    xnti::pApp()->run(video_url);
    return 0;
}