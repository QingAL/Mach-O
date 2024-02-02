#include "macho_file.h"

int main(int argc, char *argv[]) {
  auto macho_file = qing::MachOFile("./Mach_O");
  macho_file.LoadFile();
  macho_file.PrintFileInfo();
  return 0;
}
