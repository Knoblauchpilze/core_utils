
#include "RNG.hh"

namespace utils {

RNG::RNG(int seed)
  : CoreObject("rng")
  ,

  m_rng(seed)
{}

} // namespace utils
