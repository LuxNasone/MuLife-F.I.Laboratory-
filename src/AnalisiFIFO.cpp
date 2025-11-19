#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {

    ifstream FIFO("FIFOread_20251118-171617.txt");

    vector<double> CHv, CLKv;

    double CH , CLK;

    TH1F *h = new TH1F("Decay Time", "Histogram MuLife", 20, -1, 25);

    while (FIFO >> CH >> CLK){

        CHv.push_back(CH);

        CLKv.push_back(CLK);

    }

    int lenCH = CHv.size();

    int lenCLK = CLKv.size();

    double a = 5e-3;

    int m = 0;

    for (int i = 1 ; i < lenCLK ; i++){

        CLKv[i] *= a;

        if (CHv[i] == 2){

            double t_stop = CLKv[i];

            if (CHv[i-1] == 1 && t_stop - CLKv[i-1] > 0){

                double t_start =  CLKv[i-1];

                double tau = t_stop - t_start;

                m += 1;

                h->Fill(tau);

            }

        }

    }

    cout << m << endl;

    TCanvas* c = new TCanvas("c_decay", "Canvas Decay Time", 800, 600);

    h->GetXaxis()->SetTitle("Decay Time [us]");

    h->GetYaxis()->SetTitle("Events [pure]");

    h->Draw();

    return 0;

}

