#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"

using namespace std;

int makeWHeavyBGSkim (string path = "/tas/olivito/phase2_Jul28/output/V00-00-12", string tag = "Bj-4p", string cond = "PhaseII__140PU") {
  
  //--------------------------------------------------
  // cut for output files
  //--------------------------------------------------
  
  char* sel = "(nleps >= 1) && (lep1pt > 30.) && ((nbgen >= 1) || (ncgen >= 1))";
  cout << "Skimming with selection : "<<sel<<endl;

  //--------------------------------------------------
  // input and output file
  //--------------------------------------------------
  
  char* infilename = Form("%s/%s*%s_baby.root",path.c_str(),tag.c_str(),cond.c_str());
  char* outfilename = Form("%s/skim_1lpt30_2b/%s_WHeavy_%s_baby.root",path.c_str(),tag.c_str(),cond.c_str());
  
  //--------------------------------------------------
  // cout stuff
  //--------------------------------------------------
  
  cout << "Reading in : " << infilename << endl;
  cout << "Writing to : " << outfilename << endl;
  cout << "Selection : " << sel << endl;
  
  //--------------------------------------------------
  // read input file, write to output files
  //--------------------------------------------------
  
  long long max_tree_size = 20000000000000000LL;
  TTree::SetMaxTreeSize(max_tree_size);
  
  TChain *chain = new TChain("t");
  chain->Add(infilename);
  
  cout << "Input tree has entries: " << chain->GetEntries() << endl;
  
  //-------------------
  // skim
  //-------------------
  
  TFile *out = TFile::Open(outfilename, "RECREATE");
  assert( out != 0 );
  TTree* clone = chain->CopyTree( sel );
  cout << "Clone tree has entries: " << clone->GetEntries() << endl;

  clone->Write(); 
  out->Close();
  return 0;
  
}






