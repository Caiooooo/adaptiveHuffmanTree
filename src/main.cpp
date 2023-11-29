#include <iostream>
#include <Windows.h>
#include <limits>
#include "zip.h"
#include "unzip.h"
int main()
{
    while (true)
    {
        system("cls");
        std::cout << "Welcome to use zh&bw's tool!\n";
        std::cout << "choose a number: \n";
        std::cout << "1.zip 2.unzip 3.exit\n";
        std::string choose;
        std::string name;
        std::getline(std::cin, choose);
        int choose_int = 0;
        try
        {
            choose_int = std::stoi(choose);
        }
        catch (const std::exception &e)
        {
            choose_int = -1;
        }
        // input choose

        zip myzip;
        unzip myunzip;
        switch (choose_int)
        {
        case 1:
            std::cout << "please input the file name:(e.g test) ";
            std::cin >> name;
            if (myzip.zipFile(name))
                std::cout << "success!\n";
            else
                std::cout << "failed!\n";
            break;
        case 2:
            std::cout << "please input the file name:(e.g test.doc.zip) ";
            std::cin >> name;
            myunzip.unzipFile(name);
            break;
        case 3:
            return 0;
            break;
        default:
            std::cout << "please input a right number!\n";
            break;
        }

        Sleep(1000);
        // clear input buffer
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        // clear screen
        system("cls");
    }
    return 0;
}