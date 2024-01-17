/**
 * @file   defs.inl
 * @author Vic P.
 * @brief  Inline for Defines
 */

#ifdef _WIN64
#define vuapi __stdcall
#else  // _WIN32
#define vuapi
#endif // _WIN64

#ifndef MAXPATH
#define MAXPATH MAX_PATH
#endif

#define MAX_NPROCESSES 512
#define MAX_NMODULES   1024

#define INVALID_PID_VALUE -1

#define KiB     1024
#define MiB     KiB*KiB
#define GiB     MiB*KiB

#define KB      1000
#define MB      KB*KB
#define GB      MB*KB

/* Other Definitions */

#define lengthof(a) (sizeof(a) / sizeof(a[0]))

#define VU_ALIGN_UP(v, a) (((v) + ((a) - 1)) & ~((a) - 1))

#define VU_CPP_TRY() try   {
#define VU_CPP_CATCH(type) } catch (type)
// #define VU_CPP_FINALLY() finally // un-supported

#define VU_SEH_TRY() __try {
#define VU_SEH_CATCH(type) } __except (type)
#define VU_SEH_FINALLY() __finally

#ifndef ERROR_INCORRECT_SIZE
#define ERROR_INCORRECT_SIZE 1462L
#endif

#ifndef STRINGIZE
#define STRINGIZE(s) # s
#endif // STRINGIZE

// MSVC
#ifdef _MSC_VER
#define VU_FUNC_INFO __FUNCSIG__
#define VU_FUNC_NAME __FUNCTION__
#endif
// C++ Builder
#ifdef __BCPLUSPLUS__
#define VU_FUNC_INFO __FUNC__
#define VU_FUNC_NAME __FUNC__
#endif
// MingGW
#ifdef __MINGW32__
#define VU_FUNC_INFO __PRETTY_FUNCTION__
#define VU_FUNC_NAME __FUNCTION__
#endif

// VA Arguments

#ifdef _INC_STDARG

template <typename T>
bool fn_cmp_va_args(T v, size_t count, ...)
{
  bool result = false;

  va_list args;
  va_start(args, count);

  for (size_t i = 0; i < count; i++)
  {
    if (v == va_arg(args, T))
    {
      result = true;
      break;
    }
  }

  va_end(args);

  return result;
}

#define VU_CONTAINS(v, n, ...) vu::fn_cmp_va_args((v), (n), __VA_ARGS__)

#endif // _INC_STDARG
