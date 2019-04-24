
#include <iostream>
#include <vector>
#include "FPS_manager.hpp"


float								FPS_manager::fps = 0;
size_t								FPS_manager::timeCount = 0;
std::vector<FPS_manager::timePoint>	FPS_manager::times;
clock_t 							FPS_manager::beginFrame; 
clock_t								FPS_manager::endFrame;
clock_t 							FPS_manager::deltaTime = 0;
// clock_t 							FPS_manager::fps = 0;
double  							FPS_manager::frameRate = 30;
double  							FPS_manager::averageFrameTimeMilliseconds = 33.333;
unsigned int 						FPS_manager::frames = 0;

void		FPS_manager::start()
{
	times.resize(FPS_MAX_TIME_COUNT);
	timeCount = 0;

	beginFrame = clock();
}

void		FPS_manager::update()
{
	KeyTimes	keyTimes = getKeyTimes();

	if (timeCount < FPS_MAX_TIME_COUNT)
	{
		times[timeCount] = now();
		++timeCount;
	}
	else
	{
		times[keyTimes.oldest] = now();

		keyTimes.youngest = keyTimes.oldest;
		keyTimes.oldest = keyTimes.oldest2;
		keyTimes.oldest2 = keyTimes.oldest3;
	}

	// setterFPS();
	updateCounter(keyTimes);
}

FPS_manager::timePoint	FPS_manager::now()
{
	return std::chrono::high_resolution_clock::now();
}

FPS_manager::KeyTimes	FPS_manager::getKeyTimes()
{
	KeyTimes	keyTimes = { 0, 0, 0 };
	timePoint	oldest = timePoint::max();
	timePoint	oldest2 = timePoint::max();
	timePoint	youngest = timePoint::min();
	size_t		i = 0;

	for (size_t i = 0; i < timeCount; ++i)
	{
		const timePoint &	time = times[i];

		if (time > youngest)
		{
			youngest = time;
			keyTimes.youngest = i;
		}
		else if (time < oldest)
		{
			oldest2 = oldest;
			oldest = time;
			keyTimes.oldest2 = keyTimes.oldest;
			keyTimes.oldest = i;
		}
		else if (time < oldest2)
		{
			oldest2 = time;
			keyTimes.oldest2 = i;
		}
	}

	return keyTimes;
}

void					FPS_manager::updateCounter(const KeyTimes & keyTimes)
{
	std::chrono::duration<float, std::milli>	duration = times[keyTimes.youngest] - times[keyTimes.oldest];

	fps = timeCount / static_cast<float>(duration.count()) * 1000;
}

void					FPS_manager::setterFPS() {	
	endFrame = clock();
	deltaTime += endFrame - beginFrame;
    frames++;
	// printf("| %lu | %lu | %lu | %d |\n", beginFrame, endFrame, deltaTime, frames);

    //if you really want FPS
    if( clockToMilliseconds(deltaTime)>=1.0) { //every second
        frameRate = (double)frames*0.5 +  frameRate*0.5; //more stable
		fps = (float)frames;
        frames = 0;
        deltaTime = 0;
        averageFrameTimeMilliseconds  = 1000.0/(frameRate==0?0.001:frameRate);
		printf("%f\n", fps);
        // if(vsync)
        //     std::cout<<"FrameTime was:"<<averageFrameTimeMilliseconds<<std::endl;
        // else
        //    std::cout<<"CPU time was:"<<averageFrameTimeMilliseconds<<std::endl;
    }
	beginFrame = endFrame;
}

double 					FPS_manager::clockToMilliseconds(clock_t ticks) {
    // units/(units/time) => time (seconds) * 1000 = milliseconds
    return (ticks/(double)CLOCKS_PER_SEC)*10.0;
}