#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	//__int64 tick: 64비트 정수 (C/C++ 표준이 아니라서 밑줄2개 넣어준거임)

	QueryPerformanceFrequency((LARGE_INTEGER *)&tick); //타이머의 주파수를 얻어옴
	QueryPerformanceCounter((LARGE_INTEGER *)&start); //시작 시점의 CPU 클럭 수

	last = 0;
}

Time::~Time()
{

}

void Time::Update()
{
	__int64 current; //현재 시간
	QueryPerformanceCounter((LARGE_INTEGER *)&current); //현재 시점의 CPU 클럭 수

	elapsed = current - last; //경과 시간 = 현재 시간 - 마지막 시간
	last = current; //마지막 시간을 현재로 변경함
}

float Time::Running()
{
	__int64 current; //현재 시간
	QueryPerformanceCounter((LARGE_INTEGER *)&current); //현재 시점의 CPU 클럭 수

	return (float)((double)(current - start) / tick); //시간 단위로 변하는 과정
}

float Time::Elapsed()
{
	return (float)elapsed / tick; //시간 단위로 변하는 과정
}