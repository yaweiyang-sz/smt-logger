#include "smt_logger.h"
#include <iostream>
#include <thread>

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

std::string MODULE_NAME = "camera";

void test_level_off(){
	setupLogger({"default", LogLevel::OFF, false, 3});

	// no log will be printed or written
	logInfo("Camera", "LogInfo");
}

void test_level_trace(){
	LoggerConfig config ={"default", LogLevel::TRACE, false, 3};
	setupLogger(config);

	// only logs under debug level can be printed at console
	logTrace("tag0", "trace msg...");
	logDebug("tag1", "debug msg...");
	logInfo("tag2", "info msg...");
	logWarn("tag3", "info msg...");
	logError("tag4", "error msg...");
	logCritical("tag5", "critical msg...");
}

void test_multi_params(){
	logError("Camera", "hello %s %s %s", "123", "jia", "you");
}

void test_multi_logs(){
	setupLogger({"default", LogLevel::TRACE, true, 3});
	for (int i = 0; i < 10; i++){
		logWarn("multi logs", "warn logs: %d", i);
		logInfo("multi logs", "info logs: %d", i);
	}
}

void func_thread(int index){
	logInfo("multi thread", "log: %d", index);
}

void test_muti_thread(){
	for (int i = 0; i < 10; i++){
		std::thread thread = std::thread(func_thread, i);
		thread.detach();
	}

	PAUSE
}

int main(int argc, char *argv[]){
	test_multi_logs();
	return 0;
}