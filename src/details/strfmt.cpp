/**
 * @file   strfmt.cpp
 * @author Vic P.
 * @brief  Implementation for String Format
 */

#include "strfmt.h"
#include "lazy.h"

#include <math.h>
#include <iomanip>

namespace vu
{

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996 4834 26451 26812)
#endif // _MSC_VER

const std::string  VU_TITLE_BOXA =  "Vutils";
const std::wstring VU_TITLE_BOXW = L"Vutils";

int vuapi get_format_length_vl_A(const std::string format, va_list args)
{
  int N = -1;

  if (Initialize_DLL_MISC() != VU_OK)
  {
    return N;
  }

  #ifdef _MSC_VER
  N = _vscprintf(format.c_str(), args) + 1;
  #else
  N = pfn_vscprintf(format.c_str(), args) + 1;
  #endif

  return N;
}

int vuapi get_format_length_vl_W(const std::wstring format, va_list args)
{
  int N = -1;

  if (Initialize_DLL_MISC() != VU_OK)
  {
    return N;
  }

  #ifdef _MSC_VER
  N = _vscwprintf(format.c_str(), args) + 1;
  #else
  N = pfn_vscwprintf(format.c_str(), args) + 1;
  #endif

  return N;
}

int vuapi get_format_length_A(const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto N = get_format_length_vl_A(format, args);

  va_end(args);

  return N;
}

int vuapi get_format_length_W(const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto N = get_format_length_vl_W(format, args);

  va_end(args);

  return N;
}

std::string vuapi format_vl_A(const std::string format, va_list args)
{
  std::string s;
  s.clear();

  auto N = get_format_length_vl_A(format, args);
  if (N <= 0)
  {
    return s;
  }

  std::unique_ptr<char[]> p(new char [N]);
  if (p == nullptr)
  {
    return s;
  }

  ZeroMemory(p.get(), N);

  #ifdef _MSC_VER
  vsnprintf(p.get(), N, format.c_str(), args);
  #else
  pfn_vsnprintf(p.get(), N, format.c_str(), args);
  #endif

  s.assign(p.get());

  return s;
}

std::wstring vuapi format_vl_W(const std::wstring format, va_list args)
{
  std::wstring s;
  s.clear();

  auto N = get_format_length_vl_W(format, args);
  if (N <= 0)
  {
    return s;
  }

  std::unique_ptr<wchar[]> p(new wchar [N]);
  if (p == nullptr)
  {
    return s;
  }

  ZeroMemory(p.get(), 2*N);

  #ifdef _MSC_VER
  vswprintf(p.get(), format.c_str(), args);
  #else
  pfn_vswprintf(p.get(), N, format.c_str(), args);
  #endif

  s.assign(p.get());

  return s;
}

std::string vuapi format_A(const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_A(format, args);

  va_end(args);

  return s;
}

std::wstring vuapi format_W(const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_W(format, args);

  va_end(args);

  return s;
}

void vuapi msg_debug_A(const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_A(format, args);

  va_end(args);

  OutputDebugStringA(s.c_str());
}

void vuapi msg_debug_W(const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_W(format, args);

  va_end(args);

  OutputDebugStringW(s.c_str());
}

int vuapi msg_box_A(const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_A(format, args);

  va_end(args);

  return MessageBoxA(GetActiveWindow(), s.c_str(), VU_TITLE_BOXA.c_str(), MB_ICONINFORMATION);
}

int vuapi msg_box_W(const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_W(format, args);

  va_end(args);

  return MessageBoxW(GetActiveWindow(), s.c_str(), VU_TITLE_BOXW.c_str(), MB_ICONINFORMATION);
}

int vuapi msg_box_A(HWND hwnd, const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_A(format, args);

  va_end(args);

  return MessageBoxA(hwnd, s.c_str(), VU_TITLE_BOXA.c_str(), MB_ICONINFORMATION);
}

int vuapi msg_box_W(HWND hwnd, const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_W(format, args);

  va_end(args);

  return MessageBoxW(hwnd, s.c_str(), VU_TITLE_BOXW.c_str(), MB_ICONINFORMATION);
}

int vuapi msg_box_A(HWND hwnd, uint type, const std::string& caption, const std::string format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_A(format, args);

  va_end(args);

  return MessageBoxA(hwnd, s.c_str(), caption.c_str(), type);
}

int vuapi msg_box_W(HWND hwnd, uint type, const std::wstring& caption, const std::wstring format, ...)
{
  va_list args;
  va_start(args, format);

  auto s = format_vl_W(format, args);

  va_end(args);

  return MessageBoxW(hwnd, s.c_str(), caption.c_str(), type);
}

std::string vuapi get_last_error_A(ulong code)
{
  if (code == -1)
  {
    code = ::GetLastError();
  }

  return std::system_category().message(code);

  // char* ptr_error_message = nullptr;
  // 
  // FormatMessageA(
  //   FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
  //   NULL,
  //   code,
  //   LANG_USER_DEFAULT,
  //   (char*)&ptr_error_message,
  //   0,
  //   NULL
  // );
  // 
  // std::string s(ptr_error_message);
  // s = trim_string_A(s);
  // 
  // return s;
}

std::wstring vuapi get_last_error_W(ulong code)
{
  if (code == -1)
  {
    code = ::GetLastError();
  }

  const auto s = get_last_error_A(code);

  return to_string_W(s);

  // wchar* ptr_error_message = nullptr;
  // 
  // FormatMessageW(
  //   FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
  //   NULL,
  //   code,
  //   LANG_USER_DEFAULT,
  //   (wchar*)&ptr_error_message,
  //   0,
  //   NULL
  // );
  // 
  // std::wstring s(ptr_error_message);
  // s = trim_string_W(s);
  // 
  // return s;
}

std::string vuapi get_format_string_for_number(std::string type_id)
{
  /* MinGW
    i -> int
    l -> long
    x -> long long
    j -> unsigned
    m -> unsigned long
    y -> unsigned long long
    f -> float
    d -> double
    e -> long double
  */

  std::string fs = "";

  if (type_id == "i")
  {
    fs = "%d";
  }
  else if (type_id == "l")
  {
    fs = "%ld";
  }
  else if (type_id == "x")
  {
    fs = "lld";
  }
  else if (type_id == "j")
  {
    fs = "%u";
  }
  else if (type_id == "m")
  {
    fs = "%lu";
  }
  else if (type_id == "y")
  {
    fs = "%llu";
  }
  else if (type_id == "f")
  {
    fs = "%f";
  }
  else if (type_id == "d")
  {
    fs = "%e";
  }
  else if (type_id == "e")
  {
    fs = "%Le";
  }
  else
  {
    fs = "";
  }

  return fs;
}

std::string vuapi date_time_to_string_A(const time_t t)
{
  std::string s = format_date_time_A(t, "%H:%M:%S %d/%m/%Y");
  return s;
}

std::wstring vuapi date_time_to_string_W(const time_t t)
{
  std::wstring s = format_date_time_W(t, L"%H:%M:%S %d/%m/%Y");
  return s;
}

std::string vuapi format_date_time_A(const time_t t, const std::string format)
{
  std::string s;
  s.clear();

  std::unique_ptr<char[]> p(new char [MAXBYTE]);
  if (p == nullptr)
  {
    return s;
  }

  tm lt = {0};

  ZeroMemory(p.get(), MAX_SIZE);

  #if defined(_MSC_VER) && (_MSC_VER > 1200) // Above VC++ 6.0
  localtime_s(&lt, &t);
  #else
  memcpy((void*)&lt, localtime(&t), sizeof(tm));
  #endif

  strftime(p.get(), MAX_SIZE, format.c_str(), &lt);

  s.assign(p.get());

  return s;
}

std::wstring vuapi format_date_time_W(const time_t t, const std::wstring format)
{
  std::wstring s;
  s.clear();

  std::unique_ptr<wchar[]> p(new wchar [MAXBYTE]);
  if (p == nullptr) return s;

  tm lt = {0};

  ZeroMemory(p.get(), 2*MAXBYTE);

  #if defined(_MSC_VER) && (_MSC_VER > 1200) // Above VC++ 6.0
  localtime_s(&lt, &t);
  #else
  memcpy((void*)&lt, localtime(&t), sizeof(tm));
  #endif

  wcsftime(p.get(), 2*MAXBYTE, format.c_str(), &lt);

  s.assign(p.get());

  return s;
}

void vuapi hex_dump(const void* data, int size)
{
  const int DEFAULT_DUMP_COLUMN = 16;

  int i = 0;
  uchar buffer[DEFAULT_DUMP_COLUMN + 1], *ptr_data = (uchar*)data;

  for (int i = 0; i < size; i++)
  {
    if (i % DEFAULT_DUMP_COLUMN == 0)
    {
      if (i != 0)
      {
        printf("  %s\n", buffer);
      }

      printf("  %04x ", i);
    }

    if (i % DEFAULT_DUMP_COLUMN == 8) printf(" ");

    printf(" %02x", ptr_data[i]);

    if (ptr_data[i] < 0x20 || ptr_data[i] > 0x7E)
    {
      buffer[i % DEFAULT_DUMP_COLUMN] = '.';
    }
    else
    {
      buffer[i % DEFAULT_DUMP_COLUMN] = ptr_data[i];
    }

    buffer[(i % DEFAULT_DUMP_COLUMN) + 1] = '\0';
  }

  while (i % DEFAULT_DUMP_COLUMN != 0)
  {
    printf("   ");
    i++;
  }

  printf("  %s\n", buffer);
}

std::string vuapi format_bytes_A(long long bytes, data_unit unit, int digits)
{
  std::string result = "";

  if (bytes < 0 || digits < 0)
  {
    return result;
  }

  // Max positive number of long long is 2*63 ~ 9{18}.
  // So log(9{18}, 1000-1024) ~ 6-7 array index.
  static const char* SIUnits[]  = { "B", "KB", "MB", "GB", "TB", "PB", "EB" };
  static const char* IECUnits[] = { "B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB" };
  static const auto  Units = unit == data_unit::IEC ? IECUnits : SIUnits;

  const auto log2l = [](long double v) -> long double
  {
    const long double M_LOG_2E = 1.44269504088896340736;
    return logl(v) * M_LOG_2E;
  };

  const auto logn = [&](long double v, long double n) -> long double
  {
    return log2l(v) / log2l(n);
  };

  int idx = 0;

  if (bytes > 0)
  {
    idx = (int)logn(static_cast<long double>(bytes), static_cast<long double>(unit));

    std::string fmt = "%0.";
    fmt += std::to_string(digits);
    fmt += "f %s";

    result = format_A(fmt, float(bytes / powl(static_cast<long double>(unit), idx)), Units[idx]);
  }

  return result;
}

std::wstring vuapi format_bytes_W(long long bytes, data_unit unit, int digits)
{
  return to_string_W(format_bytes_A(bytes, unit, digits));
}

std::string vuapi to_hex_string_A(const byte* ptr, const size_t size)
{
  std::stringstream ss;

  for (size_t i = 0; i < size; i++)
  {
    ss << std::hex << std::setfill('0') << std::setw(2) << int(ptr[i]);
  }

  return ss.str();
}

std::wstring vuapi to_hex_string_W(const byte* ptr, const size_t size)
{
  auto s = to_hex_string_A(ptr, size);
  return to_string_W(s);
}

bool vuapi to_hex_bytes_A(const std::string& text, std::vector<byte>& bytes)
{
  bytes.clear();

  auto s = trim_string_A(text);
  s = replace_string_A(s, " ", "");

  const size_t byte_width = 2;

  if (s.size() % byte_width != 0)
  {
    throw "invalid hex string";
  }

  bytes.reserve(s.size() / byte_width);

  for (size_t i = 0; i < s.size(); i += byte_width)
  {
    const std::string e = s.substr(i, byte_width);
    if (!isxdigit(e[0]) || !isxdigit(e[1]))
    {
      throw "invalid hex string";
    }
    
    bytes.push_back((byte)strtoul(e.c_str(), nullptr, 16));
  }

  return true;
}

bool vuapi to_hex_bytes_W(const std::wstring& text, std::vector<byte>& bytes)
{
  const auto s = to_string_A(text);
  return to_hex_bytes_A(s, bytes);
}

void vuapi url_encode_A(const std::string& text, std::string& result)
{
  auto s = to_string_W(text);
  std::wstring res = L"";
  url_encode_W(s, res);
  result = to_string_A(res);
}

void vuapi url_encode_W(const std::wstring& text, std::wstring& result)
{
  result.clear();

  for (const auto& c : text)
  {
    // uncomment this if you want to encode spaces with +
    // if (c==' ')
    // {
    //   result += '+';
    // }
    // else
    if (iswalnum(c) || c == L'-' || c == L'_' || c == L'.' || c == L'~')
    {
      result += c;
    }
    else
    {
      wchar_t s[10] = {0};
      #ifdef __MINGW32__
      _itow_s(c, s, ARRAYSIZE(s), 16);
      #else // _MSC_VER
      _itow_s(c, s, 16);
      #endif
      result += c < 16 ? L"%0" : L"%";
      result += s;
    }
  }
}

void vuapi url_decode_A(const std::string& text, std::string& result)
{
  auto s = to_string_W(text);
  std::wstring res = L"";
  url_decode_W(s, res);
  result = to_string_A(res);
}

void vuapi url_decode_W(const std::wstring& text, std::wstring& result)
{
  result.clear();

  for (size_t i = 0; i < text.length(); i++)
  {
    if (text[i] != L'%')
    {
      result += text[i] == L'+' ? L' ' : text[i];
    }
    else
    {
      int v = 0;
      swscanf_s(text.substr(i + 1, 2).c_str(), L"%x", &v);
      result += wchar_t(v);
      i += 2;
    }
  }
}

/**
 * VariantX
 */

template <class T>
VariantT<T>::VariantT()
{
  m_data.reset(new T);
}

template <class T>
VariantT<T>::VariantT(const VariantT& right)
{
  *this = right;
}

template <class T>
VariantT<T>::~VariantT()
{
}

template <class T>
bool vu::VariantT<T>::empty() const
{
  return m_data->str().empty();
}

template <class T>
VariantT<T>& VariantT<T>::operator=(const VariantT<T>& right)
{
  if (this != &right)
  {
    auto ptr = new T();
    *ptr << right.m_data->str();
    this->m_data.reset(ptr);
  }

  return *this;
}

template <class T>
int VariantT<T>::to_int() const
{
  int result = 0;
  *m_data >> result;
  return result;
}

template <class T>
unsigned int VariantT<T>::to_uint() const
{
  unsigned int result = 0;
  *m_data >> result;
  return result;
}

template <class T>
__int64 VariantT<T>::to_int64() const
{
  __int64 result = 0;
  *m_data >> result;
  return result;
}

template <class T>
unsigned __int64 VariantT<T>::to_uint64() const
{
  unsigned __int64 result = 0;
  *m_data >> result;
  return result;
}

template <class T>
bool VariantT<T>::to_bool() const
{
  return to_int() != 0;
}

template <class T>
float VariantT<T>::to_float() const
{
  float result = 0.F;
  *m_data >> result;
  return result;
}

template <class T>
double VariantT<T>::to_double() const
{
  double result = 0.;
  *m_data >> result;
  return result;
}

template <class T>
std::unique_ptr<byte[]> VariantT<T>::to_bytes() const
{
  std::vector<byte> bytes;

  if (typeid(T) == typeid(std::stringstream))
  {
    to_hex_bytes_A((const char*)m_data->str().c_str(), bytes);
  }
  else if (typeid(T) == typeid(std::wstringstream))
  {
    to_hex_bytes_W((const wchar_t*)m_data->str().c_str(), bytes);
  }
  else
  {
    assert(0 && "invalid template class");
  }

  if (bytes.empty())
  {
    return nullptr;
  }

  std::unique_ptr<byte[]> result(new byte[bytes.size()]);
  for (size_t i = 0; i < bytes.size(); i++) result.get()[i] = bytes[i]; // std::move(bytes.cbegin(), bytes.cend(), result.get());
  return result;
}

/**
 * VariantA
 */

VariantA::VariantA() : VariantT()
{
}

VariantA::VariantA(const VariantA& right) : VariantT(right)
{
}

VariantA::~VariantA()
{
}

std::string VariantA::to_string() const
{
  return m_data->str();
}

template class VariantTA;

/**
 * VariantW
 */

VariantW::VariantW() : VariantT()
{
}

VariantW::VariantW(const VariantW& right) : VariantT(right)
{
}

VariantW::~VariantW()
{
}

std::wstring VariantW::to_string() const
{
  return m_data->str();
}

template class VariantTW;

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

} // namespace vu