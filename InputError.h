#pragma once
#include <iostream>
#include <exception>

class InputError : public std::exception
{
private:
	

public:
	InputError() : exception("You have entered an incorrect input.") {};
};

