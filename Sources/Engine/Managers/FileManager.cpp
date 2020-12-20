#include <Engine/Managers/FileManager.hpp>
#include <Utility/Debugging/Assert.hpp>

std::ifstream FileManager_Impl::OpenFile(const std::string& filepath, std::ios_base::openmode mode)
{
    std::ifstream file(ConstructFilePath(filepath), mode);
    return std::move(file);
}

std::vector<char> FileManager_Impl::ReadFile(const std::string& filepath)
{
    auto fileStream = OpenFile(filepath, std::ios::binary | std::ios::ate);
    const std::streamsize size = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);
    std::vector<char> data(size);

    if (fileStream.read(data.data(), size))
    {
        return data;
    }
    M42_ASSERT(false, "can't open binary file");
    data.clear();
    return data;
}

std::string FileManager_Impl::GetFullFilePath(const std::string& relativePath)
{
    std::filesystem::path absolutePath = ConstructFilePath(relativePath);
    return absolutePath.generic_string();
}

void FileManager_Impl::SetWorkingDirectory(const std::filesystem::path& workingDirectory)
{
    m_workingDirectory = workingDirectory;
}

std::filesystem::path FileManager_Impl::ConstructFilePath(const std::string& relativePath)
{
    return m_workingDirectory / relativePath;
}
