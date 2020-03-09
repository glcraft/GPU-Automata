#pragma once
#include <SFML/Window.hpp>
#include <memory>
#include <string>
#include <optional>
#include <GLCompute.h>

class MainGame
{
public:
    void init();
    void display();
private:
    std::unique_ptr<sf::Window> m_window;
    gl::sl::ComputeProgram m_cshader;
};