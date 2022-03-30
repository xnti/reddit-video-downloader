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

    nlohmann::json video_json = pJ->get_json(url_str.c_str());
    nlohmann::json video_info;

    if (video_json[0]["isSuccess"])
        video_info = pJ->get_video_information(video_json);
    else
    {
        pA->run(url);
        return;
    }

    std::string video_url = video_info["video_url"].get<std::string>();
    std::string audio_url = video_info["audio_url"].get<std::string>();
    int video_resolution = video_info["resolution"].get<int>();

    std::string video_output = video_url.substr(18, 13) + "_video.mp4";
    std::string audio_output = audio_url.substr(18, 13) + "_audio.wav";
    std::string merge_output = video_url.substr(18, 13) + "_output.mp4";

    printf("\033[32m[ ... ] Starting to download video.\033[0m\n");

    pA->download(video_url, video_output);
    printf("\033[1;32m[ +++ ] Video downloaded successfully...\033[0m\n");

    printf("\033[32m[ ... ] Starting to download audio.\033[0m\n");

    pA->download(audio_url, audio_output);
    printf("\033[1;32m[ +++ ] Audio downloaded successfully...\033[0m\n");

    printf("\033[32m[ ... ] Merging them into one file.\033[0m\n");

    if (pA->merge_video_audio(video_output, audio_output, merge_output))
        printf("\033[1;32m[ +++ ] Successfully merged to one file!\033[0m\n");
    if (pA->clerance(video_output, audio_output, merge_output))
        printf("\033[1;32m[ +++ ] Cleared & exiting.\033[0m\n");
}

bool xnti::app::download(std::string video_url, std::string output_name)
{
    auto ofstream = std::ofstream(output_name.c_str());
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{video_url});
    auto response = session.Download(ofstream);
    return true;
}

bool xnti::app::merge_video_audio(std::string video_path, std::string audio_path, std::string output)
{
    std::string command = "ffmpeg -nostats -hide_banner -loglevel quiet -y -i " + video_path + " -i " + audio_path + " -c:v copy -c:a aac " + output;
    system(command.c_str());
    return true;
}

bool xnti::app::check_if_file_exists(std::string &filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

bool xnti::app::clerance(std::string video_path, std::string audio_path, std::string output_path)
{
    auto pA = xnti::pApp();
    if (pA->check_if_file_exists(output_path))
    {
        std::remove(video_path.c_str());
        std::remove(audio_path.c_str());
    }
    else
    {
        std::remove(audio_path.c_str());
        std::rename(video_path.c_str(), output_path.c_str());
    }

    return true;
}

bool xnti::app::replace_url_with_dotjson(std::string &str)
{
    int len = str.length();
    std::string last_char = str.substr(len - 1, len);
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