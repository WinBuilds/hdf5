/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VOL_TEST_H
#define VOL_TEST_H

#include "h5test.h"

/* The names of a set of container groups which hold objects
 * created by each of the different types of tests.
 */
#define GROUP_TEST_GROUP_NAME         "group_tests"
#define ATTRIBUTE_TEST_GROUP_NAME     "attribute_tests"
#define DATASET_TEST_GROUP_NAME       "dataset_tests"
#define DATATYPE_TEST_GROUP_NAME      "datatype_tests"
#define LINK_TEST_GROUP_NAME          "link_tests"
#define OBJECT_TEST_GROUP_NAME        "object_tests"
#define MISCELLANEOUS_TEST_GROUP_NAME "miscellaneous_tests"

#define ARRAY_LENGTH(array) sizeof(array) / sizeof(array[0])

#define VOL_TEST_FILENAME_MAX_LENGTH 1024

/* The maximum size of a dimension in an HDF5 dataspace as allowed
 * for this testing suite so as not to try to create too large
 * of a dataspace/datatype. */
#define MAX_DIM_SIZE 16

/* The maximum level of recursion that the generate_random_datatype()
 * function should go down to, before being forced to choose a base type
 * in order to not cause a stack overflow.
 */
#define TYPE_GEN_RECURSION_MAX_DEPTH 3

/* The maximum number of members allowed in an HDF5 compound type, as
 * generated by the generate_random_datatype() function, for ease of
 * development.
 */
#define COMPOUND_TYPE_MAX_MEMBERS 4

/* The maximum number and size of the dimensions of an HDF5 array
 * datatype, as generated by the generate_random_datatype() function.
 */
#define ARRAY_TYPE_MAX_DIMS 4

/* The maximum number of members and the maximum size of those
 * members' names for an HDF5 enum type, as generated by the
 * generate_random_datatype() function.
 */
#define ENUM_TYPE_MAX_MEMBER_NAME_LENGTH 256
#define ENUM_TYPE_MAX_MEMBERS            16

/* The maximum size of an HDF5 string datatype, as created by the
 * generate_random_datatype() function.
 */
#define STRING_TYPE_MAX_SIZE 1024

#define NO_LARGE_TESTS

/* The name of the file that all of the tests will operate on */
#define TEST_FILE_NAME "vol_test.h5"
extern char vol_test_filename[];

hid_t generate_random_datatype(H5T_class_t parent_class);

#endif
