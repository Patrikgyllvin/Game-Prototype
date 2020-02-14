#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <fmod.hpp>
#include <fmod_errors.h>

#include <cstdio>
#include <stdlib.h>

#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <iostream>

#include <dirent.h>

#define MAX_SOUNDS 1000

#ifdef _WIN32
  #include <direct.h>
  #include "Shlwapi.h"
  #define DIR_SLASH '\\'
#else
  #define _getcwd getcwd
  #define _chdir chdir
  #define DIR_SLASH "/"
#endif

#include <limits.h>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void init();
	void cleanup();
	
	void tick();

	void loadSound();

	static void playMusic( std::string music );
	static void playSound( std::string sound );

private:
	static FMOD::System* sndSys; // fmod system variable
	static FMOD::Channel* musicChnl; // channel for music
	static FMOD::Sound* soundArr[ MAX_SOUNDS / 2 ]; // array holding every sound
	static FMOD::Sound* musicArr[ MAX_SOUNDS / 2 ]; // array holding every music
	
	static FMOD_RESULT result; // result variable for error checking

	static std::map< std::string, FMOD::Sound* > soundMap; // map to access sounds
	static std::map< std::string, FMOD::Sound* > musicMap; // map to access music
	static std::map< std::string, FMOD::Sound* >::iterator sndMapIter; // iter for sound and music maps

	static void checkError( FMOD_RESULT result ); // convenience function for error checking

	std::vector< std::string > recursiveSearch( std::string currDir ); // function for searching recursively through ever folder for sound files
};

#endif SOUNDMANAGER_H