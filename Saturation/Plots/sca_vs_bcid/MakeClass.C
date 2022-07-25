#include "TROOT.h"
#include "TFile.h"

int MakeClass(){

  TString filename = "/home/irles/Work/Saturation/full_run.root";
  TFile *file = new TFile("/home/irles/Work/Saturation/full_run.root");

  TString treename = "ecal";
  TTree* tree = (TTree*)file->Get("ecal") ;

  file->ls();

  tree->MakeClass("EventControl");

  std::cout << "processed..." << std::endl;

  return 0;

}