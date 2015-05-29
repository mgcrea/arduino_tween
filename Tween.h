#pragma once

#include <Arduino.h>
#include "Easing.h"

/*	TweenTimer
 ___________________________________________________ */

class TweenTimer {

public:

  int state;
  float created, time, duration;
  unsigned int loop, count;

  TweenTimer() {
    loop = 0;
    reset(0.0);
  }

  void reset(float _duration) {
    duration = _duration;
    reset();
  }

  void reset() {
    created = millis();
    count = 0;
    time = 0.0;
    state = 0;
  }

  void tick() {

    if(state == 0) {
      return;
    }

    int ctime = millis();
    if(state == 1) {
      time = ctime - created;
    } else if(state == -1) {
      time = (created + duration) - ctime;
    }

    if (time > duration) {
      count++;
      time = duration;
      created = ctime;

      if(loop == 0) {
        state = 0;
      } else if(loop == 1) {
        time = 0;
        state = 1;
      } else if(loop >= 2) {
        state = -1;
      }
    } else if(time < 0) {
      count++;
      time = 0;
      created = ctime;

      if(loop == 0) {
        state = 0;
      } else if(loop > 0) {
        state = 1;
      }
    }
  }
};

/*	Tween
 ___________________________________________________ */

class Tween {

public:

  Tween();
  void setup(int duration, float start, float change, float (* ease)(float, float, float, float));
  void setup(int duration, float start, float change, float (* ease)(float, float, float, float), int delay);
  void setup(int duration, float start, float change, float (* ease)(float, float, float, float), int delay, int loop);
  void play();
  void pause();
  void stop();

  bool isRunning();
  bool isFinished();

  void update();
  int getCount();
  void debug();

  float value;
  float percent;

private:

  TweenTimer _tween;
  TweenTimer _delay;

  float _begin;
  float _finish;
  float _change;
  float (* _ease)(float, float, float, float);

  void runEasing();
};
