/*
** EPITECH PROJECT, 2022
** Project Indi studio
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

Parser::Parser()
{

}

Parser::Parser(std::string const &file)
{
    std::ifstream input(file);
    for( std::string line; getline(input, line); )
        _lines.push_back(line);
}

Parser::~Parser()
{

}

std::string Parser::parseLineFromFile(std::string &line)
{
    size_t pos = 0;
    std::string delimiter = "=";
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
    }
    return line;
}

std::string Parser::getDataFromFile(std::string const &pattern)
{
    for (auto &line : _lines)
        if (!line.find(pattern))
            return parseLineFromFile(line);
    return NULL;
}