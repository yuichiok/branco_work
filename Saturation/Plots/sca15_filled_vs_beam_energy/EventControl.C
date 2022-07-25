#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <fstream>

float EventControl::Count_Event()
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
   if (fChain == 0) return 0;
   //TH1F * sca15 = new TH1F("Number of SCA15 filled", "Beam energy: Number of sca15", 15, 0, 150);

   //TFile * file = new TFile("sca15_filled_vs_beam_energy.root","RECREATE");
 
   // ofstream file;
   // file.open ("sca15.txt",std::ios_base::app);
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   int cnt = 0;
   int total_hits = 0;

   cout << "nentries = " << nentries << endl;
      
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      total_hits+=nhit_len;

      for (int ihit=0; ihit < nhit_len; ihit++){
         if (hit_slab[ihit] == 7 && hit_sca[ihit] >= 13){
                     // file << 150 << endl;                       
                     cnt++;                       
            }//end if  hit slab
      } // end for ihit

   } // end for ichip

   float scale = static_cast<float>(cnt) / static_cast<float>(total_hits);
   cout << "scale = " << scale << endl;
   return static_cast<float>(cnt);
   // return scale;
   
} // event loop

   // end of entries

   
