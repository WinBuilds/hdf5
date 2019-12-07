#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5HLDLL_LIB)
#  define HDF5HLDLL_EXPORT Q_DECL_EXPORT
# else
#  define HDF5HLDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5HLDLL_EXPORT
#endif
