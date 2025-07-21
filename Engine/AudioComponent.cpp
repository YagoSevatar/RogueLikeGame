#include "pch.h"
#include "AudioComponent.h"

EngineZ::AudioComponent::AudioComponent(GameObject* gameObject)
	: Component(gameObject)
{
	sound = new sf::Sound();
}

EngineZ::AudioComponent::~AudioComponent()
{
	sound->stop();
	delete sound;
}

void EngineZ::AudioComponent::Update(float deltaTime)
{
}

void EngineZ::AudioComponent::Render()
{
}

void EngineZ::AudioComponent::SetAudio(const sf::SoundBuffer& audio)
{
	sound->setBuffer(audio);
}

void EngineZ::AudioComponent::SetLoop(bool loop)
{
	sound->setLoop(loop);
}

void EngineZ::AudioComponent::SetVolume(float volume)
{
	sound->setVolume(volume);
}

void EngineZ::AudioComponent::Play()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}

void EngineZ::AudioComponent::Stop()
{
	sound->stop();
}

void EngineZ::AudioComponent::Pause()
{
	sound->pause();
}

void EngineZ::AudioComponent::Resume()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}
