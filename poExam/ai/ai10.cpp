#include <iostream>
#include <string>

enum LogLevel
{
  INFO,
  DEBUG,
  WARNING,
  ERROR,
};

const std::string LogLevelTab[] = {"INFO", "DEBUG", "WARNING", "ERROR"};

class Logger
{
private:
  Logger() = default;

public:
  static LogLevel state;

  static Logger getInstance()
  {
    Logger temp{};
    return temp;
  }

  void log(LogLevel log, const std::string &message) const
  {
    if (log >= state)
    {
      std::cout << "[" << LogLevelTab[log] << "] " << message << std::endl;
    }
  }

  static void setLogLevel(LogLevel log)
  {
    state = log;
  }
};

LogLevel Logger::state = LogLevel::INFO;

int main()
{
  const Logger &logger = Logger::getInstance();

  logger.log(LogLevel::INFO, "Starting application");
  logger.log(LogLevel::DEBUG, "Initializing components");
  logger.log(LogLevel::WARNING, "Low memory");
  logger.log(LogLevel::ERROR, "Failed to connect to database");

  Logger::setLogLevel(LogLevel::WARNING);

  logger.log(LogLevel::INFO, "This should not be printed");

  logger.log(LogLevel::WARNING, "This should be printed");
  logger.log(LogLevel::ERROR, "This should also be printed");

  // Logger logger2; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
[INFO] Starting application
[DEBUG] Initializing components
[WARNING] Low memory
[ERROR] Failed to connect to database

[WARNING] This should be printed
[ERROR] This should also be printed
*/