#include <MainGame.h>
#include <MyException.h>
#ifdef _WIN32
#   include <Windows.h>
#else
#   include <iostream>
#endif
int main()
{
    try
    {
        MainGame m_main;
        m_main.init();
        m_main.display();
    }
    catch(const MyException& exc)
    {
#ifdef _WIN32
        MessageBoxA(nullptr, exc.what().c_str(), exc.type().c_str(), MB_OK|MB_ICONEXCLAMATION);
#else
        std::cerr << exc.what();
#endif
    }
    return 0;
}