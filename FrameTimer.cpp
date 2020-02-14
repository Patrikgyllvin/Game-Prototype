#include "FrameTimer.h"
#include <iostream>
FrameTimer::FrameTimer()
:
begTime( 0 ),
interval( 0 ),
frame( 0 )
{}

FrameTimer::~FrameTimer()
{}

void FrameTimer::start( int startFrame, int endFrame, unsigned long interval )
{
	if( !isRunning() )
	{
		this->begTime = (unsigned long) clock();

		this->interval = interval;

		this->startFrame = startFrame;
		this->endFrame = endFrame;

		this->frame = startFrame;
	
		this->frameInterval = interval / ( endFrame - startFrame );

		std::cout << frame<<'\n';
	}
}

void FrameTimer::reset()
{}

void FrameTimer::setInterval( unsigned long interval )
{
	this->interval = interval;
	this->frameInterval = interval / ( endFrame - startFrame );
}

bool FrameTimer::isRunning()
{
	return this->running;
}

int FrameTimer::getFrame()
{
	if( (unsigned long) clock() - this->begTime >= this->interval )
	{
		this->frame = this->startFrame;
	}
	if( (unsigned long) clock() - this->begTime >= this->frameInterval )
	{
		frame++;
	}

	return this->frame;
}