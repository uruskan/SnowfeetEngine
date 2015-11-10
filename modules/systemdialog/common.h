#ifndef __HEADER_MOD_SYSTEMDIALOG_COMMON__
#define __HEADER_MOD_SYSTEMDIALOG_COMMON__

#include <core/export.h>

#ifdef SN_SYSTEMDIALOG_EXPORT
    #define SN_SYSTEMDIALOG_API SN_EXPORT_SPEC
#else
    #define SN_SYSTEMDIALOG_API SN_IMPORT_SPEC
#endif

#endif // __HEADER_MOD_SYSTEMDIALOG_COMMON__