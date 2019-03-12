#ifndef    STREAM_FORMATTER_HH
# define   STREAM_FORMATTER_HH

# include <string>

namespace utils {

  class StreamFormatter {
    public:

      enum class Color {
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White
      };

      StreamFormatter() = default;

      ~StreamFormatter() = default;

      void
      setStreamColor(std::ostream& stream, const Color& color) const noexcept;

      void
      clearStreamFormat(std::ostream& stream) const noexcept;

    private:

      std::string
      getStringForColor(const Color& color) const noexcept;

      std::string
      getFormatterForColor(const Color& fgColor) const noexcept;
  };

}

# include "StreamFormatter.hxx"

#endif    /* STREAM_FORMATTER_HH */
