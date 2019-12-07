#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5DLL_LIB)
#  define HDF5DLL_EXPORT Q_DECL_EXPORT
# else
#  define HDF5DLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5DLL_EXPORT
#endif
