#pragma once
#include <SFML/Audio.hpp>

namespace SnakeGame
{
	enum class SoundOption
	{
		Hover,
		Enter,
		Hit,
		Lose
	};
	struct GameSounds
	{
		sf::SoundBuffer hoverMenuBuffer;
		sf::SoundBuffer enterMenuBuffer;
		sf::SoundBuffer hitBuffer;
		sf::SoundBuffer loseBuffer;

		sf::Sound hoverMenuSound;
		sf::Sound enterMenuSound;
		sf::Sound hitSound;
		sf::Sound loseSound;

		sf::Music backgroundMusic;
	};

	void InitGameSounds(GameSounds& sounds);
	void PlayGameSounds(GameSounds& sounds, const std::uint8_t setting, SoundOption option);

	void InitGameMusic(GameSounds& sounds);
	void PlayGameMusic(GameSounds& sounds, const std::uint8_t setting);
	void StopGameMusic(GameSounds& sounds);
}

