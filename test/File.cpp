#include "File.h"

void ListContent( const std::filesystem::path& pathContent, uint16_t uSpace)
{
	for( const auto& it : std::filesystem::directory_iterator(pathContent) )
	{
		std::cout << std::string(uSpace * 2, ' ') << it.path().filename().string() << '\n';

		if( it.is_directory() )
		{
			ListContent(it.path(), uSpace + 1);
		}
	}
}

int main()
{
	std::filesystem::directory_entry directoryEntryContent("D:/dev/testfiles");
	std::filesystem::path pathFile = "D:/dev/testfiles/A.txt";

	/*for( const auto& it : std::filesystem::directory_iterator(directoryEntryContent) )
	{
		std::cout << it.path().string() << '\n';
	}*/

	ListContent(directoryEntryContent, 0);

	return 0;
}