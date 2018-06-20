#include <iostream>
#include "Scaner.hpp"
#include "FilterBuild.hpp"
#include "AnalyserBuild.hpp"

int main()
{
    char l_DirInput[_MAX_PATH];
    memset(l_DirInput, 0, sizeof(l_DirInput));

    Scaner l_Scaner;
    FilterBuild l_Filter;
    AnalyserBuild l_Analyser;
    l_Analyser.SetLogPath("H:\\Coding\\C++\\ScanDir\\ScanDir\\3rdParty");

    l_Scaner.SetFilter(&l_Filter);
    l_Scaner.SetAnalyser(&l_Analyser);

    while (true)
    {
        std::cout << "Please input a directory: " << std::endl;
        std::cin >> l_DirInput;

        l_Scaner.Scan(l_DirInput);

        std::cout << std::endl;
    }

    return 0;
}

