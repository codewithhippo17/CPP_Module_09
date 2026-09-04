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

std::vector<int> PmergeMe::generateJacobsthal(int n)
{
  std::vector<int> insertionSequence;

  if (n == 0)
    return insertionSequence;

  insertionSequence.push_back(1);

  int prevJacob = 1;
  int currJacob = 3;
  int lastPushed = 1;
  int nextJacob = 0;

  while (currJacob <= n)
  {
    insertionSequence.push_back(currJacob);

    for (int i = currJacob - 1; i > lastPushed; i--)
      insertionSequence.push_back(i);

    lastPushed = currJacob;
    nextJacob = currJacob + 2 * prevJacob;
    prevJacob = currJacob;
    currJacob = nextJacob;
  }

  for (int i = n; i > lastPushed; --i)
    insertionSequence.push_back(i);

  return insertionSequence;
}


void PmergeMe::processInput(int argc, char **argv)
{
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
      throw std::runtime_error("Error: Empty or whitespace-only argument provided.");

    std::stringstream ss(arg);
    std::string num;

    while (ss >> num)
    {
      for (size_t j = 0; j < num.length(); ++j)
      {
        if (j == 0 && num[j] == '+')
          continue;
        if (!isdigit(num[j]))
                    throw std::runtime_error("Error: Invalid character encountered in sequence.");
      }

      long value = std::atol(num.c_str());

      if (std::find(_vectorData.begin(), _vectorData.end(), value) != _vectorData.end())
                throw std::runtime_error("Error: Duplicate numbers are not allowed.");

      if (value < 0 || value > INT_MAX)
                throw std::runtime_error("Error: Number out of bounds (must be a positive integer up to INT_MAX).");

      _vectorData.push_back(static_cast<int>(value));
      _dequeData.push_back(static_cast<int>(value));
    }
  }

  if (_vectorData.size() < 2 || _dequeData.size() < 2)
        throw std::runtime_error("Error: Sequence must contain at least 2 numbers to be sorted.");
}
