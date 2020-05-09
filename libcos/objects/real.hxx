#ifndef libcos__objects__real_hxx_
#define libcos__objects__real_hxx_

namespace carousel {

class real {
public:
  explicit real(double value) : value_{ value }
  {}

  double
  value() const
  {
    return value_;
  }

private:
  double value_;
};

inline bool
operator==(real const& lhs, real const& rhs)
{
  return lhs.value() == rhs.value();
}

inline bool
operator!=(real const& lhs, real const& rhs)
{
  return !operator==(lhs, rhs);
}

} // namespace carousel

#endif
