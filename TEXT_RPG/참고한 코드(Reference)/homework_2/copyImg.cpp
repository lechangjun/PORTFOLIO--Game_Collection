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
		cout << "파일을 여는데 실패했습니다." << endl;

	err = fopen_s(&fp, "../Copy.jpg", "wb");

	if (0 == err)
	{
		fwrite(buffer, sizeof(char), 1113657, fp);
		cout << "파일 복사 성공!" << endl;
	}
	else
		cout << "파일을 쓰는데 실패했습니다." << endl;

	fclose(fp);
	delete[] buffer;
	buffer = nullptr;

}