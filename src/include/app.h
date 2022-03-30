#ifndef _APP_H
#define _APP_H

#include <iostream>
#include <fstream>

namespace xnti {
    class app
    {
    private:
        bool replace_string(std::string& str, const std::string& from, const std::string& to);
        bool replace_url_with_dotjson(std::string& str);
        bool check_if_file_exists(std::string& filename);
    public:
        void run(const char* url);
        std::string get_video_audio_url(const char* video_url, const char* res);
        bool download_video(std::string video_url, std::string output_name);
        bool download_audio(std::string audio_url, std::string output_name);
        bool merge_video_audio(std::string video_path, std::string audio_path, std::string output);
        bool clerance(std::string video_path, std::string audio_path, std::string output_path);
    };
    
    app* pApp();
}


#endif