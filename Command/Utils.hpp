#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

template <typename T>
void printVector(const std::vector<T>& v) {
  typename std::vector<T>::const_iterator it;
  std::cout << "Vecteur = " << std::endl;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << "|" << std::endl;
  }
}




#endif
