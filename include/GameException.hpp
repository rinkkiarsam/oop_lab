#ifndef GAME_EXCEPTION_HPP_
#define GAME_EXCEPTION_HPP_

#include <iostream>
#include <string>

class GameException: public std::exception {
public:
    GameException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private: 
    std::string message;
};

class NoAbilityError: public std::exception {
public:
    NoAbilityError(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class ShipCollisionError: public std::exception {
public:
    ShipCollisionError(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class FieldCoordinatesError: public std::exception {
public:
    FieldCoordinatesError(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class DamageError: public std::exception {
public:
    DamageError(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


#endif