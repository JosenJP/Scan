#include <iostream>
#include <time.h>
#include "Timer.hpp"

void Timer::Start(void)
{
    m_StartTime = clock();
    PrintCurrentTime();
}

void Timer::End(void)
{
    m_EndTime = clock();
    PrintCurrentTime();
}

void Timer::Duration(void)
{
    float l_Seconds = (m_EndTime - m_StartTime) / CLOCKS_PER_SEC;
    float l_Hours = l_Seconds / 3600.0;

    std::cout << "Execution Time: " << std::endl
        << "Seconds: " << l_Seconds << "(s)" << std::endl
        << "Or Hours: " << l_Hours << "(h)" << std::endl;
}

void Timer::PrintCurrentTime(void)
{
    char l_Buffer[50];
    memset(l_Buffer, 0, sizeof(l_Buffer));
    time_t l_Time = time(NULL);

    ctime_s(l_Buffer, sizeof(l_Buffer), &l_Time);
    std::cout << l_Buffer;
}

