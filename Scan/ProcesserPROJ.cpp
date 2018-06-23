#include <fstream>
#include <string>
#include <iostream>

#include "ProcesserPROJ.hpp"
#include "FileInfo.hpp"
#include "Logger.hpp"

ProcesserPROJ::ProcesserPROJ()
{
    Init();
}

ProcesserPROJ::~ProcesserPROJ()
{
}

void ProcesserPROJ::Init(void)
{
    m_pLogFileName = "Project.txt";
}

void ProcesserPROJ::Process(const char* a_pFile, const char* a_pFileName)
{
    std::ifstream l_InFile;
    std::string l_Line;
    std::size_t l_Pos = std::string::npos;

    l_InFile.open(a_pFile);

    if (!l_InFile)
    {
        std::cout << "Unable to open file: " << a_pFile << std::endl;
        return;
    }

    m_pLogger->CleanByParent(a_pFile);

    while (l_InFile.good())
    {
        getline(l_InFile, l_Line);

        l_Pos = l_Line.find(STR_COMPILE_ITEM_CPP);

        if (std::string::npos != l_Pos)
        {
            std::size_t l_StartPos  = l_Pos + strlen(STR_COMPILE_ITEM_CPP);
            std::size_t l_EndPos    = std::string::npos;
            std::string l_CppFile   = "";

            //<ClCompile Include="Source.cpp" />
            l_EndPos = l_Line.find(STR_COMPILE_ITEM_END, l_StartPos + 1, strlen(STR_COMPILE_ITEM_END));

            if ((std::string::npos != l_StartPos) && (l_EndPos > l_StartPos))
            {
                l_CppFile = l_Line.substr(l_StartPos + 1 , ((l_EndPos - 2) - (l_StartPos + 1))); //-2 is to remove the space at the end and " .

                //std::cout << "Project " << a_pFileName << " contains " << l_CppFile << std::endl;

                if (NULL != m_pLogger)
                {
                    m_pLogger->Log(a_pFile, l_CppFile.c_str());
                }
            }
        }
    }
    l_InFile.close();
}

