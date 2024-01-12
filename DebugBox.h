#pragma once
#include <string>
#include <vector>

enum class DebugMessageErrorLevel {
    INFO,
    WARNING,
    ERROR
};

static const std::string DebugMessageErrorLevelStrings[3] = {
    "INFO",
    "WARNING",
    "ERROR"
};

class DebugMessage {
    public:
        std::string message;
        DebugMessageErrorLevel error_level;

        DebugMessage(DebugMessageErrorLevel input_error_level, std::string input_message) {
            this->error_level = input_error_level;
            this->message = input_message;
        }

        std::string ToString() {
            std::string output = "[" + DebugMessageErrorLevelStrings[(int)this->error_level] + "] " + this->message;
            return output;
        }
};

class DebugBox {
    public:
        int lines_to_show;
        std::vector<DebugMessage> debug_messages;

        DebugBox() {
            this->lines_to_show = 3;
        }

        DebugBox(int input_lines_to_show) {
            this->lines_to_show = input_lines_to_show;
        }
        
        void AddMessage(DebugMessageErrorLevel error_level, std::string text) {
            this->debug_messages.push_back(DebugMessage(error_level, text));
        }

        std::string GetVisibleLines() {
            std::string output = "";
            for (int i = this->lines_to_show; i > 0; i--) {
                if (i < 0) {continue;}
                output += this->debug_messages[this->debug_messages.size() - i].ToString();
                output += "\n";
            }
            return output;
        }
};
