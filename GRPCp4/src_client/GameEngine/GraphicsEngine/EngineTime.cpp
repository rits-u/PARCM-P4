#include "EngineTime.h"
#include <thread>
#include <chrono>

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
    sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

float EngineTime::getFPS()
{
    return sharedInstance->fps;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
    sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;
    sharedInstance->deltaTime = elapsed_seconds.count();

    //smoothing
    float currentFPS = static_cast<float>(1.0 / sharedInstance->deltaTime);
    sharedInstance->fps = sharedInstance->fps * sharedInstance->smoothing + currentFPS * (1.0f - sharedInstance->smoothing);

    //limit to 60ish
    const double targetFPS = 1.0 / 60.0;
    if (sharedInstance->deltaTime < targetFPS)
    {
        std::this_thread::sleep_for(std::chrono::duration<double>(targetFPS - sharedInstance->deltaTime));
        sharedInstance->end = std::chrono::system_clock::now();
        sharedInstance->deltaTime = std::chrono::duration<double>(sharedInstance->end - sharedInstance->start).count();
    }

    //next frame
    sharedInstance->start = sharedInstance->end;

   // std::cout << "fps: " << sharedInstance->fps << std::endl;
}
