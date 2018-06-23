#include <string>
#include "Logger.hpp"

Logger::Logger(const char* a_pFile)
{
    m_Output.open(a_pFile, std::ofstream::out | std::ofstream::app);
}

Logger::~Logger()
{
    if (m_Output.is_open())
    {
        m_Output.close();
    }
}

void Logger::Log(const char* a_pParent, const char* a_pChild)
{
    std::string l_Str = std::string(a_pChild) + "," + std::string(a_pParent);
    Log(l_Str.c_str());
}

void Logger::Log(const char* a_pStr)
{
    m_Output << a_pStr << std::endl;
}

