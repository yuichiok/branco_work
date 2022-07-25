#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>

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

   TCanvas *c0 = new TCanvas("c0","c0",700,700);
   c0->Divide(4,4);
   TH1F * layer_hit[15];
   for (int ih = 0; ih < 15; ih++)
   {
      TString hname = "layer_hit" + to_string(ih);
      layer_hit[ih] = new TH1F(hname,hname,1000,0,100);
   }


   int nhit5[15];


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int count13=0;
      
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (nhit_slab>=13){
          for(int ilayer = 0; ilayer < 15; ilayer++){
            nhit5[ilayer]=0;
            for (int ihit=0; ihit < nhit_len; ihit++){
               if (hit_sca[ihit] < 15 && hit_slab[ihit] == ilayer){
                           nhit5[ilayer]++;                         
                  }//end if  hit slab
            } // end for ihit

            layer_hit[ilayer]->Fill(nhit5[ilayer]*1.0);

         } // end for ilayer
      } // end if nhit slab
       
   
   } // event loop

   for(int ih=0; ih < 15; ih++ ){
         c0->cd(ih+1);
         layer_hit[ih]->Draw("h");
   }
   
   
   // end of entries
   TFile * file = new TFile("electrons_10Gev.root","RECREATE");
   file->cd();

//   layer_energy->Write();
//   layer_hit->Write(); 
//   myenergy->Write();
   c0->Write();

   
}