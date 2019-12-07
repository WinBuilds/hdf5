#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5CPPLIB_LIB)
#  define HDF5CPPLIB_EXPORT Q_DECL_EXPORT
# else
#  define HDF5CPPLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5CPPLIB_EXPORT
#endif
