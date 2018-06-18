#ifndef PROCESSER_BASE_HPP
#define PROCESSER_BASE_HPP

class Logger;

class ProcesserBase
{
public:
    ProcesserBase():m_pLogger(NULL), m_pLogFileName(NULL) {}
    virtual ~ProcesserBase() {}

    virtual void Process(const char* a_pFile, const char* a_pFileName) = 0;
    void SetLogger(Logger* a_pLogger) { m_pLogger = a_pLogger; }

protected:
    Logger* m_pLogger;
    char* m_pLogFileName;
};

#endif // !PROCESSER_BASE_HPP

