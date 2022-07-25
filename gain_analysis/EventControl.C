#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>

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

   TFile * file = new TFile("adc_test.root","RECREATE");

   TH2F * h_signal = new TH2F("h_signal",";x;y",400,0,400,400,0,400);
   TH2F * h_noise = new TH2F("h_noise",";x;y",400,0,400,400,0,400);

   std::vector<float> sig_adc_highs, sig_adc_lows;
   std::vector<float> noise_adc_highs, noise_adc_lows;
   float MIP = 84.7308  ;
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      for (int ihit=0; ihit < nhit_len; ihit++){
        if (hit_slab[ihit]== 8){
         if ( hit_energy[ihit] > 1.0 ){

               h_signal->Fill(MIP*hit_energy_lg[ihit],MIP*hit_energy[ihit]);
               sig_adc_lows.push_back(MIP*hit_energy_lg[ihit]);
               sig_adc_highs.push_back(MIP*hit_energy[ihit]);

         }
            else if ( hit_energy[ihit] < 1.0 ){

               h_noise->Fill(MIP*hit_energy_lg[ihit],MIP*hit_energy[ihit]);;
               noise_adc_lows.push_back(MIP*hit_energy_lg[ihit]);
               noise_adc_highs.push_back(MIP*hit_energy[ihit]);

         }
       } 
      }// end of hit loop
   } // end of entries

   // TGraph Signal
   int n_sig = sig_adc_highs.size();
   float* arr_sig_adc_high = &sig_adc_highs[0];
   float* arr_sig_adc_low = &sig_adc_lows[0];

   TGraph * tg_sig = new TGraph(n_sig,arr_sig_adc_low,arr_sig_adc_high);

   // TGraph Noise
   int n_noise = noise_adc_highs.size();
   float* arr_noise_adc_high = &noise_adc_highs[0];
   float* arr_noise_adc_low = &noise_adc_lows[0];

   TGraph * tg_noise = new TGraph(n_noise,arr_noise_adc_low,arr_noise_adc_high);


   file->cd();

   h_signal->Write();
   h_noise->Write();
   tg_sig->Write();
   tg_noise->Write();


}