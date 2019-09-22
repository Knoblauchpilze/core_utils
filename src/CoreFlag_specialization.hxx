#ifndef    CORE_FLAG_SPECIALIZATION_HXX
# define   CORE_FLAG_SPECIALIZATION_HXX

# include "CoreFlag.hh"

namespace utils {

  template <int N>
  inline
  bool
  operator==(const typename CoreFlag<N>::BitDesc& lhs,
             const typename CoreFlag<N>::BitDesc& rhs) noexcept
  {
    return lhs.name == rhs.name && lhs.defVal == rhs.defVal;
  }

}

#endif    /* CORE_FLAG_SPECIALIZATION_HXX */
