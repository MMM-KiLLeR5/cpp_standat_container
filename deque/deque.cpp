#include "deque.hpp"

template <typename T>
typename Deque<T>::iterator Deque<T>::begin() {
  iterator iter(this, 0);
  return iter;
}

template <typename T>
typename Deque<T>::iterator Deque<T>::end() {
  iterator iter(this, size_);
  return iter;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const {
  const_iterator iter(this, 0);
  return iter;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cend() const {
  const_iterator iter(this, size_);
  return iter;
}

template <typename T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin() {
  iterator iter(this, size_);
  reverse_iterator r_it(iter);
  return r_it;
}

template <typename T>
typename Deque<T>::reverse_iterator Deque<T>::rend() {
  iterator iter(this, 0);
  reverse_iterator r_it(iter);
  return r_it;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const {
  const_iterator iter(this, size_);
  const_reverse_iterator r_it(iter);
  return r_it;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const {
  const_iterator iter(this, 0);
  const_reverse_iterator r_it(iter);
  return r_it;
}

template <typename T>
template <bool IsConst>
void Deque<T>::insert(CommonIterator<IsConst> iter, const T& value) {
  if (iter == end()) {
    push_back(value);
  } else {
    auto last_element = *(end() - 1);
    auto it_tmp = end() - 1;
    while (it_tmp > iter) {
      std::swap(*iter, *it_tmp);
      --it_tmp;
    }
    *iter = value;
    push_back(last_element);
  }
}

template <typename T>
template <bool IsConst>
void Deque<T>::erase(CommonIterator<IsConst> iter) {
  while (iter != end() - 1) {
    *iter = *(iter + 1);
    ++iter;
  }
  pop_back();
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>::reference
Deque<T>::CommonIterator<IsConst>::operator*() const {
  auto first_x = deque_ptr_->x_beg_;
  auto first_y = deque_ptr_->y_beg_;
  auto deque = deque_ptr_->deque_;
  auto overall_shift = first_x * kNodeSize + first_y + shift_;
  auto v_shift = overall_shift / kNodeSize;
  auto h_shift = overall_shift % kNodeSize;
  return deque[v_shift][h_shift];
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>::pointer
Deque<T>::CommonIterator<IsConst>::operator->() const {
  auto first_x = deque_ptr_->x_beg_;
  auto first_y = deque_ptr_->y_beg_;
  auto deque = deque_ptr_->deque_;
  auto overall_shift = first_x * kNodeSize + first_y + shift_;
  auto v_shift = overall_shift / kNodeSize;
  auto h_shift = overall_shift % kNodeSize;
  return deque[v_shift] + h_shift;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>&
Deque<T>::CommonIterator<IsConst>::operator++() {
  ++shift_;
  return *this;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>
Deque<T>::CommonIterator<IsConst>::operator++(int) {
  CommonIterator tmp_iter(deque_ptr_, shift_);
  ++(*this);
  return tmp_iter;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>&
Deque<T>::CommonIterator<IsConst>::operator--() {
  --shift_;
  return *this;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>
Deque<T>::CommonIterator<IsConst>::operator--(int) {
  CommonIterator tmp_iter(deque_ptr_, shift_);
  --(*this);
  return tmp_iter;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>
Deque<T>::CommonIterator<IsConst>::operator+(const size_t kValue) const {
  CommonIterator iter_copy(deque_ptr_, shift_);
  for (size_t i = 0; i < kValue; ++i) {
    ++iter_copy;
  }
  return iter_copy;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>
Deque<T>::CommonIterator<IsConst>::operator-(const size_t kValue) const {
  CommonIterator iter_copy(deque_ptr_, shift_);
  for (size_t i = 0; i < kValue; ++i) {
    --iter_copy;
  }
  return iter_copy;
}

template <typename T>
template <bool IsConst>
typename Deque<T>::template CommonIterator<IsConst>&
Deque<T>::CommonIterator<IsConst>::operator+=(size_t value) const {
  for (size_t i = 0; i < value; ++i) {
    ++(*this);
  }
  return *this;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator>(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ > other.shift_;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator==(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ == other.shift_;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator<(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ < other.shift_;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator!=(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ != other.shift_;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator>=(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ >= other.shift_;
}

template <typename T>
template <bool IsConst>
bool Deque<T>::CommonIterator<IsConst>::operator<=(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ <= other.shift_;
}

template <typename T>
template <bool IsConst>
ssize_t Deque<T>::CommonIterator<IsConst>::operator-(
    const Deque::CommonIterator<IsConst>& other) const {
  return shift_ - other.shift_;
}
template <typename T>
Deque<T>::Deque() {
  try {
    deque_.resize(1);
    ptr_buff_size_ = 1;
    size_ = 0;
    fill_with_nodes(0, ptr_buff_size_);
  } catch (...) {
    ptr_buff_size_ = 0;
    size_ = 0;
    throw;
  }
}

template <typename T>
Deque<T>::Deque(const Deque& deque) {
  destroy();
  try {
    deque_.resize(deque.size_ / kNodeSize + 1);
  } catch (...) {
    deque_.clear();
    throw;
  }
  ptr_buff_size_ = deque.ptr_buff_size_;
  size_ = deque.size_;
  try {
    fill_with_nodes(0, ptr_buff_size_);
  } catch (...) {
    throw;
  }
  for (size_t i = deque.x_beg_, j = deque.y_beg_;
       (i <= deque.x_end_ || j < deque.y_end_) && (i != 0 && j != 0);
       i += ((j + 1) / kNodeSize), j = ((j + 1) % kNodeSize)) {
    new (deque_[i] + j) T(deque.deque_[i][j]);
  }
  x_beg_ = deque.x_beg_;
  x_end_ = deque.x_end_;
  y_beg_ = deque.y_beg_;
  y_end_ = deque.y_end_;
}

template <typename T>
Deque<T>::Deque(size_t count) {
  try {
    deque_.resize(count / kNodeSize + 1);
    ptr_buff_size_ = count / kNodeSize + 1;
    size_ = count;
    fill_with_nodes(0, ptr_buff_size_);
  } catch (...) {
    ptr_buff_size_ = 0;
    size_ = 0;
    throw;
  }
  for (size_t i = 0; i < ptr_buff_size_; ++i) {
    for (size_t j = 0; j < kNodeSize; ++j) {
      if (i * kNodeSize + j < count) {
        new (deque_[i] + j) T();
      }
    }
  }
  x_end_ = count / kNodeSize;
  y_end_ = count % kNodeSize;
  x_beg_ = 0;
  y_beg_ = 0;
}

template <typename T>
Deque<T>::Deque(size_t count, const T& value) {
  try {
    deque_.resize(count / kNodeSize + 1);
  } catch (...) {
    throw;
  }

  try {
    ptr_buff_size_ = count / kNodeSize + 1;
    size_ = count;
    fill_with_nodes(0, ptr_buff_size_);
  } catch (...) {
    ptr_buff_size_ = 0;
    size_ = 0;
    throw;
  }

  size_t i_idx = 0;
  size_t j_idx = 0;
  try {
    for (; i_idx < ptr_buff_size_; ++i_idx) {
      j_idx = 0;
      for (; j_idx < kNodeSize; ++j_idx) {
        if (i_idx * kNodeSize + j_idx >= count) {
          break;
        }
        new (deque_[i_idx] + j_idx) T(value);
      }
      if (i_idx * kNodeSize + j_idx >= count) {
        break;
      }
    }
  } catch (...) {
    for (size_t i = 0; i <= i_idx; ++i) {
      for (size_t j = 0; j < j_idx; ++j) {
        (deque_[i] + j)->~T();
      }
    }
    destroy();
    ptr_buff_size_ = 0;
    size_ = 0;
    throw;
  }

  x_end_ = count / kNodeSize;
  y_end_ = count % kNodeSize;
  x_beg_ = 0;
  y_beg_ = 0;
}

template <typename T>
Deque<T>::~Deque() {
  destroy();
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
  destroy();
  try {
    deque_.resize(other.ptr_buff_size_);
    ptr_buff_size_ = other.ptr_buff_size_;
    size_ = other.size_;
    fill_with_nodes(0, ptr_buff_size_);
  } catch (...) {
    ptr_buff_size_ = 0;
    size_ = 0;
    throw;
  }
  for (size_t i = other.x_beg_, j = other.y_beg_;
       i < other.x_end_ || j < other.y_end_;
       i += ((j + 1) / kNodeSize), j = (j + 1) % kNodeSize) {
    new (deque_[i] + j) T(other.deque_[i][j]);
  }
  x_beg_ = other.x_beg_;
  x_end_ = other.x_end_;
  y_beg_ = other.y_beg_;
  y_end_ = other.y_end_;
  return *this;
}

template <typename T>
T& Deque<T>::operator[](size_t idx) {
  return deque_[x_beg_ + idx / kNodeSize][(y_beg_ + idx) % kNodeSize];
}

template <typename T>
const T& Deque<T>::operator[](size_t idx) const {
  return deque_[x_beg_ + idx / kNodeSize][(y_beg_ + idx) % kNodeSize];
}

template <typename T>
T& Deque<T>::at(size_t idx) {
  if (idx >= size_) {
    throw std::out_of_range("The index is out of range!");
  }
  return deque_[x_beg_ + (idx + y_beg_) / kNodeSize]
  [(y_beg_ + idx) % kNodeSize];
}

template <typename T>
const T& Deque<T>::at(size_t idx) const {
  if (idx >= size_) {
    throw std::out_of_range("The index is out of range!");
  }
  return deque_[x_beg_ + idx / kNodeSize][(y_beg_ + idx) % kNodeSize];
}

template <typename T>
void Deque<T>::push_back(T value) {
  if (x_end_ == ptr_buff_size_ - 1 && y_end_ == kNodeSize) {
    resize();
  }
  if (y_end_ == kNodeSize) {
    ++x_end_;
    y_end_ = 0;
  }
  new (deque_[x_end_] + y_end_) T(value);
  ++y_end_;
  ++size_;
}

template <typename T>
void Deque<T>::pop_back() {
  --size_;
  if (y_end_ == 0) {
    --x_end_;
    y_end_ = kNodeSize - 1;
  } else {
    --y_end_;
  }
}

template <typename T>
void Deque<T>::push_front(T value) {
  if (x_beg_ == 0 && y_beg_ == 0) {
    resize();
  }
  if (y_beg_ == 0) {
    --x_beg_;
    y_beg_ = kNodeSize - 1;
  } else {
    --y_beg_;
  }
  new (deque_[x_beg_] + y_beg_) T(value);
  ++size_;
}

template <typename T>
void Deque<T>::pop_front() {
  --size_;
  if (y_beg_ == kNodeSize - 1) {
    ++x_beg_;
    y_beg_ = 0;
  } else {
    ++y_beg_;
  }
}

template <typename T>
void Deque<T>::fill_with_nodes(size_t from, size_t upto) {
  size_t idx = from;
  try {
    for (; idx < upto; ++idx) {
      T* node = reinterpret_cast<T*>(new int8_t[kNodeSize * sizeof(T)]);
      deque_[idx] = node;
    }
  } catch (...) {
    for (size_t j = from; j < idx; ++j) {
      delete[] deque_[j];
    }
    throw;
  }
}

template <typename T>
void Deque<T>::fill_nodes(size_t from, size_t upto, const T& value) {
  for (size_t i = 0; i < ptr_buff_size_; ++i) {
    for (size_t j = 0; j < kNodeSize; ++j) {
      if (i * kNodeSize + j >= from && i * kNodeSize + j < upto) {
        new (deque_[i] + j) T(value);
      }
    }
  }
}

template <typename T>
void Deque<T>::resize() {
  std::vector<T*> new_base(3 * (x_end_ - x_beg_ + 1), nullptr);
  size_t new_x_beg = x_end_ - x_beg_ + 1;
  size_t new_x_end = 2 * (x_end_ - x_beg_) + 1;
  for (size_t i = x_beg_, j = new_x_beg; i <= x_end_; ++i, ++j) {
    new_base[j] = deque_[i];
  }
  for (size_t i = 0; i < x_beg_; ++i) {
    delete[] deque_[i];
  }
  for (size_t i = x_end_ + 1; i < ptr_buff_size_; ++i) {
    delete[] deque_[i];
  }
  ptr_buff_size_ = 3 * (x_end_ - x_beg_ + 1);
  x_beg_ = new_x_beg;
  x_end_ = new_x_end;
  deque_ = new_base;
  try {
    fill_with_nodes(0, x_beg_);
    fill_with_nodes(x_end_ + 1, ptr_buff_size_);
  } catch (...) {
    throw;
  }
}

template <typename T>
void Deque<T>::destroy() {
  for (size_t i = 0; i < ptr_buff_size_; ++i) {
    delete[] deque_[i];
  }
  deque_.clear();
}
