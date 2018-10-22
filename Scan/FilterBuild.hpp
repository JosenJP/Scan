#ifndef FILTER_BUILD_HPP
#define FILTER_BUILD_HPP

#include "FilterBase.hpp"

class FilterBuild : public FilterBase
{
public:
    FilterBuild() {}
    ~FilterBuild() {}

    bool IsGoodFile(const char* a_pFileName, FileType& a_FileType /* output */) override;

private:
    //bool CheckExtension(const char* a_pFileName, const char* a_pExtension);
};

#endif // !FILTER_BUILD_HPP


