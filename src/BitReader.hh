#ifndef    BIT_READER_HH
# define   BIT_READER_HH

# include <vector>
# include <fstream>
# include "CoreObject.hh"

namespace utils {

  class BitReader: public CoreObject {
    public:

      /**
       * @brief - Generate a new bit reader which will read a file
       *          a get bits individually.
       * @param in - the input stream from which bits should be
       *             read. We assume that the stream is already
       *             opened and valid.
       */
      BitReader(std::ifstream& in);

      /**
       * @brief - Whether the stream reached its end.
       * @return - `true` if the stream is over.
       */
      bool
      done() const noexcept;

      /**
       * @brief - Read a single bit from the input file. In case the
       *          stream is over `false` will always be returned.
       * @return - the value of the next bit.
       */
      bool
      read() noexcept;

    private:

      /**
       * @brief - Fetch the next bits from the input stream.
       */
      void
      fetch() noexcept;

    private:

      /**
       * @brief - Where bits will be saved.
       */
      std::ifstream& m_in;

      /**
       * @brief - The pending bits to read. Note that the
       *          bits are stored in the reverse order as
       *          they are in the file: typically the last
       *          bit of the vector is the last value of
       *          the byte read from the file.
       *          So we have to read the bits from the end
       *          of the vector to the beginning.
       */
      std::vector<bool> m_pending;

      /**
       * @brief - In order to avoid allocating and freeing
       *          the bits each time we read them we use an
       *          index which references the position of the
       *          next bit to read.
       */
      int m_bit;
  };

}

#endif    /* BIT_READER_HH */
