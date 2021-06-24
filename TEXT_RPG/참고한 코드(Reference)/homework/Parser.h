#pragma once
#include "stdafx.h"

class CParser
{
public:
	bool StringToBool(const char arr[]);

	int StringToInt(const char arr[]);

	float StringToFloat(const char arr[]);

	void OccupationToString(OCCUPATION occupation, char result[16]);

	void ElementToString(ELEMENT element, char result[16]);
	
	void PrintFile(const char path[30]);
	
};