#include "File.h"
#include <unordered_set>

const std::unordered_set<std::string> unorderedsetExtensions_g = { ".txt", ".md", ".pdf", ".docx", ".log" };

/**
* @brief Recursively lists the content of a directory 
*
* Iterates through all entries in the specified directory and stores
* text files inside vectorFiles
* 
* @param vectorFiles Vector where entries are stored
* @param pathDirectory Directory to scan
*/
void ListFiles( std::vector<std::filesystem::path>& vectorFiles, const std::filesystem::path& pathDirectory, uint8_t uRecursive )
{
	for( const auto& it : std::filesystem::directory_iterator(pathDirectory) )
	{
		const std::filesystem::path& pathEntry = it.path();

		if( it.is_directory() && uRecursive > 0 )
		{
			
			ListFiles(vectorFiles, pathEntry, uRecursive - 1 );
		}
		
		if( !it.is_regular_file() ) { continue;  }

		std::string stringExtension = pathEntry.extension().string();
		if( unorderedsetExtensions_g.find(stringExtension) != unorderedsetExtensions_g.end() )
		{
			vectorFiles.push_back(pathEntry);
		}
	}
}

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

	std::filesystem::directory_entry directoryEntryContent("D:/dev/testfiles");
	std::filesystem::path pathFile = "D:/dev/testfiles/A.txt";

	std::vector<std::filesystem::path> vectorFiles;

	ListFiles(vectorFiles, directoryEntryContent, 2);

	for( auto path : vectorFiles )
	{
		std::cout << path << '\n';
	}

	return 0;
}