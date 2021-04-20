/*****************************************************************************/
/***    \file        typewise-alert.h
***     \author      Naveen Balachandar (RBEI/ECK3) 
***
***     \brief       File to monitor the battery condition based required properties
/*****************************************************************************/

#pragma once

#define COOLTYPE_INDEX 3U

typedef struct {
	int lowerLimit;
	int upperLimit;
}BattCoolTypeLimit_s ;

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
LOW_LIMIT_1 =0,
HIGH_LIMIT_1 =35,
LOW_LIMIT_2 =0,
HIGH_LIMIT_2 = 45,
LOW_LIMIT_3 = 0,
HIGH_LIMIT_3 = 40,
}CoolTypeLimit;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);



typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void sendToConsole(BreachType breachType);
