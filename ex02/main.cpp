#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Error: No input sequence provided.\n"
              << "Usage: " << argv[0] << " <positive integer sequence>\n"
              << "Example: " << argv[0] << " 3 5 9 7 4" << std::endl;
    return 1;
  }

  PmergeMe sequence;

  try {
    sequence.processInput(argc, argv);
    sequence.sortData();
    sequence.printResults(argv, argc);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl; 
    return 1;
  }

  return 0;
}
