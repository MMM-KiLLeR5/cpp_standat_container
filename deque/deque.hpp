#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
class Deque {
  size_t size_ = 0;
  size_t ptr_buff_size_ = 0;
  static const size_t kNodeSize = 512;
  std::vector<T*> deque_ = std::vector<T*>();
  //координаты первого и следующего за последним элементов
  size_t x_beg_ = 0;  // по вертикали
  size_t y_beg_ = 0;  // по горизонтали
  size_t x_end_ = 0;
  size_t y_end_ = 0;

  void fill_with_nodes(size_t from, size_t upto);
  void fill_nodes(size_t from, size_t upto, const T& value);
  void resize();
  void destroy();

  template <bool IsConst>
  class CommonIterator
      : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    using value_type = typename std::conditional<IsConst, const T, T>::type;
    using pointer = typename std::conditional<IsConst, const T*, T*>::type;
    using reference = typename std::conditional<IsConst, const T&, T&>::type;
    using iterator_category = std::random_access_iterator_tag;

   private:
    typename std::conditional<IsConst, const Deque<T>*, Deque<T>*>::type
        deque_ptr_ = nullptr;
    size_t shift_ = 0;

   public:
    CommonIterator(Deque<T>* deque_ptr, size_t shift)
        : deque_ptr_(deque_ptr), shift_(shift) {}
    CommonIterator(const Deque<T>* deque_ptr, size_t shift)
        : deque_ptr_(deque_ptr), shift_(shift) {}
    ~CommonIterator() = default;

    CommonIterator& operator++();
    CommonIterator operator++(int);
    CommonIterator& operator--();
    CommonIterator operator--(int);
    CommonIterator operator+(size_t value) const;
    CommonIterator operator-(size_t value) const;
    CommonIterator& operator+=(size_t value) const;

    bool operator>(const CommonIterator& other) const;
    bool operator==(const CommonIterator& other) const;
    bool operator<(const CommonIterator& other) const;
    bool operator!=(const CommonIterator& other) const;
    bool operator>=(const CommonIterator& other) const;
    bool operator<=(const CommonIterator& other) const;

    ssize_t operator-(const CommonIterator& other) const;

    reference operator*() const;
    pointer operator->() const;
  };

 public:
  using iterator = CommonIterator<false>;
  using const_iterator = CommonIterator<true>;
  using reverse_iterator = std::reverse_iterator<CommonIterator<false>>;
  using const_reverse_iterator = std::reverse_iterator<CommonIterator<true>>;

  Deque();
  Deque(const Deque& deque);
  explicit Deque(size_t count);
  Deque(size_t count, const T& value);
  ~Deque();
  Deque& operator=(const Deque& other);

  size_t size() const { return size_; }
  bool empty() { return size_ == 0; }

  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;
  T& at(size_t idx);
  const T& at(size_t idx) const;

  void push_back(T value);
  void pop_back();
  void push_front(T value);
  void pop_front();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator crbegin() const;

  const_reverse_iterator crend() const;

  template <bool IsConst>
  void insert(CommonIterator<IsConst> iter, const T& value);

  template <bool IsConst>
  void erase(CommonIterator<IsConst> iter);
};
