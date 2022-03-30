#include "include/app.h"
#include "include/json.h"

static xnti::app g_app;

xnti::app *xnti::pApp()
{
    return &g_app;
}

void xnti::app::run(const char *url)
{
    auto pJ = xnti::pJson();
    auto pA = xnti::pApp();

    std::string url_str = url;
    pA->replace_url_with_dotjson(url_str);
    std::cout << url_str << "\n";

    nlohmann::json video_json = pJ->get_json(url_str.c_str());
    nlohmann::json video_info = pJ->get_video_information(video_json);

    std::cout << video_info.dump() << "\n";
}

void xnti::app::download_video(const char* video_url) {
    
}

bool xnti::app::replace_url_with_dotjson(std::string &str)
{
    int len = str.length();
    std::string last_char = str.substr(len-1, len);
    std::string test = str.substr(len - 5, len);
    std::cout << test << "\n";
    if (str.substr(len - 5, len) != ".json")
    {
        if(last_char == "/")
            str.erase(len - 1, len);
        str = str + ".json";
    }
    return true;
}

std::string xnti::app::get_video_audio_url(const char *video_url, const char *res)
{
    std::string str = video_url;
    std::string res_str = res;
    std::string from_str = "DASH_" + res_str + ".mp4";
    xnti::pApp()->replace_string(str, from_str, "DASH_audio.mp4");
    // std::cout << str << "\n";
    return str;
}

bool xnti::app::replace_string(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}