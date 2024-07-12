#pragma once

#ifndef EMULATOR_IMPORT
#define EMULATOR_API __declspec(dllexport)
#else
#define EMULATOR_API __declspec(dllimport)
#endif