/*
 * MotorEncoder.cpp
 *
 * Definition class for MotorEncoder.hpp
 */

#include "MotorEncoder.hpp"


uint64_t beginTimeOfEncoder;

/*
 * @about Each tick represents a distance traveled of about 31cm
 * Diameter = 9.9cm, radius = 4.95 cm
 * Circumference = ~31cm which is the distance traveled
 *
 * Will calculate rate based of distance traveled and amount of time it took.
 */
uint64_t previousSpeed = 0;
uint64_t currentSpeed = 0;

const int circumferenceOfTire = 31;

double percentDifferenceOfSpeed = .10;
double upperLimitThresholdDiffOfSpeed;
double lowerLimitThresholdDiffOfSpeed;

bool startOfNewTime = false;

void storeBeginTime(){
    beginTimeOfEncoder = sys_get_uptime_us();
    if (startOfNewTime){
        startOfNewTime = false;
        CalculateSpeed();
    }
    else{
        startOfNewTime = true;
    }
}

void CalculateSpeed(){
    double timeDiffOfTickMarksInSeconds = (sys_get_uptime_us() - beginTimeOfEncoder) * 1000000;
    double distanceInMeters = circumferenceOfTire / 100;

    currentSpeed = distanceInMeters / timeDiffOfTickMarksInSeconds;
}

bool HasSpeedChanged(){
    if (previousSpeed == 0){
        previousSpeed = currentSpeed;
        return false;
    }

    upperLimitThresholdDiffOfSpeed = previousSpeed + (previousSpeed * percentDifferenceOfSpeed);
    lowerLimitThresholdDiffOfSpeed = previousSpeed - (previousSpeed * percentDifferenceOfSpeed);
    if (previousSpeed > 0){
        if (currentSpeed < lowerLimitThresholdDiffOfSpeed || currentSpeed > upperLimitThresholdDiffOfSpeed)
            return true;
        return false;
    }
}












/// Probably getting deleted
void CalculateEncoderTimeDifference(){
    diffOfEncoderTime = sys_get_uptime_us() - beginTimeOfEncoder;

    double upperLimitOfThresholdDifferenceOfPrevTime = diffOfEncoderTimePrev + (diffOfEncoderTime * percentDifferenceOfTime);
    double lowerLimitOfThresholdDifferenceOfPrevTime = diffOfEncoderTimePrev - (diffOfEncoderTime * percentDifferenceOfTime);

    if (diffOfEncoderTime > upperLimitOfThresholdDifferenceOfPrevTime ||
            diffOfEncoderTime < lowerLimitOfThresholdDifferenceOfPrevTime){

    }




    if (!prevWasCalculated){
       diffOfEncoderTimePrev = endTimeOfEncoder - beginTimeOfEncoder;
       prevWasCalculated = true;
    }
    else{
        diffOfEncoderTime = endTimeOfEncoder - beginTimeOfEncoder;
        prevWasCalculated = false;
    }
}

