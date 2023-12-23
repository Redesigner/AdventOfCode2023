#include "Aplenty.h"

#include <fstream>
#include <map>
#include <queue>

#include "../Common/Common.h"

using namespace std;

int64_t Aplenty::get()
{
    bool useExample = false;

    fstream file = useExample ? fstream("Day19/test.txt", ios::in) : fstream("Day19/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    map<string, Workflow> workflows;
    vector<Part> parts;

    string line;
    bool writingParts = false;
    while (getline(file, line))
    {
        if (line.empty())
        {
            writingParts = true;
            continue;
        }

        if (writingParts)
        {
            parts.emplace_back(line.substr(1, line.size() - 2));
        }
        else
        {
            size_t separatorPosition = line.find('{');
            string workflowID = line.substr(0, separatorPosition);
            string workflowString = line.substr(separatorPosition + 1, line.size() - separatorPosition - 2);
            Workflow workflow = Workflow(workflowString);
            workflows.insert(make_pair(workflowID, workflow));
        }
    }

    int64_t sum = 0;
    for (Part& part : parts)
    {
        string nextWorkflow = "in";
        while (!nextWorkflow.empty())
        {
            nextWorkflow = workflows[nextWorkflow].processPart(part);
        }
        if (part.accepted)
        {
            sum += part.x + part.m + part.a + part.s;
        }
    }

    return sum;
}

int64_t Aplenty::get2()
{
    bool useExample = false;

    fstream file = useExample ? fstream("Day19/test.txt", ios::in) : fstream("Day19/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    map<string, Workflow> workflows;
    vector<Part> parts;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            break;
        }
        size_t separatorPosition = line.find('{');
        string workflowID = line.substr(0, separatorPosition);
        string workflowString = line.substr(separatorPosition + 1, line.size() - separatorPosition - 2);
        Workflow workflow = Workflow(workflowString);
        workflows.insert(make_pair(workflowID, workflow));
    }

    queue<PartRange> partRanges;
    vector<PartRange> completedRanges;
    partRanges.emplace(1, 4000, "in");
    while (!partRanges.empty())
    {
        PartRange partRange = partRanges.front();
        partRanges.pop();

        Workflow& workflow = workflows[partRange.destination];
        partRange.destination.clear();
        vector<PartRange> newRanges;
        for (Rule& rule : workflow.rules)
        {
            newRanges = partRange.splitByRule(rule);
            if (!newRanges[0].destination.empty())
            {
                partRanges.push(newRanges[0]);
            }
            else
            {
                completedRanges.push_back(newRanges[0]);
            }
            partRange = newRanges[1];

        }
        if (workflow.finalDestination == Jump)
        {
            partRange.destination = workflow.jumpDestination;
            partRanges.push(partRange);
        }
        else
        {
            if (workflow.finalDestination == Accepted)
            {
                partRange.accpeted = true;
            }
            completedRanges.push_back(partRange);
        }
    }

    int64_t sum = 0;
    for (PartRange& partRange : completedRanges)
    {
        if (partRange.accpeted)
        {
            sum += partRange.value();
        }
    }
    return sum;
}

Aplenty::Category Aplenty::getCategory(char c)
{
    switch (c)
    {
    case 'x':
        return X;
    case 'm':
        return M;
    case 'a':
        return A;
    case 's':
        return S;
    default:
        return Invalid;
    }
}

Aplenty::Rule::Rule(std::string_view token)
{
    // We will tokenize our rules here!
    // Expect the rule to be formatted as such: category(< or >):(destination string or R or A)
    category = getCategory(token[0]);
    greaterThan = token[1] == '>';
    size_t separatorPosition = token.find(':');
    string_view intString = token.substr(2,  separatorPosition - 2);
    value = stoi(string(intString));
    if (token[separatorPosition + 1] == 'A')
    {
        destination = Accepted;
    }
    else if (token[separatorPosition + 1] == 'R')
    {
        destination = Rejected;
    }
    else
    {
        destination = Jump;
        workflow = token.substr(separatorPosition + 1, token.size() - separatorPosition - 1);
    }
}

string Aplenty::Rule::process(Part& part) const
{
    // We have a few possible outcomes here
    // 1: the part passes our test, and we need to put it in a new workflow
    // 2: the part passes our test, but it's been accepted or rejected
    // 3: the part fail our test, so we don't do anything
    int valueToCompare = 0;
    switch (category)
    {
    case X:
        valueToCompare = part.x;
        break;
    case M:
        valueToCompare = part.m;
        break;
    case A:
        valueToCompare = part.a;
        break;
    case S:
        valueToCompare = part.s;
        break;
    }
    if ((greaterThan && valueToCompare > value) ||
        (!greaterThan && valueToCompare < value))
    {
        if (destination == Jump)
        {
            return workflow;
        }
        if (destination == Accepted)
        {
            part.accepted = true;
        }
        return "None";
    }
    return string();
}

Aplenty::Workflow::Workflow(string token)
{
    vector<string> subtokens = Common::splitString(token, ',');
    for (int i = 0; i < subtokens.size() - 1; ++i)
    {
        rules.emplace_back(subtokens[i]);
    }
    string& destinationToken = subtokens[subtokens.size() - 1];
    if (destinationToken[0] == 'A')
    {
        finalDestination = Accepted;
    }
    else if (destinationToken[0] == 'R')
    {
        finalDestination = Rejected;
    }
    else
    {
        finalDestination = Jump;
        jumpDestination = destinationToken;
    }
}

Aplenty::Workflow::Workflow()
{
    finalDestination = Rejected;
}

string Aplenty::Workflow::processPart(Part& part)
{
    for (Rule& rule : rules)
    {
        string result = rule.process(part);
        if (result == "None")
        {
            // we've hit an acception or rejection state
            // return
            return string();
        }
        if (!result.empty())
        {
            return result;
        }
    }
    if (finalDestination == Accepted)
    {
        part.accepted = true;
    }
    return jumpDestination;
}

Aplenty::Part::Part(std::string token)
{
    vector<string> properties = Common::splitString(token, ',');
    x = stoi(properties[0].substr(2, properties[0].size() - 2));
    m = stoi(properties[1].substr(2, properties[1].size() - 2));
    a = stoi(properties[2].substr(2, properties[2].size() - 2));
    s = stoi(properties[3].substr(2, properties[3].size() - 2));
}

Aplenty::PartRange::PartRange(int start, int end, string destination)
    :destination(destination)
{
    x = Range(start, end);
    m = Range(start, end);
    a = Range(start, end);
    s = Range(start, end);
}

std::vector<Aplenty::PartRange> Aplenty::PartRange::splitByRule(Rule& rule) const
{
    const Range* rangeToSplit = &x;
    switch (rule.category)
    {
    case X:
        rangeToSplit = &x;
        break;
    case M:
        rangeToSplit = &m;
        break;
    case A:
        rangeToSplit = &a;
        break;
    case S:
        rangeToSplit = &s;
        break;
    }
    int splitValue = rule.greaterThan ? rule.value : rule.value - 1;
    vector<Range> newRanges = rangeToSplit->split(splitValue);
    if (newRanges.size() == 1)
    {
        return { *this };
    }
    PartRange lowerRange = PartRange(*this);
    PartRange upperRange = lowerRange;
    switch (rule.category)
    {
    case X:
        lowerRange.x = newRanges[0];
        upperRange.x = newRanges[1];
        break;
    case M:
        lowerRange.m = newRanges[0];
        upperRange.m = newRanges[1];
        break;
    case A:
        lowerRange.a = newRanges[0];
        upperRange.a = newRanges[1];
        break;
    case S:
        lowerRange.s = newRanges[0];
        upperRange.s = newRanges[1];
        break;
    }
    vector<PartRange> result;
    PartRange& validRange = rule.greaterThan ? upperRange : lowerRange;
    PartRange& failedRange = !rule.greaterThan ? upperRange : lowerRange;
    if (rule.destination == Accepted)
    {
        validRange.accpeted = true;
    }
    if (rule.destination == Jump)
    {
        validRange.destination = rule.workflow;
    }
    result.push_back(validRange);
    result.push_back(failedRange);
    return result;
}

int64_t Aplenty::PartRange::value() const
{
    return static_cast<int64_t>(x.width()) * static_cast<int64_t>(m.width()) * static_cast<int64_t>(a.width()) * static_cast<int64_t>(s.width());
}
