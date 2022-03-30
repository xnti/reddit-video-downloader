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

    std::string video_url = video_info["video_url"].get<std::string>();
    std::string audio_url = video_info["audio_url"].get<std::string>();
    //std::cout << "video_url: " << video_url << "\n";
    //std::cout << "audio_url: " << audio_url << "\n";

    std::string video_output = video_url + "_video.mp4";
    video_output.erase(0,18);
    video_output.erase(13,30);

    std::string audio_output = audio_url + "_audio.mp4";
    audio_output.erase(0,18);
    audio_output.erase(13,30);

    pA->download_video(video_url, video_output);
    pA->download_audio(audio_url, audio_output);
    std::cout << video_info.dump() << "\n";
}

bool xnti::app::download_video(std::string video_url, std::string output_name)
{
    std::string video_output = video_url + "_video.mp4";
    video_output.erase(0,18);
    video_output.erase(13,30);
    //std::cout << "video_output 2: " << video_output << "\n";

    auto ofstream = std::ofstream(video_output.c_str());
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{video_url});
    auto response = session.Download(ofstream);
    return true;
}

bool xnti::app::download_audio(std::string audio_url, std::string output_name)
{
    std::string audio_output = audio_url + "_audio.mp4";
    audio_output.erase(0,18);
    audio_output.erase(13,30);
    //std::cout << "audio_output 2: " << audio_output << "\n";

    auto ofstream = std::ofstream(audio_output.c_str());
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{audio_url});
    auto response = session.Download(ofstream);
    return true;
}

bool xnti::app::replace_url_with_dotjson(std::string &str)
{
    int len = str.length();
    std::string last_char = str.substr(len - 1, len);
    std::string test = str.substr(len - 5, len);
    std::cout << test << "\n";
    if (str.substr(len - 5, len) != ".json")
    {
        if (last_char == "/")
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