#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
int main() {
    std::ifstream inputFile("datasets/smhi-opendata_1_52230_20231007_155448_Falsterbo.csv");
    std::ofstream outputFile("Falstebro.csv");

    if (!inputFile.is_open()) {
    std::cerr << "Can't open input file!\n";
    return 1;
    }


    std::string line;


    while (std::getline(inputFile, line)) {

        std::stringstream ss(line);
        std::string date, time, temperature;
        

        std::getline(ss, date, ';');
        std::getline(ss, time, ';');
        std::getline(ss, temperature, ';');

        if (date >= "1983-01-01" && date <= "2023-12-31" && (time == "06:00:00"|| time =="18:00:00")) {
            outputFile << date << ";" << time << ";" << temperature << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Filtered data has been saved to 'Falstebro.csv'\n";
    return 0;
}