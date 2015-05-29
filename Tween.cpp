#include "Tween.h"

/*	Constructor
 ___________________________________________________ */

Tween::Tween() {
  value = 0;
  percent = 0;
}

/*	Setup methods
 ___________________________________________________ */

void Tween::setup(int duration, float begin, float finish, float (* ease)(float, float, float, float), int delay, int loop) {
  _tween.reset(duration);
  _tween.loop = loop;
  _delay.reset(delay);

  _begin = begin;
  _finish = finish;
  _change = finish - begin;

  value = begin;
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

  if (_delay.duration > 0) {
    _delay.tick();
  }

  _tween.tick();

  percent = _tween.time / _tween.duration;

  if (_tween.state != 0 && _tween.time == _tween.duration) {
    Serial.println("! _tween.time == _tween.duration"); Serial.print("/!\\"); debug();
    if (_delay.duration > 0) {
      Serial.println("! Setup downward delay"); Serial.print("/!\\"); debug();
      // Setup downward delay
      _delay.reset();
      _delay.state = 1;
      _tween.state = 0;
    } else {
      if (_tween.loop == 2) {
        _tween.state = -1;
      }
    }
  } else if (_tween.state != 0 && _tween.time == 0) {
    Serial.println("! _tween.time == 0"); Serial.print("/!\\"); debug();
    if (_delay.duration > 0) {
      Serial.println("! Setup upward delay"); Serial.print("/!\\"); debug();
      // Setup upward delay
      _delay.reset();
      _delay.state = 1;
      _tween.state = 0;
    }
  }

  if (_delay.duration > 0) {
    if (_delay.time == _delay.duration && _delay.state == 0) {
      Serial.println("! delay finished"); Serial.print("/!\\"); debug();
      _delay.time = 0;
      _tween.created = millis();
      if (_tween.loop == 2) {
        _tween.state = _tween.count % 2 == 0 ? 1 : -1;
      } else {
        _tween.state = 1;
      }
    }
  }

  runEasing();
}

void Tween::runEasing() {

  value = _ease(_tween.time, _begin, _change, _tween.duration);

}


void Tween::debug() {

  // Debug
  Serial.print("value=");
  Serial.print(value);
  Serial.print(",tween_state=");
  Serial.print(_tween.state);
  Serial.print(",tween_count=");
  Serial.print(_tween.count);
  Serial.print(",tween_time=");
  Serial.print(static_cast<int>(_tween.time));
  Serial.print("/");
  Serial.print(static_cast<int>(_tween.duration));
  Serial.print(",delay_state=");
  Serial.print(_delay.state);
  Serial.print(",delay_count=");
  Serial.print(_delay.count);
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

int Tween::getCount() {
  return _tween.count;
}
bool Tween::isRunning() {
  return _delay.state != 0 || _tween.state != 0 ? true : false;
}
bool Tween::isFinished() {
  return _tween.time == _tween.duration ? true : false;
}
