#include <iostream>
#include <string>
#include <algorithm>
#include <dirent.h>

#include "Scaner.hpp"
#include "FileInfo.hpp"
#include "FilterBase.hpp"
#include "AnalyserBuild.hpp"

Scaner::Scaner()
{
    Init();
}

Scaner::~Scaner()
{
}

void Scaner::Init(void)
{
    m_pFilter   = NULL;
    m_pAnalyser = NULL;
}

void Scaner::SetFilter(FilterBase* a_pFilter)
{
    m_pFilter = a_pFilter;
}

void Scaner::SetAnalyser(AnalyserBase* a_pAnalyser)
{
    m_pAnalyser = a_pAnalyser;
}

void Scaner::Scan(const char* a_pDir)
{
    DIR* l_pdir     = NULL;
    dirent* l_pEnt  = NULL;
    FileType l_FileType = FileType::UNKNOW;

    if (strlen(a_pDir) > MAX_PATH)
    {
        return;
    }

    if ((l_pdir = opendir(a_pDir)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((l_pEnt = readdir(l_pdir)) != NULL)
        {
            //Scan the sub directory
            if ((DT_DIR == l_pEnt->d_type))
            {
                if (IsSubDir(l_pEnt->d_name))
                {
                    std::string l_SubDir = std::string(a_pDir).append("\\").append(l_pEnt->d_name);
                    Scan(l_SubDir.c_str());
                }
            }
            else
            {
                //print all the files, if there is no filter. otherwise filter the files with the filter
                if ((NULL == m_pFilter) ||
                    ((NULL != m_pFilter) && m_pFilter->IsGoodFile(l_pEnt->d_name, l_FileType)))
                {
                    std::cout << l_pEnt->d_name << std::endl;
                    if (NULL != m_pAnalyser)
                    {
                        std::string l_File = std::string(a_pDir).append("\\").append(l_pEnt->d_name);
                        m_pAnalyser->Process(l_File.c_str(), l_FileType, l_pEnt->d_name);
                    }
                }
            }
        }
        closedir(l_pdir);
    }
    else
    {
        std::cout << "Error open directory: " << l_pdir << std::endl;
    }
}

bool Scaner::IsSubDir(const char* a_pDir)
{
    bool l_IsGoodDir = true;

    //Exculde current directory - "."
    if (0 == memcmp(CURRENT_DIR, a_pDir, strlen(CURRENT_DIR)))
    {
        l_IsGoodDir = false;
    }

    //Exclude parent directory - ".."
    if (0 == memcmp(PARENT_DIR, a_pDir, strlen(PARENT_DIR)))
    {
        l_IsGoodDir = false;
    }

    return l_IsGoodDir;
}
