/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** IOBinary
*/

#ifndef IOBINARY_HPP_
#define IOBINARY_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include "Error.hpp"

namespace IOBinary {
    template <typename T>
        T readFile(std::string const &file) {
            std::ifstream input_file(file, std::ios::binary);
            T value;

            if (!input_file.is_open()) {
                throw FileIOError(std::cerr, "Failed to open file");
            }
            if (!input_file.read((char*)&value, sizeof(value))) {
                input_file.close();
                throw FileIOError(std::cerr, "Failed to read");
            }
            input_file.close();
            return value;
        }
    template <typename T>
        void writeFile(T send, std::string const &file) {
            std::ofstream output_file(file, std::ios::binary | std::ios::app);

            if (!output_file.is_open()) {
                throw FileIOError(std::cerr, "Failed to open file");
            }
            if (!output_file.write((char*)&send, sizeof(send))) {
                output_file.close();
                throw FileIOError(std::cerr, "Failed to read");
            }
            output_file.close();
        }
};

class WriterSave {
    public:
        WriterSave(std::string const &file) : _outputFile(file, std::ios::binary)
        {
            if (!_outputFile.is_open())
                throw FileIOError(std::cerr, "Failed to open file");
        }
        ~WriterSave()
        {
            _outputFile.close();
        }
        template <typename T>
        void writeSave(T send)
        {
            if (!_outputFile.write((char*)&send, sizeof(send))) {
                _outputFile.close();
                throw FileIOError(std::cerr, "Failed to read");
            }
        }

    private:
        std::ofstream _outputFile;
};

class ReaderSave {
    public:
        ReaderSave(std::string const &file) : _inputFile(file, std::ios::binary)
        {
            if (!_inputFile.is_open())
                throw FileIOError(std::cerr, "Failed to open file");
        };
        template <typename T>
            T readSave()
            {
                T value;
                if (!_inputFile.read((char*)&value, sizeof(value))) {
                    _inputFile.close();
                    throw FileIOError(std::cerr, "Failed to read");
                }
                return value;
            }
        ~ReaderSave()
        {
            _inputFile.close();
        };
    private:
        std::ifstream _inputFile;
};

#endif /* !IOBINARY_HPP_ */
