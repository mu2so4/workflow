#ifndef WORKFLOW_EXCEPTIONS_H
#define WORKFLOW_EXCEPTIONS_H

#include <exception>
#include <string>

class FileNotFoundException: public std::exception {
    std::string message;

public:
    explicit FileNotFoundException(std::string message):
            message(std::move(message)) {}

    ~FileNotFoundException() override = default;

    FileNotFoundException(const FileNotFoundException &otherErr) noexcept:
    message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};


class ArgumentException: public std::exception {
    std::string message;

public:
    explicit ArgumentException(std::string message):
    message(std::move(message)) {}

    ~ArgumentException() override = default;

    ArgumentException(const ArgumentException &otherErr) noexcept:
            message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};


class IllegalStateException: public std::exception {
    const std::string message;

public:
    explicit IllegalStateException(std::string message):
    message(std::move(message)) {}

    ~IllegalStateException() override = default;

    IllegalStateException(const IllegalStateException &otherErr) noexcept:
            message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};


class CommandNotFoundException: public std::exception {
    const std::string message;

public:
    explicit CommandNotFoundException(std::string message):
    message(std::move(message)) {}

    ~CommandNotFoundException() override = default;

    CommandNotFoundException(const CommandNotFoundException &otherErr) noexcept:
            message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class CommandCompatibilityException: public std::exception {
    const std::string message;

public:
    explicit CommandCompatibilityException(std::string message):
            message(std::move(message)) {}

    ~CommandCompatibilityException() override = default;

    CommandCompatibilityException(const CommandCompatibilityException &otherErr) noexcept:
            message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class ConfigFileFormatException: public std::exception {
    const std::string message;

public:
    explicit ConfigFileFormatException(std::string message):
    message(std::move(message)) {}

    ~ConfigFileFormatException() override = default;

    ConfigFileFormatException(const ConfigFileFormatException &otherErr) noexcept:
            message(otherErr.message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif //WORKFLOW_EXCEPTIONS_H
