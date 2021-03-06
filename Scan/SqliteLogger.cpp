
#include <iostream>
#include <algorithm>
#include <list>
#include <sstream>
#include "SqliteLogger.hpp"

const char* TStr = "\\rks\\";

std::list<std::string> g_ValueList;

static int callback(void* a_pNotUsed, int a_Argc, char** a_pArgv, char** a_pColName)
{
    g_ValueList.push_back(a_pArgv[0]);
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
        std::string l_LowerChild(a_pChild);
        std::transform(l_LowerChild.begin(), l_LowerChild.end(), l_LowerChild.begin(), ::tolower);
        RemoveDriveOfStr(l_LowerChild);

        std::string l_LowerParent(a_pParent);
        std::transform(l_LowerParent.begin(), l_LowerParent.end(), l_LowerParent.begin(), ::tolower);
        RemoveDriveOfStr(l_LowerParent);

        if (!IsExisted(l_LowerParent.c_str(), l_LowerChild.c_str()))
        {
            std::string l_InsertSQL = std::string("Insert into ").append(m_TableName).append(" (Child, Parent) ").append("VALUES (\'").append(l_LowerChild).append("\',\'").append(l_LowerParent).append("\');");
            ExecSql(l_InsertSQL.c_str());
        }
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

        g_ValueList.clear();
        l_Rc = sqlite3_exec(m_pDB, a_pSql, callback, NULL, &l_pMsg);

        if (SQLITE_OK != l_Rc)
        {
            fprintf(stderr, "SQL error: %s\n", l_pMsg);
            fprintf(stderr, "SQL Statement: %s\n", a_pSql);
            sqlite3_free(l_pMsg);
        }
    }

    return 0;
}

int SQLiteLogger::CreateTable(void)
{
    if (m_TableName.size() > 0)
    {
        std::string l_SQL = std::string("CREATE TABLE IF NOT EXISTS ").append(m_TableName).append("( Child CHAR(200) NOT NULL, Parent CHAR(200) NOT NULL,");
        l_SQL.append(" PRIMARY KEY (Child, Parent)");
        l_SQL.append(");");
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
        std::string l_LowerParent(a_pParent);
        std::transform(l_LowerParent.begin(), l_LowerParent.end(), l_LowerParent.begin(), ::tolower);

        std::string l_DelSQL = std::string("Delete from ").append(m_TableName).append(" where Parent = \'").append(l_LowerParent).append("\';");
        ExecSql(l_DelSQL.c_str());
    }
}

void SQLiteLogger::RemoveDriveOfStr(std::string& a_rString)
{
    std::size_t l_DriveStartPos = a_rString.find(':');
    if (l_DriveStartPos != std::string::npos)
    {
        std::size_t l_TStrPos = a_rString.find(TStr);
        if (std::string::npos != l_TStrPos)
        {
            a_rString = a_rString.substr(l_TStrPos + (strlen(TStr)) - 1, a_rString.size() - (strlen(TStr) - l_TStrPos - 1));
        }
    }
}

void SQLiteLogger::SwtichTable(Logger* a_pLogger, const char* a_pTableName)
{
    if (NULL != a_pLogger)
    {
        ((SQLiteLogger*)a_pLogger)->UpdateTableName(a_pTableName);
    }
}

bool SQLiteLogger::IsExisted(const char* a_pParent, const char* a_pChild)
{
    bool l_IsExisted = false;

    std::string l_StrSelect = std::string("Select Child,Parent from ").append(m_TableName);
    std::ostringstream l_StrWhere;
    l_StrWhere << " Where Child = \'" << a_pChild << "\' and Parent = \'" << a_pParent << "\';";

    std::string l_Query = l_StrSelect + l_StrWhere.str();

    ExecSql(l_Query.c_str());

    if (g_ValueList.size() > 0)
    {
        l_IsExisted = true;
    }

    return l_IsExisted;
}
