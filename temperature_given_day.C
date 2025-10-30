#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void tempgivenday_hist() {
    std:: ifstream file("temperature_given_day.csv");
    if (!file.is_open()){
        std::cerr << "Cannot open the file\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    TH1F* hist = new TH1F("hist", "Mean temperature of a day over the years; Mean Temperature [C]; Counts", 20, -10, 10);

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string year_str, temp_str;
        getline(ss, year_str, ';');
        getline(ss, temp_str, ';');

        double temp = std::stod(temp_str);
        hist->Fill(temp);
    }

    file.close();

    hist->Draw();
}