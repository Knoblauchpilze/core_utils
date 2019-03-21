#ifndef    UUID_SPECIALIZATION_HH
# define   UUID_SPECIALIZATION_HH

# include "Uuid.hh"
# include <functional>

namespace std {

  template<>
  struct hash<utils::Uuid> {
    inline
    std::size_t operator()(const utils::Uuid& resource) const noexcept {
      std::size_t val = hash<std::string>()(resource.toString());
      return val;
    }
  };

}

#endif    /* UUID_SPECIALIZATION_HH */
