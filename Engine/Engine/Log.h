#pragma once

#define UE_LOG(fmt, ...) ConsoleWindow::GetInstance().AddLog(fmt, ##__VA_ARGS__)
#include "ConsoleWindow.h"