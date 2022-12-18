#ifndef ROCK_HPP
#define ROCK_HPP

void playGame();
bool playAgain();
std::string getNextMove();
unsigned getPlayerBet(unsigned, unsigned);
unsigned getComputerBet(unsigned, unsigned);
std::string getPlayerChoice();
std::string getComputerChoice();
bool isDigits(const std::string&);
void changeNextMove(std::string&);
std::string getItem(const unsigned);
std::string getWinner(const std::string&, const std::string&);
void updateBankInfo(const std::string&, const unsigned, unsigned&, unsigned&);

#endif
