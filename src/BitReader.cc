
# include "BitReader.hh"

namespace utils {

  BitReader::BitReader(std::ifstream& in):
    CoreObject("reader"),

    m_in(in),

    m_pending(8u, false),
    m_bit(-1)
  {
    setService("binary");
  }

  bool
  BitReader::done() const noexcept {
    return !m_in.good();
  }

  bool
  BitReader::read() noexcept {
    // In case the stream is over, return a default value.
    if (done()) {
      return false;
    }

    // In case no elements are available, fetch new ones.
    if (m_bit < 0) {
      fetch();
    }

    // Get the next bit.
    bool b = m_pending[m_bit];
    --m_bit;

    return b;
  }

  void
  BitReader::fetch() noexcept {
    // Note that we assume that the file defines an entire
    // amount of bytes (with maybe some padding). If this
    // assumption is not verified we might not get the last
    // byte out of the input stream and so fail to get the
    // last data.
    unsigned char buf = 0u;
    m_in.read(reinterpret_cast<char*>(&buf), sizeof(unsigned char));

    // Parse the content of the byte.
    for (unsigned id = 0u ; id < 8u ; ++id) {
      m_pending[id] = (buf >> id) & 1;
    }

    // Reset the internal counter.
    m_bit = 7u;
  }

}
