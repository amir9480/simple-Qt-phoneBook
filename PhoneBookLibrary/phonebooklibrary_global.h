#ifndef PHONEBOOKLIBRARY_GLOBAL_H
#define PHONEBOOKLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

// جهت افزودن کلاس ها و توابع به فایل
// dll
// استفاده میشود

// شرط بر اساس محتویات فایل
// PhoneBookLibrary.pro
// و دستور
// DEFINES
// کار میکنه
#if defined(PHONEBOOKLIBRARY_LIBRARY)
#  define PHONEBOOKLIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PHONEBOOKLIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PHONEBOOKLIBRARY_GLOBAL_H
