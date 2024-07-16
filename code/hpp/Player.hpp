#pragma once

#include <iostream>
#include <limits>


class Player {
public:
	Player() {}

	[[nodiscard]] std::size_t userInput(std::string messageBeforeCin = "=: ")noexcept;

	~Player() {}

private:
	char symbol_;
};