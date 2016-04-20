#pragma once


class MySoundSystemInterface
{
   public:
      MySoundSystemInterface(){}
      virtual ~MySoundSystemInterface(){}

      virtual bool AddSound(char *soundfile, int numRepeats, int *id) = 0;
      virtual bool SetupSoundParameters(int id, float dopplerFactor,
                                        float rolloffFactor,
                                        float minDist,
                                        float maxDist) = 0;

      virtual bool IsPlaying(int id) = 0;
      virtual void Play(int id) = 0;
      virtual void UpdateSoundPosition(int id, float x, float y,
                                       float z) = 0;
      virtual void Stop(int id) = 0;
      virtual void Shutdown() = 0;
};


class MySoundInterface
{
   public:
      MySoundInterface() {}
      virtual ~MySoundInterface(){}

      virtual bool Initialize(char *filename, int numRepeats) = 0;
      virtual bool SetupSoundParameters(float dopplerFactor,
                                        float rolloffFactor,
                                        float minDist,
                                        float maxDist) = 0;

      virtual bool IsPlaying() = 0;
      virtual void Play() = 0;
      virtual void UpdateSoundPosition(float x, float y,
                                       float z) = 0;
      virtual void Stop() = 0;
      virtual void Shutdown() = 0;
};
