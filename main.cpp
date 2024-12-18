#include <iostream>
#include <fstream>
#include <stdint.h>

struct __attribute__((__packed__)) BMPHeader
{
    char ID[2];
    uint32_t FileSize;
    char Unused[4];
    uint32_t PixelOffset;
};

int main ()
{
    struct BMPHeader Header;
    std::ifstream MyFile("images/flag.bmp");
    MyFile.read((char*)&Header, sizeof(Header));

    std::cout << "ID address: " << &Header.ID << std::endl;
    std::cout << "File Size address: " << &Header.FileSize << std::endl;

    std::cout << "Id: " << Header.ID << std::endl;
    std::cout << "File Size: " << Header.FileSize << std::endl;
    std::cout << "Pixel offset: " << Header.PixelOffset << std::endl;
    return 0;
}

   /* 
    std::ifstream MyFile ("main.cpp");
    char array[50];
    MyFile.getline(array, 50);
    std::cout << array << std::endl;

    std::ifstream MyFile ("images/flag.bmp");
    char array[50];
    MyFile.read(array, 50);
    std::cout << array << std::endl;
  */