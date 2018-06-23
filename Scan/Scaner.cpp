#include <iostream>
#include <string>
#include <algorithm>
#include <dirent.h>
#include <queue>
#include <memory>

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

void Scaner::Scan(const char* a_pTarget)
{
    if (IsDir(a_pTarget))
    {
        ScanDir(a_pTarget);
    }
    else
    {
        ScanFile(a_pTarget);
    }
}

void Scaner::ScanDir(const char* a_pDir)
{
    DIR* l_pdir     = NULL;
    dirent* l_pEnt  = NULL;
    FileType l_FileType = FileType::UNKNOW;
    std::unique_ptr<std::queue<std::string>> l_pDirQueue = std::unique_ptr<std::queue<std::string>>(new std::queue<std::string>());

    if (strlen(a_pDir) > MAX_PATH)
    {
        std::cout << "The directory is too long." << std::endl;
        return;
    }

    l_pDirQueue->push(a_pDir);

    while (l_pDirQueue->size() > 0)
    {
        std::string l_CurDir = l_pDirQueue->front();
        l_pDirQueue->pop();

        if ((l_pdir = opendir(l_CurDir.c_str())) != NULL)
        {
            /* print all the files and directories within directory */
            while ((l_pEnt = readdir(l_pdir)) != NULL)
            {
                //Scan the sub directory
                if ((DT_DIR == l_pEnt->d_type))
                {
                    if (IsSubDir(l_pEnt->d_name))
                    {
                        std::string l_SubDir = std::string(l_CurDir).append("\\").append(l_pEnt->d_name);
                        l_pDirQueue->push(l_SubDir);
                    }
                }
                else
                {
                    std::string l_File = std::string(l_CurDir).append("\\").append(l_pEnt->d_name);
                    //print all the files, if there is no filter. otherwise filter the files with the filter
                    if ((NULL == m_pFilter) ||
                        ((NULL != m_pFilter) && m_pFilter->IsGoodFile(l_pEnt->d_name, l_FileType)))
                    {
                        //std::cout << l_pEnt->d_name << std::endl;
                        if (NULL != m_pAnalyser)
                        {
                            m_pAnalyser->Process(l_File.c_str(), l_FileType, l_pEnt->d_name);
                        }
                    }
                    else
                    {
                        std::cout << "Unknow File Type: " << l_File << std::endl;
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
}

void Scaner::ScanFile(const char* a_pFile)
{
    FileType l_FileType = FileType::UNKNOW;
    std::string l_File(a_pFile);
    std::size_t l_StartPos = l_File.rfind("\\");

    if (std::string::npos == l_StartPos)
    {
        std::cout << "Please check the file that needs to process" << std::endl;
        return;
    }

    l_StartPos += 1;
    std::string l_FileName = l_File.substr(l_StartPos, l_File.size() - l_StartPos);

    if ((NULL == m_pFilter) ||
        ((NULL != m_pFilter) && m_pFilter->IsGoodFile(l_FileName.c_str(), l_FileType)))
    {
        if (NULL != m_pAnalyser)
        {
            m_pAnalyser->Process(l_File.c_str(), l_FileType, l_FileName.c_str());
        }
    }
}

bool Scaner::IsDir(const char* a_pTarget)
{
    struct stat l_Statbuf;
    stat(a_pTarget, &l_Statbuf);
    return S_ISDIR(l_Statbuf.st_mode);
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
