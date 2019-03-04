#include <utility>

#include <utility>

#include <utility>

#include <cstring>
#include "Shader.h"
#include "utils/gl-utils.h"

#define UNIFORM_FLOAT(count, location, size, arr) glUniform##count##fv(location, size, arr)

Shader::Shader(std::string vertexShader, std::string fragmentShader, std::string geometryShader) :
        vertexShaderSrc(std::move(vertexShader)),
        fragmentShaderSrc(std::move(fragmentShader)),
        geometryShaderSrc(std::move(geometryShader)),
        program(createProgram()) {
}

Shader::~Shader() {

}

void Shader::setVertexShader(std::string vertexShader) {
    vertexShaderSrc = std::move(vertexShader);
}

void Shader::setFragmentShader(std::string fragmentShader) {
    fragmentShaderSrc = std::move(fragmentShader);
}

void Shader::setGeometryShader(std::string geometryShader) {
    geometryShaderSrc = std::move(geometryShader);
}

GLuint Shader::compileShader(GLenum type, const char *pSource) {
    GLuint shader = glCreateShader(type);
    if (shader) {
        glShaderSource(shader, 1, &pSource, nullptr);
        checkGlError("shader source");
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buffer = new char[infoLen];
                glGetShaderInfoLog(shader, infoLen, nullptr, buffer);
                const char *name;
                switch (type) {
                    case GL_VERTEX_SHADER:
                        name = "vertex";
                        break;
                    case GL_FRAGMENT_SHADER:
                        name = "fragment";
                        break;
                    case GL_GEOMETRY_SHADER:
                        name = "geometry";
                        break;
                    default:
                        name = "unknown";
                        break;
                }
                LOG("Could not compile %s shader: \n%s\n", name, buffer);
                delete[] buffer;
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint Shader::createProgram() {

    GLuint vertexShader = 0;
    if (!vertexShaderSrc.empty()) {
        vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc.c_str());
    }

    GLuint fragmentShader = 0;
    if (!fragmentShaderSrc.empty()) {
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc.c_str());
    }

    GLuint geometryShader = 0;
    if (!geometryShaderSrc.empty()) {
        geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryShaderSrc.c_str());
    }

    program = glCreateProgram();
    if (program) {
        if (vertexShader) {
            glAttachShader(program, vertexShader);
            checkGlError("Attaching VertexShader");
        }
        if (fragmentShader) {
            glAttachShader(program, fragmentShader);
            checkGlError("glAttaching FragmentShader");
        }
        if (geometryShader) {
            glAttachShader(program, fragmentShader);
            checkGlError("glAttaching GeometryShader");
        }
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufferLen = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufferLen);
            if (bufferLen) {
                char *buffer = new char[bufferLen];
                glGetProgramInfoLog(program, bufferLen, nullptr, buffer);
                LOG("Could not link program:\n%s\n", buffer);
                delete[] buffer;
            }
            glDeleteProgram(program);
            program = 0;
            checkGlError("Link fail");
        }
    }
    LOGD("Compiled Shader: %u\n", program);
    return program;
}

void Shader::use() {
    if (program != 0) {
        glUseProgram(program);
        checkGlError("use program");
    } else {
        LOGD("unable to use shader %u\n", program);
    }
}

void Shader::unUse() {
    glDeleteProgram(program);
    LOGD("Deleting shader: %d\n", program);
    checkGlError("delete program");
}

GLuint Shader::getProgram() {
    return program;
}

void Shader::setUniform(const char *name, float v) {
    GLint location = glGetUniformLocation(program, name);
    glUniform1f(location, v);
    checkGlError("Set uniform float");
}

void Shader::setUniform(const char *name, GLsizei len, float *arr) {
    GLint location = glGetUniformLocation(program, name);
    switch (len) {
        case 1:
            glUniform1fv(location, 1, arr);
            break;
        case 2:
            glUniform2fv(location, 1, arr);
            break;
        case 3:
            glUniform3fv(location, 1, arr);
            break;
        case 4:
            glUniform4fv(location, 1, arr);
            break;
        default:
            break;
    }
    checkGlError("Set uniform float vector");
}

void Shader::setUniform(const char *name, GLsizei row, GLsizei column, float *arr) {
    GLint location = glGetUniformLocation(program, name);
    switch (row) {
        case 2:
            switch (column) {
                case 2:
                    glUniformMatrix2fv(location, 1, GL_FALSE, arr);
                    break;
                case 3:
                    glUniformMatrix2x3fv(location, 1, GL_FALSE, arr);
                    break;
                case 4:
                    glUniformMatrix2x4fv(location, 1, GL_FALSE, arr);
                    break;
                default:
                    break;
            }
            break;
        case 3:
            switch (column) {
                case 2:
                    glUniformMatrix3x2fv(location, 1, GL_FALSE, arr);
                    break;
                case 3:
                    glUniformMatrix3fv(location, 1, GL_FALSE, arr);
                    break;
                case 4:
                    glUniformMatrix3x4fv(location, 1, GL_FALSE, arr);
                    break;
                default:
                    break;
            }
            break;
        case 4:
            switch (column) {
                case 2:
                    glUniformMatrix4x2fv(location, 1, GL_FALSE, arr);
                    break;
                case 3:
                    glUniformMatrix4x3fv(location, 1, GL_FALSE, arr);
                    break;
                case 4:
                    glUniformMatrix4fv(location, 1, GL_FALSE, arr);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    checkGlError("Set uniform float matrix");
}

void Shader::setAttribute(const char *name, GLsizei size, GLsizei stride) {
    auto location = (GLuint) glGetAttribLocation(program, name);
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, nullptr);
    checkGlError("Enable vertex attributes");
}

void Shader::disableAttribute(const char *name) {
    GLint location = glGetAttribLocation(program, name);
    glDisableVertexAttribArray(static_cast<GLuint>(location));
    checkGlError("Disanable vertex attributes");
}
