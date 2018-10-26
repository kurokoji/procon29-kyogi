#include "SolverAnswer.hpp"

namespace kyon {
SolverAnswer::SolverAnswer() {}

std::string SolverAnswer::to_string() {
  std::string str = "";

  for (auto& e : blue) {
    str += Format(e).narrow() + "\n";
  }

  for (auto& e : red) {
    str += Format(e).narrow() + "\n";
  }

  str += Format(bluePoint).narrow() + " " + Format(redPoint).narrow() + "\n";

  return str;
}

std::ostream& operator<<(std::ostream& os, const SolverAnswer& md) {
  for (auto& e : md.blue) {
    os << e << std::endl;
  }

  for (auto& e : md.red) {
    os << e << std::endl;
  }

  return os;
}

std::istream& operator>>(std::istream& is, SolverAnswer& md) {
  for (int i = 0; i < 2; i++) {
    int32 tmp;
    is >> tmp;
    md.blue.emplace_back(tmp);
  }

  for (int i = 0; i < 2; i++) {
    int32 tmp;
    is >> tmp;
    md.red.emplace_back(tmp);
  }

  return is;
}
}
