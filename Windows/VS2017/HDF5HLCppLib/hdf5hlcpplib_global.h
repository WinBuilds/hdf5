#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5HLCPPLIB_LIB)
#  define HDF5HLCPPLIB_EXPORT Q_DECL_EXPORT
# else
#  define HDF5HLCPPLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5HLCPPLIB_EXPORT
#endif
