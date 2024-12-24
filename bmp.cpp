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

struct __attribute__((__packed__)) DIBHeader
{
    uint32_t HeaderSize;
    uint32_t Width;
    uint32_t Height;
};

struct __attribute__((__packed__)) DIBHeaderTail
{
};

union Pixel
{
    uint32_t Value;
    struct __attribute__((__packed__)) 
    {
        unsigned int B: 8;
        unsigned int G: 8;
        unsigned int R: 8;
        unsigned int A: 8;
    };
};


int main ()
{
    struct BMPHeader Header;
    std::ifstream MyFile("images/pixels.bmp");  
    MyFile.read((char*)&Header, sizeof(Header));

    std::cout << "ID address: " << &Header.ID << std::endl;
    std::cout << "File Size address: " << &Header.FileSize << std::endl;

    std::cout << "Id: " << Header.ID << std::endl;
    std::cout << "File Size: " << Header.FileSize << std::endl;
    std::cout << "Pixel offset: " << Header.PixelOffset << std::endl;

    struct DIBHeader ImageDetails;
    MyFile.read((char*)&ImageDetails, sizeof(ImageDetails));

    std::cout << "DIB Header Size: " << ImageDetails.HeaderSize << std::endl;
    std::cout << "Width: " << ImageDetails.Width << std::endl;
    std::cout << "Height: " << ImageDetails.Height << std::endl;

    char Tail[ImageDetails.HeaderSize - sizeof(ImageDetails)];
    MyFile.read((Tail), ImageDetails.HeaderSize - sizeof(ImageDetails));

    Pixel Pixels[ImageDetails.Width * ImageDetails.Height];
    MyFile.read((char*)Pixels, sizeof(Pixel) * ImageDetails.Width * ImageDetails.Height);

    for(int h = ImageDetails.Height - 1; h >= 0; h--)
    {
        for(int w = 0; w <= ImageDetails.Width - 1; w++)
        {
            Pixel& P = Pixels[(ImageDetails.Width * h + w)];
            std::cout << "(" << P.R << ", " << P.G << ", " << P.B << ", " << P.A << ") ";
            P.B = 255 - P.B;
            P.G = 255 - P.G;
            P.R = 255 - P.R;
            std::cout << "(" << P.R << ", " << P.G << ", " << P.B << ", " << P.A << ") ";
        }
        std::cout << std::endl;
    }

    std::ofstream Output ("images/inverted.bmp");
    Output.write((char*)&Header, sizeof(Header));
    Output.write((char*)&ImageDetails, sizeof(ImageDetails));
    Output.write((char*)&Tail, ImageDetails.HeaderSize - sizeof(ImageDetails));
    Output.write((char*)Pixels, sizeof(Pixel) * ImageDetails.Width * ImageDetails.Height);
    Output.close();

    return 0;
}
