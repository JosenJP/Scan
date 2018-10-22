#include "FileInfo.hpp"

const char* DB_NAME         = "DependencyLib.db";
const char* TBL_PROJECT     = "Project";
const char* TBL_CPP         = "CPP";
const char* TBL_HEADER      = "Header";
const char* TBL_LIB         = "Lib";
const char* TBL_LIB_NAME    = "LibName";
const char* TBL_HR_RC       = "HrRc";
const char* TBL_RC_RC       = "RcRc";

const char* CURRENT_DIR  = ".";
const char* PARENT_DIR   = "..";

const char* EXTENSION_CPP    = ".cpp";
const char* EXTENSION_C      = ".c";
const char* EXTENSION_H      = ".h";
const char* EXTENSION_HPP    = ".hpp";
const char* EXTENSION_HR     = ".hr";
const char* EXTENSION_PROJ   = ".vcxproj";
const char* EXTENSION_LIB    = ".lib";
const char* EXTENSION_RC     = ".rc";

const char* STR_INCLUDE                 = "#include";
const char* STR_LEFT_BRACKET            = "<";
const char* STR_RIGHT_BRACKET           = ">";
const char* STR_RIGHT_ROUND_BRACKET     = ")";
const char* STR_QUOTE                   = "\"";
const char* STR_COMPILE_ITEM_CPP        = "<ClCompile Include=";
const char* STR_COMPILE_ITEM_RC         = "<ResourceCompile Include=";
const char* STR_COMPILE_ITEM_END        = "/>";
const char* STR_LIB_FLAG                = "StaticLibrary";
const char* STR_OUTPUT_FILE_START       = "<OutputFile>";
const char* STR_OUTPUT_FILE_END         = "</OutputFile>";
const char* STR_ADD_DEPENDENCY_START    = "<AdditionalDependencies>";
const char* STR_ADD_DEPENDENCY_END      = "</AdditionalDependencies>";
