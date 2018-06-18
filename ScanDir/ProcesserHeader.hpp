#ifndef PROCESSER_HEADER_HPP
#define PROCESSER_HEADER_HPP

#include "ProcesserBase.hpp"

class ProcesserHeader : public ProcesserBase
{
public:
    ProcesserHeader();
    ~ProcesserHeader();

    void Process(const char* a_pFile, const char* a_pFileName) override;

private:
    void Init(void);

};

#endif // !PROCESSER_HEADER_HPP


