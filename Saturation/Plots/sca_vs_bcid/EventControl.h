//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul  8 17:16:43 2022 by ROOT version 6.26/04
// from TTree ecal/Build ecal events
// found on file: /home/irles/Work/Saturation/full_run.root
//////////////////////////////////////////////////////////

#ifndef EventControl_h
#define EventControl_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class EventControl {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Int_t           spill;
   Int_t           cycle;
   Int_t           bcid;
   Int_t           bcid_first_sca_full;
   Int_t           bcid_merge_end;
   Int_t           id_run;
   Int_t           id_dat;
   Int_t           nhit_slab;
   Int_t           nhit_chip;
   Int_t           nhit_chan;
   Int_t           nhit_len;
   Float_t         sum_energy;
   Float_t         sum_energy_lg;
   Int_t           hit_slab[9999];   //[nhit_len]
   Int_t           hit_chip[9999];   //[nhit_len]
   Int_t           hit_chan[9999];   //[nhit_len]
   Int_t           hit_sca[9999];   //[nhit_len]
   Float_t         hit_x[9999];   //[nhit_len]
   Float_t         hit_y[9999];   //[nhit_len]
   Float_t         hit_z[9999];   //[nhit_len]
   Int_t           hit_adc_high[9999];   //[nhit_len]
   Int_t           hit_adc_low[9999];   //[nhit_len]
   Float_t         hit_energy[9999];   //[nhit_len]
   Float_t         hit_energy_lg[9999];   //[nhit_len]
   Int_t           hit_n_scas_filled[9999];   //[nhit_len]
   Int_t           hit_isHit[9999];   //[nhit_len]
   Int_t           hit_isMasked[9999];   //[nhit_len]
   Int_t           hit_isCommissioned[9999];   //[nhit_len]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_spill;   //!
   TBranch        *b_cycle;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_bcid_first_sca_full;   //!
   TBranch        *b_bcid_merge_end;   //!
   TBranch        *b_id_run;   //!
   TBranch        *b_id_dat;   //!
   TBranch        *b_nhit_slab;   //!
   TBranch        *b_nhit_chip;   //!
   TBranch        *b_nhit_chan;   //!
   TBranch        *b_nhit_len;   //!
   TBranch        *b_sum_energy;   //!
   TBranch        *b_sum_energy_lg;   //!
   TBranch        *b_hit_slab;   //!
   TBranch        *b_hit_chip;   //!
   TBranch        *b_hit_chan;   //!
   TBranch        *b_hit_sca;   //!
   TBranch        *b_hit_x;   //!
   TBranch        *b_hit_y;   //!
   TBranch        *b_hit_z;   //!
   TBranch        *b_hit_adc_high;   //!
   TBranch        *b_hit_adc_low;   //!
   TBranch        *b_hit_energy;   //!
   TBranch        *b_hit_energy_lg;   //!
   TBranch        *b_hit_n_scas_filled;   //!
   TBranch        *b_hit_isHit;   //!
   TBranch        *b_hit_isMasked;   //!
   TBranch        *b_hit_isCommissioned;   //!

   EventControl(int ene, TString filein_s);
   EventControl(TTree *tree=0);
   virtual ~EventControl();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   int use_energy = 10;
};

#endif

#ifdef EventControl_cxx

EventControl::EventControl(int ene, TString filein_s) : fChain(0) 
{
   if(!filein_s) cout << "Error: no file entry" << endl;
   TFile *f = new TFile(filein_s);
   TTree *tree = (TTree*)f->Get("ecal");
   Init(tree);
   use_energy = ene;
}

EventControl::EventControl(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../Runs/20GeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../Runs/20GeV.root");
      }
      f->GetObject("ecal",tree);

   }
   Init(tree);
}

EventControl::~EventControl()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EventControl::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EventControl::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void EventControl::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("spill", &spill, &b_spill);
   fChain->SetBranchAddress("cycle", &cycle, &b_cycle);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("bcid_first_sca_full", &bcid_first_sca_full, &b_bcid_first_sca_full);
   fChain->SetBranchAddress("bcid_merge_end", &bcid_merge_end, &b_bcid_merge_end);
   fChain->SetBranchAddress("id_run", &id_run, &b_id_run);
   fChain->SetBranchAddress("id_dat", &id_dat, &b_id_dat);
   fChain->SetBranchAddress("nhit_slab", &nhit_slab, &b_nhit_slab);
   fChain->SetBranchAddress("nhit_chip", &nhit_chip, &b_nhit_chip);
   fChain->SetBranchAddress("nhit_chan", &nhit_chan, &b_nhit_chan);
   fChain->SetBranchAddress("nhit_len", &nhit_len, &b_nhit_len);
   fChain->SetBranchAddress("sum_energy", &sum_energy, &b_sum_energy);
   fChain->SetBranchAddress("sum_energy_lg", &sum_energy_lg, &b_sum_energy_lg);
   fChain->SetBranchAddress("hit_slab", hit_slab, &b_hit_slab);
   fChain->SetBranchAddress("hit_chip", hit_chip, &b_hit_chip);
   fChain->SetBranchAddress("hit_chan", hit_chan, &b_hit_chan);
   fChain->SetBranchAddress("hit_sca", hit_sca, &b_hit_sca);
   fChain->SetBranchAddress("hit_x", hit_x, &b_hit_x);
   fChain->SetBranchAddress("hit_y", hit_y, &b_hit_y);
   fChain->SetBranchAddress("hit_z", hit_z, &b_hit_z);
   fChain->SetBranchAddress("hit_adc_high", hit_adc_high, &b_hit_adc_high);
   fChain->SetBranchAddress("hit_adc_low", hit_adc_low, &b_hit_adc_low);
   fChain->SetBranchAddress("hit_energy", hit_energy, &b_hit_energy);
   fChain->SetBranchAddress("hit_energy_lg", hit_energy_lg, &b_hit_energy_lg);
   fChain->SetBranchAddress("hit_n_scas_filled", hit_n_scas_filled, &b_hit_n_scas_filled);
   fChain->SetBranchAddress("hit_isHit", hit_isHit, &b_hit_isHit);
   fChain->SetBranchAddress("hit_isMasked", hit_isMasked, &b_hit_isMasked);
   fChain->SetBranchAddress("hit_isCommissioned", hit_isCommissioned, &b_hit_isCommissioned);
   Notify();
}

Bool_t EventControl::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EventControl::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EventControl::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EventControl_cxx
