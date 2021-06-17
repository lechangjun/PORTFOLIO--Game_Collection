#include "stdafx.h"
#include "Potion.h"
#include "Parser.h"


void CPotion::printPotionInfo() const
{
	CParser parser;
	cout << "\n\n";
	cout << name << '\n';
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << "회복량: " << healAmount << '\n';
	cout << description << '\n';
	cout << "가격: " << price << '\n';
	cout << "==========================================================================================" << endl;
}
