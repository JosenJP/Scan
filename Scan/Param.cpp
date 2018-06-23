#include "Param.hpp"
#include <algorithm>

const int HEADER_LEN = 2;


Param::Param()
{
}

Param::~Param()
{
}

bool Param::LoadParam(int a_Argc, char** a_pArgv)
{
    if (a_Argc < 3)
    {
        return false;
    }

    for (int i = 1; i < a_Argc; i++)
    {
        std::string l_StrParam = std::string(a_pArgv[i]);

        std::string l_Header = l_StrParam.substr(0, HEADER_LEN);
        std::string l_Value = l_StrParam.substr(HEADER_LEN, l_StrParam.size());

        std::transform(l_Header.begin(), l_Header.end(), l_Header.begin(), ::toupper);

        if (l_Header.compare(s_pKeyLogFilePath) == 0) //Log file path
        {
            m_Values[s_pKeyLogFilePath] = l_Value;
        }
        else if (l_Header.compare(s_pKeyDirOrFile) == 0) //Directory of file to be processed
        {
            m_Values[s_pKeyDirOrFile] = l_Value;
        }
        else
        {
            return false;
        }
    }

    if (m_Values.size() < 2)
    {
        return false;
    }

    return true;
}

std::string Param::GetValue(const char* a_Arg)
{
    std::map<std::string, std::string>::iterator l_It = m_Values.find(a_Arg);
    if (m_Values.end() != l_It)
    {
        return l_It->second;
    }

    return "";
}

