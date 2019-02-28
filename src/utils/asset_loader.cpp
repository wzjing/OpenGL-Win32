#include "asset_loader.h"
#include <fstream>
#include <cstring>
#include "log-utils.h"
#include "assets.h"

std::string load_text(const char *file_name) {
    std::string content;
    std::string _file_name(ASSET_DIR);
    _file_name += file_name;
    std::ifstream file(_file_name);
    if (!file.is_open()) {
        LOGD("Unable to open file: %s\n", _file_name.c_str());
        return std::string("");
    }
    const size_t LEN = 1024;
    char buffer[LEN] = {0};
    while (!file.eof()) {
        file.read(buffer, LEN);
        content.append(buffer);
        memset(buffer, 0, LEN);
    }
    file.close();
    return content;
}