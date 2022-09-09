#pragma once
#include <cstdarg>
#include <iostream>
#include <strsafe.h>
#include <windows.h>
#undef Assert
#undef ASSERT
#define COMMON_MESSAGE_LENGTH 1024
static inline void Assert(const char* aFile, unsigned int aLine, const char* aFormat, ...)
{
  va_list argList = nullptr;
  va_start(argList, aFormat);

  char logMessage[COMMON_MESSAGE_LENGTH];
  memset(logMessage, 0, sizeof(char) * COMMON_MESSAGE_LENGTH);

  _vsnprintf_s(logMessage, COMMON_MESSAGE_LENGTH, aFormat, argList);
  va_end(argList);

  char finalMessage[COMMON_MESSAGE_LENGTH];
  memset(finalMessage, 0, sizeof(char) * COMMON_MESSAGE_LENGTH);

  auto foramtMessage = [](char aMessage[COMMON_MESSAGE_LENGTH], const char* aFinalFormat, ...) {
    va_list argList = nullptr;
    va_start(argList, aFinalFormat);
    _vsnprintf_s(aMessage, COMMON_MESSAGE_LENGTH, COMMON_MESSAGE_LENGTH, aFinalFormat, argList);
    va_end(argList);
  };

  foramtMessage(finalMessage, "%s (%d): %s\n", aFile, aLine, logMessage);

  std::cout << finalMessage;

  OutputDebugStringA(finalMessage);

  char* killMe = nullptr;
  *killMe      = 0;
}

#define ASSERT_STR(x, FORMAT, ...)                                                                 \
  if (!(x))                                                                                        \
  Assert(__FILE__, __LINE__, FORMAT, __VA_ARGS__)

#define ASSERT(x)                                                                                  \
  if (!(x))                                                                                        \
  Assert(__FILE__, __LINE__, #x)