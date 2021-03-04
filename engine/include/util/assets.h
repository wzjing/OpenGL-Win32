//
// Created by wzjing on 2019/2/26.
//

#ifndef OPENGLFOO_ASSETS_H
#define OPENGLFOO_ASSETS_H

#ifdef DEBUG
#ifdef PROJECT_DIR
#define ASSET_DIR (std::string(PROJECT_DIR)+"/assets/").c_str()
#else
#define ASSET_DIR nullptr
#endif
#else
#define ASSET_DIR "./assets/"
#endif

#include <string>

struct Asset {
private:
    std::string full_path;
    std::string file_name;

public:
    explicit Asset(const char *path) {
        std::string relative_path = path;
        full_path = ASSET_DIR + relative_path;

        std::string delimiter = "/";
        size_t pos = 0;
        std::string token;
        while ((pos = relative_path.find(delimiter)) != std::string::npos) {
            relative_path.erase(0, pos + 1);
        }
        file_name = std::move(relative_path);
    }

    const char *getFullPath() {
        return full_path.c_str();
    }

    const char *getFileName() {
        return file_name.c_str();
    }


};

#endif //OPENGLFOO_ASSETS_H
