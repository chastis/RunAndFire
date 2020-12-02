#include <Engine/Managers/FileManager.hpp>

std::ifstream FileManager_Impl::OpenFile(const std::string& filepath, std::ios_base::openmode mode)
{
    std::ifstream file(ConstructFilePath(filepath), mode);
    return std::move(file);
}

void FileManager_Impl::SetWorkingDirectory(const std::filesystem::path& workingDirectory)
{
    m_workingDirectory = workingDirectory;
}

std::filesystem::path FileManager_Impl::ConstructFilePath(const std::string& relativePath)
{
    return m_workingDirectory / relativePath;
}