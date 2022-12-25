#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

template <typename T>
void printVector(const std::vector<T>& v) {
  typename std::vector<T>::const_iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}




#endif
