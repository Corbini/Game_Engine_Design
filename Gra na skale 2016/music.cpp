#include "music.h"


music::music()
{
	sound.stop();
	sound.setBuffer(buffer);
}
music::~music()
{
}

void music::play(std::string name)
{
	sound.stop();
	buffer.loadFromFile(name);
	sound.play();
}

void music::play()
{
	sound.play();
}

void music::pause()
{
	sound.pause();

}

void music::end()
{
	sound.stop();
}

void music::volume(int vol)
{
	sound.setVolume(vol);
}