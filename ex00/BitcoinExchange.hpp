#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>

class BitcoinExchange {
private:

	std::map<std::string, float> Data;

	bool isValidDate(const std::string &date) const;
	bool isValidValue(const std::string &value) const;

public:

  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &other);
  ~BitcoinExchange();


	void loadDatabase(const std::string &filename);
	void processInput(const std::string &filename);

};

#endif // BITCOINEXCHANGE_HPP
