#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5CPPDLL_LIB)
#  define HDF5CPPDLL_EXPORT Q_DECL_EXPORT
# else
#  define HDF5CPPDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5CPPDLL_EXPORT
#endif
