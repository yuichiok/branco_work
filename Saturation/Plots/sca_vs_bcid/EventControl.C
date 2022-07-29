#define EventControl_cxx
#include "EventControl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <list>
#include <iterator>

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
   c0->Divide(2,2);
   TH2F * chip_sca[4];
   for (int ih = 0; ih < 4; ih++)
   {
      TString hname = "sca_chip" + to_string(ih+12) + "vs number of event";
      chip_sca[ih] = new TH2F(hname,";number of event;sca",30000,0,30000,15,0,15);
   }

   int nhit5[15];


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int count13=0;
   list<int> bad_event;  
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (nhit_slab > 13){
         
          for(int ichip = 0; ichip < 5; ichip++){

            list<int> sca_list;

            for (int ihit=0; ihit < nhit_len; ihit++){

               int true_chip= ichip+12;

               if (hit_slab[ihit] == 7 && hit_chip[ihit] == true_chip ){

                  sca_list.push_back(hit_sca[ihit]);         
              
                          // chip_sca[ichip]->Fill(jentry, hit_sca[ihit]);                       
                  }//end if  hit slab
            } // end for ihit

            sca_list.sort();
            sca_list.unique();
            
            int range_sca;
            range_sca = sca_list.size();

            // cout << range_sca << endl;

            if (range_sca > 1){
               bad_event.push_back(jentry);
            }
         //   for (auto it = sca_list.begin(); it != sca_list.end(); ++it){
         //    cout << *it << endl;   
         //    // cout << " end ichip"<< endl;
            }
              
            
         } // end for ichip
   bad_event.sort();
   bad_event.unique();      
   
   } // event loop
   
   int ibad =0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      auto bad_entry = bad_event.begin();
      
      advance(bad_entry, ibad);
      // cout << *bad_entry << endl;
      if (jentry == *bad_entry){
         
         ibad++;
      }
      else if (jentry != *bad_entry){
       if (nhit_slab > 13){
         
          for(int ichip = 0; ichip < 5; ichip++){

            list<int> sca_list;

            for (int ihit=0; ihit < nhit_len; ihit++){

               int true_chip= ichip+12;

               if (hit_slab[ihit] == 7 && hit_chip[ihit] == true_chip ){      
              
                  chip_sca[ichip]->Fill(jentry, hit_sca[ihit]);    

                  }//end if  hit slab
            } // end for ihit
   // for (auto it = bad_event.begin(); it != bad_event.end(); ++it){
   //    cout << *it << endl;   
         } 
      }
   }
   }
   for(int ih=0; ih < 4; ih++ ){
         c0->cd(ih+1);
         chip_sca[ih]->Draw("h");
   }
   
   
   // end of entries
   TFile * file = new TFile("sca_bcid_electrons_10Gev.root","RECREATE");
   file->cd();

//   layer_energy->Write();
//   layer_hit->Write(); 
//   myenergy->Write();
   c0->Write();


   }
