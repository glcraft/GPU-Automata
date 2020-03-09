#pragma once 
#include <string>
#include <string_view>
#include <optional>

struct MyException
{
    MyException(std::string_view msg, std::optional<int> code=std::optional<int>(), std::string_view codetype="") : m_msg(msg), m_code(code), m_codetype(codetype)
    {
        
    }
    const std::string& message() const
    {
        return m_msg;
    }
    const std::string& type() const
    {
        return m_codetype;
    }
    const std::optional<int>& code() const
    {
        return m_code;
    }
    std::string what() const
    {
        std::string m_what;
        m_what.reserve(
            message().size() +
            type().size() +
            (code() ? std::log10(*code()) + 1 : 0) +
            1
        );
        if (!type().empty())
            m_what += type();
        if (code())
            m_what += "(code "+std::to_string(*code())+")";
        m_what.push_back('\n');
        m_what += message();
        return m_what;
    }
private:
    std::string m_msg;
    std::string m_codetype;
    std::optional<int> m_code;
};