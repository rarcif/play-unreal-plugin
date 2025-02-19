#pragma warning(disable:4583)
#pragma warning(disable:4582)

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <iterator>
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

class Opaque;

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

#ifndef CXXBRIDGE1_RUST_BITCOPY_T
#define CXXBRIDGE1_RUST_BITCOPY_T
struct unsafe_bitcopy_t final {
  explicit unsafe_bitcopy_t() = default;
};
#endif // CXXBRIDGE1_RUST_BITCOPY_T

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
union MaybeUninit {
  T value;
  void *operator new(::std::size_t sz) { return detail::operator_new<T>{}(sz); }
  MaybeUninit() {}
  ~MaybeUninit() {}
};

namespace {
namespace repr {
struct PtrLen final {
  void *ptr;
  ::std::size_t len;
};
} // namespace repr

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
} // namespace
} // namespace cxxbridge1
} // namespace rust

namespace org {
  namespace defi_wallet_core {
    struct U256;
    struct U256WithOverflow;
  }
}

namespace org {
namespace defi_wallet_core {
#ifndef CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256
#define CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256
struct U256 final {
  ::std::array<::std::uint64_t, 4> data;

  /// Convert to Decimal String
  ::rust::String to_string() const noexcept;

  /// Addition which saturates at the maximum value.
  ::org::defi_wallet_core::U256 saturating_add(::org::defi_wallet_core::U256 other) const noexcept;

  /// Subtraction which saturates at zero.
  ::org::defi_wallet_core::U256 saturating_sub(::org::defi_wallet_core::U256 other) const noexcept;

  /// Multiplication which saturates at maximum value.
  ::org::defi_wallet_core::U256 saturating_mul(::org::defi_wallet_core::U256 other) const noexcept;

  /// Returns the addition along with a boolean indicating whether an arithmetic overflow
  /// would occur. If an overflow would have occurred then the wrapped value is returned.
  ::org::defi_wallet_core::U256WithOverflow overflowing_add(::org::defi_wallet_core::U256 other) const noexcept;

  /// Returns the subtraction along with a boolean indicating whether an arithmetic overflow
  /// would occur. If an overflow would have occurred then the wrapped value is returned.
  ::org::defi_wallet_core::U256WithOverflow overflowing_sub(::org::defi_wallet_core::U256 other) const noexcept;

  /// Returns the multiplication along with a boolean indicating whether an arithmetic overflow
  /// would occur. If an overflow would have occurred then the wrapped value is returned.
  ::org::defi_wallet_core::U256WithOverflow overflowing_mul(::org::defi_wallet_core::U256 other) const noexcept;

  /// Returns the fast exponentiation by squaring along with a boolean indicating whether an
  /// arithmetic overflow would occur. If an overflow would have occurred then the wrapped
  /// value is returned.
  ::org::defi_wallet_core::U256WithOverflow overflowing_pow(::org::defi_wallet_core::U256 other) const noexcept;

  /// Negates self in an overflowing fashion.
  /// Returns !self + 1 using wrapping operations to return the value that represents
  /// the negation of this unsigned value. Note that for positive unsigned values
  /// overflow always occurs, but negating 0 does not overflow.
  ::org::defi_wallet_core::U256WithOverflow overflowing_neg() const noexcept;

  /// add, exception is rasided if overflow
  ::org::defi_wallet_core::U256 add(::org::defi_wallet_core::U256 other) const;

  /// sub, exception is rasided if overflow
  ::org::defi_wallet_core::U256 sub(::org::defi_wallet_core::U256 other) const;

  /// mul, exception is rasided if overflow
  ::org::defi_wallet_core::U256 mul(::org::defi_wallet_core::U256 other) const;

  /// pow, exception is rasided if overflow
  ::org::defi_wallet_core::U256 pow(::org::defi_wallet_core::U256 other) const;

  /// Negates self in an overflowing fashion.
  /// Returns !self + 1 using wrapping operations to return the value that represents
  /// the negation of this unsigned value.
  ::org::defi_wallet_core::U256 neg() const noexcept;

  /// Returns a pair `(self / other)`
  ::org::defi_wallet_core::U256 div(::org::defi_wallet_core::U256 other) const noexcept;

  /// Returns a pair `(self % other)`
  ::org::defi_wallet_core::U256 rem(::org::defi_wallet_core::U256 other) const noexcept;

  /// Write to the slice in big-endian format.
  void to_big_endian(::rust::Vec<::std::uint8_t> &bytes) const noexcept;

  /// Write to the slice in little-endian format.
  void to_little_endian(::rust::Vec<::std::uint8_t> &bytes) const noexcept;

  /// Format the output for the user which prefer to see values in ether (instead of wei)
  /// Divides the input by 1e18
  ::org::defi_wallet_core::U256 format_ether() const noexcept;

  /// Convert to common ethereum unit types: ether, gwei, or wei
  /// formatted in _ETH decimals_ (e.g. "1.50000...") wrapped as string
  ::rust::String format_units(::rust::String units) const;

  bool operator==(const U256 &) const noexcept;
  bool operator!=(const U256 &) const noexcept;
  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256

#ifndef CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256WithOverflow
#define CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256WithOverflow
struct U256WithOverflow final {
  ::org::defi_wallet_core::U256 result;
  bool overflow;

  bool operator==(const U256WithOverflow &) const noexcept;
  bool operator!=(const U256WithOverflow &) const noexcept;
  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_org$defi_wallet_core$U256WithOverflow

extern "C" {
bool org$defi_wallet_core$cxxbridge1$U256$operator$eq(const U256 &, const U256 &) noexcept;
bool org$defi_wallet_core$cxxbridge1$U256WithOverflow$operator$eq(const U256WithOverflow &, const U256WithOverflow &) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$u256_from_dec_str(::rust::String *value, ::org::defi_wallet_core::U256 *return$) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$u256_from_str_radix(::rust::String *txt, ::std::uint32_t radix, ::org::defi_wallet_core::U256 *return$) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$u256_max_value() noexcept;

void org$defi_wallet_core$cxxbridge1$U256$to_string(const ::org::defi_wallet_core::U256 &self, ::rust::String *return$) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$saturating_add(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$saturating_sub(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$saturating_mul(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256WithOverflow org$defi_wallet_core$cxxbridge1$U256$overflowing_add(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256WithOverflow org$defi_wallet_core$cxxbridge1$U256$overflowing_sub(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256WithOverflow org$defi_wallet_core$cxxbridge1$U256$overflowing_mul(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256WithOverflow org$defi_wallet_core$cxxbridge1$U256$overflowing_pow(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256WithOverflow org$defi_wallet_core$cxxbridge1$U256$overflowing_neg(const ::org::defi_wallet_core::U256 &self) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$U256$add(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other, ::org::defi_wallet_core::U256 *return$) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$U256$sub(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other, ::org::defi_wallet_core::U256 *return$) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$U256$mul(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other, ::org::defi_wallet_core::U256 *return$) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$U256$pow(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other, ::org::defi_wallet_core::U256 *return$) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$neg(const ::org::defi_wallet_core::U256 &self) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$div(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$rem(const ::org::defi_wallet_core::U256 &self, ::org::defi_wallet_core::U256 other) noexcept;

void org$defi_wallet_core$cxxbridge1$U256$to_big_endian(const ::org::defi_wallet_core::U256 &self, ::rust::Vec<::std::uint8_t> &bytes) noexcept;

void org$defi_wallet_core$cxxbridge1$U256$to_little_endian(const ::org::defi_wallet_core::U256 &self, ::rust::Vec<::std::uint8_t> &bytes) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$parse_ether(::rust::String *eth, ::org::defi_wallet_core::U256 *return$) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$parse_units(::rust::String *amount, ::rust::String *units, ::org::defi_wallet_core::U256 *return$) noexcept;

::org::defi_wallet_core::U256 org$defi_wallet_core$cxxbridge1$U256$format_ether(const ::org::defi_wallet_core::U256 &self) noexcept;

::rust::repr::PtrLen org$defi_wallet_core$cxxbridge1$U256$format_units(const ::org::defi_wallet_core::U256 &self, ::rust::String *units, ::rust::String *return$) noexcept;
} // extern "C"

bool U256::operator==(const U256 &rhs) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$operator$eq(*this, rhs);
}

bool U256::operator!=(const U256 &rhs) const noexcept {
  return !(*this == rhs);
}

bool U256WithOverflow::operator==(const U256WithOverflow &rhs) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256WithOverflow$operator$eq(*this, rhs);
}

bool U256WithOverflow::operator!=(const U256WithOverflow &rhs) const noexcept {
  return !(*this == rhs);
}

  /// Convert from a decimal string.
::org::defi_wallet_core::U256 u256(::rust::String value) {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$u256_from_dec_str(&value, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// Converts a string slice in a given base to an integer. Only supports radixes of 10
  /// and 16.
::org::defi_wallet_core::U256 u256(::rust::String txt, ::std::uint32_t radix) {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$u256_from_str_radix(&txt, radix, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// The maximum value which can be inhabited by this type.
::org::defi_wallet_core::U256 u256_max_value() noexcept {
  return org$defi_wallet_core$cxxbridge1$u256_max_value();
}

::rust::String U256::to_string() const noexcept {
  ::rust::MaybeUninit<::rust::String> return$;
  org$defi_wallet_core$cxxbridge1$U256$to_string(*this, &return$.value);
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::saturating_add(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$saturating_add(*this, other);
}

::org::defi_wallet_core::U256 U256::saturating_sub(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$saturating_sub(*this, other);
}

::org::defi_wallet_core::U256 U256::saturating_mul(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$saturating_mul(*this, other);
}

::org::defi_wallet_core::U256WithOverflow U256::overflowing_add(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$overflowing_add(*this, other);
}

::org::defi_wallet_core::U256WithOverflow U256::overflowing_sub(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$overflowing_sub(*this, other);
}

::org::defi_wallet_core::U256WithOverflow U256::overflowing_mul(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$overflowing_mul(*this, other);
}

::org::defi_wallet_core::U256WithOverflow U256::overflowing_pow(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$overflowing_pow(*this, other);
}

::org::defi_wallet_core::U256WithOverflow U256::overflowing_neg() const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$overflowing_neg(*this);
}

::org::defi_wallet_core::U256 U256::add(::org::defi_wallet_core::U256 other) const {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$U256$add(*this, other, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::sub(::org::defi_wallet_core::U256 other) const {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$U256$sub(*this, other, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::mul(::org::defi_wallet_core::U256 other) const {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$U256$mul(*this, other, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::pow(::org::defi_wallet_core::U256 other) const {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$U256$pow(*this, other, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::neg() const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$neg(*this);
}

::org::defi_wallet_core::U256 U256::div(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$div(*this, other);
}

::org::defi_wallet_core::U256 U256::rem(::org::defi_wallet_core::U256 other) const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$rem(*this, other);
}

void U256::to_big_endian(::rust::Vec<::std::uint8_t> &bytes) const noexcept {
  org$defi_wallet_core$cxxbridge1$U256$to_big_endian(*this, bytes);
}

void U256::to_little_endian(::rust::Vec<::std::uint8_t> &bytes) const noexcept {
  org$defi_wallet_core$cxxbridge1$U256$to_little_endian(*this, bytes);
}

  /// Converts the input to a U256 and converts from Ether to Wei.
::org::defi_wallet_core::U256 parse_ether(::rust::String eth) {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$parse_ether(&eth, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

  /// Multiplies the provided amount with 10^{units} provided.
::org::defi_wallet_core::U256 parse_units(::rust::String amount, ::rust::String units) {
  ::rust::MaybeUninit<::org::defi_wallet_core::U256> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$parse_units(&amount, &units, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}

::org::defi_wallet_core::U256 U256::format_ether() const noexcept {
  return org$defi_wallet_core$cxxbridge1$U256$format_ether(*this);
}

::rust::String U256::format_units(::rust::String units) const {
  ::rust::MaybeUninit<::rust::String> return$;
  ::rust::repr::PtrLen error$ = org$defi_wallet_core$cxxbridge1$U256$format_units(*this, &units, &return$.value);
  if (error$.ptr) {
    throw ::rust::impl<::rust::Error>::error(error$);
  }
  return ::std::move(return$.value);
}
} // namespace defi_wallet_core
} // namespace org
