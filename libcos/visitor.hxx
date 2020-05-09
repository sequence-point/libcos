#ifndef libcos__visitor_hxx_
#define libcos__visitor_hxx_

namespace carousel {

class visitor {
protected:
  visitor() = default;
  virtual ~visitor() = default;
};

template< typename T >
class basic_visitor {
public:
  virtual void
  visit(T& visitee)
  {
    visit(const_cast< T const& >(visitee));
  }

  virtual void
  visit(T const&) = 0;

protected:
  basic_visitor() = default;
  virtual ~basic_visitor() = default;
};

template< typename T >
void
accept(T& visitee, visitor& v)
{
  auto& v_cast = dynamic_cast< basic_visitor< T >& >(v);
  v_cast.visit(visitee);
}

template< typename T >
void
accept(T const& visitee, visitor& v)
{
  auto& v_cast = dynamic_cast< basic_visitor< T >& >(v);
  v_cast.visit(visitee);
}

} // namespace carousel

#endif
