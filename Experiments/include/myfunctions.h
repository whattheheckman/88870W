// custom function declartions

//
int Rampv2(int controllerPwr, int motorSpeed, int maxChange, int delayTime);
int rampUp(int controlInput, int maxChange);
int rampDown(int controlInput, int maxChange);
int nathanRampUp(int controllerPwr, int maxChange, int delayTime);
int nathanRampDown(int controllerPwr, int maxChange, int delayTime);
int deadzoneX(int x, int threshold);
int deadzoneY(int y, int threshold);