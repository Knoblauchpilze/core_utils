
#pragma once

#include "CoreObject.hh"
#include <fstream>
#include <vector>

namespace utils {

class BitWriter : public CoreObject
{
  public:
  /// @brief - Generate a new bit writer which will accumulate bits and output them
  /// in the provided stream.
  /// @param out - the output stream to which bits should be saved. We assume that
  /// the stream is already opened and valid.
  BitWriter(std::ofstream &out);

  /// @brief - Push the value of a single bit to the output stream. It might be
  /// that nothing is actually written just yet in case we didn't accumulate
  /// enough bits.
  /// @param b - the value to accumulate.
  void push(bool b) noexcept;

  /// @brief - Flush the remaining content of the bits that might be pending for
  /// writing.
  /// @param pad - the value to use as padding.
  void flush(bool pad) noexcept;

  private:
  ///@brief - Where bits will be saved.
  std::ofstream &m_out;

  /// @brief - The pending bits to save.
  std::vector<bool> m_pending;
};

} // namespace utils
