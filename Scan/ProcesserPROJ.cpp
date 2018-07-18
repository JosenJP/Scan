#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "ProcesserPROJ.hpp"
#include "FileInfo.hpp"
#include "SqliteLogger.hpp"

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
    std::size_t l_Pos   = std::string::npos;
    bool l_IsLib        = false;
    bool l_GetLib       = false;
    bool l_GetLibName   = false;

    l_InFile.open(a_pFile);

    if (!l_InFile)
    {
        std::cout << "Unable to open file: " << a_pFile << std::endl;
        return;
    }
    
    if (NULL != m_pLogger)
    {
        ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_PROJECT);
        m_pLogger->CleanByParent(a_pFile);

        ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_LIB_NAME);
        m_pLogger->CleanByParent(a_pFile);

        ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_LIB);
        m_pLogger->CleanByParent(a_pFile);
    }

    while (l_InFile.good())
    {
        getline(l_InFile, l_Line);

        if (GetCompileFile(a_pFile, l_Line))
        {
            continue;
        }

        l_Pos = l_Line.find(STR_LIB_FLAG);
        if (std::string::npos != l_Pos)
        {
            l_IsLib = true;
            continue;
        }

        if (l_IsLib && !l_GetLibName)
        {
            //Get the lib name for a static library.
            if (GetLibName(a_pFile, l_Line))
            {
                l_GetLibName = true;
                continue;
            }
        }

        if (!l_GetLib)
        {
            if (GetLib(a_pFile, l_Line))
            {
                l_GetLib = true;
                continue;
            }
        }
    }
    l_InFile.close();
}

bool ProcesserPROJ::GetCompileFile(const char* a_pFile, std::string a_Line)
{
    bool l_IsGot = false;
    std::size_t l_Pos = std::string::npos;

    l_Pos = a_Line.find(STR_COMPILE_ITEM_CPP);
    if (std::string::npos != l_Pos)
    {
        std::size_t l_StartPos = l_Pos + strlen(STR_COMPILE_ITEM_CPP);
        std::size_t l_EndPos = std::string::npos;
        std::string l_CppFile = "";

        //<ClCompile Include="Source.cpp" />
        l_EndPos = a_Line.find(STR_QUOTE, l_StartPos + 1, strlen(STR_QUOTE));

        if ((std::string::npos != l_StartPos) && (l_EndPos > l_StartPos))
        {
            l_CppFile = a_Line.substr(l_StartPos + 1, (l_EndPos- (l_StartPos + 1)));

            //std::cout << "Project " << a_pFileName << " contains " << l_CppFile << std::endl;

            if (NULL != m_pLogger)
            {
                ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_PROJECT);
                m_pLogger->Log(a_pFile, l_CppFile.c_str()); // CPP | Proj
            }
        }
        l_IsGot = true;;
    }

    return l_IsGot;
}

bool ProcesserPROJ::GetLibName(const char* a_pFile, std::string a_Line)
{
    bool l_IsGot = false;
    std::size_t l_Pos = std::string::npos;

    //Get the lib name for a static library.
    l_Pos = a_Line.find(STR_OUTPUT_FILE_START);
    if (std::string::npos != l_Pos)
    {
        std::size_t l_StartPos = l_Pos + strlen(STR_OUTPUT_FILE_START);
        std::size_t l_EndPos = std::string::npos;
        std::string l_LibName = "";

        //<OutputFile>$(OutDir)Proj.Lib</OutputFile>
        l_EndPos = a_Line.find(STR_OUTPUT_FILE_END, l_StartPos + 1, strlen(STR_OUTPUT_FILE_END));
        l_StartPos = a_Line.find(STR_RIGHT_ROUND_BRACKET, l_StartPos + 1, strlen(STR_RIGHT_ROUND_BRACKET));
        if ((std::string::npos != l_StartPos) && (l_EndPos > l_StartPos))
        {
            l_LibName = a_Line.substr(l_StartPos + 1, l_EndPos - (l_StartPos + 1));

            if (NULL != m_pLogger)
            {
                ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_LIB_NAME);
                m_pLogger->Log(l_LibName.c_str(), a_pFile); // Proj | Lib
            }
        }
        l_IsGot = true;
    }

    return l_IsGot;
}

bool ProcesserPROJ::GetLib(const char* a_pFile, std::string a_Line)
{
    bool l_IsGot = false;
    std::size_t l_Pos = std::string::npos;

    l_Pos = a_Line.find(STR_ADD_DEPENDENCY_START);
    if (std::string::npos != l_Pos)
    {
        std::size_t l_StartPos = l_Pos + strlen(STR_ADD_DEPENDENCY_START);
        std::size_t l_EndPos = std::string::npos;
        std::string l_LibList = "";

        //<AdditionalDependencies>bio.lib;%(AdditionalDependencies)</AdditionalDependencies>
        l_EndPos = a_Line.find(STR_ADD_DEPENDENCY_END, l_StartPos + 1, strlen(STR_ADD_DEPENDENCY_END));

        if ((std::string::npos != l_StartPos) && (l_EndPos > l_StartPos))
        {
            l_LibList = a_Line.substr(l_StartPos, l_EndPos - l_StartPos);

            std::stringstream l_StrLibList(l_LibList);
            std::string l_Lib = "";

            while (std::getline(l_StrLibList, l_Lib, ';'))
            {
                if (std::string::npos != l_Lib.find(EXTENSION_LIB))
                {
                    if (NULL != m_pLogger)
                    {
                        ((SQLiteLogger*)m_pLogger)->UpdateTableName(TBL_LIB);
                        m_pLogger->Log(a_pFile, l_Lib.c_str()); // Lib | Proj
                    }
                }
            }
        }

        l_IsGot = true;
    }

    return l_IsGot;
}

