//
// Created by octopus on 10/27/16.
//

#ifndef OGL_PLAYGROUND_SHADERS_H_H
#define OGL_PLAYGROUND_SHADERS_H_H

namespace shaders {
  const GLchar * vertex_shader = "#version 330 core\n"
      "  \n"
      "layout (location = 0) in vec3 position;\n"
      "out vec3 vcolor;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    gl_Position =  vec4(position.x, position.y, position.z, 1.0);\n"
      "    vcolor =  gl_Position.xyz;\n"
      "}\n\0";

  const GLchar * fragment_shader = "#version 330 core\n"
      "\n"
      "out vec4 color;\n"
      "in vec3 vcolor;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    color = vec4(vcolor.x, vcolor.y, vcolor.z, 0.5f);\n"
      "}\n\0";

  const GLchar * fragment_shader_niceGray = "#version 330 core\n"
      "\n"
      "out vec4 color;\n"
      "\n"
      "void main()\n"
      "{\n"
        "    color = vec4(0.1f, 0.5f, 0.1f, 1.0f);\n"
      "}\n\0";

    const GLchar * vertex_for_texture = ""
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "\n"
            "out vec3 ourColor;\n"
            "out vec2 TexCoord;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos, 1.0);\n"
            "    ourColor = aColor;\n"
            "    TexCoord = aTexCoord;\n"
            "}\n\0";

    const GLchar * fragment_for_texture = "\n"
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "  \n"
            "in vec3 ourColor;\n"
            "in vec2 TexCoord;\n"
            "\n"
            "uniform sampler2D ourTexture;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    FragColor = texture(ourTexture, TexCoord);\n"
            "}\n\0";

}

#endif //OGL_PLAYGROUND_SHADERS_H_H
