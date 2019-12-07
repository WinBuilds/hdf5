#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5LIB_LIB)
#  define HDF5LIB_EXPORT Q_DECL_EXPORT
# else
#  define HDF5LIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5LIB_EXPORT
#endif
