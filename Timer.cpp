// Courtesy Alan Gasperini, my roommate

#include "timer.h"

#ifdef WIN32
#pragma comment(lib, "winmm.lib")


Timer::Timer()
{
	_lastTime = 0;

	if( QueryPerformanceFrequency((LARGE_INTEGER*)&_perfCount) )
	{
		_perfFlag = true;
		_timeCount = DWORD(_perfCount); //perf_cnt counts per second
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		_timeScale = 1.0f/_perfCount;
		_QPC = true;
	}
	else
	{
		_perfFlag = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
		_timeCount = 33;
	}
}


float Timer::GetElapsedTime()
{
	if( _perfFlag )
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}
				
	float _time_elapsed = (_curTime-_lastTime)*_timeScale;

	return _time_elapsed;
}


void Timer::Reset()
{
	if( _perfFlag )
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		_lastTime = timeGetTime();
	}
}


#else
//***********************************unix specific*********************************
Timer::Timer()
{
	gettimeofday(&cur_time,0);
}

float Timer::GetElapsedTime()
{
	float dif;
	timeval newtime;
	gettimeofday(&newtime,0);
	dif=(newtime.tv_sec-cur_time.tv_sec);
	dif+=(newtime.tv_usec-cur_time.tv_usec)/1000000.0;
	return dif;
}

#endif // unix
