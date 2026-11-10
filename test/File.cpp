#include "File.h"

struct FileEntry
{
	std::string stringName;
	std::vector<FileEntry> vectorChildren;
	uintmax_t uSize = 0;
	bool bDirectory;
};

void PrintContent(std::vector<FileEntry>& vectorContent, const std::filesystem::path& pathContent, uint16_t uSpace)
{
	size_t uSize = vectorContent.size();

	//std::cout << pathContent.filename().string() << '\n';

	for( size_t u = 0; u < uSize; u++ )
	{
		std::cout << std::string(3 * uSpace, ' ') << "├─ " << vectorContent[u].stringName << '\n';

		if( u == uSize - 1 )
		{
			std::cout << std::string(3 * uSpace, ' ') << "└─ " << vectorContent[uSize - 1].stringName << '\n';
		}
		if( vectorContent[u].bDirectory == true && vectorContent[u].vectorChildren.empty() == false )
		{
			PrintContent( vectorContent[u].vectorChildren, pathContent, uSpace + 1 );
		}		
	}
}

/**
* @brief Recursively lists the content of a directory 
*
* Iterates through all entries in the specified directory and creates a
* FileEntry for each file or subdirectory and stores them in vectorContent.
* 
* @param vectorContent Vector where entries are stored.
* @param pathContent Directory to scan.
*/
void ListContent( std::vector<FileEntry>& vectorContent, const std::filesystem::path& pathContent )
{
	for( const auto& it : std::filesystem::directory_iterator(pathContent) )
	{
		FileEntry fileEntry;
		const std::filesystem::path& pathFile = it.path();

		fileEntry.stringName = pathFile.filename().string();

		if( it.is_directory() )
		{
			fileEntry.bDirectory = true;
			ListContent(fileEntry.vectorChildren, pathFile);
		}
		else
		{
			fileEntry.uSize = std::filesystem::file_size(pathFile);
		}
		
		vectorContent.push_back(std::move(fileEntry));
	}
}

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

	std::filesystem::directory_entry directoryEntryContent("D:/dev/testfiles");
	std::filesystem::path pathFile = "D:/dev/testfiles/A.txt";

	std::vector<FileEntry> vectorEntries;
	ListContent(vectorEntries, directoryEntryContent);
	PrintContent(vectorEntries, directoryEntryContent, 0);

	return 0;
}