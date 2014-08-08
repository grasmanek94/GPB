//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2006 SA:MP Team
//
//----------------------------------------------------------

#ifndef _PLUGINCOMMON_H_INCLUDED
#define _PLUGINCOMMON_H_INCLUDED

//----------------------------------------------------------

#define SAMP_PLUGIN_VERSION 0x0200

//----------------------------------------------------------

#ifdef __cplusplus
  #define PLUGIN_EXTERN_C extern "C"
#else
  #define PLUGIN_EXTERN_C 
#endif

#if defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
  #ifndef __GNUC__
    #pragma message "Warning: Not using a GNU compiler."
  #endif
  #define PLUGIN_CALL 
  #ifndef SAMPSVR
    // Compile code with -fvisibility=hidden to hide non-exported functions.
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C __attribute__((visibility("default")))
  #else
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C 
  #endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
  #ifndef _MSC_VER
    #pragma message "Warning: Not using a VC++ compiler."
  #endif
  #define PLUGIN_CALL __stdcall
  #define PLUGIN_EXPORT PLUGIN_EXTERN_C
#else
  #error "You must define one of WIN32, LINUX or FREEBSD"
#endif

//----------------------------------------------------------

enum SUPPORTS_FLAGS 
{
	SUPPORTS_VERSION		= SAMP_PLUGIN_VERSION,
	SUPPORTS_VERSION_MASK	= 0xffff,
	SUPPORTS_AMX_NATIVES	= 0x10000,
	SUPPORTS_PROCESS_TICK	= 0x20000,
};

//----------------------------------------------------------

enum PLUGIN_DATA_TYPE
{
	// For some debugging
	PLUGIN_DATA_LOGPRINTF		= 0x00,	// void (*logprintf)(char* format, ...)

	// AMX
	PLUGIN_DATA_AMX_EXPORTS		= 0x10,	// void* AmxFunctionTable[]    (see PLUGIN_AMX_EXPORT)
	PLUGIN_DATA_CALLPUBLIC_FS	= 0x11, // int (*AmxCallPublicFilterScript)(char *szFunctionName)
	PLUGIN_DATA_CALLPUBLIC_GM	= 0x12, // int (*AmxCallPublicGameMode)(char *szFunctionName)

};

//----------------------------------------------------------

enum PLUGIN_AMX_EXPORT
{
	PLUGIN_AMX_EXPORT_Align16		= 0,
	PLUGIN_AMX_EXPORT_Align32		= 1,
	PLUGIN_AMX_EXPORT_Align64		= 2,
	PLUGIN_AMX_EXPORT_Allot			= 3,
	PLUGIN_AMX_EXPORT_Callback		= 4,
	PLUGIN_AMX_EXPORT_Cleanup		= 5,
	PLUGIN_AMX_EXPORT_Clone			= 6,
	PLUGIN_AMX_EXPORT_Exec			= 7,
	PLUGIN_AMX_EXPORT_FindNative	= 8,
	PLUGIN_AMX_EXPORT_FindPublic	= 9,
	PLUGIN_AMX_EXPORT_FindPubVar	= 10,
	PLUGIN_AMX_EXPORT_FindTagId		= 11,
	PLUGIN_AMX_EXPORT_Flags			= 12,
	PLUGIN_AMX_EXPORT_GetAddr		= 13,
	PLUGIN_AMX_EXPORT_GetNative		= 14,
	PLUGIN_AMX_EXPORT_GetPublic		= 15,
	PLUGIN_AMX_EXPORT_GetPubVar		= 16,
	PLUGIN_AMX_EXPORT_GetString		= 17,
	PLUGIN_AMX_EXPORT_GetTag		= 18,
	PLUGIN_AMX_EXPORT_GetUserData	= 19,
	PLUGIN_AMX_EXPORT_Init			= 20,
	PLUGIN_AMX_EXPORT_InitJIT		= 21,
	PLUGIN_AMX_EXPORT_MemInfo		= 22,
	PLUGIN_AMX_EXPORT_NameLength	= 23,
	PLUGIN_AMX_EXPORT_NativeInfo	= 24,
	PLUGIN_AMX_EXPORT_NumNatives	= 25,
	PLUGIN_AMX_EXPORT_NumPublics	= 26,
	PLUGIN_AMX_EXPORT_NumPubVars	= 27,
	PLUGIN_AMX_EXPORT_NumTags		= 28,
	PLUGIN_AMX_EXPORT_Push			= 29,
	PLUGIN_AMX_EXPORT_PushArray		= 30,
	PLUGIN_AMX_EXPORT_PushString	= 31,
	PLUGIN_AMX_EXPORT_RaiseError	= 32,
	PLUGIN_AMX_EXPORT_Register		= 33,
	PLUGIN_AMX_EXPORT_Release		= 34,
	PLUGIN_AMX_EXPORT_SetCallback	= 35,
	PLUGIN_AMX_EXPORT_SetDebugHook	= 36,
	PLUGIN_AMX_EXPORT_SetString		= 37,
	PLUGIN_AMX_EXPORT_SetUserData	= 38,
	PLUGIN_AMX_EXPORT_StrLen		= 39,
	PLUGIN_AMX_EXPORT_UTF8Check		= 40,
	PLUGIN_AMX_EXPORT_UTF8Get		= 41,
	PLUGIN_AMX_EXPORT_UTF8Len		= 42,
	PLUGIN_AMX_EXPORT_UTF8Put		= 43,
};

//----------------------------------------------------------

#endif // _PLUGINCOMMON_H_INCLUDED

//----------------------------------------------------------
// EOF

/*  Pawn Abstract Machine (for the Pawn language)
 *
 *  Copyright (c) ITB CompuPhase, 1997-2005
 *
 *  This software is provided "as-is", without any express or implied warranty.
 *  In no event will the authors be held liable for any damages arising from
 *  the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1.  The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software in
 *      a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *  2.  Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *  3.  This notice may not be removed or altered from any source distribution.
 *
 *  Version: $Id: amx.h,v 1.5 2006/03/26 16:56:15 spookie Exp $
 */

#if defined FREEBSD && !defined __FreeBSD__
  #define __FreeBSD__
#endif
#if defined LINUX || defined __FreeBSD__ || defined __OpenBSD__
/*
 * Things needed to compile under linux.
 *
 * Should be reworked totally to use GNU's 'configure'
 */
#ifndef SCLINUX_H
#define SCLINUX_H

/* getchar() is not a 'cool' replacement for MSDOS getch: Linux/unix depends on the features activated or not about the
 * controlling terminal's tty. This means that ioctl(2) calls must be performed, for instance to have the controlling 
 * terminal tty's in 'raw' mode, if we want to be able to fetch a single character. This also means that everything must 
 * be put back correctly when the function ends. See GETCH.C for an implementation.
 *
 * For interactive use of SRUN/SDBG if would be much better to use GNU's readline package: the user would be able to 
 * have a complete emacs/vi like line editing system.
 */

/* Extremely inefficient but portable POSIX getch(), see getch.c */
#ifndef GETCH_H
#define GETCH_H

#if defined __cplusplus
  extern "C" {
#endif
int getch(void);
int kbhit(void);

#if defined __cplusplus
}
#endif

#endif /* GETCH_H */

#define	stricmp(a,b)    strcasecmp(a,b)
#define	strnicmp(a,b,c) strncasecmp(a,b,c)

/*
 * WinWorld wants '\'. Unices do not.
 */
#define	DIRECTORY_SEP_CHAR      '/'
#define	DIRECTORY_SEP_STR       "/"

/*
 * SC assumes that a computer is Little Endian unless told otherwise. It uses
 * (and defines) the macros BYTE_ORDER and BIG_ENDIAN.
 * For Linux, we must overrule these settings with those defined in glibc.
 */
#if !defined __BYTE_ORDER
# include <stdlib.h>
#endif

#if defined __OpenBSD__ || defined __FreeBSD__
# define __BYTE_ORDER    BYTE_ORDER
# define __LITTLE_ENDIAN LITTLE_ENDIAN
# define __BIG_ENDIAN    BIG_ENDIAN
#endif

#if !defined __BYTE_ORDER
# error	"Can't figure computer byte order (__BYTE_ORDER macro not found)"
#endif

#endif /* SCLINUX_H */

#endif

#ifndef AMX_H_INCLUDED
#define AMX_H_INCLUDED

#if defined HAVE_STDINT_H
  #include <stdint.h>
#else
  #if defined __LCC__ || defined __DMC__ || defined LINUX
    #if defined HAVE_INTTYPES_H
      #include <inttypes.h>
    #else
      #include <stdint.h>
    #endif
  #elif !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
    /* The ISO C99 defines the int16_t and int_32t types. If the compiler got
     * here, these types are probably undefined.
     */
    #if defined __MACH__
      #include <ppc/types.h>
      typedef unsigned short int  uint16_t;
      typedef unsigned long int   uint32_t;
    #elif defined __FreeBSD__
      #include <inttypes.h>
    #else
      typedef short int           int16_t;
      typedef unsigned short int  uint16_t;
      #if defined SN_TARGET_PS2
        typedef int               int32_t;
        typedef unsigned int      uint32_t;
      #else
        typedef int          int32_t;
        typedef unsigned int uint32_t;
      #endif
      #if defined __WIN32__ || defined _WIN32 || defined WIN32
        typedef __int64	          int64_t;
        typedef unsigned __int64  uint64_t;
        #define HAVE_I64
      #elif defined __GNUC__
        typedef long long         int64_t;
        typedef unsigned long long uint64_t;
        #define HAVE_I64
      #endif
    #endif
  #endif
  #define HAVE_STDINT_H
#endif
#if defined _LP64 || defined WIN64 || defined _WIN64
  #if !defined __64BIT__
    #define __64BIT__
  #endif
#endif

#if HAVE_ALLOCA_H
  #include <alloca.h>
#endif
#if defined __WIN32__ || defined _WIN32 || defined WIN32 /* || defined __MSDOS__ */
  #if !defined alloca
    #define alloca(n)   _alloca(n)
  #endif
#endif

#if !defined arraysize
  #define arraysize(array)  (sizeof(array) / sizeof((array)[0]))
#endif

#ifdef  __cplusplus
extern  "C" {
#endif

#if defined PAWN_DLL
  #if !defined AMX_NATIVE_CALL
    #define AMX_NATIVE_CALL __stdcall
  #endif
  #if !defined AMXAPI
    #define AMXAPI          __stdcall
  #endif
#endif

/* calling convention for native functions */
#if !defined AMX_NATIVE_CALL
  #define AMX_NATIVE_CALL
#endif
/* calling convention for all interface functions and callback functions */
#if !defined AMXAPI
  #if defined STDECL
    #define AMXAPI      __stdcall
  #elif defined CDECL
    #define AMXAPI      __cdecl
  #elif defined GCC_HASCLASSVISIBILITY
    #define AMXAPI __attribute__ ((visibility("default")))
  #else
    #define AMXAPI
  #endif
#endif
#if !defined AMXEXPORT
  #define AMXEXPORT
#endif

/* File format version                          Required AMX version
 *   0 (original version)                       0
 *   1 (opcodes JUMP.pri, SWITCH and CASETBL)   1
 *   2 (compressed files)                       2
 *   3 (public variables)                       2
 *   4 (opcodes SWAP.pri/alt and PUSHADDR)      4
 *   5 (tagnames table)                         4
 *   6 (reformatted header)                     6
 *   7 (name table, opcodes SYMTAG & SYSREQ.D)  7
 *   8 (opcode STMT, renewed debug interface)   8
 */
#define CUR_FILE_VERSION  8     /* current file version; also the current AMX version */
#define MIN_FILE_VERSION  6     /* lowest supported file format version for the current AMX version */
#define MIN_AMX_VERSION   8     /* minimum AMX version needed to support the current file format */

#if !defined PAWN_CELL_SIZE
  #define PAWN_CELL_SIZE 32     /* by default, use 32-bit cells */
#endif
#if PAWN_CELL_SIZE==16
  typedef uint16_t  ucell;
  typedef int16_t   cell;
#elif PAWN_CELL_SIZE==32
  typedef uint32_t  ucell;
  typedef int32_t   cell;
#elif PAWN_CELL_SIZE==64
  typedef uint64_t  ucell;
  typedef int64_t   cell;
#else
  #error Unsupported cell size (PAWN_CELL_SIZE)
#endif

#define UNPACKEDMAX   ((1L << (sizeof(cell)-1)*8) - 1)
#define UNLIMITED     (~1u >> 1)

struct tagAMX;
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, cell *params);
typedef int (AMXAPI *AMX_CALLBACK)(struct tagAMX *amx, cell index,
                                   cell *result, cell *params);
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
#if !defined _FAR
  #define _FAR
#endif

#if defined _MSC_VER
  #pragma warning(disable:4103)  /* disable warning message 4103 that complains
                                  * about pragma pack in a header file */
  #pragma warning(disable:4100)  /* "'%$S' : unreferenced formal parameter" */
#endif

/* Some compilers do not support the #pragma align, which should be fine. Some
 * compilers give a warning on unknown #pragmas, which is not so fine...
 */
#if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
  #define AMX_NO_ALIGN
#endif

#if defined __GNUC__
  #define PACKED        __attribute__((packed))
#else
  #define PACKED
#endif

#if !defined AMX_NO_ALIGN
  #if defined LINUX || defined __FreeBSD__
    #pragma pack(1)         /* structures must be packed (byte-aligned) */
  #elif defined MACOS && defined __MWERKS__
	#pragma options align=mac68k
  #else
    #pragma pack(push)
    #pragma pack(1)         /* structures must be packed (byte-aligned) */
    #if defined __TURBOC__
      #pragma option -a-    /* "pack" pragma for older Borland compilers */
    #endif
  #endif
#endif

typedef struct tagAMX_NATIVE_INFO {
  const char _FAR *name PACKED;
  AMX_NATIVE func       PACKED;
} PACKED AMX_NATIVE_INFO;

#define AMX_USERNUM     4
#define sEXPMAX         19      /* maximum name length for file version <= 6 */
#define sNAMEMAX        31      /* maximum name length of symbol name */

typedef struct tagAMX_FUNCSTUB {
  ucell address         PACKED;
  char name[sEXPMAX+1]  PACKED;
} PACKED AMX_FUNCSTUB;

typedef struct tagFUNCSTUBNT {
  ucell address         PACKED;
  uint32_t nameofs      PACKED;
} PACKED AMX_FUNCSTUBNT;

/* The AMX structure is the internal structure for many functions. Not all
 * fields are valid at all times; many fields are cached in local variables.
 */
typedef struct tagAMX {
  unsigned char _FAR *base PACKED; /* points to the AMX header plus the code, optionally also the data */
  unsigned char _FAR *data PACKED; /* points to separate data+stack+heap, may be NULL */
  AMX_CALLBACK callback PACKED;
  AMX_DEBUG debug       PACKED; /* debug callback */
  /* for external functions a few registers must be accessible from the outside */
  cell cip              PACKED; /* instruction pointer: relative to base + amxhdr->cod */
  cell frm              PACKED; /* stack frame base: relative to base + amxhdr->dat */
  cell hea              PACKED; /* top of the heap: relative to base + amxhdr->dat */
  cell hlw              PACKED; /* bottom of the heap: relative to base + amxhdr->dat */
  cell stk              PACKED; /* stack pointer: relative to base + amxhdr->dat */
  cell stp              PACKED; /* top of the stack: relative to base + amxhdr->dat */
  int flags             PACKED; /* current status, see amx_Flags() */
  /* user data */
  long usertags[AMX_USERNUM] PACKED;
  void _FAR *userdata[AMX_USERNUM] PACKED;
  /* native functions can raise an error */
  int error             PACKED;
  /* passing parameters requires a "count" field */
  int paramcount;
  /* the sleep opcode needs to store the full AMX status */
  cell pri              PACKED;
  cell alt              PACKED;
  cell reset_stk        PACKED;
  cell reset_hea        PACKED;
  cell sysreq_d         PACKED; /* relocated address/value for the SYSREQ.D opcode */
  #if defined JIT
    /* support variables for the JIT */
    int reloc_size      PACKED; /* required temporary buffer for relocations */
    long code_size      PACKED; /* estimated memory footprint of the native code */
  #endif
} PACKED AMX;

/* The AMX_HEADER structure is both the memory format as the file format. The
 * structure is used internaly.
 */
typedef struct tagAMX_HEADER {
  int32_t size          PACKED; /* size of the "file" */
  uint16_t magic        PACKED; /* signature */
  char    file_version  PACKED; /* file format version */
  char    amx_version   PACKED; /* required version of the AMX */
  int16_t flags         PACKED;
  int16_t defsize       PACKED; /* size of a definition record */
  int32_t cod           PACKED; /* initial value of COD - code block */
  int32_t dat           PACKED; /* initial value of DAT - data block */
  int32_t hea           PACKED; /* initial value of HEA - start of the heap */
  int32_t stp           PACKED; /* initial value of STP - stack top */
  int32_t cip           PACKED; /* initial value of CIP - the instruction pointer */
  int32_t publics       PACKED; /* offset to the "public functions" table */
  int32_t natives       PACKED; /* offset to the "native functions" table */
  int32_t libraries     PACKED; /* offset to the table of libraries */
  int32_t pubvars       PACKED; /* the "public variables" table */
  int32_t tags          PACKED; /* the "public tagnames" table */
  int32_t nametable     PACKED; /* name table */
} PACKED AMX_HEADER;

#if PAWN_CELL_SIZE==16
  #define AMX_MAGIC     0xf1e2
#elif PAWN_CELL_SIZE==32
  #define AMX_MAGIC     0xf1e0
#elif PAWN_CELL_SIZE==64
  #define AMX_MAGIC     0xf1e1
#endif

enum {
  AMX_ERR_NONE,
  /* reserve the first 15 error codes for exit codes of the abstract machine */
  AMX_ERR_EXIT,         /* forced exit */
  AMX_ERR_ASSERT,       /* assertion failed */
  AMX_ERR_STACKERR,     /* stack/heap collision */
  AMX_ERR_BOUNDS,       /* index out of bounds */
  AMX_ERR_MEMACCESS,    /* invalid memory access */
  AMX_ERR_INVINSTR,     /* invalid instruction */
  AMX_ERR_STACKLOW,     /* stack underflow */
  AMX_ERR_HEAPLOW,      /* heap underflow */
  AMX_ERR_CALLBACK,     /* no callback, or invalid callback */
  AMX_ERR_NATIVE,       /* native function failed */
  AMX_ERR_DIVIDE,       /* divide by zero */
  AMX_ERR_SLEEP,        /* go into sleepmode - code can be restarted */
  AMX_ERR_INVSTATE,     /* invalid state for this access */

  AMX_ERR_MEMORY = 16,  /* out of memory */
  AMX_ERR_FORMAT,       /* invalid file format */
  AMX_ERR_VERSION,      /* file is for a newer version of the AMX */
  AMX_ERR_NOTFOUND,     /* function not found */
  AMX_ERR_INDEX,        /* invalid index parameter (bad entry point) */
  AMX_ERR_DEBUG,        /* debugger cannot run */
  AMX_ERR_INIT,         /* AMX not initialized (or doubly initialized) */
  AMX_ERR_USERDATA,     /* unable to set user data field (table full) */
  AMX_ERR_INIT_JIT,     /* cannot initialize the JIT */
  AMX_ERR_PARAMS,       /* parameter error */
  AMX_ERR_DOMAIN,       /* domain error, expression result does not fit in range */
  AMX_ERR_GENERAL,      /* general error (unknown or unspecific error) */
};

/*      AMX_FLAG_CHAR16   0x01     no longer used */
#define AMX_FLAG_DEBUG    0x02  /* symbolic info. available */
#define AMX_FLAG_COMPACT  0x04  /* compact encoding */
#define AMX_FLAG_BYTEOPC  0x08  /* opcode is a byte (not a cell) */
#define AMX_FLAG_NOCHECKS 0x10  /* no array bounds checking; no STMT opcode */
#define AMX_FLAG_NTVREG 0x1000  /* all native functions are registered */
#define AMX_FLAG_JITC   0x2000  /* abstract machine is JIT compiled */
#define AMX_FLAG_BROWSE 0x4000  /* busy browsing */
#define AMX_FLAG_RELOC  0x8000  /* jump/call addresses relocated */

#define AMX_EXEC_MAIN   -1      /* start at program entry point */
#define AMX_EXEC_CONT   -2      /* continue from last address */

#define AMX_USERTAG(a,b,c,d)    ((a) | ((b)<<8) | ((long)(c)<<16) | ((long)(d)<<24))

#if !defined AMX_COMPACTMARGIN
  #define AMX_COMPACTMARGIN 64
#endif

/* for native functions that use floating point parameters, the following
 * two macros are convenient for casting a "cell" into a "float" type _without_
 * changing the bit pattern
 */
#if PAWN_CELL_SIZE==32
  #define amx_ftoc(f)   ( * ((cell*)&f) )   /* float to cell */
  #define amx_ctof(c)   ( * ((float*)&c) )  /* cell to float */
#elif PAWN_CELL_SIZE==64
  #define amx_ftoc(f)   ( * ((cell*)&f) )   /* float to cell */
  #define amx_ctof(c)   ( * ((double*)&c) ) /* cell to float */
#else
  #error Unsupported cell size
#endif

#define amx_StrParam(amx,param,result)                                      \
    do {                                                                    \
      cell *amx_cstr_; int amx_length_;                                     \
      amx_GetAddr((amx), (param), &amx_cstr_);                              \
      amx_StrLen(amx_cstr_, &amx_length_);                                  \
      if (amx_length_ > 0 &&                                                \
          ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
        amx_GetString((char*)(result), amx_cstr_, sizeof(*(result))>1, amx_length_ + 1); \
      else (result) = NULL;                                                 \
    } while (0)

uint16_t * AMXAPI amx_Align16(uint16_t *v);
uint32_t * AMXAPI amx_Align32(uint32_t *v);
#if defined _I64_MAX || defined HAVE_I64
  uint64_t * AMXAPI amx_Align64(uint64_t *v);
#endif
int AMXAPI amx_Allot(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
int AMXAPI amx_Callback(AMX *amx, cell index, cell *result, cell *params);
int AMXAPI amx_Cleanup(AMX *amx);
int AMXAPI amx_Clone(AMX *amxClone, AMX *amxSource, void *data);
int AMXAPI amx_Exec(AMX *amx, cell *retval, int index);
int AMXAPI amx_FindNative(AMX *amx, const char *name, int *index);
int AMXAPI amx_FindPublic(AMX *amx, const char *funcname, int *index);
int AMXAPI amx_FindPubVar(AMX *amx, const char *varname, cell *amx_addr);
int AMXAPI amx_FindTagId(AMX *amx, cell tag_id, char *tagname);
int AMXAPI amx_Flags(AMX *amx,uint16_t *flags);
int AMXAPI amx_GetAddr(AMX *amx,cell amx_addr,cell **phys_addr);
int AMXAPI amx_GetNative(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetPublic(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetPubVar(AMX *amx, int index, char *varname, cell *amx_addr);
int AMXAPI amx_GetString(char *dest,const cell *source, int use_wchar, size_t size);
int AMXAPI amx_GetTag(AMX *amx, int index, char *tagname, cell *tag_id);
int AMXAPI amx_GetUserData(AMX *amx, long tag, void **ptr);
int AMXAPI amx_Init(AMX *amx, void *program);
int AMXAPI amx_InitJIT(AMX *amx, void *reloc_table, void *native_code);
int AMXAPI amx_MemInfo(AMX *amx, long *codesize, long *datasize, long *stackheap);
int AMXAPI amx_NameLength(AMX *amx, int *length);
AMX_NATIVE_INFO * AMXAPI amx_NativeInfo(const char *name, AMX_NATIVE func);
int AMXAPI amx_NumNatives(AMX *amx, int *number);
int AMXAPI amx_NumPublics(AMX *amx, int *number);
int AMXAPI amx_NumPubVars(AMX *amx, int *number);
int AMXAPI amx_NumTags(AMX *amx, int *number);
int AMXAPI amx_Push(AMX *amx, cell value);
int AMXAPI amx_PushArray(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells);
int AMXAPI amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar);
int AMXAPI amx_RaiseError(AMX *amx, int error);
int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
int AMXAPI amx_Release(AMX *amx, cell amx_addr);
int AMXAPI amx_SetCallback(AMX *amx, AMX_CALLBACK callback);
int AMXAPI amx_SetDebugHook(AMX *amx, AMX_DEBUG debug);
int AMXAPI amx_SetString(cell *dest, const char *source, int pack, int use_wchar, size_t size);
int AMXAPI amx_SetUserData(AMX *amx, long tag, void *ptr);
int AMXAPI amx_StrLen(const cell *cstring, int *length);
int AMXAPI amx_UTF8Check(const char *string, int *length);
int AMXAPI amx_UTF8Get(const char *string, const char **endptr, cell *value);
int AMXAPI amx_UTF8Len(const cell *cstr, int *length);
int AMXAPI amx_UTF8Put(char *string, char **endptr, int maxchars, cell value);

#if PAWN_CELL_SIZE==16
  #define amx_AlignCell(v) amx_Align16(v)
#elif PAWN_CELL_SIZE==32
  #define amx_AlignCell(v) amx_Align32(v)
#elif PAWN_CELL_SIZE==64 && (defined _I64_MAX || defined HAVE_I64)
  #define amx_AlignCell(v) amx_Align64(v)
#else
  #error Unsupported cell size
#endif

#define amx_RegisterFunc(amx, name, func) \
  amx_Register((amx), amx_NativeInfo((name),(func)), 1);

#if !defined AMX_NO_ALIGN
  #if defined LINUX || defined __FreeBSD__
    #pragma pack()    /* reset default packing */
  #elif defined MACOS && defined __MWERKS__
    #pragma options align=reset
  #else
    #pragma pack(pop) /* reset previous packing */
  #endif
#endif

#ifdef  __cplusplus
}
#endif

#endif /* AMX_H_INCLUDED */


//----------------------------------------------------------
// EOF
