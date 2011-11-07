#ifndef SBB_UTIL_H
#define SBB_UTIL_H

#include "SBB_util.h"

static long Ticks_per_second = sysconf(_SC_CLK_TCK); 

SBB_util::SBB_util()
{
	_start_time=0;
	_end_time=0;
	memset(&_start_cpu,0,sizeof(struct tms));
	memset(&_end_cpu,0,sizeof(struct tms));
	printf("system constant: clock ticks per second: %d\n", Ticks_per_second);
}


void
SBB_util::start_clock()
{
	_start_time = times(&_start_cpu);
}

void
SBB_util::end_clock()
{

#ifdef OLD
	_end_time = times(&_end_cpu);

	intmax_t real_time_diff = _end_time - _start_time;
	intmax_t user_time_diff = _end_cpu.tms_utime - _start_cpu.tms_utime;
	intmax_t system_time_diff = _end_cpu.tms_stime - _start_cpu.tms_stime;
	double ticks_per_second_casted = Ticks_per_second; // so I can divide
#endif

	double real_time, user_time, system_time;
	end_clock(real_time,user_time,system_time);

	printf("\nREAL seconds: %3.3f - USER space seconds: %3.3f SYSTEM space seconds: %3.3f\n\n",
		real_time,
		user_time,
		system_time);
}

void 
SBB_util::end_clock(double& real_time, double& user_time, double& system_time)
{
	_end_time = times(&_end_cpu);

	intmax_t real_time_diff = _end_time - _start_time;
	intmax_t user_time_diff = _end_cpu.tms_utime - _start_cpu.tms_utime;
	intmax_t system_time_diff = _end_cpu.tms_stime - _start_cpu.tms_stime;
	double ticks_per_second_casted = Ticks_per_second; // so I can divide

	//printf("\nREAL seconds: %3.3f (USER space seconds: %3.3f SYSTEM space seconds: %3.3f)\n\n",
	real_time = real_time_diff/ticks_per_second_casted;
	user_time = user_time_diff/ticks_per_second_casted;
	system_time = system_time_diff/ticks_per_second_casted;
}

#endif
