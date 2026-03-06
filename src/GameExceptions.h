#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& msg) : std::runtime_error(msg) {}
};

// Ошибка открытия файла
class FileException : public GameException {
public:
    explicit FileException(const std::string& filename) 
        : GameException("Error: Could not open file " + filename) {}
};

// Ошибка данных (файл поврежден)
class SaveDataException : public GameException {
public:
    SaveDataException() : GameException("Error: Save file is corrupted or invalid.") {}
};

#endif