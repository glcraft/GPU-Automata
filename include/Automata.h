#pragma once

#include <libglw/GLClass.h>
#include <GLCompute.h>
class Automata
{
public:
    void init();
    void update();
    void draw();

    void setSize(glm::ivec2 size)
    {
        m_size = size;
        m_workSize = glm::ivec3(m_size, 1) / glm::ivec3(m_localSize, 1);
    }
private:
    void setBarrier();
    gl::Texture m_imgs[2];
    gl::sl::ComputeProgram m_cshader;
    bool m_currentImage=0;

    glm::ivec2 m_size;
    glm::ivec3 m_workSize;
    static constexpr glm::ivec2 m_localSize=glm::ivec2(16);
};