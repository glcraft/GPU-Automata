#include <Automata.h>
#include <MyException.h>

void Automata::init()
{
    if (!m_imgs[0].id())
    {
        for (auto& img : m_imgs)
        {
            gl::Sampler s;
            s.setFiltering(gl::Sampler::Nearest);
            s.setWrap(gl::Sampler::Wrap::ClampToEdge);
            img.instantiate();
            img.setFormat(GL_RGB);
            img.setSampler(s);
            img.setTarget(GL_TEXTURE_2D);
            img.setSize(m_size);
            img.init_null();
        }
    }
    if (!m_cshader.id())
    {
        try
        {
            m_cshader << gl::sl::Shader<gl::sl::Compute>("res/shaders/automata.comp") << gl::sl::link;
        }
        catch(const gl::sl::CompileException& e)
        {
            throw MyException(e.what(), {}, "Compute shader compilation");
        }
        catch(const gl::sl::Program::LinkException& e)
        {
            throw MyException(e.what(), {}, "Compute shader linking");
        }
    }
}
void Automata::update()
{
    setBarrier();
    m_imgs[!m_currentImage].bind(0);
    glBindImageTexture (0, m_imgs[!m_currentImage].id(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB8);
    m_imgs[m_currentImage].bind(1);
    glBindImageTexture (1, m_imgs[m_currentImage].id(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGB8);
    m_cshader.dispatch(m_workSize);
    
    m_currentImage=!m_currentImage;
}
void Automata::draw()
{
    setBarrier();
}
void Automata::setBarrier()
{
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGB8);
    glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB8);
    m_imgs[0].unbind(0);
    m_imgs[1].unbind(1);
}