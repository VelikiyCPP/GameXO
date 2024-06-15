#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <limits>


class Player {
public:
	Player() {}

	std::size_t userInput(std::string messageBeforeCin = ">> ") noexcept;

	~Player() {}

private:
	// No private members for now
};

#endif // PLAYER_HPP