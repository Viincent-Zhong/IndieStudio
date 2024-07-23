/*
** EPITECH PROJECT, 2022
** Project Indi studio
** File description:
** Parser.hpp
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <fstream>
#include <vector>

class Parser {
    public:
        Parser();
        Parser(std::string const &file);
        ~Parser();
        std::string parseLineFromFile(std::string &line);
        std::string getDataFromFile(std::string const &pattern);
    protected:
    private:
        std::string _filename;
        std::vector<std::string> _lines;
};

#endif /* !PARSER_HPP_ */
