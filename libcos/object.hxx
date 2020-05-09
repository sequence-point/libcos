#ifndef libcos__object_hxx_
#define libcos__object_hxx_

#include <libcos/value-cache.hxx>
#include <libcos/value.hxx>
#include <libcos/visitor.hxx>

#include <memory>

namespace carousel {

struct object_identity {
  std::uint32_t index;
  std::uint16_t generation;
};

class object {
public:
  template< typename T >
  object(T v) : value_{ std::make_shared< unique_t >(value{ std::move(v) }) }
  {}

  object(value_cache& vc, std::uint32_t index, std::uint16_t generation)
    : value_{ std::make_shared< reference_t >(vc, index, generation) }
  {}

  std::uint32_t
  index() const
  {
    return value_->get_index_();
  }

  std::uint16_t
  generation() const
  {
    return value_->get_generation_();
  }

  template< typename T >
  bool
  is() const
  {
    return get_value().template is< T >();
  }

  bool
  is_reference() const
  {
    return value_->is_reference_();
  }

  value&
  get_value()
  {
    return value_->get_value_();
  }

  value const&
  get_value() const
  {
    return value_->get_value_();
  }

  object&
  operator=(value const& other)
  {
    value_->assign_(other);
    return *this;
  }

  object&
  operator=(object const& other)
  {
    value_->assign_(other.get_value());
    return *this;
  }

private:
  struct concept_t {
    virtual ~concept_t() = default;

    virtual bool
    is_reference_() const = 0;

    virtual std::uint32_t
    get_index_() const = 0;

    virtual std::uint16_t
    get_generation_() const = 0;

    virtual value&
    get_value_() = 0;

    virtual void
    assign_(value const& other) = 0;
  };

  struct unique_t : concept_t {
    unique_t(value v) : value_{ std::move(v) }
    {}

    bool
    is_reference_() const override
    {
      return false;
    }

    std::uint32_t
    get_index_() const override
    {
      throw "not an indirect object";
    }

    std::uint16_t
    get_generation_() const override
    {
      throw "not an indirect object";
    }

    value&
    get_value_() override
    {
      return value_;
    }

    void
    assign_(value const& other) override
    {
      value_ = other;
    }

    value value_;
  };

  //! Implements a reference to an indirect object.
  struct reference_t : concept_t {
    reference_t(value_cache& vc, std::uint32_t index, std::uint16_t generation)
      : vc_{ vc }, index_{ index }, generation_{ generation }
    {}

    bool
    is_reference_() const override
    {
      return true;
    }

    std::uint32_t
    get_index_() const override
    {
      return index_;
    }

    std::uint16_t
    get_generation_() const override
    {
      return generation_;
    }

    value&
    get_value_() override
    {
      return vc_.lookup(index_, generation_);
    }

    void
    assign_(value const& other) override
    {
      vc_.put(index_, generation_, other);
    }

    value_cache& vc_;
    std::uint32_t index_;
    std::uint16_t generation_;
  };

  std::shared_ptr< concept_t > value_;
};

template< typename T >
T&
object_cast(object& obj)
{
  return value_cast< T >(obj.get_value());
}

template< typename T >
T const&
object_cast(object const& obj)
{
  return value_cast< T >(obj.get_value());
}

template< typename T >
T&
object_cast(object&& obj) = delete;

} // namespace carousel

#endif
