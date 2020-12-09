//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

struct InstrumentationSession;
struct ProfileResult;

class Profiler
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
public:
    Profiler();

    void BeginSession(const std::string& name, const std::string& filepath = "results.json");
    void EndSession();

    void WriteProfile(const ProfileResult& result);

    void WriteHeader();
    void WriteFooter();

    static Profiler& Get();
};

class ScopedProfileTimer
{
public:
    ScopedProfileTimer(const char* name);
    ~ScopedProfileTimer();

    void Stop();
private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#if defined(PROFILE_ENABLED)
    #define BEGIN_PROFILE_SESSION(name, filepath) Profiler::Get().BeginSession(name, filepath)
    #define END_PROFILE_SESSION() Profiler::Get().EndSession()

    #define PROFILE_SCOPE(scope) ScopedProfileTimer timer##__LINE__(scope)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
    #define BEGIN_PROFILE_SESSION(name, filepath)
    #define END_PROFILE_SESSION()

    #define PROFILE_SCOPE(scope)
    #define PROFILE_FUNCTION()
#endif //PROFILE_ENABLED