
#include "BitWriter.hh"

namespace utils {

BitWriter::BitWriter(std::ofstream &out)
  : CoreObject("writer")
  , m_out(out)
  , m_pending()
{
  setService("binary");
}

void BitWriter::push(bool b) noexcept
{
  m_pending.push_back(b);

  // Flush to the output stream if needed.
  if (m_pending.size() == 8u)
  {
    flush(false);
  }
}

void BitWriter::flush(bool pad) noexcept
{
  // Create the output byte. The code is inspired from this topic:
  // https://stackoverflow.com/questions/1856514/writing-files-in-bit-form-to-a-file-in-c?rq=1
  unsigned char buf = 0u;

  unsigned id = 0u;
  while (id < m_pending.size())
  {
    // As we traverse the bits in reverse order (as we're
    // decrementing the internal counter), we will register
    // the bits in the same order as we read them from the
    // value.
    buf <<= 1;
    if (m_pending[id])
    {
      buf |= 0x1;
    }

    ++id;
  }

  // Add padding.
  while (id < 8u)
  {
    buf <<= 1;

    if (pad)
    {
      buf |= 0x1;
    }

    ++id;
  }

  m_out.write(reinterpret_cast<char *>(&buf), sizeof(unsigned char));

  // Clear pending queue of bits to be flushed.
  m_pending.clear();
}

} // namespace utils
