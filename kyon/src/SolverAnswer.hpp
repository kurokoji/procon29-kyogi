#ifndef PROCON29_SOLVER_ANSWER_HPP_
#define PROCON29_SOLVER_ANSWER_HPP_

#include <array>

#include <Siv3D.hpp>

namespace kyon {
struct SolverAnswer {
  Array<int32> blue, red;
  int32 bluePoint, redPoint;

  SolverAnswer();

  std::string to_string();
  friend std::ostream& operator<<(std::ostream&, const SolverAnswer&);
  friend std::istream& operator>>(std::istream&, SolverAnswer&);
};
}

#endif
