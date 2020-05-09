#ifndef libcos__writer_hxx_
#define libcos__writer_hxx_

#include <libcos/value.hxx>
#include <libcos/visitor.hxx>

#include <libcos/objects/array.hxx>
#include <libcos/objects/boolean.hxx>
#include <libcos/objects/dictionary.hxx>
#include <libcos/objects/integer.hxx>
#include <libcos/objects/name.hxx>
#include <libcos/objects/real.hxx>
#include <libcos/objects/stream.hxx>
#include <libcos/objects/string.hxx>
#include <libcos/objects/undefined.hxx>

#include <cstdint>
#include <iomanip>
#include <ostream>

namespace carousel {

class writer {
public:
  explicit writer(std::ostream& output) : output_{ output }
  {}

  std::ostream&
  output()
  {
    return output_;
  }

  void
  write_header(std::string const& header)
  {
    output() << '%' << header << '\r' << '\n' << "%%\x80\xff\x80\xff\r\n";
  }

  void
  write_value(std::uint32_t index, std::uint16_t generation, value const& v)
  {
    std::uint32_t offset = static_cast< std::uint32_t >(output().tellp());

    output() << std::to_string(index) << ' ' << std::to_string(generation)
             << " obj % " << std::to_string(offset) << "\r\n";

    dispatch_emit(v, true);

    // Write stream data if this is a stream.
    if (v.template is< stream >()) {
      output() << "\r\nstream\r\n";
      output() << "\r\nendstream";
    }

    output() << "\r\nendobj\r\n";
  }

  void
  begin_xref()
  {
    std::uint32_t offset = static_cast< std::uint32_t >(output().tellp());
    output() << "xref % " << std::to_string(offset) << "\r\n";
  }

  void
  begin_xref_chunk(std::uint32_t index, std::uint16_t count)
  {
    output() << std::to_string(index) << ' ' << std::to_string(count) << '\r'
             << '\n';
  }

  void
  write_xref_used_entry(std::streamoff offset, std::uint16_t generation)
  {
    using std::setfill;
    using std::setw;

    std::ostringstream str;
    str << setw(10) << setfill('0') << offset << ' ';
    str << setw(5) << setfill('0') << generation << " n\r\n";

    output() << str.str();
  }

  void
  write_xref_free_entry(std::uint32_t prev, std::uint16_t next_generation)
  {
    using std::setfill;
    using std::setw;

    std::ostringstream str;
    str << setw(10) << setfill('0') << prev << ' ';
    str << setw(5) << setfill('0') << next_generation << " f\r\n";

    output() << str.str();
  }

  void
  write_trailer(dictionary const& dict)
  {
    output() << "trailer\r\n";
    emit_value(dict);
    output() << "\r\n";
  }

  void
  write_eof(std::streamoff xref_offset)
  {
    output() << "startxref\r\n";
    output() << std::to_string(xref_offset) << '\r' << '\n';
    output() << "%%EOF\r\n";
  }

private:
  // TODO track indentation

  void
  emit_reference(object const& obj)
  {
    output() << obj.index() << ' ' << obj.generation() << ' ' << 'R';
  }

  void
  emit_value(boolean const& b)
  {
    if (b.value())
      output() << "true";
    else
      output() << "false";
  }

  void
  emit_value(integer const& i)
  {
    output() << std::to_string(i.value());
  }

  void
  emit_value(real const& r)
  {
    output() << std::to_string(r.value());
  }

  void
  emit_value(string const& str)
  {
    // TODO add encoding preference to str
    output() << '(' << str.value() << ')';
  }

  void
  emit_value(name const& n)
  {
    output() << '/' << n.value();
  }

  void
  emit_value(array const& ar)
  {
    output() << '[';

    auto it = ar.begin();

    if (it != std::end(ar)) {
      dispatch_emit(*it);
      ++it;
    }

    for (; it != ar.end(); ++it) {
      output() << ' ';
      dispatch_emit(*it);
    }

    output() << ']';
  }

  void
  emit_value(dictionary const& dict)
  {
    output() << "<<";

    auto it = dict.begin();

    if (it == dict.end()) {
      output() << ">>";
      return;
    }

    emit_value(name{ it->first });
    output() << ' ';
    dispatch_emit(it->second);
    ++it;
    output() << '\r' << '\n';

    for (; it != dict.end(); ++it) {
      output() << "  ";
      emit_value(name{ it->first });
      output() << ' ';
      dispatch_emit(it->second);
      output() << '\r' << '\n';
    }

    output() << "  >>";
  }

  void
  emit_value(undefined const&)
  {
    output() << "null";
  }

  void
  dispatch_emit(value const& v, bool allow_stream = false)
  {
    struct dispatcher : visitor,
                        basic_visitor< boolean >,
                        basic_visitor< integer >,
                        basic_visitor< real >,
                        basic_visitor< string >,
                        basic_visitor< name >,
                        basic_visitor< array >,
                        basic_visitor< dictionary >,
                        basic_visitor< undefined > {
      writer& writer_;

      explicit dispatcher(writer& w) : writer_{ w }
      {}

      void
      visit(boolean const& b) override
      {
        writer_.emit_value(b);
      }

      void
      visit(integer const& i) override
      {
        writer_.emit_value(i);
      }

      void
      visit(real const& r) override
      {
        writer_.emit_value(r);
      }

      void
      visit(string const& str) override
      {
        writer_.emit_value(str);
      }

      void
      visit(name const& n) override
      {
        writer_.emit_value(n);
      }

      void
      visit(array const& ar) override
      {
        writer_.emit_value(ar);
      }

      void
      visit(dictionary const& dict) override
      {
        writer_.emit_value(dict);
      }

      void
      visit(undefined const& undef) override
      {
        writer_.emit_value(undef);
      }
    };

    dispatcher d{ *this };
    accept(v, d);
  }

  void
  dispatch_emit(object const& obj)
  {
    // If the object is a reference we emit a reference (N N R)
    // instead of the object value.
    if (obj.is_reference()) {
      emit_reference(obj);
      return;
    }

    dispatch_emit(obj.get_value());
  }

  void
  indent()
  {
    for (int i = 0; i < indent_; ++i)
      output() << ' ';
  }

  std::ostream& output_;
  int indent_{ 0 };
};

} // namespace carousel

#endif
