/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-sandro.sgro
** File description:
** Error
*/

#pragma once

    #include <string>

class Error : public std::exception {
    public:
            Error(std::ostream &os, const std::string &message) throw();
            virtual ~Error(void) throw();

            const char *what(void) const throw();

        private:
            std::string _message;
            std::ostream &_os;
};

class FileIOError : public Error {
    public:
		FileIOError(std::ostream &, const std::string &message) throw();
};
