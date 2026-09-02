#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
  _vectorData = other._vectorData;
  _dequeData = other._dequeData;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
  if (this != &other) {
    _vectorData = other._vectorData;
    _dequeData = other._dequeData;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}



