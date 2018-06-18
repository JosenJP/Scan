#ifndef SCANER_HPP
#define SCANER_HPP

class FilterBase;
class AnalyserBase;

class Scaner
{
public:
    Scaner();
    ~Scaner();

    void SetFilter(FilterBase* a_pFilter);
    void SetAnalyser(AnalyserBase* a_pAnalyser);
    void Scan(const char* a_pDir);

private:
    void Init(void);
    bool IsSubDir(const char* a_pDir);

    FilterBase* m_pFilter;
    AnalyserBase* m_pAnalyser;
};

#endif
