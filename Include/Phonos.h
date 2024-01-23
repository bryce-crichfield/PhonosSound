#pragma once

#include "Common.h"

namespace phonos {
// =====================================================================================================================
template <typename T> struct Parameter {
  Box<T> storage;
  Atomic<T *> atomic;

  Parameter() : storage(BoxOf(new T())), atomic(storage.get()) {}

  void access(Fn < void(T &) fn) const {
    T *value = atomic.exchange(nullptr);
    fn(*value);
    atomic.store(value);
  }

  void update(T value) {
    auto newValue = BoxOf(new T(value));
    for (auto *expected = storage.get();
         !atomic.compare_exchange_weak(expected, newValue.get());
         expected = storage.get()) {
    }
    storage = std::move(newValue);
  }

  T get() const {
    T value;
    access([&](T &v) { value = v; });
    return value;
  }
};
// =====================================================================================================================
struct AudioSample {
  f32 left;
  f32 right;

  AudioSample() : left(0), right(0) {}

  AudioSample(f32 left, f32 right) : left(left), right(right) {}

  void operator+=(f32 value) {
    left += value;
    right += value;
  }

  void operator+=(const AudioSample &other) {
    left += other.left;
    right += other.right;
  }
};
// =====================================================================================================================
struct Device;
struct Track;
struct Context
{
    const u32 sampleRate;
    const u32 blockSize;

    List<Ref<Device>> devices;
    List<Ref<Track>> tracks;

    Context(u32 sampleRate, u32 blockSize) : sampleRate(sampleRate), blockSize(blockSize) {}

    void update();
};
// =====================================================================================================================
struct Device {
  Ref<Context> context;
  List<AudioSample> output;

  Device(Ref<Context> context) : context(context) {
    output.resize(context->blockSize);
  }

  virtual void update() {
    for (int i = 0; i < output.size(); i++) {
      output[i] = AudioSample(0, 0);
    }
  }
};
// =====================================================================================================================
struct Track {
  Ref<Context> context;
  List<Ref<Device>> inputs;
  List<AudioSample> output;

  Parameter<bool> muteParam;
  Parameter<f32> volumeParam;
  Parameter<f32> panParam;
  Parameter<f32> widthParam;

  void update() {
    for (auto &input : inputs) {
      for (int i = 0; i < input->output.size(); i++) {
        if (muteParam.get()) {
          continue;
        }

        f32 volume = volumeParam.get();
        f32 pan = panParam.get();
        f32 width = widthParam.get();

        AudioSample sample = input->output[i];
        sample.left *= volume * (1 - pan) * (1 - width);
        sample.right *= volume * (1 + pan) * (1 + width);

        if (output.size() <= i) {
          output.push_back(sample);
        } else {
          output[i] += sample;
        }
      }
    }
  }
};
// =====================================================================================================================
}; // namespace phonos

void phonos::Context::update() {
    for (auto &device : devices) {
        device->update();
    }
    
    for (auto &track : tracks) {
        track->update();
    }
}