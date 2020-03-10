#pragma once

#include <string>

namespace ImageToPDF
{
  char* _GetNameNoExtension(const char* filename, char* dst);
  const char *_BaseName(const char* filename);
  const char* _Extension(const char* filename);

  std::string GetNameNoExtension(const std::string& filename);
}
