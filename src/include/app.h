#ifndef _APP_H
#define _APP_H

#include <iostream>

namespace xnti {
    class app
    {
    private:
        bool replace_string(std::string& str, const std::string& from, const std::string& to);
        bool replace_url_with_dotjson(std::string& str);
    public:
        void run(const char* url);
        std::string get_video_audio_url(const char* video_url, const char* res);
        void download_video(const char* video_url);
    };
    
    app* pApp();
}


#endif