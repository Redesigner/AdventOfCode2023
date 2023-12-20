#include "Module.h"

PulsePropogation::Module::Module(std::string name, std::vector<std::string> destinationModuleStrings)
	:name(name), destinationModuleStrings(destinationModuleStrings)
{
}

PulsePropogation::Module::Module()
{
}

void PulsePropogation::Module::initializeConnections(std::map<std::string, Module*>& moduleMap, std::queue<Signal>* outQueue)
{
	signalQueue = outQueue;

	for (std::string& destinationModuleString : destinationModuleStrings)
	{
		connectedModuleCount++;
		if (!moduleMap.contains(destinationModuleString))
		{
			continue;
		}
		Module* outputModule = moduleMap[destinationModuleString];
		destinationModules.emplace_back(outputModule);
		if (Conjunction* conjunction = dynamic_cast<Conjunction*>(outputModule))
		{
			conjunction->connect(this);
		}
	}
}

void PulsePropogation::Module::receive(Pulse signal, Module* sender)
{
}

int PulsePropogation::Module::getLowPulses() const
{
	return lowPulsesSent;
}

int PulsePropogation::Module::getHighPulses() const
{
	return highPulsesSent;
}

void PulsePropogation::Module::sendSignal(Pulse signal)
{
	for (Module* module : destinationModules)
	{
		signalQueue->emplace(this, signal, module);
	}
	if (signal == High)
	{
		highPulsesSent += connectedModuleCount;
	}
	else
	{
		lowPulsesSent += connectedModuleCount;
	}
}

PulsePropogation::FlipFlop::FlipFlop(std::string name, std::vector<std::string> destinationModuleStrings)
	:Module(name, destinationModuleStrings)
{
}

void PulsePropogation::FlipFlop::receive(Pulse signal, Module* sender)
{
	if (signal == High)
	{
		return;
	}
	if (!powered)
	{
		powered = true;
		sendSignal(High);
		return;
	}
	if (powered)
	{
		powered = false;
		sendSignal(Low);
		return;
	}
}

PulsePropogation::Conjunction::Conjunction(std::string name, std::vector<std::string> destinationModuleStrings)
	:Module(name, destinationModuleStrings)
{
}

void PulsePropogation::Conjunction::connect(Module* source)
{
	rememberedSignals.emplace(source, Low);
}

std::vector<PulsePropogation::Module*> PulsePropogation::Conjunction::getIncomingModuleConnections() const
{
	std::vector<Module*> result;
	for (std::pair<Module*, Pulse> signalPair : rememberedSignals)
	{
		result.emplace_back(signalPair.first);
	}
	return result;
}

void PulsePropogation::Conjunction::receive(Pulse signal, Module* sender)
{
	if (rememberedSignals.contains(sender))
	{
		rememberedSignals[sender] = signal;
	}

 	for (std::pair<Module*, Pulse> signalPair : rememberedSignals)
	{
		if (signalPair.second == Low)
		{
			sendSignal(High);
			return;
		}
	}
	sendSignal(Low);
	return;
}

PulsePropogation::Broadcaster::Broadcaster(std::string name, std::vector<std::string> destinationModuleStrings)
	:Module(name, destinationModuleStrings)
{
}


void PulsePropogation::Broadcaster::receive(Pulse signal, Module* sender)
{
	sendSignal(signal);
}

PulsePropogation::Signal::Signal(Module* source, Pulse pulse, Module* receiver)
	:source(source), pulse(pulse), receiver(receiver)
{
}

PulsePropogation::Button::Button(std::string name, std::vector<std::string> destinationModuleStrings)
	:Module(name, destinationModuleStrings)
{
}

void PulsePropogation::Button::receive(Pulse signal, Module* sender)
{
	sendSignal(signal);
}
