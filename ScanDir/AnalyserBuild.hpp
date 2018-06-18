#ifndef ANALYSER_BUILD_HPP
#define ANALYSER_BUILD_HPP

#include <memory>
#include "AnalyserBase.hpp"


class ProcesserHeader;
class ProcesserCPP;
class ProcesserPROJ;
class Logger;

class AnalyserBuild : public AnalyserBase
{
public:
    AnalyserBuild();
    ~AnalyserBuild();

    void Process(const char* a_pFile, FileType a_FileType, const char* a_pFileName) override;
    void SetLogPath(const char* a_pLogPath) override;

protected:
    void GetProcessers(void) override;

private:
    void Init(void);

    //std::unique_ptr<ProcesserHeader> m_pProcHeader;
    //std::unique_ptr<ProcesserCPP> m_pProcCPP;
    //std::unique_ptr<ProcesserPROJ> m_pProcPROJ;

    ProcesserHeader* m_pProcHeader;
    ProcesserCPP* m_pProcCPP;
    ProcesserPROJ* m_pProcPROJ;

    Logger* m_pLoggerHeader;
    Logger* m_pLoggerCPP;
    Logger* m_pLoggerPROJ;
};

#endif // !ANALYSER_BUILD_HPP


