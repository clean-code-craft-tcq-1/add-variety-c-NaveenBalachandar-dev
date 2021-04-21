/*****************************************************************************/
/***    \file        typewise-alert.c
***     \author      Naveen Balachandar (RBEI/ECK3) 
***
***     \brief       File to monitor the battery condition based required properties
/*****************************************************************************/
#include "typewise-alert.h"
#include <stdio.h>

BattCoolTypeLimit_s BattCoolTypeLimit[COOLTYPE_INDEX] = {{LOW_LIMIT_1,HIGH_LIMIT_1},{LOW_LIMIT_2,HIGH_LIMIT_2},{LOW_LIMIT_3,HIGH_LIMIT_3}};
alertTargetNode_s alertTargetNode[ALERTTYPE_INDEX] = {sendToController,sendToEmail};
sendChargeLevel_Mail_s SendChargeLevel_Mail[CHARGELEVEL_INDEX] = {charge_Normal,charge_TooLow,charge_TooHigh};
Alert_Status_s AlertStat = {NO_PRINT_DONE,DEFAULT_BREACH};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  
  return inferBreach(temperatureInC, BattCoolTypeLimit[coolingType].lowerLimit, BattCoolTypeLimit[coolingType].upperLimit);
}

Alert_Status_s checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  alertTargetNode[alertTarget].alertTargetType(breachType);
  AlertStat.breachType = breachType;
  return AlertStat;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
   SendChargeLevel_Mail[breachType].SendChargeLevel();
  }

void charge_TooLow(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
}

void charge_TooHigh(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
}

void charge_Normal(void)
{
	/*No action required*/
}
