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
    void Scan(const char* a_pTarget);

private:
    void ScanDir(const char* a_pDir);
    void ScanFile(const char* a_pFile);
    void Init(void);
    bool IsSubDir(const char* a_pDir);
    bool IsDir(const char* a_pTarget);

    FilterBase* m_pFilter;
    AnalyserBase* m_pAnalyser;
};

#endif
