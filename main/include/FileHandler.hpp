#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP


#include <nlohmann/json.hpp>
#include <fstream>

class GameState;

#include "CLGameInput.hpp"

using json = nlohmann::json;


class FileHandler
{
public:
    FileHandler(const std::string& filename);
    ~FileHandler();
    void openForReading();
    void closeForReading();
    void openForWriting();
    void closeForWriting();
    void read(GameState& current_state);
    void write(GameState& current_state);
    void read(CLGameInput& game_input);

private:
    const std::string& filename;
    std::ifstream input_file;
    std::ofstream output_file;
};


#endif // FILE_HANDLER_HPP