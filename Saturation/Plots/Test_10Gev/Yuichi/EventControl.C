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

   TH1F * layer_energy = new TH1F("layer_energy","Energy_vs_Bcid",10000,0,9999);
   // TH1F * layer_hit = new TH1F("myhits","nhit",1000,0,100);
   TH1F * myenergy = new TH1F("myenergy","Energy",10000,0,9999);
   TH1F * layer_hit[15];
   for (int ih = 0; ih < 15; ih++)
   {
      TString hname = "layer_hit" + to_string(ih);
      layer_hit[ih] = new TH1F(hname,hname,1000,0,100);
   }
   

   float total_energy = 0;
   float total_energy1 = 0;
   float mean_MIP; 
   float total_MIP = 0; 
   float dIdt;
   float I_MIP = 4.2e-7;
   float c = 3e8;
   float thickness = 500e-6;
   float t = thickness / c; 
   int coincidences = 0;
   int count13_sca0=0;
   int nhit5[15];
   Long64_t nentries = fChain->GetEntriesFast();
   cout << "nentries = " << nentries << endl;

   Long64_t nbytes = 0, nb = 0;
   int count13=0;
      
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (nhit_slab < 13) continue;
      count13++;
      coincidences=0;
          for(int ilayer = 0; ilayer < 15; ilayer++){

            nhit5[ilayer]=0;
            for (int ihit=0; ihit < nhit_len; ihit++){
               if (hit_sca[ihit] != 0 ) continue;
                  if (hit_slab[ihit] == ilayer){
                           nhit5[ilayer]++; 
                  }//end if  hit slab
            } // end for ihit

            layer_hit[ilayer]->Fill(nhit5[ilayer]*1.0);
            if (nhit5[ilayer] != 0){
               coincidences++;
            } 
         } // end for ilayer
         if (coincidences >= 13){
            count13_sca0++;
         }.q
         // std::cout <<  ilayer << ", " << nhit5 << std::endl;
         if ( 0 < nhit5[7]  && nhit5[7] < 10 && coincidences >= 13){
            cout << "count13 number below 10 " << nhit5[7] <<",  " << count13 << ", " <<count13_sca0<< endl; 
         }
         if ( 10 < nhit5[7] && coincidences >= 13  ){
            cout << "count13 number above 10hits " << nhit5[7] <<",  " << count13 << ", "<< count13_sca0  << endl; 
         }
       
   
   } // event loop
   
   
      //if (total_energy != 0){ 
      //      layer_energy->Fill(event,total_energy);
            
      //      myenergy->Fill(total_energy);
            //std::cout << "nhit5, total energy: " << nhit5 << ", " << total_energy << std::endl; 
      //   }

   for(int ih=0; ih < 15; ih++ ){
         c0->cd(ih+1);
         layer_hit[ih]->Draw("h");
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