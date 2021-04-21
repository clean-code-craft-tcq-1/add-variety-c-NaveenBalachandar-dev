#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("Passive Cooling system with Normal temp and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, 30);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == NORMAL);
}

TEST_CASE("Passive Cooling  with Normal lower boundary and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, 0);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == NORMAL);
}

TEST_CASE("Passive Cooling  with Normal upper boundary and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, 35);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == NORMAL);
}

TEST_CASE("Passive Cooling  with low temp and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, -10);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == TOO_LOW);
}

TEST_CASE("Passive Cooling  with high temp and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == TOO_HIGH);
}

TEST_CASE("Passive Cooling  with high temp boundary validation and O/P fed to controller") {
	Alert_Status_s AlertStatRest = {NOT_SENT,NORMAL};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"TCQ_Tests"};
	
	AlertStatRest = checkAndAlert(TO_CONTROLLER, batteryCharacter, 36);
	REQUIRE(AlertStatRest.AlertSentStatus  == SENT_TO_CONTROLLER);
	REQUIRE(AlertStatRest.breachType == TOO_HIGH);
}
