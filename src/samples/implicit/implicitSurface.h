/*
 * Copyright (c) 2016 Jonathan Glines
 * Jonathan Glines <jonathan@glines.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef MC_SAMPLES_IMPLICIT_IMPLICIT_SURFACE_H_
#define MC_SAMPLES_IMPLICIT_IMPLICIT_SURFACE_H_

extern "C" {
#include "lua.h"
}

#include <mcxx/isosurfaceBuilder.h>
#include <mcxx/scalarField.h>

#include "../common/meshObject.h"

namespace mc { namespace samples {
  class ShaderProgram;
  namespace implicit {
    class ImplicitSurface : public MeshObject {
      public:
        enum class Language {
          LUA,
          JAVASCRIPT
        };

      private:
        IsosurfaceBuilder m_builder;
        Language m_language;
        std::shared_ptr<ScalarField> m_sf;

        void m_update();

        static const int BUFFER_SIZE = 2048;

        typedef struct FileAndBuffer {
          FILE *fp;
          char buff[BUFFER_SIZE];
        } FileAndBuffer;

        class LuaScalarField : public ScalarField {
          private:
            lua_State *m_lua;

            void m_initLua();
            static const char *m_luaReader(
                lua_State *L,
                FileAndBuffer *data,
                size_t *size);
            void m_readLuaFile(FILE *fp);
            void m_closeLua();

          public:
            LuaScalarField(FILE *fp);
            ~LuaScalarField();

            float operator()(float x, float y, float z) const;
        };

        const ScalarField &m_scalarField();

      public:
        ImplicitSurface(
            const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
            const glm::quat &orientation = glm::quat());

        Language language() { return m_language; }
        void setLanguage(Language language);

        void setCode(const char *file);
        void setCode(FILE *fp);
    };
  }
} }

#endif
