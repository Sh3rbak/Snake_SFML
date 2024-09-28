#include "GameSounds.h"
#include "GameSettings.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameSounds(GameSounds& sounds)
	{
		assert(sounds.hoverMenuBuffer.loadFromFile(RESOURCES_PATH + "Sound/Theevilsocks__menu-hover.wav"));
		assert(sounds.enterMenuBuffer.loadFromFile(RESOURCES_PATH + "Sound/Timgormly_Enter.wav"));
		assert(sounds.hitBuffer.loadFromFile(RESOURCES_PATH + "Sound/Owlstorm__Snake_hit.wav"));
		assert(sounds.loseBuffer.loadFromFile(RESOURCES_PATH + "Sound/Maodin204__Lose.wav"));

		sounds.hoverMenuSound.setBuffer(sounds.hoverMenuBuffer);
		sounds.hoverMenuSound.setVolume(SOUND_VOLUME);
		sounds.enterMenuSound.setBuffer(sounds.enterMenuBuffer);
		sounds.enterMenuSound.setVolume(SOUND_VOLUME);
		sounds.hitSound.setBuffer(sounds.hitBuffer);
		sounds.hitSound.setVolume(SOUND_VOLUME);
		sounds.loseSound.setBuffer(sounds.loseBuffer);
		sounds.loseSound.setVolume(SOUND_VOLUME);
	}

	void PlayGameSounds(GameSounds& sounds, const std::uint8_t setting, SoundOption option)
	{
		if (!(setting & static_cast<uint8_t>(GameOptions::Sound)))
		{
			return;
		}

		switch (option)
		{
		case SnakeGame::SoundOption::Hover:
			sounds.hoverMenuSound.play();
			break;
		case SnakeGame::SoundOption::Enter:
			sounds.enterMenuSound.play();
			break;
		case SnakeGame::SoundOption::Hit:
			sounds.hitSound.play();
			break;
		case SnakeGame::SoundOption::Lose:
			sounds.loseSound.play();
			break;
		}
	}

	void InitGameMusic(GameSounds& sounds)
	{
		assert(sounds.backgroundMusic.openFromFile(RESOURCES_PATH + "Sound/Clinthammer__Background_Music.wav"));
		sounds.backgroundMusic.setLoop(true);
		sounds.backgroundMusic.setVolume(MUSIC_VOLUME);
	}

	void PlayGameMusic(GameSounds& sounds, const std::uint8_t setting)
	{
		if (!(setting & static_cast<uint8_t>(GameOptions::Music)))
		{
			return;
		}
		sounds.backgroundMusic.play();
	}

	void StopGameMusic(GameSounds& sounds)
	{
		sounds.backgroundMusic.stop();
	}
}