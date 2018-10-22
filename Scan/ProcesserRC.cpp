
#include <fstream>
#include <string>

#include "ProcesserRC.hpp"
#include "FileInfo.hpp"
#include "SqliteLogger.hpp"
#include "ExtensionHelper.hpp"

void ProcesserRC::Process(const char* a_pFile, const char* a_pFileName)
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

    if (NULL != m_pLogger)
    {
        SQLiteLogger::SwtichTable(m_pLogger, TBL_HR_RC);
        m_pLogger->CleanByParent(a_pFileName);

        SQLiteLogger::SwtichTable(m_pLogger, TBL_RC_RC);
        m_pLogger->CleanByParent(a_pFileName);
    }

    while (l_InFile.good())
    {
        getline(l_InFile, l_Line);

        l_Pos = l_Line.find(STR_INCLUDE);

        if (std::string::npos != l_Pos)
        {
            std::size_t l_StartPos = std::string::npos;
            std::size_t l_EndPos = std::string::npos;
            std::string l_Header = "";

            //#include <XXX.h> / <XXX.hpp>
            if (std::string::npos != (l_StartPos = l_Line.find(STR_LEFT_BRACKET)))
            {
                l_EndPos = l_Line.find(STR_RIGHT_BRACKET, l_StartPos + 1, strlen(STR_RIGHT_BRACKET));
            }
            //#include "XXX.h" / "XXX.hpp"
            else if (std::string::npos != (l_StartPos = l_Line.find(STR_QUOTE)))
            {
                l_EndPos = l_Line.find(STR_QUOTE, l_StartPos + 1, strlen(STR_QUOTE));
            }

            if ((std::string::npos != l_StartPos) && (l_EndPos > l_StartPos))
            {
                l_Header = l_Line.substr(l_StartPos + 1, l_EndPos - (l_StartPos + 1));

                //std::cout << "File " << a_pFileName << " contains " << l_Header << std::endl;

                if (NULL != m_pLogger)
                {
                    if (ExtensionHelper::CheckExtension(l_Header.c_str(), EXTENSION_RC))
                    {
                        SQLiteLogger::SwtichTable(m_pLogger, TBL_RC_RC);
                    }
                    else
                    {
                        SQLiteLogger::SwtichTable(m_pLogger, TBL_HR_RC);
                    }
                    m_pLogger->Log(a_pFileName, l_Header.c_str());
                }
            }
        }
    }
    l_InFile.close();
}


