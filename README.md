# MNXB11-Group3-Project

FalunVSFalsterbo use:
Clean the data by using cleaning_data_Falsterbo.cxx and cleaning_data_Falun.cxx. Launch these by writing "g++ cleaning_data_city.cxx -o name", replace city with the data to be cleaned and the name can be whatever. Then obtain the CSV file by writing and using "./name" in the terminal. Both Falun and Falsterbo are required for this code. Repeat the step used for cleaning_data but for FalunVSFalsterbo.cxx instead. Then get the CSV file for that in the same way "./name". Now go in to ROOT and write ".L FalunVSFalsterboPlot.C", then obtain the plot by writing  "PlotTemperatureDifference();".

Warmest_Coldest use:
Clean data using cleaning_data_Uppsala.cxx by writing g++ cleaning_data_Uppsala.cxx -o name and after that ./name in the terminal.
Create csv with coldes and warmest days of each year using warmest_caldest.cxx by writing g++ warmest_coldest.cxx -o name and after that ./name in the terminal.
Create plot in root by writing .L warmest_plot.cxx and then plot_results();

**Temperature_given_day** use:
The source code file `temperature_given_day.cxx` contains the C++ code which, from the cleaned dataset `Falsterbo.csv`, extracts two temperature readings for a given day, one at 6 AM and one at 6 PM, calculates the temperature average of that day based on those readings, and saves it. This process is performed for a given day in a given month throughout all the years in the datafile, and all the means are subsequently recorded in a new datafile called `temperature_given_day.csv`, so that an analysis of the data can be performed. The macro `temperature_given_day.C` is one instance of such an analysis, where a histogram is created in order to visualise the temperature range for a given day throughout the years. In order to run the program succesfully, the following steps have to be performed:
```
#first, make sure that 'Falsterbo.csv' exists by compiling in the terminal:
g++ cleaning_data_Falsterbo.cxx -o Falsterbo
./Falsterbo

#now, we need to compile the main .cxx file:
g++ temperature_given_day.cxx -o temperature_given_day
./temperature_given_day

#upon executing the line above, the terminal will request the user to input a specific day and month, following a MM-DD format, and finally create the desired dataset.

#having obtained the necessary files, the analysis is performed in root:
root -l
.L temperature_given_dau.C
tempgivenday_hist();

#a histogram should now pop-up.

```

Rain_analysis implementation : 

```bash
# Clone the repository
git clone https://github.com/Ossian-Malmborg/MNXB11-Group3-Project
cd MNXB11-Group3-Project/
# Create Graphical Plots
chmod +x rain_analysis/run_all.sh
./rain_analysis/run_all.sh

