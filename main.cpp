// CPlusPlusNotes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "main.h"
#include "timer.h"

int main()
{

    Timer t = Timer();

    t.setInterval([&]() {
        std::cout << "Hey.. After each 1s..." << std::endl;
    }, 1000);

    t.setTimeout([&]() {
        std::cout << "Hey.. After 5.2s. But I will stop the timer!" << std::endl;
        t.stop();
    }, 5200);


    std::cout << "I am Timer" << std::endl;

    while (true); // Keep main thread active

	//int temperature = GetTemperature();

	//std::cout << temperature << std::endl;

}



