#ifndef PARAM_HPP
#define PARAM_HPP

#include <map>
#include <string>

static const char* s_pKeyLogFilePath    = "-L"; //Log file Path
static const char* s_pKeyDirOrFile      = "-T"; //Target

class Param
{
public:
    Param();
    ~Param();

    bool LoadParam(int a_Argc, char** a_pArgv);
    std::string GetValue(const char* a_Arg);
private:

    std::map<std::string, std::string> m_Values;
};

#endif
