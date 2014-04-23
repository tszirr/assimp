#include "../AssimpPCH.h"

#include "pbrt.h"
#include <cstdio>
#include <cstdarg>

#include "../Exceptional.h"
#include "../../include/assimp/types.h"
#include "../../include/assimp/DefaultLogger.hpp"

namespace pbrt
{

string AbsolutePath(string s) { return s; }
string ResolveFilename(string s) { return s; }

void Info(const char *format, ...) {
     va_list args;
    va_start(args, format);
	char buffer[16000];
	vsprintf(buffer, format, args);
	Assimp::DefaultLogger::get()->warn(buffer);
    va_end(args);
}


void Warning(const char *format, ...) {
    va_list args;
    va_start(args, format);
	char buffer[16000];
	vsprintf(buffer, format, args);
	Assimp::DefaultLogger::get()->warn(buffer);
    va_end(args);
}


void Error(const char *format, ...) {
    va_list args;
    va_start(args, format);
	char buffer[16000];
	vsprintf(buffer, format, args);
	Assimp::DefaultLogger::get()->error(buffer);
    va_end(args);
}


void Severe(const char *format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[16000];
	vsprintf(buffer, format, args);
	Assimp::DefaultLogger::get()->error(buffer);
	throw DeadlyImportError(buffer);
	va_end(args);
}

} // namespace