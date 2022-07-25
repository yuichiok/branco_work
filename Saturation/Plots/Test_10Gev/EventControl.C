#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

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

   TH1F * layer_energy = new TH1F("layer_energy","Energy_vs_Bcid",10000,0,9999);
   TH1F * layer_hit = new TH1F("myhits","nhit",1000,0,100);
   TH1F * myenergy = new TH1F("myenergy","Energy",10000,0,9999);
   float total_energy = 0;
   float total_energy1 = 0;
   float mean_MIP; 
   float total_MIP = 0; 
   float dIdt;
   float I_MIP = 4.2e-7;
   float c = 3e8;
   float thickness = 500e-6;
   float t = thickness / c; 

   int nhit5(0);
   int nhit7 = 0;
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (int ilayer = 0; ilayer < 15; ilayer++){
      
      TH1F * layer_hit = new TH1F("myhits","nhit",1000,0,100);
      nhit5=0;
      
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      nhit5 = 0;
      nhit7 = 0;
      if (nhit_slab>12){

      for (int ihit=0; ihit < nhit_len; ihit++){
         if (hit_sca[ihit] == 0){
          if (hit_slab[ihit] == 7){
                  nhit5++; 
                  
               }//end if  hit slab
            } // end if hit sca
         } // end for ihit
      } // end if nhit slab
       std::cout <<  ilayer << ", " << nhit5 << std::endl;
       if (nhit5< 10){
         cout << "event number " << event << endl; 
       }
      layer_hit->Fill(nhit5*1.0);    
   }
   
   
      //if (total_energy != 0){ 
      //      layer_energy->Fill(event,total_energy);
            
      //      myenergy->Fill(total_energy);
            //std::cout << "nhit5, total energy: " << nhit5 << ", " << total_energy << std::endl; 
      //   }
         
         c0->cd(ilayer+1);
         layer_hit->Draw("h");
   }
//   mean_MIP = total_energy / total_MIP;
//   dIdt= mean_MIP * I_MIP / t ;
   
   
   // end of entries
   TFile * file = new TFile("energy_test.root","RECREATE");
   file->cd();

//   layer_energy->Write();
//   layer_hit->Write(); 
//   myenergy->Write();
   c0->Write();

   
}