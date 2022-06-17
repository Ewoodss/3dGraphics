#include "InputSystem.h"
#include <catch2/catch_test_macros.hpp>

/**
 * @brief a class used for testing InputSystem
 */

class TestingClass
{
public:
	int Action = 0;

	void PressKey(int newAction)
	{
		Action = newAction;
	}
};

#define KEY_W 30
#define KEY_PRESSED 87
#define KEY_RELEASED 32

TEST_CASE("Input system testing", "[input_system]")
{
	auto* testingClass = new TestingClass();
	InputSystem inputSystem = InputSystem();

	GIVEN("a InputSystem with a keyFunction")
	{
		inputSystem.AddKeyFunction(KEY_W, [testingClass](int action) {
			testingClass->PressKey(action);
		});

		SECTION("pressing KEY_W")
		{
			REQUIRE_FALSE(!inputSystem.TriggerKeyFunction(KEY_W,
			                                              KEY_PRESSED));// a function exits matching this key so should return true
			REQUIRE(testingClass->Action == KEY_PRESSED);               //should match because that's the action that was done
		}
		SECTION("releasing KEY_W")
		{
			REQUIRE_FALSE(!inputSystem.TriggerKeyFunction(KEY_W,
			                                              KEY_RELEASED));// a function exits matching this key so should return true
			REQUIRE(testingClass->Action == KEY_RELEASED);               //should match because that's the action that was done
		}
		SECTION("removing a existing keyFunction")
		{
			REQUIRE_FALSE(!inputSystem.RemoveKeyFunction(
			        KEY_W));//remove should return true first time because it can be removed
			REQUIRE_FALSE(inputSystem.RemoveKeyFunction(
			        KEY_W));// remove should return false because there is nothing to remove
		}

		SECTION("adding a keyFunction that already exist")
		{
			auto addKeyFunctionReturnValue = inputSystem.AddKeyFunction(KEY_W, [testingClass](int action) {
				testingClass->PressKey(action);//should return false because keyFunction already exists
			});
			REQUIRE_FALSE(addKeyFunctionReturnValue);
		}
	}
	GIVEN("a InputSystem without any keyFunctions")
	{
		SECTION("removing a non existing keyFunction")
		{
			REQUIRE_FALSE(inputSystem.RemoveKeyFunction(KEY_W));
		}

		SECTION("pressing KEY_W")
		{
			REQUIRE_FALSE(inputSystem.TriggerKeyFunction(KEY_W,
			                                             KEY_PRESSED));// no function exits matching this key so should return false
			REQUIRE(testingClass->Action != KEY_PRESSED);              // should not match because no function should be called
		}
		SECTION("releasing KEY_W")
		{
			REQUIRE_FALSE(inputSystem.TriggerKeyFunction(KEY_W,
			                                             KEY_RELEASED));// no function exits matching this key so should return false
			REQUIRE(testingClass->Action != KEY_RELEASED);              // should not match because no function should be called
		}
	}
}