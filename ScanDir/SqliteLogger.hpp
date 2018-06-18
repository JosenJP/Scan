#ifndef SQLITE_LOGGER_HPP
#define SQLITE_LOGGER_HPP

#include "Include/sqlite3.h"
#include "Logger.hpp"

class SQLiteLogger : public Logger
{
public:
    SQLiteLogger();
    ~SQLiteLogger();

    void Log(const char* a_pParent, const char* a_pChild) override;
    void Log(const char* a_pStr) override;

private:

};

#endif

