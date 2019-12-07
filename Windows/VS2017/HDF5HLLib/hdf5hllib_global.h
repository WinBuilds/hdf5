#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDF5HLLIB_LIB)
#  define HDF5HLLIB_EXPORT Q_DECL_EXPORT
# else
#  define HDF5HLLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDF5HLLIB_EXPORT
#endif
