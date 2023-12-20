#include "PulsePropogation.h"

#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "Module.h"
#include "../Common/Common.h"

using namespace std;

int64_t PulsePropogation::get()
{
    bool useExample = false;

    fstream file = useExample ? fstream("Day20/test.txt", ios::in) : fstream("Day20/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    map<string, Module*> modules;
    string line;
    while (getline(file, line))
    {
        vector<string> values = Common::splitString(line, ' ');
        string id = values[0];
        values.erase(values.begin(), values.begin() + 2);
        for (string& value : values)
        {
            if (value[value.size() - 1] == ',')
            {
                value.erase(value.size() - 1, 1);
            }
        }
        if (id == "broadcaster")
        {
            modules.emplace(id, new Broadcaster(id, values));
            continue;
        }
        if (id[0] == '%')
        {
            id.erase(0, 1);
            modules.emplace(id, new FlipFlop(id, values));
            continue;
        }
        if (id[0] == '&')
        {
            id.erase(0, 1);
            modules.emplace(id, new Conjunction(id, values));
            continue;
        }
    }
    modules.emplace("button", new Button("button", { "broadcaster" }));
    modules.emplace("output", new Module("output", {}));
    queue<Signal> signalQueue;
    for (pair<const string, Module*> module : modules)
    {
        module.second->initializeConnections(modules, &signalQueue);
    }

    Module* button = modules["button"];
    for (int i = 0; i < 1000; ++i)
    {
        button->receive(Low, nullptr);

        // printf("%i\n", i + 1);
        while (!signalQueue.empty())
        {
            Signal signal = signalQueue.front();
            signalQueue.pop();
            // printf("%s -%s-> %s\n", signal.source->name.c_str(), signal.pulse == High ? "high" : "low", signal.receiver->name.c_str());
            signal.receiver->receive(signal.pulse, signal.source);
        }
        // printf("\n");
    }

    int64_t highPulses = 0;
    int64_t lowPulses = 0;
    for (pair<const string, Module*> module : modules)
    {
        int64_t highPulsesThisModule = module.second->getHighPulses();
        int64_t lowPulsesThisModule = module.second->getLowPulses();

        highPulses += highPulsesThisModule;
        lowPulses += lowPulsesThisModule;
    }

    for (pair<const string, Module*> module : modules)
    {
        delete module.second;
    }
    modules.clear();

    return lowPulses * highPulses;
}

int64_t PulsePropogation::get2()
{
    bool useExample = false;

    fstream file = useExample ? fstream("Day20/test.txt", ios::in) : fstream("Day20/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    map<string, Module*> modules;
    string finalModuleID;
    string line;
    while (getline(file, line))
    {
        vector<string> values = Common::splitString(line, ' ');
        string id = values[0];
        values.erase(values.begin(), values.begin() + 2);
        for (string& value : values)
        {
            if (value[value.size() - 1] == ',')
            {
                value.erase(value.size() - 1, 1);
            }
        }
        if (id == "broadcaster")
        {
            modules.emplace(id, new Broadcaster(id, values));
            continue;
        }
        if (id[0] == '%')
        {
            id.erase(0, 1);
            modules.emplace(id, new FlipFlop(id, values));
            continue;
        }
        if (id[0] == '&')
        {
            id.erase(0, 1);
            if (values[0] == "rx")
            {
                finalModuleID = id;
            }
            modules.emplace(id, new Conjunction(id, values));
            continue;
        }
    }
    modules.emplace("button", new Button("button", { "broadcaster" }));
    modules.emplace("output", new Module("output", {}));
    queue<Signal> signalQueue;
    for (pair<const string, Module*> module : modules)
    {
        module.second->initializeConnections(modules, &signalQueue);
    }
    map<Module*, int> pulsesToEnable;
    Conjunction* finalModule = dynamic_cast<Conjunction*>(modules[finalModuleID]);
    for (Module* contributorModule : finalModule->getIncomingModuleConnections())
    {
        pulsesToEnable.emplace(contributorModule, -1);
    }

    Module* button = modules["button"];
    int i = 0;
    for (; i < 10000; ++i)
    {
        button->receive(Low, nullptr);

        // printf("%i\n", i + 1);
        while (!signalQueue.empty())
        {
            Signal signal = signalQueue.front();
            signalQueue.pop();
            // printf("%s -%s-> %s\n", signal.source->name.c_str(), signal.pulse == High ? "high" : "low", signal.receiver->name.c_str());
            signal.receiver->receive(signal.pulse, signal.source);
            if (signal.pulse == Low && pulsesToEnable.contains(signal.receiver) && pulsesToEnable[signal.receiver] < 0)
            {
                pulsesToEnable[signal.receiver] = i + 1;
            }
        }
    }
    vector<int> multiples;
    for (pair<const Module*, int> pulsesToEnableValue : pulsesToEnable)
    {
        multiples.push_back(pulsesToEnableValue.second);
    }

    for (pair<const string, Module*> module : modules)
    {
        delete module.second;
    }
    modules.clear();

    return Common::LCM(multiples);
}
