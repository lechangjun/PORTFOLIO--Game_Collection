#include <iostream>

using namespace std;

void main()
{
	char* buffer = new char[1113657];
	FILE* fp;
	errno_t err = fopen_s(&fp,"../Image.jpg", "rb");
	
	if (0 == err)
	{
		fread(buffer, sizeof(char), 1113657, fp);

	}
	else
		cout << "������ ���µ� �����߽��ϴ�." << endl;

	err = fopen_s(&fp, "../Copy.jpg", "wb");

	if (0 == err)
	{
		fwrite(buffer, sizeof(char), 1113657, fp);
		cout << "���� ���� ����!" << endl;
	}
	else
		cout << "������ ���µ� �����߽��ϴ�." << endl;

	fclose(fp);
	delete[] buffer;
	buffer = nullptr;

}