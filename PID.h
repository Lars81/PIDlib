#ifndef PID_h
#define PID_h

class PID {
  public:
    PID(float, float, float);
    void initialize();
    void setSetpoint(float);
    float getOutput();
    void setKPD(float, float, float);
    void compute(float);
    void setMaxoutput(float);
    void setMinoutput(float);
    void setMaxiterm(float);

  private:
    int _maxOutput, _minOutput;
    float _maxIterm;
    float _input, _output, _setPoint;
    float _Kp, _Ki, _Kd;
    float _currentError, _lastError, _sumError, _dError;
    unsigned long _currentTime, _previousTime, _interval;
   };

#endif
