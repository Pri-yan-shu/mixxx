#pragma once

#include <pipewire/pipewire.h>

#include "soundio/sounddevice.h"

class SoundDevicePipewire : public SoundDevice {
  public:
    SoundDevicePipewire(UserSettingsPointer config,
            SoundManager* sm);
    ~SoundDevicePipewire() override;

    SoundDeviceStatus open(bool isClkRefDevice, int syncBuffers) override;
    bool isOpen() const override;
    SoundDeviceStatus close() override;
    void readProcess(SINT framesPerBuffer) override;
    void writeProcess(SINT framesPerBuffer) override;
    QString getError() const override;

    /// Main callback process, here we also update the DAC timings
    int callbackProcess(const SINT framesPerBuffer,
            CSAMPLE* output,
            const CSAMPLE* in);

  private:
    /// Callback called when stream state changes, similar to paFinishedCallback
    void streamStateChangedCallback(enum pw_stream_state old, enum pw_stream_state state);
};
