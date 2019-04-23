
#pragma once

#include <chrono>
#include <vector>

#define FPS_MAX_TIME_COUNT	60

class FPS_manager
{
public:
	typedef std::chrono::high_resolution_clock::time_point	timePoint;

	struct		KeyTimes
	{
		size_t	oldest;
		size_t	oldest2;
		size_t	oldest3;
		size_t	youngest;
	};

	FPS_manager() = delete;
	~FPS_manager() = delete;

	static float	fps;

	static void		start();
	static void		update();

protected:
	static std::vector<timePoint>	times;
	static size_t					timeCount;

	static timePoint	now();
	static KeyTimes		getKeyTimes();
	static void			updateCounter(const KeyTimes & keyTimes);
};

