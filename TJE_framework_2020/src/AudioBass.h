#ifndef AUDIO_BASS_H
#define AUDIO_BASS_H

#include <string>
#include <iostream>
#include "extra/bass.h"
#include <map>
#include <cassert>

class MyAudioBass
{
public:
	static std::map<std::string, MyAudioBass*> sAudiosLoaded;
	std::string filename;
	
	HSAMPLE hSample;
	//El handler para un canal
	HCHANNEL hSampleChannel;
	MyAudioBass();
	~MyAudioBass();//{
		//iniciado = true;
	//};

	bool load(const char* filename, bool loop);
	static MyAudioBass* Get(const char* filename, bool loop);
	static void initBass();
	void setName(const char* filename) { sAudiosLoaded[filename] = this; }
	HCHANNEL PlaySoundAmbient();
	void stopMusic();
	void PauseMusic(HCHANNEL hSampleChannel);
	void UnPauseMusic(HCHANNEL hSampleChannel);
};

#endif