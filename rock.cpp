// ROCK PAPER SCISSORS

#include <iostream>
#include <string>
#include <random>
#include "rock.hpp"

const unsigned maxBank{100};
const std::string playerName{"Player"};
const std::string computerName{"The computer"};
const std::string separator{"----------------------------------------\n\n"};

int main()
{
	std::cout << "ROCK PAPER SCISSORS\n\n";
	
	bool gameIsRunning{true};
	
	while (gameIsRunning)
	{
		playGame();
		
		gameIsRunning = playAgain();
	}
	
	std::cout << "Bye!\n";
	return 0;
}

void playGame()
{	
	unsigned playerBank{maxBank};
	unsigned computerBank{maxBank};
	std::string nextMove = getNextMove();
	
	while (playerBank && computerBank)
	{	
		std::cout << playerName << "'s bank: $" << playerBank << '\n';
		std::cout << computerName << "'s bank: $" << computerBank << "\n\n";
		std::cout << nextMove << " begins.\n";
		
		unsigned bet;
		std::string playerChoice;
		std::string computerChoice;
		
		if (nextMove == playerName)
		{
			bet = getPlayerBet(playerBank, computerBank);
			
			std::cout << playerName << " bets $" << bet << ".\n\n"; 
			
			playerChoice = getPlayerChoice();
			computerChoice = getComputerChoice();
		}
		else
		{
			bet = getComputerBet(playerBank, computerBank);
			
			std::cout << computerName << " bets $" << bet << ".\n\n";
			
			playerChoice = getPlayerChoice();
			computerChoice = getComputerChoice();
		}
		
		std::string winner{getWinner(playerChoice, computerChoice)};
		
		if (winner != "DRAW")
		{
			std::cout << winner << " wins " << bet << " dollars!\n\n";
			updateBankInfo(winner, bet, playerBank, computerBank);
		}
		
		changeNextMove(nextMove);
		
		std::cout << "Press ENTER to continue.\n";
		
		std::string s;
		getline(std::cin, s);
		
		std::cout << separator;
	}
	
	if (!playerBank)
	{
		std::cout << "You're out of luck, my friend. YOUR GAME IS OVER!\n";
	}
	
	if (!computerBank)
	{
		std::cout << "Congratualations!\n";
		std::cout << "You're took all my money and since now I'll beg in the streets.\n";
	}
}

bool playAgain()
{
	std::string s;
	
	std::cout << "Do you want to play again? (yes/no)\n";
	getline(std::cin, s);
	
	std::cout << '\n';
	std::cout << separator;
	
	return (tolower(s[0]) == 'y');
}

std::string getNextMove()
{
	// Returns the player who will make the first move.
	std::string s;
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0,1);
	
	dist(rd) ? s = playerName : s = computerName;
	return s;
}

unsigned getPlayerBet(unsigned plbank, unsigned cbank)
{
	// Returns the bet made by the player.
	std::string s;
	unsigned b;
	unsigned minbet{1};
	unsigned maxbet{(plbank < cbank) ? plbank : cbank};
	
	do
	{
		do
		{
			std::cout << "Your bet, please: (";
			std::cout << minbet << " - " << maxbet << ")\n";
			getline(std::cin, s);
			
		} while (!isDigits(s));
		
		s = s.substr(0, 5);
		b = stoi(s);
		
		if ((maxbet == plbank) && (b > maxbet) && (plbank != cbank))
		{
			std::cout << "You don't have enough money to bet!\n\n";
		}
		
		if ((maxbet == cbank) && (b > maxbet) && (plbank != cbank))
		{
			std::cout << "I don't have enough money, my friend!\n\n";
		}
		
	} while ((b < minbet) || (b > maxbet));
	
	return b;
}

std::string getPlayerChoice()
{
	// Allows the player to choose one of the three items.
	unsigned num;
	std::string s;
	
	std::cout << "Choose one of the following:\n\n";
	std::cout << "1. I choose ROCK!\n";
	std::cout << "2. I choose PAPER!\n";
	std::cout << "3. I choose SCISSORS!\n\n";
	
	do
	{	
		do
		{
			std::cout << "Your choice: (1 - 3)\n";
			
			getline(std::cin, s);
			
		} while (!isDigits(s));
		
		s = s.substr(0, 5);
		num = stoi(s);
		
	} while ((num < 1) || (num > 3));
	
	return (getItem(num));
}
	
unsigned getComputerBet(unsigned plbank, unsigned combank)
{
	// Allows the computer to place a bet in the game.
	unsigned limit{(plbank < combank) ? plbank : combank};
	
	if (limit <= 10)
	{
		return limit;
	}
	else
	{
		std::random_device rd;
		std::uniform_int_distribution<int> dist(1, limit / 2);
		return dist(rd);
	}
}

std::string getComputerChoice()
{
	// Allows the computer to choose one of the three items.
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1, 3);
	
	int num{dist(rd)};
	return (getItem(num));
}

bool isDigits(const std::string& s)
{
	// Returns true if all characters in the string are digits.
	return (s.find_first_not_of("0123456789") == std::string::npos);
}

void changeNextMove(std::string& m)
{
	// Determines the player to bet in the game.
	if (m == playerName)
	{
		m = computerName;
	}
	else
	{
		m = playerName;
	}
}

std::string getItem(const unsigned n)
{
	// Converts the numeric value of an item to the string.
	std::string s;
	
	switch (n)
	{
		case 1:
			s = "ROCK";
			break;
			
		case 2:
			s = "PAPER";
			break;
			
		case 3:
			s = "SCISSORS";
			break;
			
		default:
			s = "ERROR!";
	}
	
	return s;
}

std::string getWinner(const std::string& pchoice, const std::string& cchoice)
{
	// Determines who is winner.
	std::string s;
	
	std::cout << playerName << " chose the " << pchoice << ".\n";
	std::cout << computerName << " chose the " << cchoice << ".\n\n";
	
	if ((pchoice == "ROCK") && (cchoice == "SCISSORS"))
	{
		std::cout << "ROCK BREAKS SCISSORS!\n";
		s = playerName;
	}
	else if ((pchoice == "PAPER") && (cchoice == "ROCK"))
	{
		std::cout << "PAPER COVERS ROCK!\n";
		s = playerName;
	}
	else if ((pchoice == "SCISSORS") && (cchoice == "PAPER"))
	{
		std::cout << "SCISSORS CUTS PAPER!\n";
		s = playerName;
	}
	else if ((cchoice == "ROCK") && (pchoice == "SCISSORS"))
	{
		std::cout << "ROCK BREAKS SCISSORS!\n";
		s = computerName;
	}
	else if ((cchoice == "PAPER") && (pchoice == "ROCK"))
	{
		std::cout << "PAPER COVERS ROCK!\n";
		s = computerName;
	}
	else if ((cchoice == "SCISSORS") && (pchoice == "PAPER"))
	{
		std::cout << "SCISSORS CUTS PAPER!\n";
		s = computerName;
	}
	else
	{
		std::cout << "It's a draw!\n";
		s = "DRAW";
	}
	
	return s;
}

void updateBankInfo(const std::string& w, const unsigned b, unsigned& pbank, unsigned& cbank)
{
	// Updates the contents of the players banks according to the result of the game.
	if (w == playerName)
	{
		pbank += b;
		cbank -= b;
	}
	else
	{
		cbank += b;
		pbank -= b;
	}
}
