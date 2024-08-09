// 21120316.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Func.h"
#include <string>

int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    cv::Mat src = cv::imread(argv[2], cv::IMREAD_COLOR);
    cv::Mat dst;
    
    std::string* command = new std::string[8];
    command[0] = "-rgb2gray";
    command[1] = "-brightness";
    command[2] = "-constrast";
    command[3] = "-avg";
    command[4] = "-med";
    command[5] = "-gau";
    command[6] = "-sobel";
    command[7] = "-laplace";

    int inx = -1;
    Func method;
    
    for (int i = 0; i < 8; i++)
    {
        if (command[i] == argv[1])
            inx = i;
    }

    int value = 0;
    if (argv[4])
        value = atoi(argv[4]);

    switch (inx)
    {
        case 0:
            method.rbg2gray(src, dst);
            break;
        case 1:
            method.brightness(src, dst, value);
            break;
        case 2:
            method.constrast(src, dst, value);
            break;
        case 3:
            method.avg(src, dst, value);
            break;
        case 4:
            method.med(src, dst, value);
            break;
        case 5:
            method.gau(src, dst, value);
            break;
        case 6:
            method.sobel(src, dst);
            break;
        case 7:
            method.laplace(src, dst);
            break;
        default:
            std::cout << "ERROR" << std::endl;
            break;
    }
        
    // Get a named window
    // cv::namedWindow("Green Color plane");

    // show the green plane (gray image)
    cv::imshow("Src", src);
    cv::imshow("Dst", dst);
    cv::imwrite(argv[3], dst);
    int k = cv::waitKey(0);

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
