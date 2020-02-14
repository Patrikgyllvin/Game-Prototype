#include "SoundManager.h"

FMOD::System* SoundManager::sndSys; // fmod system variable
FMOD::Channel* SoundManager::musicChnl; // channel for music
FMOD::Sound* SoundManager::soundArr[ MAX_SOUNDS / 2 ]; // array holding every sound
FMOD::Sound* SoundManager::musicArr[ MAX_SOUNDS / 2 ];

FMOD_RESULT SoundManager::result; // result variable for error checking

std::map< std::string, FMOD::Sound* > SoundManager::soundMap;
std::map< std::string, FMOD::Sound* > SoundManager::musicMap;
std::map< std::string, FMOD::Sound* >::iterator SoundManager::sndMapIter;

SoundManager::SoundManager(void)
{

}
SoundManager::~SoundManager(void)
{
}

void SoundManager::checkError( FMOD_RESULT result )
{
	if( result != FMOD_OK )
	{
		fprintf( stderr, "Sound Error: %d, %s\n", result, FMOD_ErrorString( result ) );
		exit( -1 );
	}
}

void SoundManager::init()
{
	checkError( result = FMOD::System_Create( &sndSys ) );
	
	checkError( result = sndSys->init( 32, FMOD_INIT_NORMAL, 0 ) );
}

void SoundManager::cleanup()
{
	for( int i = 0; i < MAX_SOUNDS; i++ )
	{
		soundArr[ i ]->release();
	}
	
	sndSys->release();
}

void SoundManager::tick()
{
	sndSys->update();
}

void SoundManager::loadSound()
{
	std::string soundPath = "Res"; soundPath += DIR_SLASH; soundPath += "Sound"; soundPath += DIR_SLASH;
	std::string musicPath = "Res"; musicPath += DIR_SLASH; musicPath += "Music"; musicPath += DIR_SLASH;
	
	std::vector< std::string > sndFiles = recursiveSearch( soundPath );

	int i = 0;
	for( std::vector< std::string >::iterator sndIter = sndFiles.begin(); sndIter != sndFiles.end(); ++sndIter, ++i )
	{
		checkError( result = sndSys->createSound( (*sndIter).c_str(), FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &soundArr[ i ] ) );
		
		std::string tmp;
		std::deque< std::string > parts;
		
		int pos = (*sndIter).find( soundPath );
		parts.push_back( (*sndIter).erase( 0, pos + soundPath.length() ) );

		tmp = "";
		std::istringstream ss( parts.back() );
		parts.clear();
		
		while( std::getline( ss, tmp, DIR_SLASH ) )
		{
			parts.push_back( tmp );
		}
		
		tmp = "";
		
		int size = parts.size();
		for( int j = 0; j < size; j++ )
		{
			if( parts.size() == 1 )
				tmp += parts.front();
			else
			{
				tmp += parts.front();
				tmp += '.';
				
				parts.pop_front();
			}
		}

		tmp.erase( tmp.end() - 4, tmp.end() );
		
		soundMap.insert( std::pair< std::string, FMOD::Sound* >( tmp, soundArr[ i ] ) );
	}
}

std::vector< std::string > SoundManager::recursiveSearch( std::string currDir )
{
	static std::vector< std::string > fileNames;

	_chdir( currDir.c_str() );

	DIR* dir = opendir( "." );
	struct dirent* ent = readdir( dir );

	while( ent )
	{
		if( ent->d_type == DT_DIR )
		{
			std::string fname = ent->d_name;
			if( fname.compare( "." ) != 0 && fname.compare( ".." ) != 0 )
			{
				recursiveSearch( ent->d_name );
			}
		}
		else if( ent->d_type == DT_REG )
		{
			std::string file = ent->d_name, cd = _getcwd( NULL, 0 ), filePath = ( ( cd += DIR_SLASH ) += file ), wav = ".wav", ogg = ".ogg";
			
			if( file.find( wav, ( file.length() - wav.length() ) ) != std::string::npos )
				fileNames.push_back( filePath );
			else if ( file.find( ogg, ( file.length() - ogg.length() ) ) != std::string::npos )
				fileNames.push_back( filePath );
		}
		ent = readdir( dir );
	}
	_chdir( ".." );
	closedir( dir );

	return fileNames;
}

void SoundManager::playMusic( std::string music )
{
	for( sndMapIter = musicMap.begin(); sndMapIter != musicMap.end(); ++sndMapIter )
	{
		if( (*sndMapIter).first == music )
		{
			checkError( result = sndSys->playSound( FMOD_CHANNEL_FREE, (*sndMapIter).second, false, &musicChnl ) );
			return;
		}
	}

	fprintf( stderr, "Error cannot find music: %s\n", music.c_str() );
}

void SoundManager::playSound( std::string sound )
{
	for( sndMapIter = soundMap.begin(); sndMapIter != soundMap.end(); ++sndMapIter )
	{
		if( (*sndMapIter).first == sound )
		{
			checkError( result = sndSys->playSound( FMOD_CHANNEL_FREE, (*sndMapIter).second, false, NULL ) );
			
			return;
		}
	}
	
	fprintf( stderr, "Could not find sound: %s\n", sound.c_str() );
}