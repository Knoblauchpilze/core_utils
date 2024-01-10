
#include "BitReader.hh"

namespace utils {
constexpr auto BITS_IN_A_BYTE = 8u;

BitReader::BitReader(std::ifstream &in)
  : CoreObject("reader")
  , m_in(in)
  , m_pending(BITS_IN_A_BYTE, false)
{
  setService("binary");
}

bool BitReader::done() const noexcept
{
  return !m_in.good();
}

bool BitReader::read() noexcept
{
  if (done())
  {
    return false;
  }

  if (m_bit < 0)
  {
    fetch();
  }

  const auto b = m_pending[m_bit];
  --m_bit;

  return b;
}

void BitReader::fetch() noexcept
{
  // Note that we assume that the file defines an entire
  // amount of bytes (with maybe some padding). If this
  // assumption is not verified we might not get the last
  // bits out of the input stream and so fail to get the
  // last data.
  unsigned char buf = 0u;
  m_in.read(reinterpret_cast<char *>(&buf), sizeof(unsigned char));

  // Parse the content of the byte.
  for (unsigned id = 0u; id < 8u; ++id)
  {
    m_pending[id] = (buf >> id) & 1;
  }

  // Reset the internal counter.
  m_bit = 7u;
}

} // namespace utils
