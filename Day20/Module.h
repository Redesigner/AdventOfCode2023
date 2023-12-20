#pragma once

#include <vector>
#include <map>
#include <string>
#include <queue>

namespace PulsePropogation
{
	enum Pulse
	{
		Low,
		High
	};

	struct Signal
	{
		Signal(class Module* source, Pulse pulse, class Module* receiver);
		class Module* source;
		Pulse pulse;
		class Module* receiver;
	};

	class Module
	{
	public:
		Module(std::string name, std::vector<std::string> destinationModuleStrings);
		Module();

		void initializeConnections(std::map<std::string, Module*>& moduleMap, std::queue<Signal>* outQueue);

		virtual void receive(Pulse signal, Module* sender);

		int getLowPulses() const;
		int getHighPulses() const;

		std::string name;

	protected:
		void sendSignal(Pulse signal);

		std::vector<std::string> destinationModuleStrings;
		std::vector<Module*> destinationModules;

		int lowPulsesSent = 0;
		int highPulsesSent = 0;
		int connectedModuleCount = 0;
		std::queue<Signal>* signalQueue = nullptr;
	};

	class Button : public Module
	{
	public:
		Button(std::string name, std::vector<std::string> destinationModuleStrings);

	private:
		void receive(Pulse signal, Module* sender) override;
	};


	class Broadcaster : public Module
	{
	public:
		Broadcaster(std::string name, std::vector<std::string> destinationModuleStrings);

	private:
		void receive(Pulse signal, Module* sender) override;
	};


	class FlipFlop : public Module
	{
	public:
		FlipFlop(std::string name, std::vector<std::string> destinationModuleStrings);

	private:
		void receive(Pulse signal, Module* sender) override;

		bool powered = false;
	};



	class Conjunction : public Module
	{
	public:
		Conjunction(std::string name, std::vector<std::string> destinationModuleStrings);
		
		void connect(Module* source);

		std::vector<Module*> getIncomingModuleConnections() const;

	private:
		void receive(Pulse signal, Module* sender) override;

		std::map<Module*, Pulse> rememberedSignals;
	};
}