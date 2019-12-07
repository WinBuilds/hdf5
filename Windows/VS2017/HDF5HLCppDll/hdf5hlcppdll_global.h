#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5HLCPPDLL_LIB)
#  define HDF5HLCPPDLL_EXPORT Q_DECL_EXPORT
# else
#  define HDF5HLCPPDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5HLCPPDLL_EXPORT
#endif
