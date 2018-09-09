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
    void CleanByParent(const char* a_pParent) override;

    void UpdateTableName(std::string a_TableName) { m_TableName = a_TableName; }
    std::string GetCurrTablename(void) { return m_TableName;  }

    static void FreeDB(void);

private:
    void RemoveDriveOfStr(std::string& a_rString);
    int ExecSql(const char* a_pSql);
    /*int callback(void* a_pNotUsed, int a_Argc, char** a_pArgv, char** a_pColName);*/
    int OpenDB(void);
    int CreateTable(void);
    
    std::string m_DBPath;
    std::string m_TableName;
    static sqlite3* m_pDB;
};

#endif

