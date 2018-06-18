#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

class Logger
{
public:
    explicit Logger(const char* a_pFile) ;
    ~Logger();

    void Log(const char* a_pParent, const char* a_pChild);
    void Log(const char* a_pStr);

private:
    std::ofstream m_Output;
};

#endif

