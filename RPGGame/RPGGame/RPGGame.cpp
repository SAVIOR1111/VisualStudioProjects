#include "stdafx.h"
#include "Character.h"
#include "FightingSequence.h"
#include "ClassItemsPowers.h"
#include "Story.h"
#include <iostream>
#include <string>

using namespace std;

void PlayingAsMage(int, int, int);
void PlayGame();
bool WantsToPlayAgain();
bool RestartFromCheckpoint();

int main()
{
	do
	{
		PlayGame();
	} while (WantsToPlayAgain());
	return 0;
}

void PlayGame()
{
	Character character;
	AttribtesMage attributesmage;

	cout << "Hello and welcome to my RPG game, this is a console game as you have probably noticed." << endl;
	cout << "The goal is simple just follow the story kill the bad guys and win." << endl;

	attributesmage = character.MageClass();
	PlayingAsMage(attributesmage.SpellPower, attributesmage.intelligence, attributesmage.Vitality);
	return;
}

void PlayingAsMage(int spellpower, int intelligence, int vitality)
{
	Character character;
	MageStory Story;
	MageWeapons Weapons;
	MageArmor Armor;
	FightingSequenceMage Battles;

	//The health after every battle
	int AfterBattleVitality;
	//Variable for returning spellpower to the value before the last weapon equip
	int SwitchingWeapons;
	//Stores additional points that will be added to stats from the story
	int StatsIncreaseContainer;

	Story.StoryLeadingToFirstFight();
	AfterBattleVitality = Battles.WolfFight(spellpower, intelligence, vitality);
	if (character.IsCharacterDead(AfterBattleVitality)) { return; }

	intelligence += Story.WitchHutStory();
	SwitchingWeapons = Weapons.WitchStaff;
	spellpower += SwitchingWeapons;
	cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;

	Story.FirstPaladinBattle();
	AfterBattleVitality = Battles.FirstPaladinFight(spellpower, intelligence, vitality);
	if (character.IsCharacterDead(AfterBattleVitality)) { return; }
	StatsIncreaseContainer = Story.AfterFPaladinBattle();
	intelligence += StatsIncreaseContainer;
	cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;

	Battles.SecondPaladinFight(spellpower, intelligence, vitality);
	do
	{
		cout << "Checkpoint reached." << endl;
		//If puzzle is not solved go to checkpoint
		if (!Story.FirstTombPuzzle())
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
		spellpower += Armor.MageFirstSetSpellPower;
		vitality += Armor.MageFirstSetVitality;
		//Switching weapons
		spellpower -= SwitchingWeapons;
		SwitchingWeapons = Weapons.StaffOfTheNetherworld;
		spellpower += SwitchingWeapons;
		cout << "Current stats: SpellPower: " << spellpower << "  Inteligence: " << intelligence << "  Vitality: " << vitality << endl;

		Story.RematchInfrontOfTheTomb();
		AfterBattleVitality = Battles.RematchInTheTomb(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
		StatsIncreaseContainer = Story.SecondPaladinDeath();
		intelligence += StatsIncreaseContainer;
		cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;

		AfterBattleVitality = Battles.EarthGuardian(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0;  continue; }
			return;
		}
	} while (AfterBattleVitality == 0);

	do
	{
		cout << "Checkpoint reached." << endl;
		if (!Story.SecondTombPuzzle())
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0;  continue; }
			return;
		}
		spellpower += Armor.MageSecondSetSpellPower;
		vitality += Armor.MageSecondSetVitality;

		AfterBattleVitality = Battles.FireGuardian(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0;  continue; }
			return;
		}
		Story.ReachingThirdPaladin();
		AfterBattleVitality = Battles.ThirdPaladinFight(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0;  continue; }
			return;
		}
		StatsIncreaseContainer = Story.ThirdPaladinDeath();
		intelligence += StatsIncreaseContainer;
		vitality += StatsIncreaseContainer;
	} while (AfterBattleVitality == 0);
	
	do
	{
		cout << "Checkpoint reached." << endl;
		cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;
		AfterBattleVitality = Battles.TheFinalGuardianFight(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
	} while (AfterBattleVitality == 0);

	do
	{
		cout << "Checkpoint reached." << endl;
		if (!Story.ThirdTombPuzzle())
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
		spellpower -= SwitchingWeapons;
		SwitchingWeapons = Weapons.StaffOfTheAncients;
		spellpower += SwitchingWeapons;
		spellpower += Armor.MageThirdetSpellPower;
		intelligence += Armor.MageThirdSetIntelligence;
		vitality += Armor.MageThirdSetVitality;
		cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;
		AfterBattleVitality = Battles.FinalPaladinFight(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
		StatsIncreaseContainer = Story.FinalPaladinDeath();
		spellpower += StatsIncreaseContainer;
		intelligence += StatsIncreaseContainer;
	} while (AfterBattleVitality == 0);

	do
	{
		cout << "Final Checkpoint reached." << endl;
		cout << "Current stats: SpellPower: " << spellpower << "  Intelligence: " << intelligence << "  Vitality: " << vitality << endl;
		Story.FacingTheKing();
		AfterBattleVitality = Battles.KingFight(spellpower, intelligence, vitality);
		if (character.IsCharacterDead(AfterBattleVitality))
		{
			if (RestartFromCheckpoint()) { AfterBattleVitality = 0; continue; }
			return;
		}
	}while (AfterBattleVitality == 0);
	Story.Ending();
	return;
}

bool RestartFromCheckpoint()
{
	string RestartFromCheckpoint = "";
	cout << "Would you like to play again?(y for yes/any other key for no): " << endl;
	cin >> RestartFromCheckpoint;
	if (RestartFromCheckpoint[0] == 'y' || RestartFromCheckpoint[0] == 'Y')
	{
		cout << "Checkpoint loaded" << endl;
		system("pause");
		system("cls");
		return true;
	}
	return false;
}

bool WantsToPlayAgain()
{
	string Response = "";
	cout << "Would you like to play again?(y for yes/any other key for no): " << endl;
	cin >> Response;
	return (Response[0] == 'y' || Response[0] == 'Y');
}
