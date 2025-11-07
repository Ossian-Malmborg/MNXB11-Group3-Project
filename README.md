# MNXB11-Group3-Project

**FalunVSFalsterbo** use:
```bash
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/
g++ cleaning_data_Falun.cxx -o Falun
./Falun
g++ cleaning_data_Falsterbo.cxx -o Falsterbo
./Falsterbo
g++ FalunVSFalsterbo.cxx -o FalunVSFalsterbo
./FalunVSFalsterbo 
#open root
.L FalunVSFalsterboPlot.C
PlotTemperatureDifference();
```

Warmest_Coldest use:
```bash
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/
g++ cleaning_data_Uppsala.cxx -o name
./name
g++ warmest_coldest.cxx -o name
./name
# open root
.L warmest_plot.cxx
plot_results();

```
**Temperature_given_day** use:
The source code file `temperature_given_day.cxx` contains the C++ code which, from the cleaned dataset `Falsterbo.csv`, extracts two temperature readings for a given day, one at 6 AM and one at 6 PM, calculates the temperature average of that day based on those readings, and saves it. This process is performed for a given day in a given month throughout all the years in the datafile, and all the means are subsequently recorded in a new datafile called `temperature_given_day.csv`, so that an analysis of the data can be performed. The macro `temperature_given_day.C` is one instance of such an analysis, where a histogram is created in order to visualise the temperature range for a given day throughout the years. In order to run the program succesfully, the following steps have to be performed:
```bash
# first, make sure that 'Falsterbo.csv' exists by compiling in the terminal:
g++ cleaning_data_Falsterbo.cxx -o Falsterbo
./Falsterbo

# now, we need to compile the main .cxx file:
g++ temperature_given_day.cxx -o temperature_given_day
./temperature_given_day

# upon executing the line above, the terminal will request the user to input a specific day and month, following a MM-DD format, and finally create the desired dataset.

# having obtained the necessary files, the analysis is performed in root:
root -l
.L temperature_given_day.C
tempgivenday_hist();

# a histogram should now pop-up.

```

Rain_analysis implementation : 

```bash
# Clone the repository
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/
# Create Graphical Plots
chmod +x rain_analysis/run_all.sh
./rain_analysis/run_all.sh
```


**Rain_analysis** implementation : 

The Rain_analysis project processes the raw SMHI file **SMHI_pthbv_p_t_1961_2025_daily_4326.csv** that consists of precipitation and temperature data.  
It performs three main tasks:
1. **Data Cleaning** — cleaning of the raw dataset into a clean csv file that can be used.  
2. **Analysis** — computes monthly rainfall and temperature summaries for selected stations and years.  
3. **Plotting** — visualises rainfall, temperature, and rainy-day frequency variation throughout the years(1961 and 2024) specifically comparing monthly precipitation(mm) with average maximum and minimum temperatures(°C) and the number of rainy days per month of the cities Uppsala and Lund.

## Instant Implementation

```bash
# Clone the repository
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/

# Run everything automatically to create graphical plots
chmod +x rain_analysis/run_all.sh
./rain_analysis/run_all.sh

#Access the plots
cd rain_analysis/figures
```

## Step by Step Implementation

```bash
# Clone the repository and move into the rain_analysis folder.
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/rain_analysis/

# Compile and run the data cleaning program.
cd data_clean/
g++ Rain_data_clean.cxx -o Rain_data_clean
./Rain_data_clean

# Go to rain_analysis/data_clean/Rain_temperature_cleaned.csv if you want to access the cleaned dataset.

# Compile and run the analysis.
cd ..
cd analysis/
g++ analysis.cxx -o analysis
chmod +x run_analysis_script.sh
./run_analysis_script.sh

# Go to rain_analysis/results if you want to access the monthly rainfall and temperature summaries for selected stations(Lund and Uppsala) and years(1961 and 2024).

# Run the plotting script.
cd ..
cd plots/
chmod +x run_root_plots.sh
./run_root_plots.sh

#Access the plots.
cd ..
cd figures
```