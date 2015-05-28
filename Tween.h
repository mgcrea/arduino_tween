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
    reset();
  }

  void reset() {
    created = millis();
    count = 0;
    loop = 0;
    time = 0.0;
    duration = 0.0;
    state = 0;
  }

  void tick() {

    int ctime = millis();

    if(state == 0) {
      return;
    } else if(state == 1) {
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
      } else if(loop == 2) {
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

  float num;
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
