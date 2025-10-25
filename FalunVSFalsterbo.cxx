#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

//Function to compute average yearly temperatures from a CSV file
map<int, double> computeYearlyAverages(const string &filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Can't open file: " << filename << endl;
        return {};
    }

//Maps with the year as the key
    map<int, double> sumT; //The sum of all temperatures during a year
    map<int, int> countT; //The amount of temperatures counted (limited to a year's worth)
    string line;

//Turning the csv data file into variables like date, time, and temperature
    while (getline(inputFile, line)) {
        string date, time, temperature;
        stringstream ss(line);
        getline(ss, date, ';');
        getline(ss, time, ';');
        getline(ss, temperature, ';');

        //Only the correct time will be read
        if (time != "18:00:00")
            continue;

        int year = stoi(date.substr(0, 4));
        double temp = stod(temperature);

        sumT[year] += temp;
        countT[year]++;
    }

    inputFile.close();

    //Calculating the average temperature for each year and saving it witha  map
    map<int, double> averages;
    for (auto &entry : sumT) {
        int year = entry.first;
        averages[year] = sumT[year] / countT[year];
    }

    return averages;
}

int main() {
    //Putting both files through the code that takes the average
    map<int, double> falun_avg = computeYearlyAverages("Falun.csv");
    map<int, double> falsterbo_avg = computeYearlyAverages("Falsterbo.csv");

    //Combining all years found in either dataset
    map<int, bool> all_years;
    for (auto &e : falun_avg) all_years[e.first] = true;
    for (auto &e : falsterbo_avg) all_years[e.first] = true;

    //Finding the latest year in the dataset
    int maxYear = 0;
    for (auto &y : all_years)
        if (y.first > maxYear)
            maxYear = y.first;

    int cutoffYear = maxYear - 29; //Choosing how many years that are kept

    //Checking if the file can be created, error if it can't
    ofstream outfile("FalunVSFalsterbo.csv");
    if (!outfile.is_open()) {
        cerr << "Can't create file FalunVSFalsterbo.csv" << endl;
        return 1;
    }

    //Formatting for the output file
    outfile << "year,Falun_avg,Falsterbo_avg,Difference\n";
    outfile << fixed << setprecision(2);

    for (auto &y : all_years) {
        int year = y.first;
        if (year < cutoffYear)
            continue;

        bool falunHas = falun_avg.count(year);
        bool falsterboHas = falsterbo_avg.count(year);

        if (falunHas && falsterboHas) {
            double diff = abs(falun_avg[year] - falsterbo_avg[year]);
            outfile << year << "," << falun_avg[year] << "," << falsterbo_avg[year] << "," << diff << "\n";
        }
    }

    outfile.close();
    cout << "File 'FalunVSFalsterbo.csv' saved (latest 30 years)\n";
    return 0;
}