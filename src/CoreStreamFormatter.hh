#ifndef    CORE_STREAM_FORMATTER_HH
# define   CORE_STREAM_FORMATTER_HH

# include <string>

namespace core {
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
}

# include "CoreStreamFormatter.hxx"

#endif    /* CORE_STREAM_FORMATTER_HH */
