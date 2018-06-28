#ifndef FILE_INFO_HPP
#define FILE_INFO_HPP

enum FileType
{
    UNKNOW  = 0,
    CPP     = 1,
    H       = 2,
    HPP     = 3,
    PROJ    = 4,
    C       = 5
};

extern const char* CURRENT_DIR;
extern const char* PARENT_DIR;

extern const char* EXTENSION_CPP;
extern const char* EXTENSION_C;
extern const char* EXTENSION_H;
extern const char* EXTENSION_HPP;
extern const char* EXTENSION_PROJ;

extern const char* STR_INCLUDE;
extern const char* STR_LEFT_BRACKET;
extern const char* STR_RIGHT_BRACKET;
extern const char* STR_QUOTE;
extern const char* STR_COMPILE_ITEM_CPP;
extern const char* STR_COMPILE_ITEM_END;

#endif // !FILE_INFO_HPP
