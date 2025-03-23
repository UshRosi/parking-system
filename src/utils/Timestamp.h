#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <chrono>
#include <string>

uint64_t getTimestamp();

std::string getString(uint64_t timestamp);

#endif // TIMESTAMP_H
