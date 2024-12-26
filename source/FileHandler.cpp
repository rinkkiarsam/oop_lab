#include "FileHandler.hpp"
#include "GameState.hpp"


FileHandler::FileHandler(const std::string& filename)
    : filename(filename) {}

FileHandler::~FileHandler()
{
    closeForReading();
    closeForWriting();
}

void FileHandler::openForReading()
{
    input_file.open(filename);

    if (!input_file.is_open())
    {
        throw std::runtime_error("Failed to open file for reading\n");
    }
}

void FileHandler::closeForReading()
{
    if (input_file.is_open())
    {
        input_file.close();
    }
}

void FileHandler::openForWriting()
{
    output_file.open(filename);

    if (!output_file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing\n");
    }
}

void FileHandler::closeForWriting()
{
    if (output_file.is_open())
    {
        output_file.close();
    }
}

void FileHandler::read(GameState& current_state)
{
    if (input_file.is_open())
    {
        input_file >> current_state;
    }
    else
    {
        throw std::runtime_error("File is not open for reading\n");
    }
}

void FileHandler::write(GameState& current_state)
{
    if (output_file.is_open())
    {
        output_file << current_state;
    }
    else
    {
        throw std::runtime_error("File is not open for writing\n");
    }
}

void FileHandler::read(CLGameInput& game_input)
{
    if (input_file.is_open())
    {
        input_file >> game_input;
    }
    else
    {
        throw std::runtime_error("File is not open for reading\n");
    }
}