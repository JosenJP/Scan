#ifndef PROCESSER_CR_HPP
#define PROCESSER_CR_HPP

#include "ProcesserBase.hpp"

class ProcesserCR : public ProcesserBase
{
public:
    ProcesserCR() { Init(); };
    ~ProcesserCR() {};

    void Process(const char* a_pFile, const char* a_pFileName) override;

private:
    void Init(void){};
};

#endif // !PROCESSER_CR_HPP

