#include <MainGame.h>
#include <gl/glew.h>
#include <MyException.h>
void MainGame::init()
{
    m_window = std::make_unique<sf::Window>(sf::VideoMode(1280, 720, 24), "GLCompute Sample", 7, sf::ContextSettings(0,0,0,3,3,sf::ContextSettings::Core));
    m_window->setVerticalSyncEnabled(true);
    glewExperimental = true;
    if (int code=glewInit(); code!=GLEW_OK)
        throw MyException("glew did not init properly.", code, "GLEW");
    if (!GLEW_ARB_compute_shader)
        throw MyException("GL Compute shader not available.", {}, "GLEW");

    {
        auto v = gl::sl::ComputeProgram::GetMaxWorkgroupCount();
        std::ostringstream ostr;
        ostr << "GetMaxWorkgroupCount: " << v.x << ", " << v.y << ", " << v.z << '\n';
        v = gl::sl::ComputeProgram::GetMaxWorkgroupSize();
        ostr << "GetMaxWorkgroupSize: " << v.x << ", " << v.y << ", " << v.z << '\n';
        throw MyException(ostr.str(), {}, "test");
    }
    try
    {
        m_cshader << gl::sl::Shader<gl::sl::Compute>("res/shaders/compute.comp") << gl::sl::link;
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
void MainGame::display()
{
    bool pause = false;
    glClear(GL_COLOR_BUFFER_BIT);
    m_window->display();
    while(m_window->isOpen())
    {
        sf::Event ev;
        while (m_window->isOpen() && m_window->pollEvent(ev))
        {
            if ((ev.type==sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || ev.type == sf::Event::Closed)
                m_window->close();
            else if (ev.type==sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
                pause = !pause;
            else if (ev.type==sf::Event::Resized)
            {
                glViewport(0,0,m_window->getSize().x,m_window->getSize().y);
            }
        }
        if (m_window->isOpen() && !pause)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->display();
        }
    }
}