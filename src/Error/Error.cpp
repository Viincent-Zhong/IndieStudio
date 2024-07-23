/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-sandro.sgro
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(std::ostream &os, const std::string &message) throw()
	: _os(os)
{
	_message = message;
}

Error::~Error(void) throw()
{
	
}

const char *Error::what(void) const throw()
{
	return _message.c_str();
}

FileIOError::FileIOError(std::ostream &os, const std::string &message) throw()
	: Error(os, message)
{}