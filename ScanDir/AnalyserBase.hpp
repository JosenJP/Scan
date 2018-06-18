#ifndef ANALYSER_BASE_HPP
#define ANALYSER_BASE_HPP

#include <string>
#include "FileInfo.hpp"


class AnalyserBase
{
public:
    AnalyserBase() { m_LogPath = ""; }
    virtual ~AnalyserBase() {}

    virtual void Process(const char* a_pFile, FileType a_FileType, const char* a_pFileName) = 0;
    virtual void SetLogPath(const char* a_pLogPath) = 0;

protected:
    virtual void GetProcessers(void) = 0;

    std::string m_LogPath;
};

#endif // !ANALYZER_BASE_HPP



