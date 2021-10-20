/*
*/

// LIBRERIE
#include <bits/stdc++.h>
#include "alberi.cpp"

// DICHIARAZIONE COSTANTI
const int N = 20;

// DICHIARAZIONE FUNZIONI
double getResolution();
double getTmin();
double getFinalTime(double[], int);

int main() {
    
}

int calcTimes(auto tree) {
    for(int i = 0; i <= 100; i++) {
        int size = (int)floor(A * pow(B, i));
        cout << "alberi numero: " << i+1 << "\tSize: " << size << endl;

        double times[N];
        double minTime = getTmin();

        for (int j=0; j<N; j++) {
            //cout << "TOTALE: " << j << endl;
            int iter = 0;
            double time;
            duration<double, seconds::period> partialTime;
            double doubleTime = 0.0;
            
            steady_clock::time_point start = steady_clock::now();
            steady_clock::time_point end;

            do {
                    //cout << "IT: " << iter << endl;
                    //cout << j << " : " << iter << endl;
                    useRBT(size);
                    end = steady_clock::now();
                    partialTime = duration_cast<duration<double>>(end - start);
                    doubleTime = partialTime.count();
                    iter++;
            } while(doubleTime <= minTime);
            time = doubleTime / (double) iter; 
            times[j] = time;
        }

        double finalTime = getFinalTime(times, N);
        cout << "FINAL: " << finalTime << endl;
    }

return 0;
}

// DEFINIZIONE FUNZIONI

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> duration;

    return duration(end - start).count();
}

double getTmin(){ // a posto

    double R = getResolution();

    double Tmin = R * ((1.000/0.01) + 1.000);

    return Tmin;
}

double getFinalTime(double times[], int length) {
    double sum = 0.0;

    for (int i = 0; i < length; i++) {
        sum += times[i];
    }

    return sum / length;
}