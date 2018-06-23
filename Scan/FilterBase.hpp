#ifndef FILTER_BASE_HPP
#define FILTER_BASE_HPP

#include "FileInfo.hpp"

class FilterBase
{
public:
    FilterBase() {}
    virtual ~FilterBase() {}

    virtual bool IsGoodFile(const char* a_pFileName, FileType& a_FileType /* output */) = 0;
};

#endif // !FILTER_BASE_HPP


