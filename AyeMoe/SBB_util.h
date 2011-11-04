#include <sys/times.h>

#include <stdexcept> // std::runtime_error

#define START_TIMER(obj) \
	printf("start_clock in file: %s line: %d\n", __FILE__, __LINE__); \
	obj.start_clock();

#define END_TIMER(obj) \
	printf("end_clock in file: %s line: %d\n", __FILE__, __LINE__); \
	obj.end_clock();
	

class SBB_util {
	public:
		SBB_util();
		void start_clock();
		void end_clock();

	private:
		clock_t _start_time;
		clock_t _end_time;
		struct tms _start_cpu;
		struct tms _end_cpu;
};
