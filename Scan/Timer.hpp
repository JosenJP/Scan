#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer
{
public:
    Timer() {}
    ~Timer() {}

    void Start(void);
    void End(void);
    void Duration(void);

private:
    void PrintCurrentTime(void);

    std::clock_t m_StartTime;
    std::clock_t m_EndTime;
};

#endif // !TIMER_HPP

