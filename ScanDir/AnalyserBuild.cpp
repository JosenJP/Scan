#include <stdlib.h>
#include <string>

#include "AnalyserBuild.hpp"
#include "ProcesserHeader.hpp"
#include "ProcesserCPP.hpp"
#include "ProcesserPROJ.hpp"
#include "SqliteLogger.hpp"

AnalyserBuild::AnalyserBuild()
{
    Init();
}

AnalyserBuild::~AnalyserBuild()
{
    if (NULL != m_pProcHeader)
    {
        delete m_pProcHeader;
        m_pProcHeader = NULL;
    }

    if (NULL != m_pProcCPP)
    {
        delete m_pProcCPP;
        m_pProcCPP = NULL;
    }

    if (NULL != m_pProcPROJ)
    {
        delete m_pProcPROJ;
        m_pProcPROJ = NULL;
    }

    if (NULL != m_pLoggerHeader)
    {
        delete m_pLoggerHeader;
        m_pLoggerHeader = NULL;
    }

    if (NULL != m_pLoggerCPP)
    {
        delete m_pLoggerCPP;
        m_pLoggerCPP = NULL;
    }

    if (NULL != m_pLoggerPROJ)
    {
        delete m_pLoggerPROJ;
        m_pLoggerPROJ = NULL;
    }
}

void AnalyserBuild::Init(void)
{
    m_pProcHeader   = NULL;
    m_pProcCPP      = NULL;
    m_pProcPROJ     = NULL;

    m_pLoggerHeader = NULL;
    m_pLoggerCPP    = NULL;
    m_pLoggerPROJ   = NULL;
}

void AnalyserBuild::Process(const char* a_pFile, FileType a_FileType, const char* a_FileName)
{
    GetProcessers();

    ProcesserBase* l_pProcesser = NULL;

    switch (a_FileType)
    {
    case H:
    case HPP:
    {
        if (NULL != m_pProcHeader)
        {
            l_pProcesser = m_pProcHeader;
        }
        break;
    }
    case CPP:
    {
        if (NULL != m_pProcCPP)
        {
            l_pProcesser = m_pProcCPP;
        }
        break;
    }
    case PROJ:
    {
        if (NULL != m_pProcPROJ)
        {
            l_pProcesser = m_pProcPROJ;

        }
        break;
    }
    case UNKNOW:
    default:
    {
        break;
    }
    }

    if (NULL != l_pProcesser)
    {
        l_pProcesser->Process(a_pFile, a_FileName);
    }
}

void AnalyserBuild::SetLogPath(const char* a_pLogPath)
{
    m_LogPath = std::string(a_pLogPath);
}

void AnalyserBuild::GetProcessers(void)
{
    std::string l_Str;

    if (NULL == m_pProcHeader)
    {
        m_pProcHeader = new ProcesserHeader();
    }

    if (NULL == m_pProcCPP)
    {
        m_pProcCPP = new ProcesserCPP();
    }

    if (NULL == m_pProcPROJ)
    {
        m_pProcPROJ = new ProcesserPROJ();
    }

    //Set logger for processer
    if (m_LogPath.length() > 0)
    {
        std::string l_DBPath = m_LogPath + std::string("\\DependencyLib.db");
        if (NULL != m_pProcHeader)
        {
            //std::string l_DBPath = l_Str + std::string("Header");
            m_pLoggerHeader = new SQLiteLogger(l_DBPath.c_str(), "Header");
            m_pProcHeader->SetLogger(m_pLoggerHeader);
        }

        if (NULL != m_pProcCPP)
        {
            //std::string l_LogCpp = l_Str + std::string("Cpp.txt");
            m_pLoggerCPP = new SQLiteLogger(l_DBPath.c_str(), "CPP");
            m_pProcCPP->SetLogger(m_pLoggerCPP);
        }

        if (NULL != m_pProcPROJ)
        {
            //std::string l_LogProj = l_Str + std::string("Proj");
            m_pLoggerPROJ = new SQLiteLogger(l_DBPath.c_str(), "Project");
            m_pProcPROJ->SetLogger(m_pLoggerPROJ);
        }
    }
}
