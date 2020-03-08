#pragma once 
#include <string>
#include <string_view>
#include <optional>

struct MyException
{
    MyException(std::string_view msg, std::optional<int> code=std::optional<int>(), std::string_view codetype="")
    {
        m_what += msg;
        if (code)
        {
            m_what.push_back('\n');
            if (!codetype.empty())
            {
                m_what += codetype;
                m_what += " error ";
            }
            else
            {
                m_what += "Error ";
            }
            m_what += std::to_string(*code);
        }
    }
    const char* what() const
    {
        return m_what.c_str();
    }
    private:
    std::string m_what;
};