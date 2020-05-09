#ifndef libcos__objects__undefined_hxx_
#define libcos__objects__undefined_hxx_

namespace carousel {

class undefined {
public:
};

inline bool
operator==(undefined const&, undefined const&)
{
  return false;
}

inline bool
operator!=(undefined const&, undefined const&)
{
  return true;
}

} // namespace carousel

#endif
