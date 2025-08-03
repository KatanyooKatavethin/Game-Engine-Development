#pragma once
#include <string>
#include "miniaudio.h"

namespace TK
{
	class SoundManager
	{

	private:

		ma_engine engine;
		ma_sound musicSound{};
		bool songLoaded = false;

	public:

		SoundManager();
		~SoundManager();
		void playMusic(const std::string& filePath);
		void pauseMusic();
		void resumeMusic();
		void stopMusic();
		void setVolume(float volume);
		int init();


	};
}

