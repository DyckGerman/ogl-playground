//
// Created by octopus on 10/27/16.
//

#ifndef OGL_PLAYGROUND_SHADERS_H_H
#define OGL_PLAYGROUND_SHADERS_H_H

namespace shaders {
  const GLchar * vertex_shader = "#version 330 core\n"
      "  \n"
      "layout (location = 0) in vec3 position;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    gl_Position =  vec4(position.x, position.y, position.z, 1.0);\n"
      "}\n\0";

  const GLchar * fragment_shader = "#version 330 core\n"
      "\n"
      "out vec4 color;\n"
      "\n"
      "void main()\n"
      "{\n"
//      "    color = vec4(0.1f, 0.1f, 0.1f, 1.0f);\n"
      "}\n\0";
}

#endif //OGL_PLAYGROUND_SHADERS_H_H
