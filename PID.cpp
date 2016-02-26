#include "PID.h"
#include <arduino.h>


PID::PID(float Kp, float Ki, float Kd) {
  setKPD(Kp, Ki, Kd);
  _maxOutput = 0;
  _minOutput = 0;
  _maxIterm = 0; // "0" == no max integrated error
}

void PID::compute(float input) {
  _input = input;
  _currentTime = millis();
  _interval = _currentTime - _previousTime;
  _currentError = _setPoint - _input;
  _dError = (_currentError - _lastError) / _interval;
  _sumError += (_lastError * _interval);
  if(_maxIterm) _sumError = constrain(_sumError, -_maxIterm, _maxIterm); //

  _output = _Kp * _currentError + _Ki * _sumError + _Kd * _dError;
  _lastError = _currentError;
  _previousTime = _currentTime;
}

void PID::setSetpoint(float setPoint) {
  _setPoint = setPoint;
}

void PID::setMaxoutput(float maxOutput) {
  _maxOutput = maxOutput;
}

void PID::setMinoutput(float minOutput) {
  _minOutput = minOutput;
}

void PID::setMaxiterm(float maxIterm){
	_maxIterm = maxIterm;
}

float PID::getOutput() {
  if (_maxOutput) _output = min(_output, _maxOutput); // Changed "if (!_maxOutput)" to "if (_maxOutput)"
  if (_minOutput) _output = max(_output, _minOutput);

  return _output;
}

void PID::setKPD(float Kp, float Ki, float Kd) {
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}
