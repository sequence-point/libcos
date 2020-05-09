#ifndef libcos__trailer_hxx_
#define libcos__trailer_hxx_

#include <libcos/objects/dictionary.hxx>
#include <libcos/objects/integer.hxx>

namespace carousel {

class trailer {
public:
  explicit trailer(object source) : source_{ source }
  {}

  std::uint32_t
  size() const
  {
    return object_cast< integer >(get_source().get("Size")).value();
  }

  void
  size(std::uint32_t size)
  {
    get_source().set("Size", object{ integer{ size } });
  }

  object
  root() const
  {
    return get_source().get("Root");
  }

  void
  root(object root)
  {
    get_source().set("Root", root);
  }

  object
  info() const
  {
    return get_source().get("Info");
  }

  void
  info(object info)
  {
    get_source().set("Info", info);
  }

private:
  dictionary&
  get_source()
  {
    return object_cast< dictionary >(source_);
  }

  dictionary const&
  get_source() const
  {
    return object_cast< dictionary >(source_);
  }

  object source_;
};

} // namespace carousel

#endif
