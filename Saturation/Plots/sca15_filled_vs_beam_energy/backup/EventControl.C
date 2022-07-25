#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <fstream>

void EventControl::Loop()
{
//   In a ROOT session, you can do:
//      root> .L EventControl.C
//      root> EventControl t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   TH1F * sca15 = new TH1F("Number of SCA15 filled", "Beam energy: Number of sca15", 15, 0, 150);
   string line;
   
   ifstream file ("sca15.txt");
   while (getline (file, line)){
      float num_float = std::stof(line);
      sca15->Fill(num_float); 
   }
TFile * sca15_filled = new TFile("sca15_filled_vs_beam_energy.root","RECREATE");
   sca15_filled->cd();
   sca15->Write();
   
   } // event loop

   // end of entries


   