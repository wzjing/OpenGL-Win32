#ifndef OPENGLFOO_SHADER_H
#define OPENGLFOO_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
private:
    std::string vertexShaderSrc;
    std::string fragmentShaderSrc;
    std::string geometryShaderSrc;

    GLuint program;

    GLuint createProgram();

    GLuint compileShader(GLenum type, const char *pSource);

public:

    explicit Shader(std::string vertexShader = std::string(), std::string fragmentShader = std::string(),
                    std::string geometryShader = std::string());

    ~Shader();

    void setVertexShader(std::string vertexShader);

    void setFragmentShader(std::string fragmentShader);

    void setGeometryShader(std::string geometryShader);

    GLuint getProgram();

    void use();

    void unUse();

    void setUniform(const char *name, float v);

    void setUniform(const char *name, GLsizei len, float *arr);

    void setUniform(const char *name, GLsizei row, GLsizei column, float *arr);

    void setAttribute(const char *name, GLsizei size, GLsizei stride);

    void disableAttribute(const char *name);

};


#endif //OPENGLFOO_SHADER_H
