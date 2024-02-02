#include <mach-o/loader.h>

#include <fstream>
#include <string>

namespace qing {
class MachOFile {
 private:
  std::string _file_path;
  mach_header_64 _header;
  load_command _load_cmd;
  std::vector<segment_command_64> _segment;

 public:
  MachOFile(const char* file_path);
  void LoadFile();
  void PrintFileInfo();
};
};  // namespace qing