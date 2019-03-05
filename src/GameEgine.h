//
// Created by wzjing on 2019/2/20.
//

#ifndef OPENGL_WIN32_APPLICATION_H
#define OPENGL_WIN32_APPLICATION_H

class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    bool init(bool fullScreen, int minWidth, int minHeight);
    void start();
    void pause();
    void destroy();
};


#endif //OPENGL_WIN32_APPLICATION_H
