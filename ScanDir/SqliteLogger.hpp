#ifndef SQLITE_LOGGER_HPP
#define SQLITE_LOGGER_HPP

#include <string>

#include "sqlite3.h"
#include "Logger.hpp"

class SQLiteLogger : public Logger
{
public:
    SQLiteLogger(std::string a_DBPath, std::string a_TableName);
    ~SQLiteLogger();

    void Log(const char* a_pParent, const char* a_pChild) override;
    void Log(const char* a_pStr) override;
    int ExecSql(const char* a_pSql);

private:
    /*int callback(void* a_pNotUsed, int a_Argc, char** a_pArgv, char** a_pColName);*/
    int OpenDB(void);
    int CreateTable(void);
    
    std::string m_DBPath;
    std::string m_TableName;
    sqlite3* m_pDB = NULL;
};

#endif

