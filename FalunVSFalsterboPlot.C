#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Setting up the plotting function
void PlotTemperatureDifference() {
    std::ifstream file("FalunVSFalsterbo.csv");
    if (!file.is_open()) {
        std::cerr << "Error: cannot open FalunVSFalsterbo.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    std::vector<double> years, falun, falsterbo, diff;

    //Reading the CSV data
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string yearStr, fStr, fsStr, dStr;

        std::getline(ss, yearStr, ',');
        std::getline(ss, fStr, ',');
        std::getline(ss, fsStr, ',');
        std::getline(ss, dStr, ',');

        if (yearStr.empty() || fStr.empty() || fsStr.empty() || dStr.empty()) continue;

        years.push_back(std::stod(yearStr));
        falun.push_back(std::stod(fStr));
        falsterbo.push_back(std::stod(fsStr));
        diff.push_back(std::stod(dStr));
    }

    file.close();

    //Creating TGraph objects
    int n = years.size();
    TGraph *gFalun = new TGraph(n, &years[0], &falun[0]);
    TGraph *gFalsterbo = new TGraph(n, &years[0], &falsterbo[0]);
    TGraph *gDiff = new TGraph(n, &years[0], &diff[0]);

    //Some changes to how the plot looks
    gFalun->SetLineColor(kBlue);
    gFalun->SetLineWidth(2);
    gFalun->SetTitle("Average Yearly Temperatures;Year;Temperature (°C)");

    gFalsterbo->SetLineColor(kRed);
    gFalsterbo->SetLineWidth(2);

    gDiff->SetLineColor(kGreen + 2);
    gDiff->SetLineWidth(2);
    gDiff->SetLineStyle(2);

    //Drawing the plot
    TCanvas *c = new TCanvas("c", "Temperature Comparison", 900, 600);
    gFalun->SetMinimum(0);
    gFalun->SetMaximum(15);
    gFalun->Draw("AL"); //Note to self, this can't really be changed since something needs to be the standard
    gFalsterbo->Draw("L SAME");
    gDiff->Draw("L SAME");

    //Actually creating the plot
    TLegend *leg = new TLegend(0.15, 0.7, 0.45, 0.88);
    leg->AddEntry(gFalun, "Falun average", "l");
    leg->AddEntry(gFalsterbo, "Falsterbo average", "l");
    leg->AddEntry(gDiff, "Difference (Falun - Falsterbo)", "l");
    leg->Draw();

    c->SetGrid();
    c->SaveAs("FalunVSFalsterbo.png");
}
