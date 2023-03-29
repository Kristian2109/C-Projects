#include <iostream>
#include "TextFilesManager.h"

int main()
{
	TextFilesManager fs(5);
	fs.addFile("test.txt", 14, 0, 0, 20, 3, 2023, "rwxr--r--");
	fs.editFile("test.txt", "Hello, world!", 14, 10, 0, 20, 3, 2023, 'u');
	fs.editFile("test.txt", "Hello, world!", 14, 11, 0, 20, 3, 2023, 'o');
	fs.addInFile("test.txt", "Hello, my friend!", 14, 13, 0, 20, 3, 2023, 'u');
	fs.editFile("test.txt", "Hello", 14, 15, 0, 20, 3, 2023, 'u');
	fs.addFile("attest.txt", 14, 30, 0, 20, 3, 2023, "rwxr--r--");
	fs.deleteFile("attest.txt");
	fs.printFileInfo("test.txt");
	fs.addFile("attest.txt", 14, 35, 0, 20, 3, 2023, "rwxr--r--");
	fs.changeRights("attest.txt", 'u', 'r');
	fs.printFile("attest.txt", 'u');
	fs.changeRights("attest.txt", 'u', 'r');
	fs.printFile("attest.txt", 'u');
	fs.printFileInfo("test.txt");
	fs.sort(SortOptions::name);
	fs.print();
	//attest.txt
	//test.txt

	fs.sort(SortOptions::modificationTime);
	fs.print();//test.txt
		//attest.txt
}
