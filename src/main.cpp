#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#ifdef DEBUGGING
#include <spdlog/spdlog.h>
#endif

#include "version.h"
#include <bson.h>
#include <mongoc.h>

// to be include here

// use these tags to remind others
// Tags: TODO:, BUGME:, NEW:, MORETEST:

using namespace std;

#ifdef DEBUGGING

void initLoggers() {
      // setup loggers
      try {
            // create two logger for console and file
            auto console = spdlog::stdout_color_mt("console.log");

            // get file name as run time
            time_t      t = time(nullptr);
            std::string file_name(asctime(std::localtime(&t)));
            file_name = file_name.substr(0, 24);
            file_name = "logs/" + file_name + ".log";
            // create log file with name as run time
            auto file = spdlog::basic_logger_mt("file.log", file_name);

            console->set_pattern("[ %H:%M:%S.%F ]\n    >> %v");
            file->set_pattern("[%H:%M:%S.%F]\n    >> %v");

      } catch (const spdlog::spdlog_ex& ex) {
            std::cout << "Some error occured " << ex.what() << "\n";
            exit(255);
      }
}

#endif      // NDEBUG

int main(int argc, char** argv, char** envp) {
      if (argc == 2 && strcmp(argv[1], "--version") == 0) {
            cout << "mloader" << endl;
            cout << "VERSION: ";
            cout << VERSION_MAJOR << ".";
            cout << VERSION_MINOR << ".";
            cout << VERSION_FIX << endl;
            cout << "Created by Ryan" << endl;
            return 0;
      }

#ifdef _WIN32
      system("cls");
#elif __unix
      system("clear");
#endif

#ifdef DEBUGGING
      initLoggers();
      auto console = spdlog::get("console.log");
      auto file    = spdlog::get("file.log");
      console->info("Logging system initialized");
      file->info("Logging system initialized");
#endif      // NDEBUG

      // TODO: Code here
      cout << "Hello World!" << endl;
      return 0;
}