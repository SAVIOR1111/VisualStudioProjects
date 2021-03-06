#include "stdafx.h"
#include "FightingSequence.h"
#include "Character.h"
#include "ClassItemsPowers.h"
#include "Enemy.h"
#include <iostream>
#include <string>

using namespace std;

// MAGE FIGHTING SEQUENCE

// Enemy health set to 1 in all fight in beggining for protection of early cycle exit

int FightingSequenceMage::WolfFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	WolfMutant Wolf;
	MageItemsAndPowers MagePowers;
	Enemies* enemywolf = &Wolf;
	enemywolf->SetDamage(5);
	enemywolf->SetVitality(30);

	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	do
	{
		MagePowers.DefenceSPellsInfo(SpellPower);
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= MagePowers.SpellManaCost(ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do 
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		//Checks if you have mana for any spell
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana)) 
		{
			Vitality = 0;
			break;
		}
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		cout << "Remaining mana: " << Mana << endl;
		EnemyHealth = enemywolf->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}

		Vitality -= enemywolf->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::FirstPaladinFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	FirstPaladin firstpaladin;
	MageItemsAndPowers MagePowers;
	Enemies* WeakenedPaladin = &firstpaladin;

	WeakenedPaladin->SetDamage(4);
	WeakenedPaladin->SetVitality(20);

	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= MagePowers.SpellManaCost(ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		cout << "Remaining mana: " << Mana << endl;
		EnemyHealth = WeakenedPaladin->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}

		Vitality -= WeakenedPaladin->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::SecondPaladinFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	SecondPaladin secondpaladin;
	MageItemsAndPowers MagePowers;
	Enemies* fightingsecondpaladin = &secondpaladin;

	fightingsecondpaladin->SetDamage(7);
	fightingsecondpaladin->SetVitality(70);

	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= MagePowers.SpellManaCost(ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		cout << "Remaining mana: " << Mana << endl;
		EnemyHealth = fightingsecondpaladin->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}

		Vitality -= fightingsecondpaladin->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::RematchInTheTomb(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	SecondPaladin secondpaladin;
	MageItemsAndPowers MagePowers;
	Enemies* fightingsecondpaladin = &secondpaladin;

	fightingsecondpaladin->SetDamage(7);
	fightingsecondpaladin->SetVitality(80);

	EnemyHealth = 1;
	EnemyShield = 20;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= (ChosenSpell[0] * ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		PreviousSpell = Response[1];
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		// Checks if damage wont be negated by enemy spells
		if (EnemyShield <= 0)
		{
			cout << "Remaining mana: " << Mana << endl;
			EnemyHealth = fightingsecondpaladin->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower) + MagePowers.ElementalChainBonusDMG(Response[1], PreviousSpell));
		}
		else if (EnemyShield > 0)
		{
			EnemyShield -= ChosenSpell[1];
			cout << "Spell was deflected but you feel the barrier weakening." << endl;
			cout << "Barried strenght: " << EnemyShield << endl;
		}

		if (EnemyHealth <= 0)
		{
			break;
		}
		Vitality -= fightingsecondpaladin->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::EarthGuardian(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	EarthGolem earthgolem;
	MageItemsAndPowers MagePowers;
	Enemies* FightingGuardian = &earthgolem;

	FightingGuardian->SetDamage(10);
	FightingGuardian->SetVitality(60);

	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= (ChosenSpell[0] * ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		EnemyHealth = FightingGuardian->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}
		Vitality -= FightingGuardian->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::FireGuardian(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	FireElemental firelemental;
	MageItemsAndPowers MagePowers;
	Enemies* FightingElement = &firelemental;

	FightingElement->SetDamage(5);

	EnemyHealth = 1;
	EnemyShield = 1;
	int Response;
	int ChosenSpell;
	int Mana = character.GetMana(Intelligence);
	
	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		// If its a block of ice it cant attack you
		if (EnemyShield > 0)
		{
			Vitality -= FightingElement->Attacking();
		}
		cout << "Your current health: " << Vitality << endl;
		if (Vitality <= 0) { continue; }

		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}

		// Do cicle prevents on invalid input to be attacked again and also protects the acceptance of an invalid input 
		do
		{
			cin >> Response;
			if (Response <= MagePowers.SpellsToShow() && Response > 0)
			{
				ChosenSpell = MagePowers.MageOffenceSpells(Response);
				if (Mana >= MagePowers.SpellManaCost(ChosenSpell))
				{
					Mana -= MagePowers.SpellManaCost(ChosenSpell);
					if (EnemyShield == 0 && ChosenSpell == JadeBlast)
					{
						cout << "The ice shatters and the elemental cant regenerate." << endl;
						EnemyHealth = 0;
						continue;
					}
					EnemyShield = FightingElement->HealthRemaining(ChosenSpell, character.SpellPowerBonusDamage(SpellPower));
				}
				else if (Mana < (ChosenSpell * ChosenSpell))
				{
					cout << "Not enough mana please try again: " << endl;
				}
			}
			else
			{
				cout << "Invalid Input. Please try again: " << endl;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				continue;
			}
		} while (Response <= 0 || Response > MagePowers.SpellsToShow());

		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::ThirdPaladinFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	MageItemsAndPowers MagePowers;
	ThirdAndFourthPaladin paladin;
	Enemies* fightingthirdpaladin = &paladin;

	fightingthirdpaladin->SetDamage(3);
	fightingthirdpaladin->SetVitality(150);
	
	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= (ChosenSpell[0] * ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana) && Response[1] > 0)
		{
			Vitality = 0;
			break;
		}
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow())
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		EnemyHealth = fightingthirdpaladin->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0) 
		{
			break;
		}
		Vitality -= fightingthirdpaladin->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::TheFinalGuardianFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	MageItemsAndPowers MagePowers;
	FinalGuardian TheGuardian;
	Enemies* FightingFinalGuardian = &TheGuardian;

	FightingFinalGuardian->SetDamage(4);
	FightingFinalGuardian->SetVitality(100);

	EnemyHealth = 1;
	int AvailableGuardianSkills = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= (ChosenSpell[0] * ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		Vitality -= FightingFinalGuardian->Attacking();
		cout << "Your current health: " << Vitality << endl;
		if (Vitality <= 0) 
		{
			return Vitality;
		}

		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		PreviousSpell = Response[1];
		do
		{
			cin >> Response[1];
			if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
			{
				ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
				if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
				{
					Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
				}
				else
				{
					cout << "Not enough mana please try again: " << endl;
					continue;
				}
			}
			else
			{
				cout << "Invalid Input. Please try again: " << endl;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				continue;
			}
		} while (Response[1] > MagePowers.SpellsToShow() || Response[1] <= 0);
		EnemyHealth = FightingFinalGuardian->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}

		if (AvailableGuardianSkills > 0)
		{
			AvailableGuardianSkills = TheGuardian.Skills();
			Vitality -= AvailableGuardianSkills;
		}
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::FinalPaladinFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	MageItemsAndPowers MagePowers;
	ThirdAndFourthPaladin paladin;
	Enemies* fightingthirdpaladin = &paladin;

	fightingthirdpaladin->SetDamage(8);
	fightingthirdpaladin->SetVitality(100);
	EnemyHealth = 1;
	int Response[2];
	int ChosenSpell[2];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;
	MagePowers.DefenceSPellsInfo(SpellPower);
	do
	{
		cin >> Response[0];
		if (cin.fail())
		{
			cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (Response[0] == 0);
	if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
	{
		ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
		Mana -= (ChosenSpell[0] * ChosenSpell[0]);
		Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
		cout << "Spell successfull. Current vitality: " << Vitality << endl;
	}
	else
	{
		cout << "Defence menu closed. No buffs applied" << endl;
	}

	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		PreviousSpell = Response[1];
		cin >> Response[1];
		if (Response[1] <= MagePowers.SpellsToShow() && Response[1] > 0)
		{
			ChosenSpell[1] = MagePowers.MageOffenceSpells(Response[1]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[1]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[1]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		EnemyHealth = fightingthirdpaladin->HealthRemaining(ChosenSpell[1], character.SpellPowerBonusDamage(SpellPower) + MagePowers.ElementalChainBonusDMG(ChosenSpell[1], PreviousSpell));
		if (EnemyHealth <= 0)
		{
			break;
		}
		Vitality -= fightingthirdpaladin->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}

int FightingSequenceMage::KingFight(int SpellPower, int Intelligence, int Vitality)
{
	Character character;
	MageItemsAndPowers MagePowers;
	TheKing King;
	Enemies* FightingKing = &King;

	FightingKing->SetVitality(200);

	EnemyHealth = 1;
	int Response[3];
	int ChosenSpell[3];
	int Mana = character.GetMana(Intelligence);
	cout << "Current mana: " << Mana << endl;

	for (int i = 0; i <= 1; i++)
	{
		MagePowers.DefenceSPellsInfo(SpellPower);
		do
		{
			cin >> Response[0];
			if (cin.fail())
			{
				cout << "Invalid. Your Response must be a number not a character or 0. Please type in a number:" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (Response[0] == 0);
		if (Response[0] <= NumberOfSpellsPerList && Response[0] > 0)
		{
			ChosenSpell[0] = MagePowers.MageDefenceSpells(Response[0]);
			Mana -= (ChosenSpell[0] * ChosenSpell[0]);
			Vitality += (ChosenSpell[0] + character.SpellPowerBonusDamage(SpellPower));
			cout << "Spell successfull. Current vitality: " << Vitality << endl;
		}
		else
		{
			cout << "Defence menu closed." << endl;
			cout << "Current vitality: " << Vitality << endl;
		}
	}
	cout << "Current mana: " << Mana << endl;
	
	MagePowers.GetNumberOfSpellsAvailiable(Intelligence);

	do
	{
		cout << "Remaining mana: " << Mana << endl;
		MagePowers.OffenceSpellsInfo(SpellPower);
		if (!MagePowers.IsManaEnoughForLowestCostSpell(Mana))
		{
			Vitality = 0;
			break;
		}
		PreviousSpell = Response[2];
		cin >> Response[2];
		if (Response[2] <= MagePowers.SpellsToShow() && Response[2] > 0)
		{
			ChosenSpell[2] = MagePowers.MageOffenceSpells(Response[2]);
			if (Mana >= MagePowers.SpellManaCost(ChosenSpell[2]))
			{
				Mana -= MagePowers.SpellManaCost(ChosenSpell[2]);
			}
			else
			{
				cout << "Not enough mana please try again: " << endl;
				continue;
			}
		}
		else
		{
			cout << "Invalid Input. Please try again: " << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			continue;
		}
		EnemyHealth = FightingKing->HealthRemaining(ChosenSpell[2],character.SpellPowerBonusDamage(SpellPower));
		if (EnemyHealth <= 0)
		{
			break;
		}
		Vitality -= FightingKing->Attacking();
		cout << "Your current health: " << Vitality << endl;
		system("pause");
		system("cls");
	} while (Vitality > 0 && EnemyHealth > 0);
	return Vitality;
}
