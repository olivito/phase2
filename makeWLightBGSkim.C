#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"

using namespace std;

int makeWLightBGSkim (string path = "/tas/olivito/phase2_Jul28/output/V00-00-12", string tag = "Bj-4p", string cond = "PhaseII__140PU") {
  
  //--------------------------------------------------
  // cut for output files
  //--------------------------------------------------
  
  char* sel = "(nleps >= 1) && (lep1pt > 30.) && (nb == 0) && (nbgen == 0) && (ncgen == 0)";
  cout << "Skimming with selection : "<<sel<<endl;

  //--------------------------------------------------
  // input and output file
  //--------------------------------------------------
  
  char* infilename = Form("%s/%s*%s_baby.root",path.c_str(),tag.c_str(),cond.c_str());
  char* outfilename = Form("%s/skim_1lpt30_2b/%s_WLight_%s_baby.root",path.c_str(),tag.c_str(),cond.c_str());
  
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
  TTree* temptree = chain->CopyTree( sel );
  cout << "Temp tree has entries: " << temptree->GetEntries() << endl;

  // //-------------------
  // // copy again to overwrite nb value to 2
  // //-------------------
  
  // const Int_t nb_new = 2;

  // std::cout << "Setting nb == 2" << std::endl;
  
  // //-------------------------------------------------------------
  // // Replace branches
  // //-------------------------------------------------------------`
  // t->SetBranchStatus("*", 1);

  // // Removes the branches that we want to replace
  // t->SetBranchStatus("nb", 0); 

  // TTree* clone = temptree->CloneTree(-1, "fast");

  // //-------------------------------------------------------------

  // TBranch* b1 = clone->Branch("nb", &nb_new, "nb/I");
   
  // Int_t nentries = t->GetEntries();
  // for(Int_t i = 0; i < nentries; i++) {
  //   b1->Fill();
  // }
  // //-------------------------------------------------------------

  // cout << "Out tree has entries: " << clone->GetEntries() << endl;

  //  clone->Write(); 
  temptree->Write(); 
  out->Close();
  return 0;
  
}






