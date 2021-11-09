/*
*   Author: Tim Robbins
*   Date: 9/26/21
*
*   Purpose: 
*        Encode an image using the FibLFSR class. Store encoded image on disk.
*
*   Known Bugs:
*        None known
*/

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FibLFSR.h"

void transform(sf::Image& image, FibLFSR* seed);
std::string passwordToBinary(std::string password);

int main(int argc, char* argv[])
{   
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string password = argv[3];
    std::string key(passwordToBinary(password));

    FibLFSR *fib = new FibLFSR(key);
  
    sf::Image image;
    if (!image.loadFromFile(inputFile)) {
        std::cout << "Failed to load image." << std::endl;
        exit(1);
    }

    sf::Image alteredImage;
    if (!alteredImage.loadFromFile(inputFile)) {
        std::cout << "Failed to load image." << std::endl;
        exit(1);
    }

    transform(alteredImage, fib);
    
    sf::Vector2u size = image.getSize();
    sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Original Image");
    sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Encrypted Image");

    sf::Texture original;
    original.loadFromImage(image);
    sf::Sprite spriteOriginal;
    spriteOriginal.setTexture(original);

    sf::Texture encryptedImage;
    encryptedImage.loadFromImage(alteredImage);
    sf::Sprite spriteEncrypted;
    spriteEncrypted.setTexture(encryptedImage);



    while (window1.isOpen() && window2.isOpen())
    {
            sf::Event event;
            while (window1.pollEvent(event))
            {
                    if (event.type == sf::Event::Closed)
                            window1.close();
            }
            while (window2.pollEvent(event))
            {
                    if (event.type == sf::Event::Closed)
                            window2.close();
            }

            window1.clear(sf::Color::White);
            window1.draw(spriteOriginal);
            window1.display();
            window2.clear(sf::Color::White);
            window2.draw(spriteEncrypted);
            window2.display();
    }

    if (!alteredImage.saveToFile(outputFile)){
        std::cout << "Failed to save image to file" << std::endl;
        exit(1);
    }

    return 0;
}

void transform(sf::Image& image, FibLFSR* seed) {
    sf::Color p;
    sf::Vector2u size = image.getSize();

    for (int x = 0; x< (int)size.x; x++) {
            for (int y = 0; y < (int)size.y; y++) {
                p = image.getPixel(x, y);

                p.r ^= seed->generate(8);
                p.g ^= seed->generate(8);
                p.b ^= seed->generate(8);

                image.setPixel(x, y, p);
            }
    }
}

std::string passwordToBinary(std::string password) {
    int sum{ 0 };
    std::string reverseBinaryKey;
    std::string binaryKey;
    
    for (int i = 0; i < static_cast<int>(password.size()); i++) {
        sum += static_cast<int>(password.at(i));
    }

    while (sum > 1) {
        char binary;
        binary = (sum % 2 == 1) ? '1' : '0';
        reverseBinaryKey.push_back(binary);
        sum /= 2;
    }
    reverseBinaryKey.push_back('1');

    for (int i = static_cast<int>(reverseBinaryKey.size() - 1); i >= 0; i--) {
        binaryKey.push_back(reverseBinaryKey.at(i));
    }

    return binaryKey;
}