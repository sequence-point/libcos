#ifndef libcos__objects__boolean_hxx_
#define libcos__objects__boolean_hxx_

namespace carousel {

class boolean {
public:
  explicit boolean(bool value) : value_{ value }
  {}

  bool
  value() const
  {
    return value_;
  }

private:
  bool value_;
};

inline bool
operator==(boolean const& lhs, boolean const& rhs)
{
  return lhs.value() == rhs.value();
}

inline bool
operator!=(boolean const& lhs, boolean const& rhs)
{
  return !operator==(lhs, rhs);
}

} // namespace carousel

#endif
