#include "stdafx.h"
#include <iostream>
#include <string>
#include "B_A_C_Class.h"

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();
void PrintEndScreen(bool);

B_A_C_Class BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
    return 0;
}

void PrintIntro()
{
	string Response = "";
	cout << "Welcome to Bulls and Cows, a fun word game." << endl;
	cout << "Are you familiar with how the game is played?(y/n): ";
	cin >> Response;
	if (Response[0] == 'y' || Response[0] == 'Y') 
	{
		return;
	}
	cout << "Bulls and cows is a fund word game in which you try and guess a word which has no repeating letters." << endl;
	cout << "Letters must be all lowercase. After you type the word the I will tell you how many bulls and cows you have." << endl;
	cout << "A bull is a letter which is in the same place in your word as in mine and a cow is a letter existing in both words but not in the same place." << endl;
}

void PlayGame()
{
	int SetDificulty = 1;
	cout << "Now we will set the difficulty. The game has a 3,4,5 and 6 letter word, the bigger the word the more tries you have." << endl;
	do
	{
		cout << "Please type in the number of letters you want your word to be(3,4,5,6): ";
		cin >> SetDificulty;
		if (SetDificulty >= 3 && SetDificulty <= 6)
		{
			BCGame.ChooseWordDifficulty(SetDificulty);
		}
		else
		{
			cout << "Invalid input please try again." << endl;
		}
	} while (SetDificulty < 3 || SetDificulty > 6);
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram i am thinking of: " << endl;
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	cout << "Your have " << MaxTries << " tries." << endl;
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		string Guess = GetGuess();
		BullCowCount BCCounter = BCGame.SubmitGuess(Guess);
		cout << "Bulls: " << BCCounter.Bulls;
		cout << ".  Cows: " << BCCounter.Cows << endl;
	}
	PrintEndScreen(BCGame.IsGameWon());
	return;
}

string GetGuess()
{
	WordStatus Status = WordStatus::InvalidStats;
	string Guess = "";
	do {
		cout << "Try " << BCGame.GetCurrentTry() << ": " << endl;
		cout << "Enter guess: ";
		cin >> Guess;
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case WordStatus::NotIsogram:
			cout << "The guess is not an isogram, please enter a word without repeating letters" << endl;
			break;
		case WordStatus::NotLowercase:
			cout << "The word must not have higher case characters, please input your guess again" << endl;
			break;
		case WordStatus::WrongLength:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << endl;
			break;
		default:
			WordStatus::OK;
			break;
		}
	} while (Status != WordStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	string Response = "";
	cout << "Do you want to play again with the same word?(y/n): ";
	cin >> Response;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintEndScreen(bool Condition)
{
	if (Condition)
	{
		cout << "YOU WIN. " << endl;
	}
	else
	{
		cout << "YOU LOSE." << endl;
	}
	return;
}