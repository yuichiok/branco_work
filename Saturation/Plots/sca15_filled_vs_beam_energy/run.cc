#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"

#include "EventControl.C"

void run(){

	const int nene = 7;
	int l_energy[nene] = {10,20,40,60,80,100,150};

	TFile *MyFile = new TFile("output.root","RECREATE");
	TH1F *h_cnt = new TH1F("h_cnt","Hits above sca 13;Energy (GeV);nHits",16,-5,155);

	for(int ie=0; ie<nene; ie++)
	{
		TString filepath = "../../Runs/";
		TString filename = to_string(l_energy[ie]) + "GeV.root";
		TString fullname = filepath + filename;
		EventControl EventControl(fullname);
		float count = EventControl.Count_Event();
		h_cnt->Fill(l_energy[ie],count);
	}

	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );

	h_cnt->Draw("h");
	MyFile->cd();
	h_cnt->Write();

	gSystem->Exit(0);

	// return 0;

}
