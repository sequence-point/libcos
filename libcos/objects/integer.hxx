#ifndef libcos__objects__integer_hxx_
#define libcos__objects__integer_hxx_

namespace carousel {

class integer {
public:
  explicit integer(std::int64_t value) : value_{ value }
  {}

  std::int64_t
  value() const
  {
    return value_;
  }

private:
  std::int64_t value_;
};

inline bool
operator==(integer const& lhs, integer const& rhs)
{
  return lhs.value() == rhs.value();
}

inline bool
operator!=(integer const& lhs, integer const& rhs)
{
  return !operator==(lhs, rhs);
}

} // namespace carousel

#endif
