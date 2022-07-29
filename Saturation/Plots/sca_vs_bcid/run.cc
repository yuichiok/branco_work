#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"

#include "EventControl.C"

void run(int energy=10){

	TString filepath = "../../Runs/";
	TString filename = to_string(energy) + "GeV.root";
	TString fullfile = filepath + filename;

	EventControl EventControl(energy, fullfile);
	EventControl.Loop();

	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );

	gSystem->Exit(0);

	// return 0;

}
