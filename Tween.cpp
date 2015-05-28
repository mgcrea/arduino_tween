#include "Tween.h"

/*	Constructor
 ___________________________________________________ */

Tween::Tween() {
  num = 0;
  percent = 0;
}

/*	Setup methods
 ___________________________________________________ */

void Tween::setup(int duration, float begin, float finish, float (* ease)(float, float, float, float), int delay, int loop) {
  _tween.reset();
  _tween.duration = duration;
  _tween.loop = loop;
  _delay.reset();
  _delay.duration = delay;

  _begin = begin;
  _finish = finish;
  _change = finish - begin;

  num = begin;
  percent = 0;
  _ease = ease;
}

void Tween::setup(int duration, float begin, float change, float (* ease)(float, float, float, float)) {
  setup(duration, begin, change, ease, 0, 0);
}

void Tween::setup(int duration, float begin, float change, float (* ease)(float, float, float, float), int delay) {
  setup(duration, begin, change, ease, delay, 0);
}

/*	Update
 ___________________________________________________ */

void Tween::update() {

  if(_delay.duration > 0) {
    if(_delay.time == _delay.duration && _delay.state == 0) {
      Serial.println("delay finished");
      // _tween.created = millis();
      // _tween.state = _tween.count % 2 == 0 ? 1 : -1;
    }
    _delay.tick();
  }

  _tween.tick();

  percent = _tween.time / _tween.duration;

  if(_tween.time == _tween.duration) {
    // Serial.println("DOWN!");
    // Serial.println(_tween.count);
    _tween.state = -1;
  } else if(_tween.state == 1 && _tween.time == 0) {
    // Serial.println("UP!");
    // Serial.println(_tween.count);
    // _delay.time = 0;
    // _delay.created = millis();
    // _tween.state = 0;
  }

  runEasing();
}

void Tween::runEasing() {

  num = _ease(_tween.time, _begin, _change, _tween.duration);

  // Debug
  Serial.print("num=");
  Serial.print(num);
  Serial.print(",tween_state=");
  Serial.print(_tween.state);
  Serial.print(",tween_time=");
  Serial.print(static_cast<int>(_tween.time));
  Serial.print("/");
  Serial.print(static_cast<int>(_tween.duration));
  Serial.print(",delay_state=");
  Serial.print(_delay.state);
  Serial.print(",delay_time=");
  Serial.print(static_cast<int>(_delay.time));
  Serial.print("/");
  Serial.println(static_cast<int>(_delay.duration));

}

/*	Control methods
 ___________________________________________________ */

void Tween::play() {

  _tween.created = millis();
  _delay.created = millis();

  if(_delay.duration > 0 && _delay.time != _delay.duration) {
    _delay.state = 1;
  } else {
    _tween.state = 1;
  }
}

void Tween::pause() {
  _delay.state = 0;
  _tween.state = 0;
}

void Tween::stop() {
  pause();

  _delay.time = 0;
  _tween.time = 0;
}

bool Tween::isRunning() {
  return _delay.state != 0 || _tween.state != 0 ? true : false;
}
bool Tween::isFinished() {
  return _tween.time == _tween.duration ? true : false;
}
