#pragma once

#include <string>
#include <vector>

#include "../../include/assimp/ai_assert.h"
#include "../qnan.h"

#define YY_NO_UNISTD_H

#ifndef INFINITY
#define INFINITY 2.0e38f
#endif

#ifndef M_PI
#define M_PI 3.141592653589793238f
#endif

#define Assert(x) ai_assert(x)

namespace pbrt
{

using std::string;
using std::vector;
using std::min;
using std::max;
using std::swap;

void Info(const char *, ...);
void Warning(const char *, ...);
void Error(const char *, ...);
void Severe(const char *, ...);

// we're not even reentrant
typedef int AtomicInt32;
AtomicInt32 AtomicAdd(AtomicInt32* p, AtomicInt32 n) { return *p += n; }

template <class Real> inline Real Clamp(Real x, Real a, Real b) { return min(max(a, x), b); }
inline float Lerp(float x, float y, float a) { return (1.0f - a) * x + a * y; }
template <class Real> inline bool isnan(Real x) { return x != x; }

// not needed
inline int isatty(...) { return 0; }
inline int fileno(...) { return 0; }

// todo
string AbsolutePath(string s);
string ResolveFilename(string s);

inline bool ReadFloatFile(...) { return false; }

} // namespace