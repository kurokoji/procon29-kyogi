#include "ProblemState.hpp"

namespace kyon {
ProblemState::ProblemState() {}
std::ostream& operator<<(std::ostream& os, const ProblemState& ps) {
  os << ps.field.back().size() << " " << ps.field.size() << std::endl;

  for (const auto& v : ps.field) {
    for (size_t i = 0; i < v.size(); ++i) {
      os << v[i] << (i == v.size() - 1 ? '\n' : ' ');
    }
  }

  for (const auto& v : ps.fieldColor) {
    for (size_t i = 0; i < v.size(); ++i) {
      os << static_cast<int32>(v[i]) << (i == v.size() - 1 ? '\n' : ' ');
    }
  }

  for (const auto& agent : ps.blue) {
    os << agent.first << " " << agent.second << std::endl;
  }

  for (const auto& agent : ps.red) {
    os << agent.first << " " << agent.second << std::endl;
  }

  return os;
}
std::istream& operator>>(std::istream& is, ProblemState& ps) {
  // int32 h, w;
  is >> ps.h >> ps.w;

  ps.field.clear();
  ps.fieldColor.clear();
  for (size_t i = 0; i < ps.h; ++i) {
    ps.field.emplace_back(Array<int32>(ps.w));
    for (size_t j = 0; j < ps.w; ++j) {
      is >> ps.field[i][j];
    }
  }

  for (size_t i = 0; i < ps.h; ++i) {
    ps.fieldColor.emplace_back(Array<int32>(ps.w));
      for (size_t j = 0; j < ps.w; ++j) {
        is >> ps.fieldColor[i][j];
      }
  }

  for (auto& e : ps.blue) {
    is >> e.first >> e.second;
  }

  for (auto& e : ps.red) {
    is >> e.first >> e.second;
  }


  return is;
}
}
