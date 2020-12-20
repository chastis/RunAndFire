#pragma once

#include <Utility/Core/Singleton.hpp>

#include <filesystem>
#include <fstream>

class FileManager_Impl
{
public:
    std::ifstream OpenFile(const std::string& filepath, std::ios_base::openmode mode = std::ios_base::in);
    std::vector<char> ReadFile(const std::string& filepath);
    std::string GetFullFilePath(const std::string& relativePath);
    void SetWorkingDirectory(const std::filesystem::path& workingDirectory);

private:
    std::filesystem::path ConstructFilePath(const std::string& relativePath);

    std::filesystem::path m_workingDirectory;
private:
    FileManager_Impl() = default;
    ~FileManager_Impl() = default;


    friend class Singleton<FileManager_Impl>;
};

using FileManager = Singleton<FileManager_Impl>;