#include "MoveData.hpp"

namespace kyon {
MoveData::MoveData() {}

std::string MoveData::to_string() {
  std::string str = "";

  for (auto& e : blue) {
    str += Format(e.first).narrow() + " " + Format(e.second).narrow() + "\n";
  }

  for (auto& e : red) {
    str += Format(e.first).narrow() + " " + Format(e.second).narrow() + "\n";
  }

  return str;
}

std::ostream& operator<<(std::ostream& os, const MoveData& md) {
  for (auto& e : md.blue) {
    os << e.first << " " << e.second << std::endl;
  }

  for (auto& e : md.red) {
    os << e.first << " " << e.second << std::endl;
  }

  return os;
}

std::istream& operator>>(std::istream& is, MoveData& md) {
  for (auto& e : md.blue) {
    is >> e.first >> e.second;
  }

  for (auto& e : md.red) {
    is >> e.first >> e.second;
  }

  return is;
}
}
