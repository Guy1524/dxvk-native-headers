#ifndef WINDOWS_H
#define WINDOWS_H

#include <inttypes.h>
#include <cstring>

// barebones windows.h for compatibility

// basic integer definitions
typedef uint8_t        BYTE;
typedef uint16_t       WORD;
typedef uint32_t       DWORD;
typedef uint32_t       ULONG;
typedef int32_t        LONG;
typedef uint32_t       UINT;
typedef int32_t        INT;
typedef int            BOOL;
typedef uint8_t        UINT8;
typedef float          FLOAT;
typedef uint16_t       USHORT;
typedef uint64_t       ULONGLONG;
typedef uint64_t       ULONG_PTR;
typedef uint64_t       UINT64;
typedef int64_t        LONGLONG;
typedef ULONG_PTR      SIZE_T;

typedef struct _LARGE_INTEGER {
  LONGLONG QuadPart;
} LARGE_INTEGER;

// more from windef

typedef void  *PVOID;
typedef void  *LPVOID;
typedef PVOID  HANDLE;
typedef HANDLE HMODULE;
typedef HANDLE HDC;
typedef HANDLE HINSTANCE;
typedef HANDLE HWND;
typedef HANDLE HMONITOR;

typedef struct _RECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT, *PRECT;

typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT;

typedef struct tagSIZE
{
    LONG cx;
    LONG cy;
} SIZE, *PSIZE, *LPSIZE;

// user32 stuff

#define SWP_NOZORDER 0x0004
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020
#define SWP_SHOWWINDOW 0x0040

#define HWND_TOPMOST ((HWND)-1)

#define ENUM_REGISTRY_SETTINGS ((DWORD) -2)

#define WS_OVERLAPPED 0x00000000
#define WS_VISIBLE 0x10000000
#define WS_BORDER 0x00800000
#define WS_DLGFRAME 0x00400000
#define WS_SYSMENU 0x00080000
#define WS_THICKFRAME 0x00040000
#define WS_MINIMIZEBOX 0x00020000
#define WS_MAXIMIZEBOX 0x00010000
#define WS_CAPTION (WS_BORDER | WS_DLGFRAME)
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME| WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

#define WS_EX_TOPMOST 0x00000008
#define WS_EX_WINDOWEDGE 0x00000100
#define WS_EX_CLIENTEDGE 0x00000200
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)

// strings

typedef const char *LPCSTR;
typedef char *LPSTR;

// errors
typedef LONG HRESULT;

#define _HRESULT_TYPEDEF_(x) ((HRESULT)x)

#define S_OK    _HRESULT_TYPEDEF_(0)
#define S_FALSE _HRESULT_TYPEDEF_(1)

#define E_NOTIMPL     _HRESULT_TYPEDEF_(0x80004001)
#define E_NOINTERFACE _HRESULT_TYPEDEF_(0x80004002)
#define E_FAIL        _HRESULT_TYPEDEF_(0x80004005)
#define E_INVALIDARG  _HRESULT_TYPEDEF_(0x80070057)
#define E_POINTER     _HRESULT_TYPEDEF_(0x80004003)

#define DXGI_ERROR_INVALID_CALL            _HRESULT_TYPEDEF_(0x887a0001)
#define DXGI_ERROR_NOT_FOUND               _HRESULT_TYPEDEF_(0x887a0002)
#define DXGI_ERROR_MORE_DATA               _HRESULT_TYPEDEF_(0x887a0003)
#define DXGI_ERROR_UNSUPPORTED             _HRESULT_TYPEDEF_(0x887a0004)
#define DXGI_ERROR_WAS_STILL_DRAWING       _HRESULT_TYPEDEF_(0x887a000a)
#define DXGI_ERROR_DRIVER_INTERNAL_ERROR   _HRESULT_TYPEDEF_(0x887a0020)
#define DXGI_ERROR_NOT_CURRENTLY_AVAILABLE _HRESULT_TYPEDEF_(0x887a0022)

#define SUCCEEDED(stat) ((HRESULT)(stat)>=0)
#define FAILED(stat)    ((HRESULT)(stat)<0)

// COM

struct GUID{
    DWORD Data1;
    WORD  Data2;
    WORD  Data3;
    BYTE  Data4[8];

    bool operator ==(const GUID& other) const
    {
        return this->Data1 == other.Data1
            && this->Data2 == other.Data2
            && this->Data3 == other.Data3
            && !std::memcmp(this->Data4, other.Data4, 8);
    
    }

    bool operator ==(const GUID* other) const
    {
        return this->Data1 == other->Data1
            && this->Data2 == other->Data2
            && this->Data3 == other->Data3
            && !std::memcmp(this->Data4, other->Data4, 8);
    
    }
};

typedef const GUID& REFIID;
typedef const GUID& REFGUID;

typedef GUID IID;

# ifdef INITGUID
#  ifndef __cplusplus
#   define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        const GUID name __attribute__((visibility("hidden"))); \
        const GUID name = \
    { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 }}
#  else
#   define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        extern "C" const GUID name __attribute__((visibility("hidden"))); \
        extern "C" const GUID name = \
    { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 }}
#  endif
# else
#  define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        extern "C" const GUID name __attribute__((visibility("hidden")));
# endif

template<typename T> const GUID &__dxvk_uuidof();

# define __CRT_UUID_DECL(type, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C++" \
    { \
        template<> inline const GUID &__dxvk_uuidof<type>() \
        { \
            static const IID __uuid_inst = {l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}}; \
            return __uuid_inst; \
        } \
        template<> inline const GUID &__dxvk_uuidof<type *>() \
        { \
            return __dxvk_uuidof<type>(); \
        } \
    }

# define __uuidof(type) __dxvk_uuidof<__typeof(type)>()

// boilerplate COM

# define BEGIN_INTERFACE
# define END_INTERFACE
# define MIDL_INTERFACE(x) struct

# define interface struct
# define STDMETHOD(m) virtual HRESULT STDMETHODCALLTYPE m
# define STDMETHOD_(t,m) virtual t STDMETHODCALLTYPE m
# define PURE =0
# define THIS_
# define THIS void
# define DECLARE_INTERFACE(i)    interface i
# define DECLARE_INTERFACE_(i,b) interface i : public b

# define DECLSPEC_SELECTANY __attribute__((weak))

# ifdef __x86_64__
#  define __stdcall __attribute__((ms_abi))
# else
#  if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) || defined(__APPLE__)
#   define __stdcall __attribute__((__stdcall__)) __attribute__((__force_align_arg_pointer__))
#  else
#   define __stdcall __attribute__((__stdcall__))
#  endif
# endif
# define WINAPI __stdcall
# define STDMETHODCALLTYPE __stdcall

# define __C89_NAMELESS
# define __C89_NAMELESSUNIONNAME
# define __C89_NAMELESSUNIONNAME1
# define __C89_NAMELESSUNIONNAME2

# define COM_NO_WINDOWS_H

// misc.
typedef unsigned short WCHAR;
typedef const WCHAR *LPCWSTR;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _LUID {
  DWORD LowPart;
  LONG  HighPart;
} LUID, *PLUID;

#define TRUE  1
#define FALSE 0

#define ENUM_CURRENT_SETTINGS  ((DWORD) -1)

#define __MSABI_LONG(x) x

#endif