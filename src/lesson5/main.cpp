#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Bar
{
public:
    int64_t source;
    int64_t destination;
    int64_t length;
};

class SeedPair
{
public:
    int64_t source;
    int64_t length;
};


// trim from start (in place)
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s)
{
    rtrim(s);
    ltrim(s);
}

std::vector<std::string> resplit(const std::string& s, const std::regex& sep_regex = std::regex{"\\s+"})
{
    std::sregex_token_iterator iter(s.begin(), s.end(), sep_regex, -1);
    std::sregex_token_iterator end;
    return {iter, end};
}

void split(const std::string& s, char c, std::vector<std::string>& v)
{
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

void parseLineToBar(std::vector<Bar>& bars, const std::string& line, const std::regex& parseLine)
{
    std::cout << line << std::endl;

    std::smatch matches;
    std::regex_search(line, matches, parseLine);
    Bar bar{};
    bar.destination = std::stol(matches[1]);
    bar.source = std::stol(matches[2]);
    bar.length = (std::stol(matches[3]) - 1);
    bars.push_back(bar);
}

int64_t foo(const std::vector<Bar>& bars, int64_t seedint)
{
    for (auto bar : bars)
    {
        if (seedint >= bar.source && seedint <= bar.source + bar.length)
        {
            return bar.destination + (seedint - bar.source);
        }
    }

    return seedint;
}


int64_t bar(const std::vector<Bar>& bars, int64_t seedint)
{
    for (auto bar : bars)
    {
        if (seedint >= bar.destination && seedint <= bar.destination + bar.length)
        {
            return bar.source + (seedint - bar.destination);
        }
    }

    return seedint;
}

std::vector<std::string> getSeedsLessonA(std::vector<std::string> splittedFirstline)
{
    return resplit(splittedFirstline[1], std::regex("\\s+"));
}


std::vector<SeedPair> getSeedsLessonB(std::vector<std::string> splittedFirstline)
{
    std::vector<std::string> seedPairs = getSeedsLessonA(splittedFirstline);
    std::vector<SeedPair> seeds;
    for (int i = 0; i < seedPairs.size(); i += 2)
    {
        SeedPair seedPair{};
        seedPair.source = std::stol(seedPairs[i]);
        seedPair.length = std::stol(seedPairs[i + 1]);
        seeds.push_back(seedPair);
    }

    return seeds;
}

int main()
{
    // std::cout << "Hello, World!" << std::endl;
    int32_t mapCount = 0;
    std::regex isHeader("[a-zA-Z- :]+");
    std::regex parseLine(R"(^(\d*)\s(\d*)\s(\d*)$)");
    std::ifstream file("/home/thomas/projects/github.com/advent-of-code-2023/src/lesson5/lesson5-data.txt");
    std::string currentMap;
    std::string line;
    bool firstLine = false;
    std::vector<std::string> splittedFirstline;
    // std::vector<std::string> seeds;
    std::vector<SeedPair> seeds;
    std::vector<Bar> seedToSoilBar;
    std::vector<Bar> soilToFertilizerBar;
    std::vector<Bar> fertilizerToWaterBar;
    std::vector<Bar> waterToLightBar;
    std::vector<Bar> lightToTemperatureBar;
    std::vector<Bar> temperatureToHumidityBar;
    std::vector<Bar> humidityToLocationBar;
    while (std::getline(file, line))
    {
        if (firstLine == false)
        {
            split(line, ':', splittedFirstline);
            trim(splittedFirstline[1]);
            // seeds = getSeedsLessonA(splittedFirstline);
            seeds = getSeedsLessonB(splittedFirstline);
            firstLine = true;
            continue;
        }
        if (line.empty())
        {
            continue;
        }
        // std::cout << seeds[0] << std::endl;
        for (const auto& seed : seeds)
        {
            // std::cout << seed << std::endl;
        }
        if (std::regex_match(line, isHeader))
        {
            std::cout << "increase mapcount" << std::endl;
            mapCount++;
            continue;
        }
        std::cout << "hier" << std::endl;

        switch (mapCount)
        {
        case 1:
            std::cout << "hier2" << std::endl;
            parseLineToBar(seedToSoilBar, line, parseLine);
            break;
        case 2:
            std::cout << "hier2" << std::endl;
            parseLineToBar(soilToFertilizerBar, line, parseLine);
            break;
        case 3:
            parseLineToBar(fertilizerToWaterBar, line, parseLine);
            break;
        case 4:
            parseLineToBar(waterToLightBar, line, parseLine);
            break;
        case 5:
            parseLineToBar(lightToTemperatureBar, line, parseLine);
            break;
        case 6:
            parseLineToBar(temperatureToHumidityBar, line, parseLine);
            break;
        case 7:
            parseLineToBar(humidityToLocationBar, line, parseLine);
            break;
        }
    }
    std::cout << "hier55" << std::endl;
    int64_t minLocation = -1;
    // for (const auto& seed : seeds)
    // {
    //     int64_t seedint = std::stol(seed);
    //     seedint = foo(seedToSoilBar, seedint);
    //     seedint = foo(soilToFertilizerBar, seedint);
    //     seedint = foo(fertilizerToWaterBar, seedint);
    //     seedint = foo(waterToLightBar, seedint);
    //     seedint = foo(lightToTemperatureBar, seedint);
    //     seedint = foo(temperatureToHumidityBar, seedint);
    //     seedint = foo(humidityToLocationBar, seedint);
    //     std::cout << seed << ":" << seedint << "\n";
    //     if (minLocation == -1 || seedint < minLocation)
    //     {
    //         minLocation = seedint;
    //     }
    // }
    // std::cout << "seedint: " << seed.source << "\n";
    int64_t count = 1;
    while (true)
    {
        if (count % 100000 == 0)
        {
            std::cout << "count: " << count << "\n";
        }
        int64_t seedint = count;
        seedint = bar(humidityToLocationBar, seedint);
        seedint = bar(temperatureToHumidityBar, seedint);
        seedint = bar(lightToTemperatureBar, seedint);
        seedint = bar(waterToLightBar, seedint);
        seedint = bar(fertilizerToWaterBar, seedint);
        seedint = bar(soilToFertilizerBar, seedint);
        seedint = bar(seedToSoilBar, seedint);
        for (auto seed : seeds)
        {
            if (seedint >= seed.source && seedint <= seed.source + seed.length)
            {
                std::cout << "minlocation2: " << count << "\n";
                return 0;
            }
        }
        // std::cout << "seedint: " << seedint << "\n";
        if (minLocation == -1 || seedint < minLocation)
        {
            minLocation = seedint;
        }
        count++;
    }
    // for (const auto& x : humidityToLocation)
    // {
    //     std::cout << x.first << ": " << x.second << "\n";
    // }
    std::cout << "minlocation: " << minLocation << "\n";

    return 0;
}
