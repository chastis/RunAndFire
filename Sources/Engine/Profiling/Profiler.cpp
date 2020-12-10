#include <Engine/Profiling/Profiler.hpp>

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    size_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

Profiler::Profiler()
    : m_CurrentSession(nullptr), m_ProfileCount(0)
{
}

void Profiler::BeginSession(const std::string& name, const std::string& filepath)
{
    m_OutputStream.open(filepath);
    WriteHeader();
    m_CurrentSession = new InstrumentationSession{ name };
}

void Profiler::EndSession()
{
    WriteFooter();
    m_OutputStream.close();
    delete m_CurrentSession;
    m_CurrentSession = nullptr;
    m_ProfileCount = 0;
}

void Profiler::WriteProfile(const ProfileResult& result)
{
    if (m_ProfileCount++ > 0)
        m_OutputStream << ",";

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    m_OutputStream << "{";
    m_OutputStream << "\"cat\":\"function\",";
    m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
    m_OutputStream << "\"name\":\"" << name << "\",";
    m_OutputStream << "\"ph\":\"X\",";
    m_OutputStream << "\"pid\":0,";
    m_OutputStream << "\"tid\":" << result.ThreadID << ",";
    m_OutputStream << "\"ts\":" << result.Start;
    m_OutputStream << "}";

    m_OutputStream.flush();
}

void Profiler::WriteHeader()
{
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputStream.flush();
}

void Profiler::WriteFooter()
{
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

Profiler& Profiler::Get()
{
    static Profiler instance;
    return instance;
}

ScopedProfileTimer::ScopedProfileTimer(const char* name)
    : m_Name(name), m_Stopped(false)
{
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

ScopedProfileTimer::~ScopedProfileTimer()
{
    if (!m_Stopped)
        Stop();
}

void ScopedProfileTimer::Stop()
{
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

    size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Profiler::Get().WriteProfile({ m_Name, start, end, threadID });

    m_Stopped = true;
}
