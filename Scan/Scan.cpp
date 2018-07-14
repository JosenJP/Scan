#include <iostream>
#include "Scaner.hpp"
#include "FilterBuild.hpp"
#include "AnalyserBuild.hpp"
#include "Param.hpp"
#include "Timer.hpp"

void PrintUsage(void)
{
    std::cout << "Usage: Scan.exe -L<LogFilePath> -D<DiretoryOrFile>" << std::endl
        << "Currently, the tool supports to scan directory/.h/.hpp/.cpp/.c" << std::endl
        << "Example: ScanDir.exe -LD:\\Log -TE:\\Test" << std::endl
        << "         ScanDir.exe -LD:\\Log -TE:\\Test\\Test.cpp" << std::endl;
}

int main(int a_Argc, char** a_pArgv)
{
    Timer l_Timer;

    Scaner l_Scaner;
    FilterBuild l_Filter;
    AnalyserBuild l_Analyser;
    Param l_Param;

    if (!l_Param.LoadParam(a_Argc, a_pArgv))
    {
        PrintUsage();
        return 0;
    }

    std::string l_Target = l_Param.GetValue(s_pKeyDirOrFile);
    l_Analyser.SetLogPath(l_Param.GetValue(s_pKeyLogFilePath).c_str());
    l_Scaner.SetFilter(&l_Filter);
    l_Scaner.SetAnalyser(&l_Analyser);

    l_Timer.Start();
    l_Scaner.Scan(l_Target.c_str());
    l_Timer.End();

    l_Timer.Duration();

    return 0;
}

