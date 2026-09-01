#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
  *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    this->Data = other.Data;
  }
  return (*this);
}

BitcoinExchange::~BitcoinExchange() {
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
  if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    return false;

  for (size_t i = 0; i < date.length(); i++)
  {
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i]))
      return false;
  }

  int year = std::stoi(date.substr(0, 4));
  int month = std::stoi(date.substr(5, 2));
  int day = std::stoi(date.substr(8, 2));

  std::tm time = {0, 0, 0, day, month - 1, year - 1900};
  std::mktime(&time);

  if (time.tm_mday != day || time.tm_mon != month - 1 || time.tm_year != year - 1900)
    return false;
  if (year < 2009) 
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;

  return true;
}

bool BitcoinExchange::isValidValue(const std::string &value) const
{
  if (value.empty()) return false;

  char *endptr;
  double val = std::strtod(value.c_str(), &endptr);

  if (value.c_str() == endptr || *endptr != '\0') {
    std::cerr << "Error: Invalid numeric format => " << value << std::endl;
    return false;
  }

  if (val < 0) {
    std::cerr << "Error: Value cannot be negative." << std::endl;
    return false;
  }

  else if (val > 1000)
  {
    std::cerr << "Error: Value exceeds maximum allowed limit (1000)." << std::endl;
    return false;
  }

  return true;
}
