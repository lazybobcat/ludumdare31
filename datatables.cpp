#include <datatables.h>
#include <resources/particle.h>


std::vector<ParticleData> initializeParticleData()
{
    std::vector<ParticleData> data(Particle::ParticleCount);

    data[Particle::Default].color = sf::Color(255, 255, 50);
    data[Particle::Default].lifetime = sf::seconds(0.6f);

    return data;
}


std::vector<Wave> initializeWaves()
{
    std::vector<Wave> data;
    Wave w;
    int counter = 0;

    // Tutotial time, fake wave
    w.initialWaitTime = sf::seconds(16.f);
    w.repopTime = sf::seconds(0.f);
    w.kidsToKill = 0;
    w.nbTraps = 5;
    w.minIntel = 4;
    w.kidSpeed = 1.5f;
    w.waveTotalTime = sf::seconds(3.f);
    data.push_back(w);
    counter++;

    // First wave
    w.initialWaitTime = sf::seconds(1.f);
    w.repopTime = sf::seconds(5.f);
    w.kidsToKill = 2;
    w.nbTraps = 2;
    w.minIntel = 4;
    w.kidSpeed = 1.5f;
    w.waveTotalTime = sf::seconds(6.f);
    data.push_back(w);
    counter++;

    // Wave 2
    w.initialWaitTime = sf::seconds(1.f);
    w.repopTime = sf::seconds(3.f);
    w.kidsToKill = counter * 2;
    w.nbTraps = 3;
    w.minIntel = 4;
    w.kidSpeed = 1.5f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 3
    w.initialWaitTime = sf::seconds(1.f);
    w.repopTime = sf::seconds(3.f);
    w.kidsToKill = counter * 2;
    w.nbTraps = 4;
    w.minIntel = 3;
    w.kidSpeed = 1.5f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 4
    w.initialWaitTime = sf::seconds(1.f);
    w.repopTime = sf::seconds(2.f);
    w.kidsToKill = counter * 2 + 2;
    w.nbTraps = 8;
    w.minIntel = 3;
    w.kidSpeed = 1.5f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 5
    w.initialWaitTime = sf::seconds(6.f);
    w.repopTime = sf::seconds(2.f);
    w.kidsToKill = counter * 2;
    w.nbTraps = 2;
    w.minIntel = 3;
    w.kidSpeed = 0.9f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 6
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(5.f);
    w.kidsToKill = counter * 2 + 2;
    w.nbTraps = 10;
    w.minIntel = 3;
    w.kidSpeed = 0.9f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 7
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(5.f);
    w.kidsToKill = counter * 2 + 2;
    w.nbTraps = 16;
    w.minIntel = 3;
    w.kidSpeed = 0.8f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 8
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(5.f);
    w.kidsToKill = 18;
    w.nbTraps = 16;
    w.minIntel = 3;
    w.kidSpeed = 0.7f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 9
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(3.f);
    w.kidsToKill = 20;
    w.nbTraps = 17;
    w.minIntel = 3;
    w.kidSpeed = 0.7f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 10
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(2.5f);
    w.kidsToKill = 20;
    w.nbTraps = 17;
    w.minIntel = 3;
    w.kidSpeed = 0.6f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 11
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(2.5f);
    w.kidsToKill = 22;
    w.nbTraps = 17;
    w.minIntel = 2;
    w.kidSpeed = 0.6f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 12
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(2.5f);
    w.kidsToKill = 20;
    w.nbTraps = 17;
    w.minIntel = 2;
    w.kidSpeed = 0.6f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 13
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(2.5f);
    w.kidsToKill = 25;
    w.nbTraps = 20;
    w.minIntel = 2;
    w.kidSpeed = 0.55f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 14
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(2.f);
    w.kidsToKill = 25;
    w.nbTraps = 18;
    w.minIntel = 2;
    w.kidSpeed = 0.55f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    // Wave 15
    w.initialWaitTime = sf::seconds(2.f);
    w.repopTime = sf::seconds(1.f);
    w.kidsToKill = 25;
    w.nbTraps = 10;
    w.minIntel = 1;
    w.kidSpeed = 0.55f;
    w.waveTotalTime = sf::seconds(w.kidsToKill * 3.5f);
    data.push_back(w);
    counter++;

    return data;
}


