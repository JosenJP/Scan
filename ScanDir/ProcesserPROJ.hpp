#ifndef PROCESSER_PROJ_HPP
#define PROCESSER_PROJ_HPP

#include "ProcesserBase.hpp"

class ProcesserPROJ : public ProcesserBase
{
public:
    ProcesserPROJ();
    ~ProcesserPROJ();

    void Process(const char* a_pFile, const char* a_pFileName) override;

private:
    void Init(void);

};

#endif // !PROCESSER_PROJ_HPP

