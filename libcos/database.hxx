#ifndef libcos__database_hxx_
#define libcos__database_hxx_

#include <libcos/exception.hxx>
#include <libcos/ios-value-source.hxx>
#include <libcos/object.hxx>
#include <libcos/trailer.hxx>
#include <libcos/writer.hxx>
#include <libcos/xref.hxx>

#include <fstream>
#include <map>
#include <memory>
#include <string>

namespace carousel {

class database {
public:
  database()
  {}

  void
  create(std::iostream& s, std::string const& version)
  {
    if (state_)
      throw std::logic_error{ "the database is already open" };

    state_.reset(new state{ s });

    writer w{ s };
    w.write_header(version);

    // state_->catalog = allocate< dictionary >();
    state_->trailer.size(314);
  }

  void
  open(std::iostream& s)
  {
    throw not_implemented{};
  }

  void
  flush()
  {
    // Flush value cache.
    state_->vc.flush();

    std::streamoff xref_offset = state_->stream->tellp();
    state_->xref.write(*state_->stream);

    // TODO write trailer
    writer w{ *state_->stream };
    w.write_eof(xref_offset);

    state_->stream->flush();
  }

  void
  close()
  {
    state_.reset();
  }

  std::string
  version() const
  {
    throw "not implemented";
  }

  template< typename T, typename... Args >
  object
  allocate(Args&&... args)
  {
    return state_->allocate< T, Args... >(std::forward< Args >(args)...);
  }

private:
  struct state {
    state(std::iostream& stream)
      : stream{ &stream },
        vs{ stream, xref },
        vc{ vs },
        catalog{ allocate< dictionary >() },
        trailer{ catalog }
    {}

    template< typename T, typename... Args >
    object
    allocate(Args&&... args)
    {
      auto index = xref.allocate();

      object obj{ vc, index, 0 }; // TODO generation
      vc.put(index, 0, T{ std::forward< Args >(args)... });

      return obj;
    }

    std::iostream* stream;
    cross_reference xref;
    ios_value_source vs;
    value_cache vc;

    object catalog;
    trailer trailer;
  };

  std::unique_ptr< state > state_;
};

} // namespace carousel

#endif
