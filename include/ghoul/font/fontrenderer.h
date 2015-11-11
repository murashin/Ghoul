/*****************************************************************************************
 *                                                                                       *
 * GHOUL                                                                                 *
 * General Helpful Open Utility Library                                                  *
 *                                                                                       *
 * Copyright (c) 2012-2015                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __FONTRENDERER_H__
#define __FONTRENDERER_H__

#include <ghoul/glm.h>
#include <ghoul/font/font.h>

namespace ghoul {

namespace opengl {
    class ProgramObject;
}

namespace fontrendering {
    
class FontRenderer {
public:
    FontRenderer(opengl::ProgramObject* program, glm::vec2 windowSize);
    ~FontRenderer();
    static bool initialize();
    static bool deinitialize();
    static FontRenderer& defaultRenderer();
    
    void render(Font& font, glm::vec2 pos, const glm::vec4& color, const glm::vec4& outlineColor, const char* format, ...) const;
    void render(Font& font, const glm::vec2& pos, const char* format, ...) const;
    
    void setWindowSize(glm::vec2 windowSize);
    
private:
    FontRenderer();
    
    static FontRenderer* _defaultRenderer;
    
    glm::vec2 _windowSize;
    
    opengl::ProgramObject* _program;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ibo;
};
    
} // namespace fontrendering
} // namespace ghoul

#endif // __FONTRENDERER_H__

