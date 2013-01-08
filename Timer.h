// Courtesy Alan Gasperini

#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef WIN32
#include <windows.h>

class Timer
{
public:

	Timer();

	float GetElapsedTime();
	void Reset();

private:

	LONGLONG	_curTime;
	LONGLONG	_lastTime;

	float		_timeScale;

	DWORD		_timeCount;
	LONGLONG	_perfCount;
	bool		_perfFlag;

	bool		_QPC;
};


#else
//*****************************unix stuff****************************
#include <sys/time.h>

class Timer
{
public:
	Timer();

	void Reset();
	float GetElapsedTime();

private:
	timeval cur_time;

};

inline void Timer::Reset()
{
	gettimeofday(&cur_time,0);
}



#endif //unix

#endif  // _TIMER_H_
