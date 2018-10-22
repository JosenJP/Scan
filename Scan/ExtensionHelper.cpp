#include <iostream>
#include <algorithm>

#include "ExtensionHelper.hpp"

bool ExtensionHelper::CheckExtension(const char* a_pFileName, const char* a_pExtension)
{
    std::size_t l_FileLen = strlen(a_pFileName);
    std::size_t l_ExtensionLen = strlen(a_pExtension);

    std::string l_FileName(a_pFileName);
    std::transform(l_FileName.begin(), l_FileName.end(), l_FileName.begin(), ::tolower);
    std::size_t l_Found = l_FileName.find(a_pExtension, l_FileLen - l_ExtensionLen, l_ExtensionLen);

    if (std::string::npos != l_Found)
    {
        return true;
    }

    return false;
}