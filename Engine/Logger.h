#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>

enum class LogLevel { INFO, WARNING, ERROR };

class LogSink {
public:
    virtual void log(LogLevel level, const std::string& message) = 0;
    virtual ~LogSink() = default;
};

class ConsoleSink : public LogSink {
public:
    void log(LogLevel level, const std::string& message) override {
        std::cout << logLevelToString(level) << " " << message << std::endl;
    }

private:
    std::string logLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO: return "[INFO]";
        case LogLevel::WARNING: return "[WARNING]";
        case LogLevel::ERROR: return "[ERROR]";
        default: return "[UNKNOWN]";
        }
    }
};

class FileSink : public LogSink {
private:
    std::ofstream logFile;

public:
    FileSink(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }

    void log(LogLevel level, const std::string& message) override {
        if (logFile) {
            logFile << logLevelToString(level) << " " << message << std::endl;
        }
    }

    ~FileSink() {
        if (logFile.is_open()) logFile.close();
    }

private:
    std::string logLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO: return "[INFO]";
        case LogLevel::WARNING: return "[WARNING]";
        case LogLevel::ERROR: return "[ERROR]";
        default: return "[UNKNOWN]";
        }
    }
};

class Logger {
private:
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::mutex logMutex;

public:
    void addSink(std::shared_ptr<LogSink> sink) {
        sinks.push_back(sink);
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        for (auto& sink : sinks) {
            sink->log(level, message);
        }
    }

    void info(const std::string& message) { log(LogLevel::INFO, message); }
    void warn(const std::string& message) { log(LogLevel::WARNING, message); }
    void error(const std::string& message) { log(LogLevel::ERROR, message); }
};

class LoggerRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
    std::shared_ptr<Logger> defaultLogger;
    std::mutex registryMutex;

public:
    static LoggerRegistry& getInstance() {
        static LoggerRegistry instance;
        return instance;
    }

    std::shared_ptr<Logger> getLogger(const std::string& name) {
        std::lock_guard<std::mutex> lock(registryMutex);
        if (loggers.find(name) != loggers.end()) {
            return loggers[name];
        }
        return defaultLogger;
    }

    void setDefaultLogger(std::shared_ptr<Logger> logger) {
        defaultLogger = logger;
    }

    void registerLogger(const std::string& name, std::shared_ptr<Logger> logger) {
        std::lock_guard<std::mutex> lock(registryMutex);
        loggers[name] = logger;
    }
};

#define LOG_INFO(message) LoggerRegistry::getInstance().getLogger("global")->info(message)
#define LOG_WARN(message) LoggerRegistry::getInstance().getLogger("global")->warn(message)
#define LOG_ERROR(message) LoggerRegistry::getInstance().getLogger("global")->error(message)
