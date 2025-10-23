void plot_results() {
    // --- Создаём две гистограммы ---
    // warm_hist — для самых тёплых дней
    // cold_hist — для самых холодных дней
    TH1F *warm_hist = new TH1F("warm_hist", "Warmest and Coldest Days;Day of Year;Entries", 366, 0.5, 366.5);
    TH1F *cold_hist = new TH1F("cold_hist", "Coldest Days", 366, 0.5, 366.5);

    // --- Читаем данные из results.csv ---
    ifstream infile("results.csv");
    string line;
    getline(infile, line); // пропускаем заголовок

    while (getline(infile, line)) {
        stringstream ss(line);
        string year_str, warm_str, cold_str;
        getline(ss, year_str, ',');
        getline(ss, warm_str, ',');
        getline(ss, cold_str, ',');

        int warm_day = stoi(warm_str);
        int cold_day = stoi(cold_str);

        // Заполняем гистограммы
        warm_hist->Fill(warm_day);
        cold_hist->Fill(cold_day);
    }
    infile.close();

    // --- Настраиваем внешний вид ---
    warm_hist->SetLineColor(kRed);
    cold_hist->SetLineColor(kBlue);
    warm_hist->SetFillColorAlpha(kRed, 0.35);
    cold_hist->SetFillColorAlpha(kBlue, 0.35);

    // --- Создаём Гауссовы функции для подгонки ---
    TF1 *gaussWarm = new TF1("gaussWarm", "gaus", 1, 366);
    TF1 *gaussCold = new TF1("gaussCold", "gaus", 1, 366);

    // --- Фитируем гистограммы ---
    warm_hist->Fit(gaussWarm, "Q0R"); // Q — тихо, 0 — без автоплота, R — в диапазоне функции
    cold_hist->Fit(gaussCold, "Q0R");

    // --- Рисуем гистограммы ---
    warm_hist->Draw();
    cold_hist->Draw("SAME");

    // --- Добавляем легенду ---
    TLegend *legend = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->AddEntry(warm_hist, "Warmest day", "F");
    legend->AddEntry(cold_hist, "Coldest day", "F");
    legend->Draw();

    // --- Выводим в консоль результаты фитирования ---
    cout << "Mean warmest day: " << gaussWarm->GetParameter(1)
         << " ± " << gaussWarm->GetParError(1) << endl;

    cout << "Mean coldest day: " << gaussCold->GetParameter(1)
         << " ± " << gaussCold->GetParError(1) << endl;
}
