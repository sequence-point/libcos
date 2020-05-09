#ifndef libcos__value_hxx_
#define libcos__value_hxx_

#include <libcos/visitor.hxx>

#include <cstdint>
#include <memory>
#include <type_traits>

namespace carousel {

//! The value class represents the value of an object.
/*!
 * \note The type of a value cannot be changed once it's been created.
 */
class value {
public:
  template< typename T >
  value(T v) : value_{ std::make_unique< value_t< T > >(std::move(v)) }
  {}

  value(value const& other) : value_{ other.value_->clone() }
  {}

  value(value&& other)
  {
    std::swap(value_, other.value_);
  }

  friend void
  accept(value& visitee, visitor& v);

  friend void
  accept(value const& visitee, visitor& v);

  template< typename T >
  bool
  is() const
  {
    return nullptr != dynamic_cast< value_t< T > const* >(value_.get());
  }

  value&
  operator=(value const& other)
  {
    value_->assign_(*other.value_);
    return *this;
  }

  value&
  operator=(value&& other)
  {
    value_->assign_(*other.value_);
    return *this;
  }

  friend bool
  operator==(value const& lhs, value const& rhs);

  template< typename T >
  friend T&
  value_cast(value& v);

  template< typename T >
  friend T const&
  value_cast(value const& v);

  template< typename T >
  friend T
  value_cast(value&& v);

private:
  struct concept_t {
    virtual ~concept_t() = default;

    virtual std::unique_ptr< concept_t >
    clone() const = 0;

    virtual void
    assign_(concept_t const& other) = 0;

    virtual void
    assign_(concept_t&& other) = 0;

    virtual bool
    compare_(concept_t const& other) = 0;

    virtual void
    accept_(visitor& v) = 0;

    virtual void
    accept_(visitor& v) const = 0;
  };

  template< typename T >
  struct value_t : concept_t {
    using value_type = T;

    explicit value_t(value_type value) : value_{ std::move(value) }
    {}

    std::unique_ptr< concept_t >
    clone() const override
    {
      return std::make_unique< value_t >(value_);
    }

    bool
    compare_(concept_t const& other) override
    {
      if (this == &other)
        return true;

      auto ptr = dynamic_cast< value_t const* >(&other);

      if (!ptr)
        return false;

      return value_ == ptr->value_;
    }

    void
    assign_(concept_t const& other) override
    {
      if (this == &other)
        return;

      value_ = dynamic_cast< value_t const& >(other).value_;
    }

    void
    assign_(concept_t&& other) override
    {
      if (this == &other)
        return;

      value_ = std::move(dynamic_cast< value_t& >(other).value_);
    }

    void
    accept_(visitor& v) override
    {
      accept(value_, v);
    }

    void
    accept_(visitor& v) const override
    {
      accept(value_, v);
    }

    value_type value_;
  };

  std::unique_ptr< concept_t > value_;
};

inline bool
operator==(value const& lhs, value const& rhs)
{
  return lhs.value_->compare_(*rhs.value_);
}

inline bool
operator!=(value const& lhs, value const& rhs)
{
  return !operator==(lhs, rhs);
}

inline void
accept(value& visitee, visitor& v)
{
  visitee.value_->accept_(v);
}

inline void
accept(value const& visitee, visitor& v)
{
  visitee.value_->accept_(v);
}

template< typename T >
T&
value_cast(value& v)
{
  return dynamic_cast< value::value_t< T >& >(*v.value_).value_;
}

template< typename T >
T const&
value_cast(value const& v)
{
  return dynamic_cast< value::value_t< T > const& >(*v.value_).value_;
}

template< typename T >
T
value_cast(value&& v)
{
  return dynamic_cast< value::value_t< T > const& >(*v.value_).value_;
}

} // namespace carousel

#endif
