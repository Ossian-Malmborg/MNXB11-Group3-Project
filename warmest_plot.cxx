#include <fstream>
#include <sstream>
#include <string>
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include <iostream>

using namespace std;

// --- Gaussian function ---
double Gaussian(double* x, double* par) {
    return par[0] * exp(-0.5 * pow((x[0] - par[1]) / par[2], 2));
}

void plot_results() {

    // --- Clean up previous objects ---
    if (gROOT->FindObject("c")) delete gROOT->FindObject("c");
    if (gROOT->FindObject("warm_hist")) delete gROOT->FindObject("warm_hist");
    if (gROOT->FindObject("cold_hist")) delete gROOT->FindObject("cold_hist");
    if (gROOT->FindObject("cold_hist_left")) delete gROOT->FindObject("cold_hist_left");
    if (gROOT->FindObject("cold_hist_right")) delete gROOT->FindObject("cold_hist_right");

    // --- Canvas and style ---
    TCanvas *c = new TCanvas("c", "Warmest & Coldest Days", 800, 600);
    gStyle->SetOptStat(0);
    gStyle->SetTitleFontSize(0.045);

    // --- Histograms ---
    TH1F *warm_hist = new TH1F("warm_hist", "Warmest and Coldest Days;Day of Year;Entries", 366, 0.5, 366.5);
    TH1F *cold_hist = new TH1F("cold_hist", "Warmest and Coldest Days;Day of Year;Entries", 366, 0.5, 366.5);
    TH1F *cold_hist_left = new TH1F("cold_hist_left", "Left", 366, -60.5, 425.5);
    TH1F *cold_hist_right = new TH1F("cold_hist_right", "Right", 366, -60.5, 425.5);

    // --- Read CSV file ---
    ifstream infile("Uppsala_warmest_results.csv");
    if (!infile.is_open()) {
        cout << "Error: cannot open CSV file!" << endl;
        return;
    }

    string line;
    getline(infile, line); // skip header
    while (getline(infile, line)) {
        stringstream ss(line);
        string year_str, warm_str, cold_str;
        getline(ss, year_str, ',');
        getline(ss, warm_str, ',');
        getline(ss, cold_str, ',');

        int warm_day = stoi(warm_str);
        int cold_day = stoi(cold_str);

        warm_hist->Fill(warm_day);
        cold_hist->Fill(cold_day);

        // duplicate cold entries for wrapping
        if (cold_day < 60) cold_hist_right->Fill(cold_day + 366);
        if (cold_day > 306) cold_hist_right->Fill(cold_day);
        if (cold_day < 60) {
            cold_hist_left->Fill(cold_day - 366);  
        }
        if (cold_day > 306) {
            cold_hist_left->Fill(cold_day);        
        }

    }
    infile.close();

    // --- Style settings ---
    warm_hist->SetLineColor(kRed + 1);
    warm_hist->SetFillColorAlpha(kRed, 0.5);
    warm_hist->SetLineWidth(1);

    cold_hist->SetLineColor(kBlue + 1);
    cold_hist->SetFillColorAlpha(kBlue, 0.5);
    cold_hist->SetLineWidth(1);


    // --- Draw base histograms ---
    cold_hist->Draw("HIST");
    warm_hist->Draw("HIST SAME");

    // --- Adjust visible range ---
    warm_hist->GetXaxis()->SetRangeUser(-50, 420);

    // --- Legend ---
    TLegend *legend = new TLegend(0.6, 0.75, 0.9, 0.9);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->AddEntry(warm_hist, "Warmest day", "f");
    legend->AddEntry(cold_hist, "Coldest day", "f");
    legend->Draw();

    // --- Fit Gaussian to warm days ---
    TF1 *func1 = new TF1("Gaussian_warm", Gaussian, 1, 366, 3);
    func1->SetParameters(5, 200, 50);
    warm_hist->Fit(func1, "Q0R");
    func1->SetLineColor(kBlack);
    func1->SetLineWidth(2);
    func1->Draw("SAME");


    // --- Fit Gaussian to cold days (left) ---
    TF1 *func2 = new TF1("Gaussian_left", Gaussian, -100, 100, 3);
    func2->SetParameters(3, 0, 30);   // amplitude, mean, sigma
    func2->SetParLimits(0, 2, 2.5);  
    cold_hist_left->Fit(func2, "Q0R");
    func2->SetLineColor(kBlack);
    func2->SetLineWidth(2);
    func2->Draw("SAME");

    double A  = func2->GetParameter(0);
    double mu = func2->GetParameter(1);
    double s  = func2->GetParameter(2);



    // --- Fit Gaussian to cold days (right) ---
    TF1 *func3 = new TF1("Gaussian_right", Gaussian, 250, 480, 3);
    func3->FixParameter(0, A);              // same amplitude
    func3->FixParameter(2, s);              // same sigma
    func3->SetParameter(1, mu + 366);       // shifted center
    cold_hist_right->Fit(func3, "Q0R");
    func3->SetLineColor(kBlack);
    func3->SetLineWidth(2);
    func3->Draw("SAME");

    // --- Final update ---
    c->Update();
}
