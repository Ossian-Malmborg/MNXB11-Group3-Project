#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>

using namespace std;

int main() {
    std::ifstream inputFile("Falun.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Can't open input file!\n";
        return 1;
    }

    // Для хранения самого тёплого и холодного дня по каждому году
    map<int, int> warmest_day;
    map<int, double> warmest_temp;
    map<int, int> coldest_day;
    map<int, double> coldest_temp;

    string line;

    while (getline(inputFile, line)) {
        std::string date, time, temperature;
        stringstream ss(line);
        getline(ss, date, ';');
        getline(ss, time, ';');
        getline(ss, temperature, ';');

        if (time != "18:00:00")
            continue;
        
        int year = stoi(date.substr(0, 4));

        int y, m, d;
        char dash;
        stringstream date_ss(date);
        date_ss >> y >> dash >> m >> dash >> d;

        tm timeinfo = {};
        timeinfo.tm_year = y - 1900;
        timeinfo.tm_mon = m - 1;
        timeinfo.tm_mday = d;
        mktime(&timeinfo);
        int day_of_year = timeinfo.tm_yday + 1;

        double temp = stod(temperature);

        // Проверяем, является ли эта температура новой максимальной или минимальной
        if (warmest_temp.find(year) == warmest_temp.end() || temp > warmest_temp[year]) {
            warmest_temp[year] = temp;
            warmest_day[year] = day_of_year;
        }
        if (coldest_temp.find(year) == coldest_temp.end() || temp < coldest_temp[year]) {
            coldest_temp[year] = temp;
            coldest_day[year] = day_of_year;
        }

    }

    inputFile.close();

    // Сохраняем результат
    ofstream outfile("results.csv");
    if (!outfile.is_open()) {
        cout << "Can't create file results.csv" << endl;
        return 1;
    }

    outfile << "year,warmest_day,coldest_day\n";

    // Проходим по всем годам и записываем результат
    for (auto &w : warmest_day) {
        int year = w.first;
        outfile << year << "," << warmest_day[year] << "," << coldest_day[year] << "\n";
    }

    outfile.close();
    cout << "File results.csv saved!" << endl;

    return 0;

}