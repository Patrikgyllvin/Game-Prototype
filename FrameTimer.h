#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include <ctime>

class FrameTimer
{
private:
	unsigned long begTime, interval;
	
	bool running;

	int frame, startFrame, endFrame;
	double frameInterval;

public:
	FrameTimer();
	~FrameTimer();

	void start( int startFrame, int endFrame, unsigned long interval );
	void reset();

	void setInterval( unsigned long interval );

	bool isRunning();

	int getFrame();
};

#endif