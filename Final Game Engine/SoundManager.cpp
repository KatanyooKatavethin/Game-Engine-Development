#include "SoundManager.hpp"
#include "miniaudio.h"
namespace TK
{
	SoundManager::SoundManager()
	{

	}

	SoundManager::~SoundManager()
	{
		ma_engine_uninit(&engine);
	}

	int SoundManager::init()
	{
		ma_result result;
		result = ma_engine_init(NULL, &engine);
		if (result != MA_SUCCESS)
		{
			return -1;
		}
		return 1;
	}

	void SoundManager::playMusic(const std::string& filePath)
	{
		if (songLoaded) 
		{
			ma_sound_uninit(&musicSound);
			songLoaded = false;
		}

		if (ma_sound_init_from_file(&engine, filePath.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &musicSound) != MA_SUCCESS)
		{
			return;
		}

		songLoaded = true;
		ma_sound_start(&musicSound);
	}
	//------------------------------------------------------------
	void SoundManager::pauseMusic()
	{
		if (songLoaded)
		{
			ma_sound_stop(&musicSound); // stop() is pause-like for stream sounds
		}
	}

	void SoundManager::resumeMusic()
	{
		if (songLoaded)
		{
			ma_sound_start(&musicSound);
		}
	}

	void SoundManager::stopMusic()
	{
		if (songLoaded) 
		{
			ma_sound_stop(&musicSound);
			ma_sound_uninit(&musicSound);
			songLoaded = false;
		}
	}

	void SoundManager::setVolume(float volume)
	{
		if (songLoaded)
		{
			ma_sound_set_volume(&musicSound, volume);
		}
	}
}
