#pragma once

#include <memory>

#include "soundio/sounddeviceenumerator.h"
#include "soundio/sounddevicepipewire.h"

class PipewireEnumerator : SoundDeviceEnumerator {
  public:
    PipewireEnumerator(UserSettingsPointer config,
            SoundManager* sm);
    ~PipewireEnumerator() override;

  signals:
    void deviceAdded(SoundDevice* device);
    void deviceRemoved(SoundDevice* device);

    /// Signal SoundManager about external change in connection, which further
    /// 	signals the DlgPrefSound/DlgPrefSoundItem for updating its state.
    void linkChanged();

  private:
    /// Source of all events, like a soundcard is detected/removed, link is created/destroyed
    void registryEventGlobal();

    void createSoundDevice();
    void destroySoundDevice();

    std::unique_ptr<SoundDevicePipewire> m_devices;
};
