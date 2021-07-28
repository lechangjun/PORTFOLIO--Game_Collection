#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&tick);
	QueryPerformanceCounter((LARGE_INTEGER *)&start);

	last = 0; //마지막 시간
}

Time::~Time()
{

}

void Time::Update()
{
	__int64 current; //현재 시간
	QueryPerformanceCounter((LARGE_INTEGER *)&current); //현재 시간 기준 CPU 클릭 수

	elapsed = current - last; //경과시간 = 현재 시간 - 마지막 시간
	last = current; //마지막 시간을 현재 시간과 같게 변경
}

float Time::Running()
{
	__int64 current; //현재 시간
	QueryPerformanceCounter((LARGE_INTEGER *)&current); 

	return (float)((double)(current - start) / tick); // (current - start = 경과 시간)/ 경과시간 나누기 틱 수
}

float Time::Elapsed() //elapsed: 경과
{
	return (float)elapsed / tick; // 경과시간 나누기 틱 수
}