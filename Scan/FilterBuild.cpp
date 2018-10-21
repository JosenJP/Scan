#include <string>
#include <algorithm>
#include "FilterBuild.hpp"


bool FilterBuild::IsGoodFile(const char* a_pFileName, FileType& a_FileType /* output */)
{
    bool l_IsGoodFile = true;

    if (CheckExtension(a_pFileName, EXTENSION_CPP))
    {
        a_FileType = FileType::CPP;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_H))
    {
        a_FileType = FileType::H;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_HPP))
    {
        a_FileType = FileType::HPP;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_HR))
    {
        a_FileType = FileType::HR;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_PROJ))
    {
        a_FileType = FileType::PROJ;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_C))
    {
        a_FileType = FileType::C;
    }
    else if (CheckExtension(a_pFileName, EXTENSION_CR))
    {
        a_FileType = FileType::CR;
    }
    else
    {
        a_FileType = FileType::UNKNOW;
    }

    l_IsGoodFile = (FileType::UNKNOW != a_FileType);

    return l_IsGoodFile;
}

bool FilterBuild::CheckExtension(const char* a_pFileName, const char* a_pExtension)
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

