#pragma warning(disable:4583)
#pragma warning(disable:4582)

#include "../../walletconnectcallback.h"
#include "../../walletconnectcallback.h"
#include "../../pay.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_PANIC
#define CXXBRIDGE1_PANIC
template <typename Exception>
void panic [[noreturn]] (const char *msg);
#endif // CXXBRIDGE1_PANIC

struct unsafe_bitcopy_t;

namespace {
template <typename T>
class impl;
} // namespace

template <typename T>
::std::size_t size_of();
template <typename T>
::std::size_t align_of();

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final {
public:
  String() noexcept;
  String(const String &) noexcept;
  String(String &&) noexcept;
  ~String() noexcept;

  String(const std::string &);
  String(const char *);
  String(const char *, std::size_t);
  String(const char16_t *);
  String(const char16_t *, std::size_t);

  static String lossy(const std::string &) noexcept;
  static String lossy(const char *) noexcept;
  static String lossy(const char *, std::size_t) noexcept;
  static String lossy(const char16_t *) noexcept;
  static String lossy(const char16_t *, std::size_t) noexcept;

  String &operator=(const String &) &noexcept;
  String &operator=(String &&) &noexcept;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  const char *c_str() noexcept;

  std::size_t capacity() const noexcept;
  void reserve(size_t new_cap) noexcept;

  using iterator = char *;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const String &) const noexcept;
  bool operator!=(const String &) const noexcept;
  bool operator<(const String &) const noexcept;
  bool operator<=(const String &) const noexcept;
  bool operator>(const String &) const noexcept;
  bool operator>=(const String &) const noexcept;

  void swap(String &) noexcept;

  String(unsafe_bitcopy_t, const String &) noexcept;

private:
  struct lossy_t;
  String(lossy_t, const char *, std::size_t) noexcept;
  String(lossy_t, const char16_t *, std::size_t) noexcept;
  friend void swap(String &lhs, String &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const String &) noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, std::size_t);

  Str &operator=(const Str &) &noexcept = default;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const Str &) const noexcept;
  bool operator!=(const Str &) const noexcept;
  bool operator<(const Str &) const noexcept;
  bool operator<=(const Str &) const noexcept;
  bool operator>(const Str &) const noexcept;
  bool operator>=(const Str &) const noexcept;

  void swap(Str &) noexcept;

private:
  class uninit;
  Str(uninit) noexcept;
  friend impl<Str>;

  std::array<std::uintptr_t, 2> repr;
};
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_SLICE
#define CXXBRIDGE1_RUST_SLICE
namespace detail {
template <bool>
struct copy_assignable_if {};

template <>
struct copy_assignable_if<false> {
  copy_assignable_if() noexcept = default;
  copy_assignable_if(const copy_assignable_if &) noexcept = default;
  copy_assignable_if &operator=(const copy_assignable_if &) &noexcept = delete;
  copy_assignable_if &operator=(copy_assignable_if &&) &noexcept = default;
};
} // namespace detail

template <typename T>
class Slice final
    : private detail::copy_assignable_if<std::is_const<T>::value> {
public:
  using value_type = T;

  Slice() noexcept;
  Slice(T *, std::size_t count) noexcept;

  Slice &operator=(const Slice<T> &) &noexcept = default;
  Slice &operator=(Slice<T> &&) &noexcept = default;

  T *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  T &operator[](std::size_t n) const noexcept;
  T &at(std::size_t n) const;
  T &front() const noexcept;
  T &back() const noexcept;

  Slice(const Slice<T> &) noexcept = default;
  ~Slice() noexcept = default;

  class iterator;
  iterator begin() const noexcept;
  iterator end() const noexcept;

  void swap(Slice &) noexcept;

private:
  class uninit;
  Slice(uninit) noexcept;
  friend impl<Slice>;
  friend void sliceInit(void *, const void *, std::size_t) noexcept;
  friend void *slicePtr(const void *) noexcept;
  friend std::size_t sliceLen(const void *) noexcept;

  std::array<std::uintptr_t, 2> repr;
};

template <typename T>
class Slice<T>::iterator final {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::add_pointer<T>::type;
  using reference = typename std::add_lvalue_reference<T>::type;

  reference operator*() const noexcept;
  pointer operator->() const noexcept;
  reference operator[](difference_type) const noexcept;

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  iterator &operator+=(difference_type) noexcept;
  iterator &operator-=(difference_type) noexcept;
  iterator operator+(difference_type) const noexcept;
  iterator operator-(difference_type) const noexcept;
  difference_type operator-(const iterator &) const noexcept;

  bool operator==(const iterator &) const noexcept;
  bool operator!=(const iterator &) const noexcept;
  bool operator<(const iterator &) const noexcept;
  bool operator<=(const iterator &) const noexcept;
  bool operator>(const iterator &) const noexcept;
  bool operator>=(const iterator &) const noexcept;

private:
  friend class Slice;
  void *pos;
  std::size_t stride;
};

template <typename T>
Slice<T>::Slice() noexcept {
  sliceInit(this, reinterpret_cast<void *>(align_of<T>()), 0);
}

template <typename T>
Slice<T>::Slice(T *s, std::size_t count) noexcept {
  assert(s != nullptr || count == 0);
  sliceInit(this,
            s == nullptr && count == 0
                ? reinterpret_cast<void *>(align_of<T>())
                : const_cast<typename std::remove_const<T>::type *>(s),
            count);
}

template <typename T>
T *Slice<T>::data() const noexcept {
  return reinterpret_cast<T *>(slicePtr(this));
}

template <typename T>
std::size_t Slice<T>::size() const noexcept {
  return sliceLen(this);
}

template <typename T>
std::size_t Slice<T>::length() const noexcept {
  return this->size();
}

template <typename T>
bool Slice<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T &Slice<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto ptr = static_cast<char *>(slicePtr(this)) + size_of<T>() * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
T &Slice<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Slice index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Slice<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Slice<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
typename Slice<T>::iterator::reference
Slice<T>::iterator::operator*() const noexcept {
  return *static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::pointer
Slice<T>::iterator::operator->() const noexcept {
  return static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator[](
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ptr = static_cast<char *>(this->pos) + this->stride * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator++() noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator++(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator--() noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator--(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator+=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator-=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator+(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) + this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator-(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) - this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator::difference_type
Slice<T>::iterator::operator-(const iterator &other) const noexcept {
  auto diff = std::distance(static_cast<char *>(other.pos),
                            static_cast<char *>(this->pos));
  return diff / this->stride;
}

template <typename T>
bool Slice<T>::iterator::operator==(const iterator &other) const noexcept {
  return this->pos == other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator!=(const iterator &other) const noexcept {
  return this->pos != other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<(const iterator &other) const noexcept {
  return this->pos < other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<=(const iterator &other) const noexcept {
  return this->pos <= other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>(const iterator &other) const noexcept {
  return this->pos > other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>=(const iterator &other) const noexcept {
  return this->pos >= other.pos;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::begin() const noexcept {
  iterator it;
  it.pos = slicePtr(this);
  it.stride = size_of<T>();
  return it;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::end() const noexcept {
  iterator it = this->begin();
  it.pos = static_cast<char *>(it.pos) + it.stride * this->size();
  return it;
}

template <typename T>
void Slice<T>::swap(Slice &rhs) noexcept {
  std::swap(*this, rhs);
}
#endif // CXXBRIDGE1_RUST_SLICE

#ifndef CXXBRIDGE1_RUST_BOX
#define CXXBRIDGE1_RUST_BOX
template <typename T>
class Box final {
public:
  using element_type = T;
  using const_pointer =
      typename std::add_pointer<typename std::add_const<T>::type>::type;
  using pointer = typename std::add_pointer<T>::type;

  Box() = delete;
  Box(Box &&) noexcept;
  ~Box() noexcept;

  explicit Box(const T &);
  explicit Box(T &&);

  Box &operator=(Box &&) &noexcept;

  const T *operator->() const noexcept;
  const T &operator*() const noexcept;
  T *operator->() noexcept;
  T &operator*() noexcept;

  template <typename... Fields>
  static Box in_place(Fields &&...);

  void swap(Box &) noexcept;

  static Box from_raw(T *) noexcept;

  T *into_raw() noexcept;

  /* Deprecated */ using value_type = element_type;

private:
  class uninit;
  class allocation;
  Box(uninit) noexcept;
  void drop() noexcept;

  friend void swap(Box &lhs, Box &rhs) noexcept { lhs.swap(rhs); }

  T *ptr;
};

template <typename T>
class Box<T>::uninit {};

template <typename T>
class Box<T>::allocation {
  static T *alloc() noexcept;
  static void dealloc(T *) noexcept;

public:
  allocation() noexcept : ptr(alloc()) {}
  ~allocation() noexcept {
    if (this->ptr) {
      dealloc(this->ptr);
    }
  }
  T *ptr;
};

template <typename T>
Box<T>::Box(Box &&other) noexcept : ptr(other.ptr) {
  other.ptr = nullptr;
}

template <typename T>
Box<T>::Box(const T &val) {
  allocation alloc;
  ::new (alloc.ptr) T(val);
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::Box(T &&val) {
  allocation alloc;
  ::new (alloc.ptr) T(std::move(val));
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::~Box() noexcept {
  if (this->ptr) {
    this->drop();
  }
}

template <typename T>
Box<T> &Box<T>::operator=(Box &&other) &noexcept {
  if (this->ptr) {
    this->drop();
  }
  this->ptr = other.ptr;
  other.ptr = nullptr;
  return *this;
}

template <typename T>
const T *Box<T>::operator->() const noexcept {
  return this->ptr;
}

template <typename T>
const T &Box<T>::operator*() const noexcept {
  return *this->ptr;
}

template <typename T>
T *Box<T>::operator->() noexcept {
  return this->ptr;
}

template <typename T>
T &Box<T>::operator*() noexcept {
  return *this->ptr;
}

template <typename T>
template <typename... Fields>
Box<T> Box<T>::in_place(Fields &&...fields) {
  allocation alloc;
  auto ptr = alloc.ptr;
  ::new (ptr) T{std::forward<Fields>(fields)...};
  alloc.ptr = nullptr;
  return from_raw(ptr);
}

template <typename T>
void Box<T>::swap(Box &rhs) noexcept {
  using std::swap;
  swap(this->ptr, rhs.ptr);
}

template <typename T>
Box<T> Box<T>::from_raw(T *raw) noexcept {
  Box box = uninit{};
  box.ptr = raw;
  return box;
}

template <typename T>
T *Box<T>::into_raw() noexcept {
  T *raw = this->ptr;
  this->ptr = nullptr;
  return raw;
}

template <typename T>
Box<T>::Box(uninit) noexcept {}
#endif // CXXBRIDGE1_RUST_BOX

#ifndef CXXBRIDGE1_RUST_BITCOPY_T
#define CXXBRIDGE1_RUST_BITCOPY_T
struct unsafe_bitcopy_t final {
  explicit unsafe_bitcopy_t() = default;
};
#endif // CXXBRIDGE1_RUST_BITCOPY_T

#ifndef CXXBRIDGE1_RUST_BITCOPY
#define CXXBRIDGE1_RUST_BITCOPY
constexpr unsafe_bitcopy_t unsafe_bitcopy{};
#endif // CXXBRIDGE1_RUST_BITCOPY

#ifndef CXXBRIDGE1_RUST_VEC
#define CXXBRIDGE1_RUST_VEC
template <typename T>
class Vec final {
public:
  using value_type = T;

  Vec() noexcept;
  Vec(std::initializer_list<T>);
  Vec(const Vec &);
  Vec(Vec &&) noexcept;
  ~Vec() noexcept;

  Vec &operator=(Vec &&) &noexcept;
  Vec &operator=(const Vec &) &;

  std::size_t size() const noexcept;
  bool empty() const noexcept;
  const T *data() const noexcept;
  T *data() noexcept;
  std::size_t capacity() const noexcept;

  const T &operator[](std::size_t n) const noexcept;
  const T &at(std::size_t n) const;
  const T &front() const noexcept;
  const T &back() const noexcept;

  T &operator[](std::size_t n) noexcept;
  T &at(std::size_t n);
  T &front() noexcept;
  T &back() noexcept;

  void reserve(std::size_t new_cap);
  void push_back(const T &value);
  void push_back(T &&value);
  template <typename... Args>
  void emplace_back(Args &&...args);
  void truncate(std::size_t len);
  void clear();

  using iterator = typename Slice<T>::iterator;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = typename Slice<const T>::iterator;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  void swap(Vec &) noexcept;

  Vec(unsafe_bitcopy_t, const Vec &) noexcept;

private:
  void reserve_total(std::size_t new_cap) noexcept;
  void set_len(std::size_t len) noexcept;
  void drop() noexcept;

  friend void swap(Vec &lhs, Vec &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};

template <typename T>
Vec<T>::Vec(std::initializer_list<T> init) : Vec{} {
  this->reserve_total(init.size());
  std::move(init.begin(), init.end(), std::back_inserter(*this));
}

template <typename T>
Vec<T>::Vec(const Vec &other) : Vec() {
  this->reserve_total(other.size());
  std::copy(other.begin(), other.end(), std::back_inserter(*this));
}

template <typename T>
Vec<T>::Vec(Vec &&other) noexcept : repr(other.repr) {
  new (&other) Vec();
}

template <typename T>
Vec<T>::~Vec() noexcept {
  this->drop();
}

template <typename T>
Vec<T> &Vec<T>::operator=(Vec &&other) &noexcept {
  this->drop();
  this->repr = other.repr;
  new (&other) Vec();
  return *this;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec &other) & {
  if (this != &other) {
    this->drop();
    new (this) Vec(other);
  }
  return *this;
}

template <typename T>
bool Vec<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T *Vec<T>::data() noexcept {
  return const_cast<T *>(const_cast<const Vec<T> *>(this)->data());
}

template <typename T>
const T &Vec<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto data = reinterpret_cast<const char *>(this->data());
  return *reinterpret_cast<const T *>(data + n * size_of<T>());
}

template <typename T>
const T &Vec<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Vec index out of range");
  }
  return (*this)[n];
}

template <typename T>
const T &Vec<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
const T &Vec<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
T &Vec<T>::operator[](std::size_t n) noexcept {
  assert(n < this->size());
  auto data = reinterpret_cast<char *>(this->data());
  return *reinterpret_cast<T *>(data + n * size_of<T>());
}

template <typename T>
T &Vec<T>::at(std::size_t n) {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Vec index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Vec<T>::front() noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Vec<T>::back() noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
void Vec<T>::reserve(std::size_t new_cap) {
  this->reserve_total(new_cap);
}

template <typename T>
void Vec<T>::push_back(const T &value) {
  this->emplace_back(value);
}

template <typename T>
void Vec<T>::push_back(T &&value) {
  this->emplace_back(std::move(value));
}

template <typename T>
template <typename... Args>
void Vec<T>::emplace_back(Args &&...args) {
  auto size = this->size();
  this->reserve_total(size + 1);
  ::new (reinterpret_cast<T *>(reinterpret_cast<char *>(this->data()) +
                               size * size_of<T>()))
      T(std::forward<Args>(args)...);
  this->set_len(size + 1);
}

template <typename T>
void Vec<T>::clear() {
  this->truncate(0);
}

template <typename T>
typename Vec<T>::iterator Vec<T>::begin() noexcept {
  return Slice<T>(this->data(), this->size()).begin();
}

template <typename T>
typename Vec<T>::iterator Vec<T>::end() noexcept {
  return Slice<T>(this->data(), this->size()).end();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::begin() const noexcept {
  return this->cbegin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::end() const noexcept {
  return this->cend();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cbegin() const noexcept {
  return Slice<const T>(this->data(), this->size()).begin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cend() const noexcept {
  return Slice<const T>(this->data(), this->size()).end();
}

template <typename T>
void Vec<T>::swap(Vec &rhs) noexcept {
  using std::swap;
  swap(this->repr, rhs.repr);
}

template <typename T>
Vec<T>::Vec(unsafe_bitcopy_t, const Vec &bits) noexcept : repr(bits.repr) {}
#endif // CXXBRIDGE1_RUST_VEC

#ifndef CXXBRIDGE1_RUST_ERROR
#define CXXBRIDGE1_RUST_ERROR
class Error final : public std::exception {
public:
  Error(const Error &);
  Error(Error &&) noexcept;
  ~Error() noexcept override;

  Error &operator=(const Error &) &;
  Error &operator=(Error &&) &noexcept;

  const char *what() const noexcept override;

private:
  Error() noexcept = default;
  friend impl<Error>;
  const char *msg;
  std::size_t len;
};
#endif // CXXBRIDGE1_RUST_ERROR

#ifndef CXXBRIDGE1_RUST_OPAQUE
#define CXXBRIDGE1_RUST_OPAQUE
class Opaque {
public:
  Opaque() = delete;
  Opaque(const Opaque &) = delete;
  ~Opaque() = delete;
};
#endif // CXXBRIDGE1_RUST_OPAQUE

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout {
  template <typename T>
  friend std::size_t size_of();
  template <typename T>
  friend std::size_t align_of();
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return T::layout::size();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return sizeof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      size_of() {
    return do_size_of<T>();
  }
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return T::layout::align();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return alignof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      align_of() {
    return do_align_of<T>();
  }
};

template <typename T>
std::size_t size_of() {
  return layout::size_of<T>();
}

template <typename T>
std::size_t align_of() {
  return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT

namespace detail {
template <typename T, typename = void *>
struct operator_new {
  void *operator()(::std::size_t sz) { return ::operator new(sz); }
};

template <typename T>
struct operator_new<T, decltype(T::operator new(sizeof(T)))> {
  void *operator()(::std::size_t sz) { return T::operator new(sz); }
};
} // namespace detail

template <typename T>
union ManuallyDrop {
  T value;
  ManuallyDrop(T &&value) : value(::std::move(value)) {}
  ~ManuallyDrop() {}
};

template <typename T>
union MaybeUninit {
  T value;
  void *operator new(::std::size_t sz) { return detail::operator_new<T>{}(sz); }
  MaybeUninit() {}
  ~MaybeUninit() {}
};

namespace {
namespace repr {
using Fat = ::std::array<::std::uintptr_t, 2>;

struct PtrLen final {
  void *ptr;
  ::std::size_t len;
};
} // namespace repr

template <>
class impl<Str> final {
public:
  static repr::Fat repr(Str str) noexcept {
    return str.repr;
  }
};

template <>
class impl<Error> final {
public:
  static Error error(repr::PtrLen repr) noexcept {
    Error error;
    error.msg = static_cast<const char *>(repr.ptr);
    error.len = repr.len;
    return error;
  }
};

template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};

template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1
} // namespace rust

namespace com {
  namespace crypto {
    namespace game_sdk {
      using WalletConnectCallback = ::com::crypto::game_sdk::WalletConnectCallback;
      using WalletConnectSessionInfo = ::com::crypto::game_sdk::WalletConnectSessionInfo;
      struct WalletConnectTxLegacy;
      struct WalletConnectAddress;
      struct WalletConnectEnsureSessionResult;
      struct CryptoComPaymentResponse;
      struct RawTxDetail;
      struct RawTokenResult;
      enum class QueryOption : ::std::uint8_t;
      struct WalletconnectClient;
      using OptionalArguments = ::com::crypto::game_sdk::OptionalArguments;
    }
  }
}

namespace com {
namespace crypto {
namespace game_sdk {
#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectTxLegacy
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectTxLegacy
  /// wallet connect cronos(eth) legacy-tx signing info
struct WalletConnectTxLegacy final {
  ::rust::String to;
  ::rust::String gas;
  ::rust::String gas_price;
  ::rust::String value;
  ::rust::Vec<::std::uint8_t> data;
  ::rust::String nonce;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectTxLegacy

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectAddress
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectAddress
  /// cronos address info
struct WalletConnectAddress final {
  ::std::array<::std::uint8_t, 20> address;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectAddress

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectEnsureSessionResult
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectEnsureSessionResult
  /// walletconnect ensure-session result
struct WalletConnectEnsureSessionResult final {
  ::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> addresses;
  ::std::uint64_t chain_id;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletConnectEnsureSessionResult

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$CryptoComPaymentResponse
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$CryptoComPaymentResponse
  /// the subset of payment object from https://pay-docs.crypto.com
struct CryptoComPaymentResponse final {
  /// uuid of the payment object
  ::rust::String id;
  /// the base64 payload to be displayed as QR code that
  /// can be scanned by the main app
  ::rust::String main_app_qr_code;
  /// if the on-chain payment is desired, this will
  /// have the cryptocurrency address that can be displayed
  /// as a QR code or put in a tx to be signed via WalletConnect
  ::rust::String onchain_deposit_address;
  /// the amount in base denomination
  /// e.g. for USD, it's cents (1 USD == 100 cents)
  ::rust::String base_amount;
  /// the 3-letter currency code
  ::rust::String currency;
  /// expiration time in unix timestamp (10 minutes)
  ::std::uint64_t expiration;
  /// the status of the payment
  ::rust::String status;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$CryptoComPaymentResponse

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTxDetail
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTxDetail
  /// Raw transaction details (extracted from Cronoscan/Etherscan or BlockScout API)
struct RawTxDetail final {
  /// Transaction hash
  ::rust::String hash;
  /// the hexadecimal address of the receiver
  ::rust::String to_address;
  /// the hexadecimal address of the sender
  ::rust::String from_address;
  /// the value sent in decimal (in base tokens)
  ::rust::String value;
  /// block number when it happened
  ::std::uint64_t block_no;
  /// the time it happened
  ::rust::String timestamp;
  /// the address of the contract (if no contract, it's an empty string)
  ::rust::String contract_address;

  bool operator==(const RawTxDetail &) const noexcept;
  bool operator!=(const RawTxDetail &) const noexcept;
  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTxDetail

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTokenResult
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTokenResult
  /// Token ownership result detail from BlockScout API
struct RawTokenResult final {
  /// how many tokens are owned by the address
  ::rust::String balance;
  /// the deployed contract address
  ::rust::String contract_address;
  /// the number of decimal places
  ::rust::String decimals;
  /// the token id
  ::rust::String id;
  /// the human-readable name of the token
  ::rust::String name;
  /// the ticker for the token
  ::rust::String symbol;
  /// the token type (ERC-20, ERC-721, ERC-1155)
  ::rust::String token_type;

  bool operator==(const RawTokenResult &) const noexcept;
  bool operator!=(const RawTokenResult &) const noexcept;
  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$RawTokenResult

#ifndef CXXBRIDGE1_ENUM_com$crypto$game_sdk$QueryOption
#define CXXBRIDGE1_ENUM_com$crypto$game_sdk$QueryOption
enum class QueryOption : ::std::uint8_t {
  ByContract = 0,
  ByAddressAndContract = 1,
  ByAddress = 2,
};
#endif // CXXBRIDGE1_ENUM_com$crypto$game_sdk$QueryOption

#ifndef CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletconnectClient
#define CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletconnectClient
  /// WallnetConnect API
struct WalletconnectClient final : public ::rust::Opaque {
  /// setup callback
  void setup_callback(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback> usercallback);

  /// create or restore a session
  /// once session is created, it will be reused
  ::com::crypto::game_sdk::WalletConnectEnsureSessionResult ensure_session_blocking();

  /// get connection string for qrcode
  ::rust::String get_connection_string();

  /// write session-info to string, which can be written to file
  ::rust::String save_client();

  /// print qrcode in termal, for debugging
  ::rust::String print_uri();

  /// sign message
  ::rust::Vec<::std::uint8_t> sign_personal_blocking(::rust::String message, ::std::array<::std::uint8_t, 20> address);

  /// sign cronos(eth) legacy-tx
  ::rust::Vec<::std::uint8_t> sign_legacy_transaction_blocking(const ::com::crypto::game_sdk::WalletConnectTxLegacy &info, ::std::array<::std::uint8_t, 20> address);

  ~WalletconnectClient() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_com$crypto$game_sdk$WalletconnectClient

extern "C" {
void com$crypto$game_sdk$cxxbridge1$WalletConnectCallback$onConnected(const ::com::crypto::game_sdk::WalletConnectCallback &self, ::com::crypto::game_sdk::WalletConnectSessionInfo *sessioninfo) noexcept {
  void (::com::crypto::game_sdk::WalletConnectCallback::*onConnected$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) const = &::com::crypto::game_sdk::WalletConnectCallback::onConnected;
  (self.*onConnected$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>(sessioninfo));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectCallback$onDisconnected(const ::com::crypto::game_sdk::WalletConnectCallback &self, ::com::crypto::game_sdk::WalletConnectSessionInfo *sessioninfo) noexcept {
  void (::com::crypto::game_sdk::WalletConnectCallback::*onDisconnected$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) const = &::com::crypto::game_sdk::WalletConnectCallback::onDisconnected;
  (self.*onDisconnected$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>(sessioninfo));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectCallback$onConnecting(const ::com::crypto::game_sdk::WalletConnectCallback &self, ::com::crypto::game_sdk::WalletConnectSessionInfo *sessioninfo) noexcept {
  void (::com::crypto::game_sdk::WalletConnectCallback::*onConnecting$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) const = &::com::crypto::game_sdk::WalletConnectCallback::onConnecting;
  (self.*onConnecting$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>(sessioninfo));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectCallback$onUpdated(const ::com::crypto::game_sdk::WalletConnectCallback &self, ::com::crypto::game_sdk::WalletConnectSessionInfo *sessioninfo) noexcept {
  void (::com::crypto::game_sdk::WalletConnectCallback::*onUpdated$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) const = &::com::crypto::game_sdk::WalletConnectCallback::onUpdated;
  (self.*onUpdated$)(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>(sessioninfo));
}

::com::crypto::game_sdk::WalletConnectSessionInfo *com$crypto$game_sdk$cxxbridge1$new_walletconnect_sessioninfo() noexcept {
  ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo> (*new_walletconnect_sessioninfo$)() = ::com::crypto::game_sdk::new_walletconnect_sessioninfo;
  return new_walletconnect_sessioninfo$().release();
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_chainid(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *chainid) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_chainid$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_chainid;
  (self.*set_chainid$)(::rust::String(::rust::unsafe_bitcopy, *chainid));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_connected(::com::crypto::game_sdk::WalletConnectSessionInfo &self, bool connected) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_connected$)(bool) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_connected;
  (self.*set_connected$)(connected);
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_accounts(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::Vec<::rust::String> *accounts) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_accounts$)(::rust::Vec<::rust::String>) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_accounts;
  (self.*set_accounts$)(::rust::Vec<::rust::String>(::rust::unsafe_bitcopy, *accounts));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_bridge(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *bridge) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_bridge$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_bridge;
  (self.*set_bridge$)(::rust::String(::rust::unsafe_bitcopy, *bridge));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_key(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *key) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_key$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_key;
  (self.*set_key$)(::rust::String(::rust::unsafe_bitcopy, *key));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_clientid(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *clientid) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_clientid$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_clientid;
  (self.*set_clientid$)(::rust::String(::rust::unsafe_bitcopy, *clientid));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_clientmeta(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *clientmeta) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_clientmeta$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_clientmeta;
  (self.*set_clientmeta$)(::rust::String(::rust::unsafe_bitcopy, *clientmeta));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_peerid(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *peerid) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_peerid$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_peerid;
  (self.*set_peerid$)(::rust::String(::rust::unsafe_bitcopy, *peerid));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_peermeta(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *peermeta) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_peermeta$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_peermeta;
  (self.*set_peermeta$)(::rust::String(::rust::unsafe_bitcopy, *peermeta));
}

void com$crypto$game_sdk$cxxbridge1$WalletConnectSessionInfo$set_handshaketopic(::com::crypto::game_sdk::WalletConnectSessionInfo &self, const ::rust::String *handshaketopic) noexcept {
  void (::com::crypto::game_sdk::WalletConnectSessionInfo::*set_handshaketopic$)(::rust::String) = &::com::crypto::game_sdk::WalletConnectSessionInfo::set_handshaketopic;
  (self.*set_handshaketopic$)(::rust::String(::rust::unsafe_bitcopy, *handshaketopic));
}
bool com$crypto$game_sdk$cxxbridge1$RawTxDetail$operator$eq(const RawTxDetail &, const RawTxDetail &) noexcept;
bool com$crypto$game_sdk$cxxbridge1$RawTokenResult$operator$eq(const RawTokenResult &, const RawTokenResult &) noexcept;
::std::size_t com$crypto$game_sdk$cxxbridge1$WalletconnectClient$operator$sizeof() noexcept;
::std::size_t com$crypto$game_sdk$cxxbridge1$WalletconnectClient$operator$alignof() noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$walletconnect_restore_client(::rust::String *session_info, ::rust::Box<::com::crypto::game_sdk::WalletconnectClient> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$walletconnect_new_client(::rust::String *description, ::rust::String *url, ::rust::Vec<::rust::String> *icon_urls, ::rust::String *name, ::rust::Box<::com::crypto::game_sdk::WalletconnectClient> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$setup_callback(::com::crypto::game_sdk::WalletconnectClient &self, ::com::crypto::game_sdk::WalletConnectCallback *usercallback) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$ensure_session_blocking(::com::crypto::game_sdk::WalletconnectClient &self, ::com::crypto::game_sdk::WalletConnectEnsureSessionResult *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$get_connection_string(::com::crypto::game_sdk::WalletconnectClient &self, ::rust::String *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$save_client(::com::crypto::game_sdk::WalletconnectClient &self, ::rust::String *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$print_uri(::com::crypto::game_sdk::WalletconnectClient &self, ::rust::String *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$sign_personal_blocking(::com::crypto::game_sdk::WalletconnectClient &self, ::rust::String *message, ::std::array<::std::uint8_t, 20> *address, ::rust::Vec<::std::uint8_t> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$WalletconnectClient$sign_legacy_transaction_blocking(::com::crypto::game_sdk::WalletconnectClient &self, const ::com::crypto::game_sdk::WalletConnectTxLegacy &info, ::std::array<::std::uint8_t, 20> *address, ::rust::Vec<::std::uint8_t> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_transaction_history_blocking(::rust::String *address, ::rust::String *api_key, ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_erc20_transfer_history_blocking(::rust::String *address, ::rust::String *contract_address, ::com::crypto::game_sdk::QueryOption option, ::rust::String *api_key, ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_erc721_transfer_history_blocking(::rust::String *address, ::rust::String *contract_address, ::com::crypto::game_sdk::QueryOption option, ::rust::String *api_key, ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_tokens_blocking(::rust::String *blockscout_base_url, ::rust::String *account_address, ::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_token_transfers_blocking(::rust::String *blockscout_base_url, ::rust::String *address, ::rust::String *contract_address, ::com::crypto::game_sdk::QueryOption option, ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$create_payment(::rust::String *secret_or_publishable_api_key, ::rust::String *base_unit_amount, ::rust::String *currency, const ::com::crypto::game_sdk::OptionalArguments &optional_args, ::com::crypto::game_sdk::CryptoComPaymentResponse *return$) noexcept;

::rust::repr::PtrLen com$crypto$game_sdk$cxxbridge1$get_payment(::rust::String *secret_or_publishable_api_key, ::rust::String *payment_id, ::com::crypto::game_sdk::CryptoComPaymentResponse *return$) noexcept;

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_description(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_description$)() const = &::com::crypto::game_sdk::OptionalArguments::get_description;
  return ::rust::impl<::rust::Str>::repr((self.*get_description$)());
}

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_metadata(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_metadata$)() const = &::com::crypto::game_sdk::OptionalArguments::get_metadata;
  return ::rust::impl<::rust::Str>::repr((self.*get_metadata$)());
}

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_order_id(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_order_id$)() const = &::com::crypto::game_sdk::OptionalArguments::get_order_id;
  return ::rust::impl<::rust::Str>::repr((self.*get_order_id$)());
}

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_return_url(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_return_url$)() const = &::com::crypto::game_sdk::OptionalArguments::get_return_url;
  return ::rust::impl<::rust::Str>::repr((self.*get_return_url$)());
}

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_cancel_url(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_cancel_url$)() const = &::com::crypto::game_sdk::OptionalArguments::get_cancel_url;
  return ::rust::impl<::rust::Str>::repr((self.*get_cancel_url$)());
}

::rust::repr::Fat com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_sub_merchant_id(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::rust::Str (::com::crypto::game_sdk::OptionalArguments::*get_sub_merchant_id$)() const = &::com::crypto::game_sdk::OptionalArguments::get_sub_merchant_id;
  return ::rust::impl<::rust::Str>::repr((self.*get_sub_merchant_id$)());
}

bool com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_onchain_allowed(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  bool (::com::crypto::game_sdk::OptionalArguments::*get_onchain_allowed$)() const = &::com::crypto::game_sdk::OptionalArguments::get_onchain_allowed;
  return (self.*get_onchain_allowed$)();
}

::std::uint64_t com$crypto$game_sdk$cxxbridge1$OptionalArguments$get_expired_at(const ::com::crypto::game_sdk::OptionalArguments &self) noexcept {
  ::std::uint64_t (::com::crypto::game_sdk::OptionalArguments::*get_expired_at$)() const = &::com::crypto::game_sdk::OptionalArguments::get_expired_at;
  return (self.*get_expired_at$)();
}
} // extern "C"

bool RawTxDetail::operator==(const RawTxDetail &rhs) const noexcept {
  return com$crypto$game_sdk$cxxbridge1$RawTxDetail$operator$eq(*this, rhs);
}

bool RawTxDetail::operator!=(const RawTxDetail &rhs) const noexcept {
  return !(*this == rhs);
}

bool RawTokenResult::operator==(const RawTokenResult &rhs) const noexcept {
  return com$crypto$game_sdk$cxxbridge1$RawTokenResult$operator$eq(*this, rhs);
}

bool RawTokenResult::operator!=(const RawTokenResult &rhs) const noexcept {
  return !(*this == rhs);
}

::std::size_t WalletconnectClient::layout::size() noexcept {
  return com$crypto$game_sdk$cxxbridge1$WalletconnectClient$operator$sizeof();
}

::std::size_t WalletconnectClient::layout::align() noexcept {
  return com$crypto$game_sdk$cxxbridge1$WalletconnectClient$operator$alignof();
}

  /// restore walletconnect-session from string
::rust::Box<::com::crypto::game_sdk::WalletconnectClient> walletconnect_restore_client(::rust::String session_info) {
  ::rust::MaybeUninit<::rust::Box<::com::crypto::game_sdk::WalletconnectClient>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$walletconnect_restore_client(&session_info, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// create walletconnect-session
::rust::Box<::com::crypto::game_sdk::WalletconnectClient> walletconnect_new_client(::rust::String description, ::rust::String url, ::rust::Vec<::rust::String> icon_urls, ::rust::String name) {
  ::rust::ManuallyDrop<::rust::Vec<::rust::String>> icon_urls$(::std::move(icon_urls));
  ::rust::MaybeUninit<::rust::Box<::com::crypto::game_sdk::WalletconnectClient>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$walletconnect_new_client(&description, &url, &icon_urls$.value, &name, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

void WalletconnectClient::setup_callback(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback> usercallback) {
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$setup_callback(*this, usercallback.release());
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
}

::com::crypto::game_sdk::WalletConnectEnsureSessionResult WalletconnectClient::ensure_session_blocking() {
  ::rust::MaybeUninit<::com::crypto::game_sdk::WalletConnectEnsureSessionResult> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$ensure_session_blocking(*this, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::String WalletconnectClient::get_connection_string() {
  ::rust::MaybeUninit<::rust::String> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$get_connection_string(*this, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::String WalletconnectClient::save_client() {
  ::rust::MaybeUninit<::rust::String> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$save_client(*this, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::String WalletconnectClient::print_uri() {
  ::rust::MaybeUninit<::rust::String> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$print_uri(*this, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::Vec<::std::uint8_t> WalletconnectClient::sign_personal_blocking(::rust::String message, ::std::array<::std::uint8_t, 20> address) {
  ::rust::ManuallyDrop<::std::array<::std::uint8_t, 20>> address$(::std::move(address));
  ::rust::MaybeUninit<::rust::Vec<::std::uint8_t>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$sign_personal_blocking(*this, &message, &address$.value, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::Vec<::std::uint8_t> WalletconnectClient::sign_legacy_transaction_blocking(const ::com::crypto::game_sdk::WalletConnectTxLegacy &info, ::std::array<::std::uint8_t, 20> address) {
  ::rust::ManuallyDrop<::std::array<::std::uint8_t, 20>> address$(::std::move(address));
  ::rust::MaybeUninit<::rust::Vec<::std::uint8_t>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$WalletconnectClient$sign_legacy_transaction_blocking(*this, info, &address$.value, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// Etherscan API
::rust::Vec<::com::crypto::game_sdk::RawTxDetail> get_transaction_history_blocking(::rust::String address, ::rust::String api_key) {
  ::rust::MaybeUninit<::rust::Vec<::com::crypto::game_sdk::RawTxDetail>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_transaction_history_blocking(&address, &api_key, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::Vec<::com::crypto::game_sdk::RawTxDetail> get_erc20_transfer_history_blocking(::rust::String address, ::rust::String contract_address, ::com::crypto::game_sdk::QueryOption option, ::rust::String api_key) {
  ::rust::MaybeUninit<::rust::Vec<::com::crypto::game_sdk::RawTxDetail>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_erc20_transfer_history_blocking(&address, &contract_address, option, &api_key, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::Vec<::com::crypto::game_sdk::RawTxDetail> get_erc721_transfer_history_blocking(::rust::String address, ::rust::String contract_address, ::com::crypto::game_sdk::QueryOption option, ::rust::String api_key) {
  ::rust::MaybeUninit<::rust::Vec<::com::crypto::game_sdk::RawTxDetail>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_erc721_transfer_history_blocking(&address, &contract_address, option, &api_key, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// BlockScout API
::rust::Vec<::com::crypto::game_sdk::RawTokenResult> get_tokens_blocking(::rust::String blockscout_base_url, ::rust::String account_address) {
  ::rust::MaybeUninit<::rust::Vec<::com::crypto::game_sdk::RawTokenResult>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_tokens_blocking(&blockscout_base_url, &account_address, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::rust::Vec<::com::crypto::game_sdk::RawTxDetail> get_token_transfers_blocking(::rust::String blockscout_base_url, ::rust::String address, ::rust::String contract_address, ::com::crypto::game_sdk::QueryOption option) {
  ::rust::MaybeUninit<::rust::Vec<::com::crypto::game_sdk::RawTxDetail>> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_token_transfers_blocking(&blockscout_base_url, &address, &contract_address, option, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// Crypto.com Pay API
::com::crypto::game_sdk::CryptoComPaymentResponse create_payment(::rust::String secret_or_publishable_api_key, ::rust::String base_unit_amount, ::rust::String currency, const ::com::crypto::game_sdk::OptionalArguments &optional_args) {
  ::rust::MaybeUninit<::com::crypto::game_sdk::CryptoComPaymentResponse> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$create_payment(&secret_or_publishable_api_key, &base_unit_amount, &currency, optional_args, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::com::crypto::game_sdk::CryptoComPaymentResponse get_payment(::rust::String secret_or_publishable_api_key, ::rust::String payment_id) {
  ::rust::MaybeUninit<::com::crypto::game_sdk::CryptoComPaymentResponse> return$;
  ::rust::repr::PtrLen error$ = com$crypto$game_sdk$cxxbridge1$get_payment(&secret_or_publishable_api_key, &payment_id, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}
} // namespace game_sdk
} // namespace crypto
} // namespace com

extern "C" {
static_assert(::rust::detail::is_complete<::com::crypto::game_sdk::WalletConnectSessionInfo>::value, "definition of WalletConnectSessionInfo is required");
static_assert(sizeof(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>) == alignof(void *), "");
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectSessionInfo$null(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>();
}
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectSessionInfo$raw(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo> *ptr, ::com::crypto::game_sdk::WalletConnectSessionInfo *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>(raw);
}
const ::com::crypto::game_sdk::WalletConnectSessionInfo *cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectSessionInfo$get(const ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>& ptr) noexcept {
  return ptr.get();
}
::com::crypto::game_sdk::WalletConnectSessionInfo *cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectSessionInfo$release(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo>& ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectSessionInfo$drop(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectSessionInfo> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::com::crypto::game_sdk::WalletConnectSessionInfo>::value>{}(ptr);
}

void cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$new(const ::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$drop(::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$len(const ::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$capacity(const ::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr) noexcept;
const ::com::crypto::game_sdk::WalletConnectAddress *cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$data(const ::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$reserve_total(::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr, ::std::size_t new_cap) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$set_len(::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr, ::std::size_t len) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$truncate(::rust::Vec<::com::crypto::game_sdk::WalletConnectAddress> *ptr, ::std::size_t len) noexcept;

::com::crypto::game_sdk::WalletconnectClient *cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$alloc() noexcept;
void cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$dealloc(::com::crypto::game_sdk::WalletconnectClient *) noexcept;
void cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$drop(::rust::Box<::com::crypto::game_sdk::WalletconnectClient> *ptr) noexcept;

static_assert(::rust::detail::is_complete<::com::crypto::game_sdk::WalletConnectCallback>::value, "definition of WalletConnectCallback is required");
static_assert(sizeof(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>) == alignof(void *), "");
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectCallback$null(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>();
}
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectCallback$raw(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback> *ptr, ::com::crypto::game_sdk::WalletConnectCallback *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>(raw);
}
const ::com::crypto::game_sdk::WalletConnectCallback *cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectCallback$get(const ::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>& ptr) noexcept {
  return ptr.get();
}
::com::crypto::game_sdk::WalletConnectCallback *cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectCallback$release(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback>& ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$com$crypto$game_sdk$WalletConnectCallback$drop(::std::unique_ptr<::com::crypto::game_sdk::WalletConnectCallback> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::com::crypto::game_sdk::WalletConnectCallback>::value>{}(ptr);
}

void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$new(const ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$drop(::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$len(const ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$capacity(const ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr) noexcept;
const ::com::crypto::game_sdk::RawTxDetail *cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$data(const ::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$reserve_total(::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr, ::std::size_t new_cap) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$set_len(::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr, ::std::size_t len) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$truncate(::rust::Vec<::com::crypto::game_sdk::RawTxDetail> *ptr, ::std::size_t len) noexcept;

void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$new(const ::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$drop(::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$len(const ::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr) noexcept;
::std::size_t cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$capacity(const ::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr) noexcept;
const ::com::crypto::game_sdk::RawTokenResult *cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$data(const ::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$reserve_total(::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr, ::std::size_t new_cap) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$set_len(::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr, ::std::size_t len) noexcept;
void cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$truncate(::rust::Vec<::com::crypto::game_sdk::RawTokenResult> *ptr, ::std::size_t len) noexcept;
} // extern "C"

namespace rust {
inline namespace cxxbridge1 {
template <>
Vec<::com::crypto::game_sdk::WalletConnectAddress>::Vec() noexcept {
  cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$new(this);
}
template <>
void Vec<::com::crypto::game_sdk::WalletConnectAddress>::drop() noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$drop(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::WalletConnectAddress>::size() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$len(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::WalletConnectAddress>::capacity() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$capacity(this);
}
template <>
const ::com::crypto::game_sdk::WalletConnectAddress *Vec<::com::crypto::game_sdk::WalletConnectAddress>::data() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$data(this);
}
template <>
void Vec<::com::crypto::game_sdk::WalletConnectAddress>::reserve_total(::std::size_t new_cap) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$reserve_total(this, new_cap);
}
template <>
void Vec<::com::crypto::game_sdk::WalletConnectAddress>::set_len(::std::size_t len) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$set_len(this, len);
}
template <>
void Vec<::com::crypto::game_sdk::WalletConnectAddress>::truncate(::std::size_t len) {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$WalletConnectAddress$truncate(this, len);
}
template <>
::com::crypto::game_sdk::WalletconnectClient *Box<::com::crypto::game_sdk::WalletconnectClient>::allocation::alloc() noexcept {
  return cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$alloc();
}
template <>
void Box<::com::crypto::game_sdk::WalletconnectClient>::allocation::dealloc(::com::crypto::game_sdk::WalletconnectClient *ptr) noexcept {
  cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$dealloc(ptr);
}
template <>
void Box<::com::crypto::game_sdk::WalletconnectClient>::drop() noexcept {
  cxxbridge1$box$com$crypto$game_sdk$WalletconnectClient$drop(this);
}
template <>
Vec<::com::crypto::game_sdk::RawTxDetail>::Vec() noexcept {
  cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$new(this);
}
template <>
void Vec<::com::crypto::game_sdk::RawTxDetail>::drop() noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$drop(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::RawTxDetail>::size() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$len(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::RawTxDetail>::capacity() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$capacity(this);
}
template <>
const ::com::crypto::game_sdk::RawTxDetail *Vec<::com::crypto::game_sdk::RawTxDetail>::data() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$data(this);
}
template <>
void Vec<::com::crypto::game_sdk::RawTxDetail>::reserve_total(::std::size_t new_cap) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$reserve_total(this, new_cap);
}
template <>
void Vec<::com::crypto::game_sdk::RawTxDetail>::set_len(::std::size_t len) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$set_len(this, len);
}
template <>
void Vec<::com::crypto::game_sdk::RawTxDetail>::truncate(::std::size_t len) {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTxDetail$truncate(this, len);
}
template <>
Vec<::com::crypto::game_sdk::RawTokenResult>::Vec() noexcept {
  cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$new(this);
}
template <>
void Vec<::com::crypto::game_sdk::RawTokenResult>::drop() noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$drop(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::RawTokenResult>::size() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$len(this);
}
template <>
::std::size_t Vec<::com::crypto::game_sdk::RawTokenResult>::capacity() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$capacity(this);
}
template <>
const ::com::crypto::game_sdk::RawTokenResult *Vec<::com::crypto::game_sdk::RawTokenResult>::data() const noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$data(this);
}
template <>
void Vec<::com::crypto::game_sdk::RawTokenResult>::reserve_total(::std::size_t new_cap) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$reserve_total(this, new_cap);
}
template <>
void Vec<::com::crypto::game_sdk::RawTokenResult>::set_len(::std::size_t len) noexcept {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$set_len(this, len);
}
template <>
void Vec<::com::crypto::game_sdk::RawTokenResult>::truncate(::std::size_t len) {
  return cxxbridge1$rust_vec$com$crypto$game_sdk$RawTokenResult$truncate(this, len);
}
} // namespace cxxbridge1
} // namespace rust
