/**
 * @file
 * @brief Source file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#include "GameTimer.h"
#include <stdexcept>

void GameTimer::Update(double time)
{
	if (time < 0)
		throw std::invalid_argument("time is not allowed to be negative");

	if (time < currentTime)
	{
		throw std::invalid_argument("time is not allowed to be set to a smaller value than the "
		                            "previous Update time");
	}

	deltaTime = time - currentTime;
	currentTime = time;
}

[[maybe_unused]] void GameTimer::Reset()
{
	GameTimer::currentTime = 0.0;
	GameTimer::deltaTime = 0.0;
}

[[maybe_unused]] double GameTimer::GetCurrentTime()
{
	return GameTimer::currentTime;
}

[[maybe_unused]] double GameTimer::GetDeltaTime()
{
	return GameTimer::deltaTime;
}