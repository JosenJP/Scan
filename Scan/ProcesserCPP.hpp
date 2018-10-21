#ifndef PROCESSER_CPP_HPP
#define PROCESSER_CPP_HPP

#include "ProcesserBase.hpp"

class ProcesserCPP : public ProcesserBase
{
public:
    ProcesserCPP();
    ~ProcesserCPP();

    void Process(const char* a_pFile, const char* a_pFileName) override;

private:
    void Init(void){};

};

#endif // !PROCESSER_CPP_HPP

