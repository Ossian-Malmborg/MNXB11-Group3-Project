#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include<map>

std::map<std::string, double> temperature_given_day(const char* filename, const std::string& givenday) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return {};
    }

    std::string line;
    std::getline(file, line); // skip header

    std::map<std::string, std::pair<std::optional<double>, std::optional<double>>> tempyear;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, time, temp_str;

        std::getline(ss, date, ';');
        std::getline(ss, time, ';');
        std::getline(ss, temp_str, ';');

        if (date.size() < 10)
            continue;

        std::string monthandday = date.substr(5, 5); //subtracts characters from date so as to keep only the month and day
        
        if (monthandday != givenday)
            continue;

        std::string year = date.substr(0, 4); //subtractcs characters to save the year
        
        try {
            double temperature = std::stod(temp_str);
            auto& entry = tempyear[year];

            if (time == "06:00:00")
                entry.first = temperature;
            else if (time == "18:00:00")
                entry.second = temperature;
        } catch (...) {
            continue;
        }
    }

    file.close();

    std::map<std::string, double> results; //computes mean temperatures for each year for a given day and stores in results map
    for(const auto& [year, temp]: tempyear){
        if (temp.first && temp.second){
            double meantemp = (*temp.first + *temp.second) / 2;
            results[year] = meantemp;
        }
        else{
            std::cerr << "Incomplete data for given day.\n";
        }
    }

    return results;
}

int main() {
    const char* filename = "Falsterbo.csv";
    std::string givenday;
    std::cout << "Enter date (MM-DD): ";
    std::cin >> givenday;

    auto yearlymeans = temperature_given_day(filename, givenday);

    std::ofstream resultfile("temperature_given_day.csv");
    if (!resultfile.is_open()){
        std::cerr << "Cannot create temperature_given_day.csv file. \n";
        return 1;
    }

    resultfile << "Year;Mean_Daily_Temperature\n";

    for(const auto& [year, mean]: yearlymeans){
        resultfile << year << ";" << mean << std::endl;
    }

    resultfile.close();

    std::cout << "Saved mean temperatures for the given day&month over a number of years in temperature_given_day.csv\n";
    
    return 0;
}

