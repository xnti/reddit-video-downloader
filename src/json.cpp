
/**     author: xnti
 *      purpose: handling json objects & convert them.
 */
#include <iostream>
#include "include/json.h"
#include "include/app.h"

static xnti::json g_json;

xnti::json* xnti::pJson() {
    return &g_json;
}

nlohmann::json xnti::json::get_json(const char* url) {
    
    nlohmann::json j;

    cpr::Response r = cpr::Get(cpr::Url{url});
    std::cout << "Request status code: " << r.status_code << "\n";

    if(r.status_code == 200) {
        j = nlohmann::json::parse(r.text);
        j[0]["isSuccess"] = true;
    } else {
        std::cout << "Request failed." << "\n";
        j[0]["isSuccess"] = false;
    }

    return j;
}

nlohmann::json xnti::json::get_video_information(nlohmann::json json_data) {
    nlohmann::json j;
    j["video_url"] = json_data[0]["data"]["children"][0]["data"]["secure_media"]["reddit_video"]["fallback_url"];
    j["resolution"] = json_data[0]["data"]["children"][0]["data"]["secure_media"]["reddit_video"]["height"];
    
    std::string video_url = j["video_url"].get<std::string>();
    int video_resolution_int = j["resolution"].get<int>();
    std::string video_resolution_str = std::to_string(video_resolution_int);
    std::string audio_url = xnti::pApp()->get_video_audio_url(video_url.c_str(), video_resolution_str.c_str());

    j["audio_url"] = audio_url;
    return j;
}