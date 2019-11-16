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

/*
 * This file contains public declarations for authoring VOL connectors.
 */

#ifndef _H5VLconnector_H
#define _H5VLconnector_H

/* Public headers needed by this file */
#include "H5public.h"           /* Generic Functions                    */
#include "H5Apublic.h"          /* Attributes                           */
#include "H5ESpublic.h"         /* Event Stack                          */
#include "H5Fpublic.h"          /* Files                                */
#include "H5Ipublic.h"          /* IDs                                  */
#include "H5Lpublic.h"          /* Links                                */
#include "H5Opublic.h"          /* Objects                              */
#include "H5Rpublic.h"          /* References                           */
#include "H5VLpublic.h"         /* Virtual Object Layer                 */


/*****************/
/* Public Macros */
/*****************/

/* Capability flags for connector */
#define H5VL_CAP_FLAG_NONE              0       /* No special connector capabilities */
#define H5VL_CAP_FLAG_THREADSAFE        0x01    /* Connector is threadsafe */

/* Container info version */
#define H5VL_CONTAINER_INFO_VERSION     0x01    /* Container info struct version */

/* The maximum size allowed for blobs */
#define H5VL_MAX_BLOB_ID_SIZE           (16)    /* Allow for 128-bits blob IDs */

/* The maximum size allowed for tokens */
#define H5VL_MAX_TOKEN_SIZE             (16)    /* Allow for 128-bits tokens */

/*******************/
/* Public Typedefs */
/*******************/

/* Enum type for each VOL subclass */
/* (Used for various queries, etc) */
typedef enum H5VL_subclass_t {
    H5VL_SUBCLS_NONE,                   /* Operations outside of a subclass */
    H5VL_SUBCLS_INFO,                   /* 'Info' subclass */
    H5VL_SUBCLS_WRAP,                   /* 'Wrap' subclass */
    H5VL_SUBCLS_ATTR,                   /* 'Attribute' subclass */
    H5VL_SUBCLS_DATASET,                /* 'Dataset' subclass */
    H5VL_SUBCLS_DATATYPE,               /* 'Named datatype' subclass */
    H5VL_SUBCLS_FILE,                   /* 'File' subclass */
    H5VL_SUBCLS_GROUP,                  /* 'Group' subclass */
    H5VL_SUBCLS_LINK,                   /* 'Link' subclass */
    H5VL_SUBCLS_OBJECT,                 /* 'Object' subclass */
    H5VL_SUBCLS_REQUEST,                /* 'Request' subclass */
    H5VL_SUBCLS_BLOB                    /* 'Blob' subclass */
} H5VL_subclass_t;

/* type for tokens. Token are unique and permanent identifiers that are
 * used to reference HDF5 objects. */
typedef unsigned char H5VL_token_t[H5VL_MAX_TOKEN_SIZE];

/* types for attribute GET callback */
typedef enum H5VL_attr_get_t {
    H5VL_ATTR_GET_ACPL,                     /* creation property list              */
    H5VL_ATTR_GET_INFO,                     /* info                                */
    H5VL_ATTR_GET_NAME,                     /* access property list                */
    H5VL_ATTR_GET_SPACE,                    /* dataspace                           */
    H5VL_ATTR_GET_STORAGE_SIZE,             /* storage size                        */
    H5VL_ATTR_GET_TYPE                      /* datatype                            */
} H5VL_attr_get_t;

/* types for attribute SPECFIC callback */
typedef enum H5VL_attr_specific_t {
    H5VL_ATTR_DELETE,                       /* H5Adelete(_by_name/idx)             */
    H5VL_ATTR_EXISTS,                       /* H5Aexists(_by_name)                 */
    H5VL_ATTR_ITER,                         /* H5Aiterate(_by_name)                */
    H5VL_ATTR_RENAME                        /* H5Arename(_by_name)                 */
} H5VL_attr_specific_t;

/* Typedef and values for VOL connector attribute optional VOL operations */
typedef int H5VL_attr_optional_t;
#ifndef H5_NO_DEPRECATED_SYMBOLS
#define H5VL_ATTR_OPT_ITERATE_OLD    0      /* H5Aiterate (deprecated routine) */
#endif /* H5_NO_DEPRECATED_SYMBOLS */

/* types for dataset GET callback */
typedef enum H5VL_dataset_get_t {
    H5VL_DATASET_GET_DAPL,                  /* access property list                */
    H5VL_DATASET_GET_DCPL,                  /* creation property list              */
    H5VL_DATASET_GET_OFFSET,                /* offset                              */
    H5VL_DATASET_GET_SPACE,                 /* dataspace                           */
    H5VL_DATASET_GET_SPACE_STATUS,          /* space  status                       */
    H5VL_DATASET_GET_STORAGE_SIZE,          /* storage size                        */
    H5VL_DATASET_GET_TYPE                   /* datatype                            */
} H5VL_dataset_get_t;

/* types for dataset SPECFIC callback */
typedef enum H5VL_dataset_specific_t {
    H5VL_DATASET_SET_EXTENT,                /* H5Dset_extent                       */
    H5VL_DATASET_FLUSH,                     /* H5Dflush                            */
    H5VL_DATASET_REFRESH                    /* H5Drefresh                          */
} H5VL_dataset_specific_t;

/* Typedef and values for native VOL connector dataset optional VOL operations */
typedef int H5VL_dataset_optional_t;
#define H5VL_DATASET_OPT_FORMAT_CONVERT          0   /* H5Dformat_convert (internal) */
#define H5VL_DATASET_OPT_GET_CHUNK_INDEX_TYPE    1   /* H5Dget_chunk_index_type      */
#define H5VL_DATASET_OPT_GET_CHUNK_STORAGE_SIZE  2   /* H5Dget_chunk_storage_size    */
#define H5VL_DATASET_OPT_GET_NUM_CHUNKS          3   /* H5Dget_num_chunks            */
#define H5VL_DATASET_OPT_GET_CHUNK_INFO_BY_IDX   4   /* H5Dget_chunk_info            */
#define H5VL_DATASET_OPT_GET_CHUNK_INFO_BY_COORD 5   /* H5Dget_chunk_info_by_coord   */
#define H5VL_DATASET_OPT_CHUNK_READ              6   /* H5Dchunk_read                */
#define H5VL_DATASET_OPT_CHUNK_WRITE             7   /* H5Dchunk_write               */

/* types for datatype GET callback */
typedef enum H5VL_datatype_get_t {
    H5VL_DATATYPE_GET_BINARY,               /* get serialized form of transient type    */
    H5VL_DATATYPE_GET_TCPL                  /* datatype creation property list          */
} H5VL_datatype_get_t;

/* types for datatype SPECFIC callback */
typedef enum H5VL_datatype_specific_t {
    H5VL_DATATYPE_FLUSH,
    H5VL_DATATYPE_REFRESH
} H5VL_datatype_specific_t;

/* Typedef and values for native VOL connector named datatype optional VOL operations */
typedef int H5VL_datatype_optional_t;
/* (No optional named datatype VOL operations currently) */

/* types for file GET callback */
typedef enum H5VL_file_get_t {
    H5VL_FILE_GET_CONT_INFO,                /* file get container info              */
    H5VL_FILE_GET_FAPL,                     /* file access property list            */
    H5VL_FILE_GET_FCPL,                     /* file creation property list          */
    H5VL_FILE_GET_FILENO,                   /* file number                          */
    H5VL_FILE_GET_INTENT,                   /* file intent                          */
    H5VL_FILE_GET_NAME,                     /* file name                            */
    H5VL_FILE_GET_OBJ_COUNT,                /* object count in file                 */
    H5VL_FILE_GET_OBJ_IDS                   /* object ids in file                   */
} H5VL_file_get_t;

/* types for file SPECIFIC callback */
typedef enum H5VL_file_specific_t {
    H5VL_FILE_FLUSH,                        /* Flush file                       */
    H5VL_FILE_REOPEN,                       /* Reopen the file                  */
    H5VL_FILE_MOUNT,                        /* Mount a file                     */
    H5VL_FILE_UNMOUNT,                      /* Unmount a file                   */
    H5VL_FILE_IS_ACCESSIBLE,                /* Check if a file is accessible    */
    H5VL_FILE_DELETE                        /* Delete a file                    */
} H5VL_file_specific_t;

/* Typedef and values for native VOL connector file optional VOL operations */
typedef int H5VL_file_optional_t;
#define H5VL_FILE_OPT_CLEAR_ELINK_CACHE             0   /* H5Fclear_elink_file_cache            */
#define H5VL_FILE_OPT_GET_FILE_IMAGE                1   /* H5Fget_file_image                    */
#define H5VL_FILE_OPT_GET_FREE_SECTIONS             2   /* H5Fget_free_sections                 */
#define H5VL_FILE_OPT_GET_FREE_SPACE                3   /* H5Fget_freespace                     */
#define H5VL_FILE_OPT_GET_INFO                      4   /* H5Fget_info1/2                       */
#define H5VL_FILE_OPT_GET_MDC_CONF                  5   /* H5Fget_mdc_config                    */
#define H5VL_FILE_OPT_GET_MDC_HR                    6   /* H5Fget_mdc_hit_rate                  */
#define H5VL_FILE_OPT_GET_MDC_SIZE                  7   /* H5Fget_mdc_size                      */
#define H5VL_FILE_OPT_GET_SIZE                      8   /* H5Fget_filesize                      */
#define H5VL_FILE_OPT_GET_VFD_HANDLE                9   /* H5Fget_vfd_handle                    */
#define H5VL_FILE_OPT_GET_FILE_ID                   10  /* H5Fget_file_id                       */
#define H5VL_FILE_OPT_RESET_MDC_HIT_RATE            11  /* H5Freset_mdc_hit_rate_stats          */
#define H5VL_FILE_OPT_SET_MDC_CONFIG                12  /* H5Fset_mdc_config                    */
#define H5VL_FILE_OPT_GET_METADATA_READ_RETRY_INFO  13  /* H5Fget_metadata_read_retry_info      */
#define H5VL_FILE_OPT_START_SWMR_WRITE              14  /* H5Fstart_swmr_write                  */
#define H5VL_FILE_OPT_START_MDC_LOGGING             15  /* H5Fstart_mdc_logging                 */
#define H5VL_FILE_OPT_STOP_MDC_LOGGING              16  /* H5Fstop_mdc_logging                  */
#define H5VL_FILE_OPT_GET_MDC_LOGGING_STATUS        17  /* H5Fget_mdc_logging_status            */
#define H5VL_FILE_OPT_FORMAT_CONVERT                18  /* H5Fformat_convert                    */
#define H5VL_FILE_OPT_RESET_PAGE_BUFFERING_STATS    19  /* H5Freset_page_buffering_stats        */
#define H5VL_FILE_OPT_GET_PAGE_BUFFERING_STATS      20  /* H5Fget_page_buffering_stats          */
#define H5VL_FILE_OPT_GET_MDC_IMAGE_INFO            21  /* H5Fget_mdc_image_info                */
#define H5VL_FILE_OPT_GET_EOA                       22  /* H5Fget_eoa                           */
#define H5VL_FILE_OPT_INCR_FILESIZE                 23  /* H5Fincrement_filesize                */
#define H5VL_FILE_OPT_SET_LIBVER_BOUNDS             24  /* H5Fset_latest_format/libver_bounds   */
#define H5VL_FILE_OPT_GET_MIN_DSET_OHDR_FLAG        25  /* H5Fget_dset_no_attrs_hint            */
#define H5VL_FILE_OPT_SET_MIN_DSET_OHDR_FLAG        26  /* H5Fset_dset_no_attrs_hint            */
#define H5VL_FILE_OPT_GET_MPI_ATOMICITY             27  /* H5Fget_mpi_atomicity                 */
#define H5VL_FILE_OPT_SET_MPI_ATOMICITY             28  /* H5Fset_mpi_atomicity                 */
#define H5VL_FILE_OPT_POST_OPEN                     29  /* Adjust file after open, with wrapping context */

/* types for group GET callback */
typedef enum H5VL_group_get_t {
    H5VL_GROUP_GET_GCPL,                    /* group creation property list     */
    H5VL_GROUP_GET_INFO                     /* group info                       */
} H5VL_group_get_t;

/* types for group SPECFIC callback */
typedef enum H5VL_group_specific_t {
    H5VL_GROUP_FLUSH,
    H5VL_GROUP_REFRESH
} H5VL_group_specific_t;

/* Typedef and values for native VOL connector group optional VOL operations */
typedef int H5VL_group_optional_t;
#ifndef H5_NO_DEPRECATED_SYMBOLS
#define H5VL_GROUP_OPT_ITERATE_OLD      0   /* HG5Giterate (deprecated routine) */
#define H5VL_GROUP_OPT_GET_OBJINFO      1   /* HG5Gget_objinfo (deprecated routine) */
#endif /* H5_NO_DEPRECATED_SYMBOLS */

/* link create types for VOL */
typedef enum H5VL_link_create_type_t {
    H5VL_LINK_CREATE_HARD,
    H5VL_LINK_CREATE_SOFT,
    H5VL_LINK_CREATE_UD
} H5VL_link_create_type_t;

/* types for link GET callback */
typedef enum H5VL_link_get_t {
    H5VL_LINK_GET_INFO,        /* link info                         */
    H5VL_LINK_GET_NAME,        /* link name                         */
    H5VL_LINK_GET_VAL          /* link value                        */
} H5VL_link_get_t;

/* types for link SPECIFIC callback */
typedef enum H5VL_link_specific_t {
    H5VL_LINK_DELETE,          /* H5Ldelete(_by_idx)                */
    H5VL_LINK_EXISTS,          /* link existence                    */
    H5VL_LINK_ITER             /* H5Literate/visit(_by_name)              */
} H5VL_link_specific_t;

/* Typedef and values for native VOL connector link optional VOL operations */
typedef int H5VL_link_optional_t;
/* (No optional link VOL operations currently) */

/* types for object GET callback */
typedef enum H5VL_object_get_t {
    H5VL_OBJECT_GET_NAME,              /* object name                       */
    H5VL_OBJECT_GET_TYPE               /* object type                       */
} H5VL_object_get_t;

/* types for object SPECIFIC callback */
typedef enum H5VL_object_specific_t {
    H5VL_OBJECT_CHANGE_REF_COUNT,       /* H5Oincr/decr_refcount             */
    H5VL_OBJECT_EXISTS,                 /* H5Oexists_by_name                 */
    H5VL_OBJECT_LOOKUP,                 /* Lookup object                     */
    H5VL_OBJECT_VISIT,                  /* H5Ovisit(_by_name)                */
    H5VL_OBJECT_FLUSH,                  /* H5{D|G|O|T}flush                  */
    H5VL_OBJECT_REFRESH                 /* H5{D|G|O|T}refresh                */
} H5VL_object_specific_t;

/* Typedef and values for native VOL connector object optional VOL operations */
typedef int H5VL_object_optional_t;
#define H5VL_OBJECT_OPT_GET_COMMENT                 0   /* H5G|H5Oget_comment, H5Oget_comment_by_name   */
#define H5VL_OBJECT_OPT_GET_INFO                    1   /* H5Oget_info(_by_idx, _by_name)(2)            */
#define H5VL_OBJECT_OPT_SET_COMMENT                 2   /* H5G|H5Oset_comment, H5Oset_comment_by_name   */
#define H5VL_OBJECT_OPT_DISABLE_MDC_FLUSHES         3   /* H5Odisable_mdc_flushes                       */
#define H5VL_OBJECT_OPT_ENABLE_MDC_FLUSHES          4   /* H5Oenable_mdc_flushes                        */
#define H5VL_OBJECT_OPT_ARE_MDC_FLUSHES_DISABLED    5   /* H5Oare_mdc_flushes_disabled                  */

/* types for async request SPECIFIC callback */
typedef enum H5VL_request_specific_t {
    H5VL_REQUEST_WAITANY,               /* Wait until any request completes */
    H5VL_REQUEST_WAITSOME,              /* Wait until at least one requesst completes */
    H5VL_REQUEST_WAITALL                /* Wait until all requests complete */
} H5VL_request_specific_t;

/* Typedef and values for native VOL connector request optional VOL operations */
typedef int H5VL_request_optional_t;
/* (No optional request VOL operations currently) */

/* types for 'blob' SPECIFIC callback */
typedef enum H5VL_blob_specific_t {
    H5VL_BLOB_DELETE,                   /* Delete a blob (by ID) */
    H5VL_BLOB_GETSIZE,                  /* Get size of blob */
    H5VL_BLOB_ISNULL,                   /* Check if a blob ID is "null" */
    H5VL_BLOB_SETNULL                   /* Set a blob ID to the connector's "null" blob ID value */
} H5VL_blob_specific_t;

/* Typedef and values for native VOL connector blob optional VOL operations */
typedef int H5VL_blob_optional_t;
/* (No optional blob VOL operations currently) */

/* Types for different ways that objects are located in an HDF5 container */
typedef enum H5VL_loc_type_t {
    H5VL_OBJECT_BY_SELF,
    H5VL_OBJECT_BY_NAME,
    H5VL_OBJECT_BY_IDX,
    H5VL_OBJECT_BY_TOKEN
} H5VL_loc_type_t;

typedef struct H5VL_loc_by_name {
    const char *name;
    hid_t lapl_id;
} H5VL_loc_by_name_t;

typedef struct H5VL_loc_by_idx {
    const char *name;
    H5_index_t idx_type;
    H5_iter_order_t order;
    hsize_t n;
    hid_t lapl_id;
} H5VL_loc_by_idx_t;

typedef struct H5VL_loc_by_token {
    void *token;
} H5VL_loc_by_token_t;

/* Structure to hold parameters for object locations.
 * Either: BY_SELF, BY_NAME, BY_IDX, BY_TOKEN
 *
 * Note: Leave loc_by_token as the first union member so we
 *       can perform the simplest initialization of the struct
 *       without raising warnings.
 *
 * Note: BY_SELF requires no union members.
 */
typedef struct H5VL_loc_params_t {
    H5I_type_t      obj_type;
    H5VL_loc_type_t type;
    union {
        H5VL_loc_by_token_t     loc_by_token;
        H5VL_loc_by_name_t      loc_by_name;
        H5VL_loc_by_idx_t       loc_by_idx;
    } loc_data;
} H5VL_loc_params_t;

/* Info for H5VL_FILE_GET_CONT_INFO */
typedef struct H5VL_file_cont_info_t {
    unsigned version;                   /* version information (keep first) */
    uint64_t feature_flags;             /* Container feature flags          */
                                        /* (none currently defined)         */
    size_t token_size;                  /* Size of tokens                   */
    size_t blob_id_size;                /* Size of blob IDs                 */
} H5VL_file_cont_info_t;

/* VOL connector info fields & callbacks */
typedef struct H5VL_info_class_t {
    size_t size;                                    /* Size of the VOL info                         */
    void * (*copy)(const void *info);               /* Callback to create a copy of the VOL info    */
    herr_t (*cmp)(int *cmp_value, const void *info1, const void *info2); /* Callback to compare VOL info */
    herr_t (*free)(void *info);                     /* Callback to release a VOL info               */
    herr_t (*to_str)(const void *info, char **str); /* Callback to serialize connector's info into a string */
    herr_t (*from_str)(const char *str, void **info); /* Callback to deserialize a string into connector's info */
} H5VL_info_class_t;

/* VOL object wrap / retrieval callbacks */
/* (These only need to be implemented by "pass through" VOL connectors) */
typedef struct H5VL_wrap_class_t {
    void * (*get_object)(const void *obj);          /* Callback to retrieve underlying object       */
    herr_t (*get_wrap_ctx)(const void *obj, void **wrap_ctx); /* Callback to retrieve the object wrapping context for the connector */
    void * (*wrap_object)(void *obj, H5I_type_t obj_type, void *wrap_ctx); /* Callback to wrap a library object */
    void * (*unwrap_object)(void *obj);             /* Callback to unwrap a library object */
    herr_t (*free_wrap_ctx)(void *wrap_ctx);        /* Callback to release the object wrapping context for the connector */
} H5VL_wrap_class_t;

/* H5A routines */
typedef struct H5VL_attr_class_t {
    void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name,
            hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id,
            hid_t dxpl_id, void **req);
    void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name,
                  hid_t aapl_id, hid_t dxpl_id, void **req);
    herr_t (*read)(void *attr, hid_t mem_type_id, void *buf, hid_t dxpl_id, void **req);
    herr_t (*write)(void *attr, hid_t mem_type_id, const void *buf, hid_t dxpl_id, void **req);
    herr_t (*get)(void *obj, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_attr_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_attr_optional_t opt_type, hid_t dxpl_id,
        void **req, va_list arguments);
    herr_t (*close) (void *attr, hid_t dxpl_id, void **req);
} H5VL_attr_class_t;

/* H5D routines */
typedef struct H5VL_dataset_class_t {
    void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
            hid_t lcpl_id, hid_t type_id, hid_t space_id, hid_t dcpl_id,
            hid_t dapl_id, hid_t dxpl_id, void **req);
    void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
                  hid_t dapl_id, hid_t dxpl_id, void **req);
    herr_t (*read)(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id,
                   hid_t xfer_plist_id, void * buf, void **req);
    herr_t (*write)(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id,
                    hid_t xfer_plist_id, const void * buf, void **req);
    herr_t (*get)(void *obj, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, H5VL_dataset_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_dataset_optional_t opt_type, hid_t dxpl_id,
        void **req, va_list arguments);
    herr_t (*close) (void *dset, hid_t dxpl_id, void **req);
} H5VL_dataset_class_t;

/* H5T routines*/
typedef struct H5VL_datatype_class_t {
    void *(*commit)(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t type_id,
                    hid_t lcpl_id, hid_t tcpl_id, hid_t tapl_id, hid_t dxpl_id, void **req);
    void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char * name,
                  hid_t tapl_id, hid_t dxpl_id, void **req);
    herr_t (*get)   (void *obj, H5VL_datatype_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, H5VL_datatype_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_datatype_optional_t opt_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*close) (void *dt, hid_t dxpl_id, void **req);
} H5VL_datatype_class_t;

/* H5F routines */
typedef struct H5VL_file_class_t {
    void *(*create)(const char *name, unsigned flags, hid_t fcpl_id,
                    hid_t fapl_id, hid_t dxpl_id, void **req);
    void *(*open)(const char *name, unsigned flags, hid_t fapl_id, hid_t dxpl_id, void **req);
    herr_t (*get)(void *obj, H5VL_file_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, H5VL_file_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_file_optional_t opt_type, hid_t dxpl_id,
                       void **req, va_list arguments);
    herr_t (*close) (void *file, hid_t dxpl_id, void **req);
} H5VL_file_class_t;

/* H5G routines */
typedef struct H5VL_group_class_t {
    void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
        hid_t lcpl_id, hid_t gcpl_id, hid_t gapl_id, hid_t dxpl_id, void **req);
    void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
                  hid_t gapl_id, hid_t dxpl_id, void **req);
    herr_t (*get)(void *obj, H5VL_group_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, H5VL_group_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_group_optional_t opt_type, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*close) (void *grp, hid_t dxpl_id, void **req);
} H5VL_group_class_t;

/* H5L routines */
typedef struct H5VL_link_class_t {
    herr_t (*create)(H5VL_link_create_type_t create_type, void *obj, const H5VL_loc_params_t *loc_params,
            hid_t lcpl_id, hid_t lapl_id, hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*copy)(void *src_obj, const H5VL_loc_params_t *loc_params1,
                   void *dst_obj, const H5VL_loc_params_t *loc_params2,
                   hid_t lcpl, hid_t lapl, hid_t dxpl_id, void **req);
    herr_t (*move)(void *src_obj, const H5VL_loc_params_t *loc_params1,
                   void *dst_obj, const H5VL_loc_params_t *loc_params2,
                   hid_t lcpl, hid_t lapl, hid_t dxpl_id, void **req);
    herr_t (*get)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_link_get_t get_type,
                  hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_link_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_link_optional_t opt_type, hid_t dxpl_id,
                       void **req, va_list arguments);
} H5VL_link_class_t;

/* H5O routines */
typedef struct H5VL_object_class_t {
    void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, H5I_type_t *opened_type,
                  hid_t dxpl_id, void **req);
    herr_t (*copy)(void *src_obj, const H5VL_loc_params_t *loc_params1, const char *src_name,
                   void *dst_obj, const H5VL_loc_params_t *loc_params2, const char *dst_name,
                   hid_t ocpypl_id, hid_t lcpl_id, hid_t dxpl_id, void **req);
    herr_t (*get)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_object_get_t get_type,
                  hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_object_specific_t specific_type,
                       hid_t dxpl_id, void **req, va_list arguments);
    herr_t (*optional)(void *obj, H5VL_object_optional_t opt_type,
                       hid_t dxpl_id, void **req, va_list arguments);
} H5VL_object_class_t;

/* Asynchronous request 'notify' callback */
typedef herr_t (*H5VL_request_notify_t)(void *ctx, H5ES_status_t status);

/* Container/connector introspection routines */
typedef struct H5VL_introspect_class_t {
    herr_t (*opt_query)(void *obj, H5VL_subclass_t cls, int opt_type, hbool_t *supported);
} H5VL_introspect_class_t;

/* Async request operation routines */
typedef struct H5VL_request_class_t {
    herr_t (*wait)(void *req, uint64_t timeout, H5ES_status_t *status);
    herr_t (*notify)(void *req, H5VL_request_notify_t cb, void *ctx);
    herr_t (*cancel)(void *req);
    herr_t (*specific)(void *req, H5VL_request_specific_t specific_type, va_list arguments);
    herr_t (*optional)(void *req, H5VL_request_optional_t opt_type, va_list arguments);
    herr_t (*free)(void *req);
} H5VL_request_class_t;

/* 'blob' routines */
typedef struct H5VL_blob_class_t {
    herr_t (*put)(void *obj, const void *buf, size_t size, void *blob_id, void *ctx);
    herr_t (*get)(void *obj, const void *blob_id, void *buf, size_t size, void *ctx);
    herr_t (*specific)(void *obj, void *blob_id, H5VL_blob_specific_t specific_type, va_list arguments);
    herr_t (*optional)(void *obj, void *blob_id, H5VL_blob_optional_t opt_type, va_list arguments);
} H5VL_blob_class_t;

/*
 * VOL connector identifiers.  Values 0 through 255 are for connectors defined
 * by the HDF5 library.  Values 256 through 511 are available for testing new
 * filters.  Subsequent values should be obtained from the HDF5 development
 * team at help@hdfgroup.org.
 */
typedef int H5VL_class_value_t;

/* Class information for each VOL connector */
typedef struct H5VL_class_t {
    /* Overall connector fields & callbacks */
    unsigned int version;                   /* VOL connector class struct version #     */
    H5VL_class_value_t value;               /* Value to identify connector              */
    const char *name;                       /* Connector name (MUST be unique!)         */
    unsigned cap_flags;                     /* Capability flags for connector           */
    herr_t (*initialize)(hid_t vipl_id);    /* Connector initialization callback        */
    herr_t (*terminate)(void);              /* Connector termination callback           */

    /* VOL framework */
    H5VL_info_class_t       info_cls;       /* VOL info fields & callbacks  */
    H5VL_wrap_class_t       wrap_cls;       /* VOL object wrap / retrieval callbacks */

    /* Data Model */
    H5VL_attr_class_t       attr_cls;       /* Attribute (H5A*) class callbacks */
    H5VL_dataset_class_t    dataset_cls;    /* Dataset (H5D*) class callbacks   */
    H5VL_datatype_class_t   datatype_cls;   /* Datatype (H5T*) class callbacks  */
    H5VL_file_class_t       file_cls;       /* File (H5F*) class callbacks      */
    H5VL_group_class_t      group_cls;      /* Group (H5G*) class callbacks     */
    H5VL_link_class_t       link_cls;       /* Link (H5L*) class callbacks      */
    H5VL_object_class_t     object_cls;     /* Object (H5O*) class callbacks    */

    /* Infrastructure / Services */
    H5VL_introspect_class_t introspect_cls; /* Container/connector introspection class callbacks */
    H5VL_request_class_t    request_cls;    /* Asynchronous request class callbacks */
    H5VL_blob_class_t       blob_cls;       /* 'blob' callbacks */

    /* Catch-all */
    herr_t (*optional)(void *obj, int op_type, hid_t dxpl_id, void **req, va_list arguments); /* Optional callback */
} H5VL_class_t;


/********************/
/* Public Variables */
/********************/


/*********************/
/* Public Prototypes */
/*********************/

#ifdef __cplusplus
extern "C" {
#endif

/* Helper routines for VOL connector authors */
H5_DLL void *H5VLobject(hid_t obj_id);
H5_DLL hid_t H5VLget_file_type(void *file_obj, hid_t connector_id,
    hid_t dtype_id);
H5_DLL hid_t H5VLpeek_connector_id(const char *name);

#ifdef __cplusplus
}
#endif

#endif /* _H5VLconnector_H */

