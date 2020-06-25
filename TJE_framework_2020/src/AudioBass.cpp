#include "AudioBass.h"


std::map<std::string, MyAudioBass*> MyAudioBass::sAudiosLoaded;

MyAudioBass::MyAudioBass() {
	
}

MyAudioBass::~MyAudioBass() {

}

void MyAudioBass::initBass() {
	if (BASS_Init(-1, 44100, 0, 0, NULL) == false) //-1 significa usar el por defecto del sistema operativo
	{
		//error abriendo la tarjeta de sonido...
	}
}

bool MyAudioBass::load(const char* filename,bool loop)
{
	std::string str = filename;
	if (loop) {
		hSample = BASS_SampleLoad(false, filename, 0, 0, 3, BASS_SAMPLE_LOOP);
	}
	else {
		hSample = BASS_SampleLoad(false, filename, 0, 0, 3, 0);
	}
	
	
	std::cout << " + Texture loading: " << filename << " ... ";

	this->filename = filename;

	//upload to VRAM
	return true;
}




MyAudioBass* MyAudioBass::Get(const char* filename,bool loop)
{
	assert(filename);

	//check if loaded

	auto it = sAudiosLoaded.find(filename);
	//std::map<std::string, MyAudioBass*>::iterator it = sAudiosLoaded.find(filename);
	
	if (it != sAudiosLoaded.end())
		return it->second;

	//load it
	MyAudioBass* audioBass = new MyAudioBass();
	
	if (!audioBass->load(filename, loop))
	{
		delete audioBass;
		return NULL;
	}
	
	audioBass->setName(filename);
	return audioBass;
}




HCHANNEL MyAudioBass::PlaySoundAmbient() {

	//El handler para un sample
	

	//Cargamos un sample del disco duro (memoria, filename, offset, length, max, flags)
	//use BASS_SAMPLE_LOOP in the last param to have a looped sound
	


	if (hSample == 0){
		std::cout << "file not found" << std::endl;
		//file not found
	}

	//Creamos un canal para el sample
	hSampleChannel = BASS_SampleGetChannel(hSample, false);

	
	//Lanzamos un sample
	BASS_ChannelPlay(hSampleChannel, true);

	return hSampleChannel;
}



void MyAudioBass::PauseMusic(HCHANNEL hSampleChannel) {

	if (hSample == 0) {
		std::cout << "file not found" << std::endl;
		//file not found
	}

	//hSampleChannel = BASS_SampleGetChannel(hSample, false);

	//Creamos un canal para el sample
	bool resp = BASS_ChannelPause(hSampleChannel);

}

void MyAudioBass::UnPauseMusic(HCHANNEL hSampleChannel) {

	if (hSample == 0) {
		std::cout << "file not found" << std::endl;
		//file not found
	}

	//hSampleChannel = BASS_SampleGetChannel(hSample, false);

	//Creamos un canal para el sample
	bool resp = BASS_ChannelPlay(hSampleChannel,false);
}


void MyAudioBass::stopMusic() {

	if (hSample == 0) {
		std::cout << "file not found" << std::endl;
		//file not found
	}

	//Creamos un canal para el sample
	bool resp = BASS_SampleStop(hSample);
}

