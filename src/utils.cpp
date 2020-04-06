#include "utils.h"

#include <string.h>
#include <string>

#ifdef _DEBUG_OUTPUT_
  #include <iostream>
#endif

namespace ImageToPDF
{
  char* _GetNameNoExtension(const char* filename, char* dst)
  {
      const char delim = '.';
      const char* p = strrchr (filename, delim);
      size_t num = p - filename;
      strncpy(dst, filename, num);
      dst[num] = '\0';
      return dst;
  }

  std::string GetNameNoExtension(const std::string& filename)
  {
      char buf[filename.size()];
      return std::string(_GetNameNoExtension(filename.c_str(), buf ) );
  }

  const char *_BaseName(const char *filename)
  {
    const char delim = '/';
    const char* p = strrchr (filename, delim);

    return p ? p + 1 : filename;
  }

  const char *_Extension(const char *filename)
  {
    const char delim = '.';
    const char* p = strrchr (filename, delim);

    return p ? p + 1 : filename;
  }

  void DebugOutput(const std::__cxx11::string &var)
  {
#ifdef _DEBUG_OUTPUT_
    std::cout << var << std::endl;
#endif
  }

}
