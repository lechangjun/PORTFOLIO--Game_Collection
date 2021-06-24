#include "stdafx.h"
#include "Parser.h"

bool CParser::StringToBool(const char arr[])
{
	if ((arr[0] - '0') == 0)
	{
		return false;
	}
	else return true;
}

int CParser::StringToInt(const char arr[])
{
	//문자열->숫자 파싱
	int result = 0;
	int len = strlen(arr);

	for (int i = 0; i < len; ++i)
	{
		int tmp = arr[i] - '0';
		result += (int)(tmp * (pow((double)10, (double)len - i - 1)));
	}

	// 1  1 
	// 2  10
	// 3  100
	// 10의 0승은 1 
	//      1승은 10 ...

	return result;
}

float CParser::StringToFloat(const char arr[])
{
	//문자열->숫자 파싱
	float result = 0.0f;
	int totalLen = strlen(arr);

	//소수점 이상의 길이
	int overZeroLen = 0;

	for (int i = 0; i < totalLen; ++i)
	{
		if ('.' == arr[i])
		{
			break;
		}
		else
			++overZeroLen;
	}

	int below = -1;
	for (int i = 0; i < totalLen; ++i)
	{
		if (arr[i] == '.')
		{
			continue;
		}
		if (i < overZeroLen)
		{
			int tmp = arr[i] - '0';
			result += (int)(tmp * (pow((double)10, (double)overZeroLen - i - 1)));
		}
		else
		{
			int tmp = arr[i] - '0';
			result += (float)(tmp * pow((double)10, (double)below));
			--below;
		}

	}


	return result;
}

void CParser::OccupationToString(OCCUPATION occupation, char result[16])
{
	switch (occupation)
	{
	case WARRIOR:
		strcpy_s(result, 16, "warrior");
		break;
	case WIZARD:
		strcpy_s(result, 16, "wizard");
		break;
	case THIEF:
		strcpy_s(result, 16, "thief");
		break;
	default:
		cout << "없는 직업입니다." << endl;
		break;
	}


}

void CParser::ElementToString(ELEMENT element, char result[16])
{
	switch (element)
	{
	case FIRE:
		strcpy_s(result, 16, "불");
		break;
	case WATER:
		strcpy_s(result, 16, "물");
		break;
	case GRASS:
		strcpy_s(result, 16, "풀");
		break;
	case EARTH:
		strcpy_s(result, 16, "땅");
		break;
	case ELEMENT_END:
		strcpy_s(result, 16, "무");
		break;
	default:
		cout << "없는 속성입니다." << endl;
		break;
	}


}

void CParser::PrintFile(const char path[30])
{
	FILE* fp;
	errno_t err = fopen_s(&fp, path, "rt");

	if (0 == err)
	{
		char ch = 0;
		while (true)
		{
			int cnt = fread(&ch, sizeof(char), 1, fp);
			if (1 > cnt)
				break;
			cout << ch;

		}
		fclose(fp);
		cout << '\n';
	}
	else
		cout << "파일을 열수 없습니다." << endl;

}