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
