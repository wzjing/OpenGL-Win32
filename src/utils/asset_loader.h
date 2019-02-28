//
// Created by wzjing on 2019/2/21.
//

#ifndef OPENGLFOO_FILE_LOADER_H
#define OPENGLFOO_FILE_LOADER_H

#include <string>
#include <GLTFSDK/Document.h>

std::string  load_text(const char *file_name);

Microsoft::glTF::Document load_module(const char * file_name);

#endif //OPENGLFOO_FILE_LOADER_H
