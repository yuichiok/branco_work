#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"

#include "EventControl.C"

float looper(int set_ene = 10){

	TString fname = "/home/irles/Work/Saturation/Runs/" + to_string(set_ene) + "GeV.root";
	EventControl *evcontrol = new EventControl(fname);
	float count = evcontrol->Count_Event();
	cout << "success with " << fname << endl;

	return count;


}

void run(){

	// const int nene = 7;
	// int l_energy[nene] = {10,20,40,60,80,100,150};
	const int nene = 4;
	int l_energy[nene] = {60,80,100,150};

	TFile *MyFile = new TFile("output2.root","RECREATE");
	TH1F *h_cnt = new TH1F("h_cnt","Hits above sca 13;Energy (GeV);nHits",16,-5,155);
	h_cnt->Sumw2();

	for(int ie=0; ie<nene; ie++)
	{
		float number = looper(l_energy[ie]);
		h_cnt->Fill(l_energy[ie],number);
	}

	// h_cnt->Draw("h");
	MyFile->cd();
	h_cnt->Write();

}
