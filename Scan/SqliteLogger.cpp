
#include<iostream>
#include "SqliteLogger.hpp"

static int callback(void* a_pNotUsed, int a_Argc, char** a_pArgv, char** a_pColName)
{
    return 0;
}

sqlite3* SQLiteLogger::m_pDB = NULL;

void SQLiteLogger::FreeDB(void)
{
    if (NULL != m_pDB)
    {
        sqlite3_close(m_pDB);
    }
}

SQLiteLogger::SQLiteLogger(std::string a_DBPath, std::string a_TableName)
{
    m_DBPath = a_DBPath;
    m_TableName = a_TableName;
}

SQLiteLogger::~SQLiteLogger()
{

}

void SQLiteLogger::Log(const char* a_pParent, const char* a_pChild)
{

    if (SQLITE_OK != CreateTable())
    {
        return;
    }

    if ((NULL != m_pDB) && (m_TableName.size() > 0))
    {
        std::string l_InsertSQL = std::string("Insert into ").append(m_TableName).append(" (Child, Parent) ").append("VALUES (\'").append(a_pChild).append("\',\'").append(a_pParent).append("\');");
        ExecSql(l_InsertSQL.c_str());

        //std::cout << "Child: " << a_pChild << " Parent: " << a_pParent << std::endl;
    }
}

void SQLiteLogger::Log(const char* a_pStr)
{
}

int SQLiteLogger::OpenDB()
{
    int l_Rc = SQLITE_OK;
    if (NULL == m_pDB)
    {
        /* Open database */
        l_Rc = sqlite3_open(m_DBPath.c_str(), &m_pDB);

        if (SQLITE_OK != l_Rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_pDB));
            sqlite3_close(m_pDB);
            m_pDB = NULL;
        }
    }
    return 0;
}

int SQLiteLogger::ExecSql(const char* a_pSql)
{
    int l_Rc = SQLITE_OK;

    OpenDB();
    if (NULL != m_pDB)
    {
        char* l_pMsg = NULL;

        l_Rc = sqlite3_exec(m_pDB, a_pSql, callback, NULL, &l_pMsg);

        if (SQLITE_OK != l_Rc)
        {
            fprintf(stderr, "SQL error: %s\n", l_pMsg);
            sqlite3_free(l_pMsg);
        }
    }

    return 0;
}

int SQLiteLogger::CreateTable(void)
{
    if (m_TableName.size() > 0)
    {
        std::string l_SQL = std::string("CREATE TABLE IF NOT EXISTS ").append(m_TableName).append("( Child CHAR(200) NOT NULL, Parent CHAR(200) NOT NULL);");
        return ExecSql(l_SQL.c_str());
    }

    return 0;
}

void SQLiteLogger::CleanByParent(const char* a_pParent)
{
    if (SQLITE_OK != CreateTable())
    {
        return;
    }

    if (m_TableName.size() > 0)
    {
        std::string l_DelSQL = std::string("Delete from ").append(m_TableName).append(" where Parent = \'").append(a_pParent).append("\';");
        ExecSql(l_DelSQL.c_str());
    }
}
