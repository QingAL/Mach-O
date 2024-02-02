
#include "macho_file.h"

#include <fstream>
#include <iostream>

#include "error_code.h"

qing::MachOFile::MachOFile(const char* file_path) { _file_path = file_path; }

void qing::MachOFile::LoadFile() {
  // header
  if (!_file_path.c_str()) {
    std::cerr << "Invalid Mach-O file path." << std::endl;
    exit(INVALID_FILE);
  }
  std::ifstream input_file(_file_path.c_str(), std::ios::binary);
  if (!input_file) {
    std::cerr << "Failed to open file." << _file_path << std::endl;
    exit(INVALID_FILE);
  }
  input_file.read(reinterpret_cast<char*>(&_header), sizeof(_header));
  if (_header.magic != MH_MAGIC_64) {
    std::cerr << "Invalid Mach-O file" << std::endl;
    exit(INVALID_FILE);
  }

  // load_command
  for (int i = 0; i < _header.ncmds; i++) {
    load_command lc;
    input_file.read(reinterpret_cast<char*>(&lc), sizeof(lc));
    _load_cmd.push_back(lc);
    input_file.seekg(lc.cmdsize - sizeof(lc), std::ios::cur);
  }
}

void qing::MachOFile::PrintFileInfo() {
  std::cout << "---------------------- header ----------------------\n";
  std::cout << "CPU Type: " << _header.cputype << std::endl;
  std::cout << "CPU Subtype: " << _header.cpusubtype << std::endl;
  std::cout << "File Type: " << _header.filetype << std::endl;
  std::cout << "Number of Commands: " << _header.ncmds << std::endl;
  std::cout << "Size of Commands: " << _header.sizeofcmds << std::endl;
  std::cout << "Flags: " << _header.flags << std::endl;

  std::cout << "---------------------- load_command ----------------------\n";
  for (int i = 0; i < _load_cmd.size(); ++i) {
    std::cout << "cmd: " << _load_cmd[i].cmd << std::endl;
    std::cout << "cmdsize: " << _load_cmd[i].cmdsize << std::endl;
  }
}