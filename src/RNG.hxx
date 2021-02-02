#ifndef    RNG_HXX
# define   RNG_HXX

# include "RNG.hh"

namespace utils {

  inline
  RNG
  RNG::createRandomRNG() noexcept {
    // Create a random device. This will be used to
    // provide the seed of the RNG. This articla is
    // nice to explain how things work here:
    // https://diego.assencio.com/?index=6890b8c50169ef45b74db135063c227c
    std::random_device device;

    // Use this as a seed.
    return RNG(device());
  }

  inline
  int
  RNG::rndInt(int min, int max) noexcept {
    // Generate an integer distribution and use it.
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_rng);
  }

  inline
  float
  RNG::rndFloat(float min, float max) noexcept {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_rng);
  }

  inline
  float
  RNG::rndAngle(float min, float max) noexcept {
    return rndFloat(min, max);
  }

  inline
  std::ostream&
  RNG::operator<<(std::ostream& out) const {
    out << m_rng;
    return out;
  }

  inline
  std::istream&
  RNG::operator>>(std::istream& in) {
    in >> m_rng;
    return in;
  }

}

inline
std::ostream&
operator<<(std::ostream& out, const utils::RNG& rng) noexcept {
  rng << out;
  return out;
}

inline
std::istream&
operator>>(std::istream& in, utils::RNG& rng) noexcept {
  rng >> in;
  return in;
}

#endif    /* RNG_HXX */
