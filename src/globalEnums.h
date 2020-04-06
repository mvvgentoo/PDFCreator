#include <string>
#include <map>
#include "utils.h"

namespace ImageToPDF
{
  enum class ListOfConverters : char
  {
      PDF = 0,
      PNG
  };

  static std::map<std::string, std::string> s_Mapping
  {
    {"pdf", "PDF"}
  };

  namespace ID
  {
    class FileName
    {
      public:
        FileName(const char* name) : m_FullName(name),
                                     m_ShortName(_BaseName(name)),
                                     m_Extension(_Extension(name)) {}
      private:
        const char* m_FullName;
        const char* m_ShortName;
        const char* m_Extension;
    };
  };
}
