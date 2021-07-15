#ifndef B1_POLICY_HPP
#define B1_POLICY_HPP

template<class T>
struct BracketsPolicy
{
  using iterator = typename T::size_type;
  using elementValue = typename T::value_type;
  static iterator begin(const T& )
  {
    return 0;
  }
  static iterator end(const T& vector)
  {
    return vector.size();
  }
  static elementValue &get(T& vector, iterator index)
  {
    return vector[index];
  }
};

template<class T>
struct AtPolicy
{
  using iterator = typename T::size_type;
  using elementValue = typename T::value_type;
  static iterator begin(const T& )
  {
    return 0;
  }
  static iterator end(const T& vector)
  {
    return vector.size();
  }
  static elementValue &get(T& vector, iterator index)
  {
    return vector.at(index);
  }
};

template<class T>
struct IteratorPolicy
{
  using iterator = typename T::iterator;
  using elementValue = typename T::value_type;
  static iterator begin(T& list)
  {
    return list.begin();
  }
  static iterator end(T& list)
  {
    return list.end();
  }
  static elementValue &get(T& , iterator iterat)
  {
    return *iterat;
  }
};

#endif
