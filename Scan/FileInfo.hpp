#ifndef FILE_INFO_HPP
#define FILE_INFO_HPP

enum FileType
{
    UNKNOW  = 0,
    CPP     = 1,
    H       = 2,
    HPP     = 3,
    PROJ    = 4,
    C       = 5,
    HR      = 6,
    RC      = 7
};

extern const char* DB_NAME;
extern const char* TBL_PROJECT;
extern const char* TBL_CPP;
extern const char* TBL_HEADER;
extern const char* TBL_LIB;
extern const char* TBL_LIB_NAME;
extern const char* TBL_HR_RC;
extern const char* TBL_RC_RC;

extern const char* CURRENT_DIR;
extern const char* PARENT_DIR;

extern const char* EXTENSION_CPP;
extern const char* EXTENSION_C;
extern const char* EXTENSION_H;
extern const char* EXTENSION_HPP;
extern const char* EXTENSION_HR;
extern const char* EXTENSION_PROJ;
extern const char* EXTENSION_LIB;
extern const char* EXTENSION_RC;

extern const char* STR_INCLUDE;
extern const char* STR_LEFT_BRACKET;
extern const char* STR_RIGHT_BRACKET;
extern const char* STR_RIGHT_ROUND_BRACKET;
extern const char* STR_QUOTE;
extern const char* STR_COMPILE_ITEM_CPP;
extern const char* STR_COMPILE_ITEM_RC;
extern const char* STR_COMPILE_ITEM_END;
extern const char* STR_LIB_FLAG;
extern const char* STR_OUTPUT_FILE_START;
extern const char* STR_OUTPUT_FILE_END;
extern const char* STR_ADD_DEPENDENCY_START;
extern const char* STR_ADD_DEPENDENCY_END;

#endif // !FILE_INFO_HPP
