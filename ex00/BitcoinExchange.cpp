#include "BitcoinExchange.hpp"
#include <ctime>

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

  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());

  struct tm timeStruct = {};
  timeStruct.tm_mday = day;
  timeStruct.tm_mon = month - 1;
  timeStruct.tm_year = year - 1900;
  
  mktime(&timeStruct);

  if (timeStruct.tm_mday != day || timeStruct.tm_mon != month - 1 || timeStruct.tm_year != year - 1900)
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

void BitcoinExchange::loadDatabase(const std::string &filename)
{
  std::ifstream file(filename.c_str());

  if (!file.is_open()) {
    std::cerr << "Error: Could not open database file => " << filename << std::endl;
    return;
  }

  std::string line;
  std::getline(file, line);

  while (std::getline(file, line))
  {
    size_t delimiter = line.find(",");
    if (delimiter == std::string::npos)
      continue;
    std::string date = line.substr(0, delimiter);
    std::string value = line.substr(delimiter + 1);

    if (isValidDate(date))
      Data[date] = std::strtod(value.c_str(), NULL);
  }

  file.close();
}

void BitcoinExchange::processInput(const std::string &filename)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "Error: Could not open input file => " << filename << std::endl;
    return;
  }

  std::string firstLine;
  std::getline(file, firstLine);
  if (firstLine != "date | value") {
    std::cerr << "Error: Invalid header format. Expected 'date | value'." << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    size_t delimiter = line.find(" | ");
    if (delimiter == std::string::npos) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }

    std::string date = line.substr(0, delimiter);
    std::string value = line.substr(delimiter + 3);
    if (!isValidDate(date)) {
      std::cerr << "Error: bad input => " << date << std::endl;
      continue;
    }
    else if (!isValidValue(value))
      continue;

    std::map<std::string, float>::iterator it = Data.upper_bound(date);
    if (it == Data.begin()) {
      std::cerr << "Error: no exchange rate available for date => " << date << std::endl;
      continue;
    }
    it--;

    float exchangeRate = it->second;
    std::cout << date << " => " << value << " = " << exchangeRate * std::atof(value.c_str()) << std::endl;
  }

  file.close();
}
