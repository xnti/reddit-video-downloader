#ifndef _JSON_H
#define _JSON_H

#include "../libs/json.hpp"
#include "cpr/cpr.h"

namespace xnti {
    class json {
        public:
        nlohmann::json get_json(const char* url);
        nlohmann::json get_video_information(nlohmann::json json_data);
    };
    json* pJson();
};

#endif