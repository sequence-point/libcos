#ifndef libcos__objects__array_hxx_
#define libcos__objects__array_hxx_

#include <libcos/object.hxx>
#include <libcos/visitor.hxx>

#include <deque>

namespace carousel {

class array {
public:
  using container_type = std::deque< object >;
  using size_type = typename container_type::size_type;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  iterator
  begin()
  {
    return container_.begin();
  }

  const_iterator
  begin() const
  {
    return container_.begin();
  }

  const_iterator
  cbegin() const
  {
    return container_.cbegin();
  }

  iterator
  end()
  {
    return container_.end();
  }

  const_iterator
  end() const
  {
    return container_.end();
  }

  const_iterator
  cend() const
  {
    return container_.cend();
  }

  object&
  get(size_type index)
  {
    return container_.at(index);
  }

  object const&
  get(size_type index) const
  {
    return container_.at(index);
  }

  void
  shift(object obj)
  {
    //container_.emplace_front(std::move(obj));
  }

  void
  unshift()
  {
    container_.pop_front();
  }

  void
  push(object obj)
  {
    //container_.emplace_back(std::move(obj));
  }

  void
  pop()
  {
    container_.pop_back();
  }

  void
  replace(size_type index, object obj)
  {
    throw 0;
  }

  void
  erase(size_type index)
  {
    throw 0;
  }

  friend bool
  operator==(array const& lhs, array const& rhs)
  {
    return lhs.container_ == rhs.container_;
  }

  friend bool
  operator!=(array const& lhs, array const& rhs)
  {
    return lhs.container_ != rhs.container_;
  }

private:
  container_type container_;
};

} // namespace carousel

#endif
