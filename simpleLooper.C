#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"

#include "TString.h"

#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include "classes/DelphesClasses.h"

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootUtilities.h"

#include "fullModelskfactor/McTruthInfo.hh"
//#include "McTruthInfo.hh"

#include "simpleLooper.h"


char* version = (char*) "V00-00-12_nopujetid";
//char* version = (char*) "V00-00-12";
//char* version = (char*) "temp";
//char* version = (char*) "printout";

using namespace std;

//void doLoop(const char *inputFile, int nfiles=1);
void doLoop(const string inputFile, int nfiles=1, bool isSignal=false, int part = -1);

//--------------------------------------
// Function to run over various samples
//--------------------------------------

void simpleLooper(char* sample, char* phase, char* config, char* PU, int stbin = 0 , int nfiles = 1, int part = -1 ){
 
  gSystem->Load("libDelphes");

  TString tsample(sample);

  if ( tsample.Contains("ttbar") ){
    if     ( stbin == 1 ) doLoop( Form("tt-4p-0-600-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 2 ) doLoop( Form("tt-4p-600-1100-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 3 ) doLoop( Form("tt-4p-1100-1700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 4 ) doLoop( Form("tt-4p-1700-2500-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 5 ) doLoop( Form("tt-4p-2500-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) , nfiles , false , part );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if ( tsample.Contains("diboson") ){
    if     ( stbin == 1 ) doLoop( Form("BB-4p-0-300-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("BB-4p-300-700-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("BB-4p-700-1300-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("BB-4p-1300-2100-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("BB-4p-2100-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if( tsample.Contains("boson") ){
    if     ( stbin == 1 ) doLoop( Form("Bj-4p-0-300-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 2 ) doLoop( Form("Bj-4p-300-600-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 3 ) doLoop( Form("Bj-4p-600-1100-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 4 ) doLoop( Form("Bj-4p-1100-1800-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 5 ) doLoop( Form("Bj-4p-1800-2700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 6 ) doLoop( Form("Bj-4p-2700-3700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles , false , part );
    else if( stbin == 7 ) doLoop( Form("Bj-4p-3700-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) , nfiles , false , part );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if( tsample.Contains("tW") ){
    if     ( stbin == 1 ) doLoop( Form("tB-4p-0-500-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("tB-4p-500-900-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("tB-4p-900-1500-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("tB-4p-1500-2200-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("tB-4p-2200-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if( tsample.Contains("singletop") ){
    if     ( stbin == 1 ) doLoop( Form("tj-4p-0-500-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("tj-4p-500-1000-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("tj-4p-1000-1600-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("tj-4p-1600-2400-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("tj-4p-2400-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if( tsample.Contains("VH") ){
    if     ( stbin == 1 ) doLoop( Form("BBB-4p-0-600-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("BBB-4p-600-1300-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("BBB-4p-1300-100000-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if( tsample.Contains("TChiWHTest") ){
    doLoop( Form("TChiWH14PythiaTest_%s_%s_%s"       , phase , config , PU ) , nfiles, true );
  }

  else if( tsample.Contains("TChiWH") ){
    doLoop( Form("TChiWH14Pythia_%s_%s_%s"       , phase , config , PU ) , nfiles, true );
  }

  else if( tsample.Contains("naturalModel2") ){
    doLoop( Form("naturalModel2_%s_%s_%s"       , phase , config , PU ) , nfiles, true );
  }

}

//-------------------------------------------
// Retrieve file names
//-------------------------------------------

//vector<char*> fileNames( const char* sample , int nfiles = 1){
vector<string> fileNames( const string sample , int nfiles = 1, int part = -1){

  cout << "Opening file list for sample " << sample;
  if (part > 0) cout << ", part " << part;
  cout << endl;

  TString filelist = Form("fileLists/%s.txt",sample.c_str());
  if (part > 0) filelist = Form("fileLists/%s_part%d.txt",sample.c_str(),part);
  ifstream ifile( filelist );
  
  string filepath;

  vector<string> names;

  int n = 0;

  if( !ifile.is_open() ){
    cout << "Couldn't find file for sample " << sample << endl;
    exit(0);
  }

  char* fullfilepath = (char*) "";
  string previousfilepath = "";

  // if nfiles > 0, run over nfiles in list
  if( nfiles > 0 ){
    while( n < nfiles){
      ifile >> filepath;
      
      fullfilepath = Form("root://eoscms//eos/cms/store/group/%s",filepath.c_str());
      cout << fullfilepath << endl;
      names.push_back(fullfilepath);
      n++;
    }
  }

  // if nfiles = -1, run over all files in list
  else{
    while( !ifile.eof() ){

      previousfilepath = filepath;

      ifile >> filepath;

      // check for duplicate at end of file
      if( strcmp(previousfilepath.c_str(),filepath.c_str()) != 0 ){
      
	fullfilepath = Form("root://eoscms//eos/cms/store/group/%s",filepath.c_str());
	cout << fullfilepath << endl;      
	names.push_back(fullfilepath);
      }

    }
  }

  return names;
}


//-------------------------------------------------------------------------------------
// cross sections from:
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsWG/Phase2UpgradeStudies#Background_samples
//-------------------------------------------------------------------------------------

//float getCrossSection( const char* sample ){
float getCrossSection( const string sample ){

  float xsec = -1;
  TString tsample(sample);
  
  // dibosons
  if      ( tsample.Contains("BB-4p-0-300-v1510_14TEV"          ) )  xsec = 249.977;
  else if ( tsample.Contains("BB-4p-300-700-v1510_14TEV"        ) )  xsec = 35.2306;
  else if ( tsample.Contains("BB-4p-700-1300-v1510_14TEV"       ) )  xsec = 4.13743;
  else if ( tsample.Contains("BB-4p-1300-2100-v1510_14TEV"      ) )  xsec = 0.41702;
  else if ( tsample.Contains("BB-4p-2100-100000-v1510_14TEV"    ) )  xsec = 0.04770;

  // ttbar
  else if ( tsample.Contains("tt-4p-0-600-v1510_14TEV"          ) )  xsec = 530.894;
  else if ( tsample.Contains("tt-4p-600-1100-v1510_14TEV"       ) )  xsec = 42.5535;
  else if ( tsample.Contains("tt-4p-1100-1700-v1510_14TEV"      ) )  xsec = 4.48209;
  else if ( tsample.Contains("tt-4p-1700-2500-v1510_14TEV"      ) )  xsec = 0.52795;
  else if ( tsample.Contains("tt-4p-2500-100000-v1510_14TEV"    ) )  xsec = 0.05449;

  // W+jets
  else if ( tsample.Contains("Bj-4p-0-300-v1510_14TEV"          ) )  xsec = 34409.9;
  else if ( tsample.Contains("Bj-4p-300-600-v1510_14TEV"        ) )  xsec = 2642.85;
  else if ( tsample.Contains("Bj-4p-600-1100-v1510_14TEV"       ) )  xsec = 294.123;
  else if ( tsample.Contains("Bj-4p-1100-1800-v1510_14TEV"      ) )  xsec = 25.9500;
  else if ( tsample.Contains("Bj-4p-1800-2700-v1510_14TEV"      ) )  xsec = 2.42111;
  else if ( tsample.Contains("Bj-4p-2700-3700-v1510_14TEV"      ) )  xsec = 0.22690;
  else if ( tsample.Contains("Bj-4p-3700-100000-v1510_14TEV"    ) )  xsec = 0.02767;

  // tW
  else if ( tsample.Contains("tB-4p-0-500-v1510_14TEV"          ) )  xsec = 63.8892;
  else if ( tsample.Contains("tB-4p-500-900-v1510_14TEV"        ) )  xsec = 7.12172;
  else if ( tsample.Contains("tB-4p-900-1500-v1510_14TEV"       ) )  xsec = 0.98030;
  else if ( tsample.Contains("tB-4p-1500-2200-v1510_14TEV"      ) )  xsec = 0.08391;
  else if ( tsample.Contains("tB-4p-2200-100000-v1510_14TEV"    ) )  xsec = 0.00953;

  // single top
  else if ( tsample.Contains("tj-4p-0-500-v1510_14TEV"          ) )  xsec = 109.736;
  else if ( tsample.Contains("tj-4p-500-1000-v1510_14TEV"       ) )  xsec = 5.99325;
  else if ( tsample.Contains("tj-4p-1000-1600-v1510_14TEV"      ) )  xsec = 0.37680;
  else if ( tsample.Contains("tj-4p-1600-2400-v1510_14TEV"      ) )  xsec = 0.03462;
  else if ( tsample.Contains("tj-4p-2400-100000-v1510_14TEV"    ) )  xsec = 0.00312;

  // VH/triboson
  else if ( tsample.Contains("BBB-4p-0-600-v1510_14TEV"         ) )  xsec = 2.57304;
  else if ( tsample.Contains("BBB-4p-600-1300-v1510_14TEV"      ) )  xsec = 0.14935;
  else if ( tsample.Contains("BBB-4p-1300-100000-v1510_14TEV"   ) )  xsec = 0.01274;

  // // WH
  // else if( TString(sample).Contains("ewkino_WH_500_1000"  ) ) xsec =  0.0650 * 1.3 * 0.56;
  // else if( TString(sample).Contains("ewkino_WH_500_2000"  ) ) xsec =  0.0051 * 1.3 * 0.56;
  // else if( TString(sample).Contains("ewkino_WH_500_3000"  ) ) xsec =  0.0010 * 1.3 * 0.56;

  cout << "Sample cross section " << xsec << endl;

  if( xsec < 0 ){
    cout << "ERROR! couldn't find cross section for sample " << sample << endl;
    exit(0);
  }

  return 1000.0 * xsec;

}

void InitVars(){
  nb_       = 0  ;
  dilmass_  = 0.  ;
  nbgen_    = 0  ;
  ncgen_    = 0  ;
  njets_    = 0  ;
  njets40_  = 0  ;
  njets50_  = 0  ;
  njets100_ = 0  ;
  ngenjets_ = 0  ;
  njetsfwd_    = 0  ;
  njetsfwd40_  = 0  ;
  njetsfwd50_  = 0  ;
  njetsfwd100_ = 0  ;
  ngenjetsfwd_ = 0  ;
  nels_     = 0  ;
  nmus_     = 0  ;
  nleps_    = 0  ; 
  ngenels_  = 0  ;
  ngenmus_  = 0  ;
  ngentaus_ = 0  ;
  ngenleps_ = 0  ;
  met_      = 0. ;
  metphi_   = 0. ;
  ht_       = 0. ;
  jet1pt_   = 0. ;
  jet1eta_  = 0. ;
  jet1phi_  = 0. ;
  jet1genpt_= -1.;
  jet2pt_   = 0. ;
  jet2eta_  = 0. ;
  jet2phi_  = 0. ;
  jet2genpt_= -1.;
  bjet1pt_  = 0. ;
  bjet1eta_ = 0. ;
  bjet1phi_ = 0. ;
  bjet2pt_  = 0. ;
  bjet2eta_ = 0. ;
  bjet2phi_ = 0. ;
  jet3pt_   = 0. ;
  jet3eta_  = 0. ;
  jet3phi_  = 0. ;
  jet3genpt_= -1.;
  jet4pt_   = 0. ;
  jet4eta_  = 0. ;
  jet4phi_  = 0. ;
  jet4genpt_= -1.;
  genjetb1pt_   = -1.;
  genjetb1eta_  = 0. ;
  genjetb1phi_  = 0. ;
  genjetb1recopt_= -1.;
  genjetb1tag_  = -1 ;
  genjetb2pt_   = -1.;
  genjetb2eta_  = 0. ;
  genjetb2phi_  = 0. ;
  genjetb2recopt_= -1.;
  genjetb2tag_  = -1 ;
  st_       = 0. ;
  stlep_    = 0. ;
  genweight_ = 0. ;
  // xsec_     = 0. ;
  // nevents_  = 0  ;
  // weight_   = 0. ;
  nw_       = 0  ;
  nh_       = 0  ;
  nz_       = 0  ;
  ntop_     = 0  ;
  mt_       = 0  ;
  mct_      = 0  ;
  mbb_      = 0  ;
  ptbb_     = 0  ;
  drbb_     = 0  ;
  drbbgen_  = 0  ;
  pthgen_   = 0  ;
  ptc1gen_  = 0  ;
  genlep1pt_  = -1.;
  genlep1eta_ = 0. ;
  genb1pt_  = -1.;
  genb1eta_ = 0. ;
  genb2pt_  = -1.;
  genb2eta_ = 0. ;
  lep1pt_   = 0. ;
  lep1eta_  = 0. ;
  lep1phi_  = 0. ;
  lep1iso_  = -1. ;
  lep1genpt_= -1. ;
  lep2pt_   = 0. ;
  lep2eta_  = 0. ;
  lep2phi_  = 0. ;
  lep2iso_  = -1. ;
  leptype_  = -1 ;
  // mchi_     = -1 ;
  // mlsp_     = -1 ;
  mwgen_     = -1. ;
  mtwgen_    = -1. ;
  mttgen_    = -1. ;
  ptttgen_   = -1. ;
  genmet_    = -1. ;
  genmetphi_ = -1. ;
  pujetmet_  = -1. ;
  pujetmetphi_   = -1. ;
  pujetmt_   = -1. ;
  puppimet_  = -1. ;
  puppimetphi_   = -1. ;
  puppimt_   = -1. ;
  phot1pt_   = 0. ;
  phot1eta_  = 0. ;
  phot1phi_  = 0. ;
  phot1iso_  = -1. ;
  bgweight_ = 1. ;
  prodcode_    = 0 ;

  // puppi versions
  nb_puppi_       = 0  ;
  njets_puppi_    = 0  ;
  njets40_puppi_  = 0  ;
  njets50_puppi_  = 0  ;
  njets100_puppi_ = 0  ;
  njetsfwd_puppi_    = 0  ;
  njetsfwd40_puppi_  = 0  ;
  njetsfwd50_puppi_  = 0  ;
  njetsfwd100_puppi_ = 0  ;
  jet1pt_puppi_   = 0. ;
  jet1eta_puppi_  = 0. ;
  jet1phi_puppi_  = 0. ;
  jet1genpt_puppi_= -1.;
  jet2pt_puppi_   = 0. ;
  jet2eta_puppi_  = 0. ;
  jet2phi_puppi_  = 0. ;
  jet2genpt_puppi_= -1.;
  bjet1pt_puppi_  = 0. ;
  bjet1eta_puppi_ = 0. ;
  bjet1phi_puppi_ = 0. ;
  bjet2pt_puppi_  = 0. ;
  bjet2eta_puppi_ = 0. ;
  bjet2phi_puppi_ = 0. ;
  jet3pt_puppi_   = 0. ;
  jet3eta_puppi_  = 0. ;
  jet3phi_puppi_  = 0. ;
  jet3genpt_puppi_= -1.;
  jet4pt_puppi_   = 0. ;
  jet4eta_puppi_  = 0. ;
  jet4phi_puppi_  = 0. ;
  jet4genpt_puppi_= -1.;
  mct_puppi_      = 0  ;
  mbb_puppi_      = 0  ;
  ptbb_puppi_     = 0  ;
  drbb_puppi_     = 0  ;

}

//-------------------------------------------
// Function to loop over events in sample
//-------------------------------------------

//void doLoop(const char *prefix, int nfiles ){
void doLoop(const string prefix, int nfiles , bool isSignal, int part){

  //static const char* sample = prefix;

  cout << endl << endl;
  cout << "Running on sample: " << prefix  << endl;
  cout << "Code version     : " << version << endl;

  bool hasFwdTrk = false;
  if ((prefix.find("Configuration4") != string::npos) || (prefix.find("Conf4") != string::npos) || (prefix.find("PhaseII") != string::npos)) {
    hasFwdTrk = true;
    cout << "Found PhaseII or Configuration4, hasFwdTrk = " << hasFwdTrk << endl;
  }

  //--------------------------------------------------------------
  // input files for sig nevents, xsec
  //--------------------------------------------------------------

  //  TString h_nsig_filename = "events_TChiWH.root";
  TString h_nsig_filename = "events_TChiWH_Jul31_PhaseII_Conf4_140PileUp.root";
  cout << "opening mass TH2 file for TChiWH: " << h_nsig_filename << endl;

  TFile *f_nsig = TFile::Open(h_nsig_filename);
  if( !f_nsig->IsOpen() ){
    cout << "Error, could not open TChiWH nevents TFile, quitting" << endl;
    exit(0);
  }
  
  TH2F* h_nsig = (TH2F*) f_nsig->Get("hevts");

  if( h_nsig == 0 ){
    cout << "Error, could not retrieve TChiWH nevents hist, quitting" << endl;
    exit(0);
  }

  TFile* f_c1n2_xsec = TFile::Open("c1n2_xsec_14tev.root");
  
  if( !f_c1n2_xsec->IsOpen() ){
    cout << "Error, could not open c1n2 cross section TFile, quitting" << endl;
    exit(0);
  }
  
  TH1F* h_c1n2_xsec        = (TH1F*) f_c1n2_xsec->Get("h_c1n2_xsec");
  
  if( h_c1n2_xsec == 0 ){
    cout << "Error, could not retrieve c1n2 cross section hist, quitting" << endl;
    exit(0);
  }


  //--------------------------------------------------------------
  // make an output ntuple
  //--------------------------------------------------------------

  TString outfilename = Form("output/%s/%s_baby.root",version,prefix.c_str());
  if (part > 0) outfilename = Form("output/%s/%s_part%d_baby.root",version,prefix.c_str(),part);
  TFile *fbaby = TFile::Open(  outfilename ,"RECREATE" );
  fbaby->cd();

  TTree* tree = new TTree("t","Tree");

  //--------------------------------------------------------------
  // define variables for output ntuple
  //--------------------------------------------------------------

  tree->Branch("nb"         ,  &nb_         ,   "nb/I"		);
  tree->Branch("dilmass"    ,  &dilmass_    ,   "dilmass/F"	);
  tree->Branch("nbgen"      ,  &nbgen_      ,   "nbgen/I"	);
  tree->Branch("ncgen"      ,  &ncgen_      ,   "ncgen/I"	);
  tree->Branch("njets"      ,  &njets_      ,   "njets/I"	);
  tree->Branch("njets40"    ,  &njets40_    ,   "njets40/I"	);
  tree->Branch("njets50"    ,  &njets50_    ,   "njets50/I"	);
  tree->Branch("njets100"   ,  &njets100_   ,   "njets100/I"	);
  tree->Branch("ngenjets"   ,  &ngenjets_   ,   "ngenjets/I"	);
  tree->Branch("njetsfwd"   ,  &njetsfwd_   ,   "njetsfwd/I"	);
  tree->Branch("njetsfwd40" ,  &njetsfwd40_ ,   "njetsfwd40/I"	);
  tree->Branch("njetsfwd50" ,  &njetsfwd50_ ,   "njetsfwd50/I"	);
  tree->Branch("njetsfwd100",  &njetsfwd100_,   "njetsfwd100/I"	);
  tree->Branch("ngenjetsfwd",  &ngenjetsfwd_,   "ngenjetsfwd/I"	);
  tree->Branch("nels"       ,  &nels_       ,   "nels/I"	);
  tree->Branch("nmus"       ,  &nmus_       ,   "nmus/I"	);
  tree->Branch("nleps"      ,  &nleps_      ,   "nleps/I"	);
  tree->Branch("ngenels"    ,  &ngenels_    ,   "ngenels/I"	);
  tree->Branch("ngenmus"    ,  &ngenmus_    ,   "ngenmus/I"	);
  tree->Branch("ngentaus"   ,  &ngentaus_   ,   "ngentaus/I"	);
  tree->Branch("ngenleps"   ,  &ngenleps_   ,   "ngenleps/I"	);
  tree->Branch("met"        ,  &met_        ,   "met/F"		);
  tree->Branch("metphi"     ,  &metphi_     ,   "metphi/F"	);
  tree->Branch("ht"         ,  &ht_         ,   "ht/F"		);
  tree->Branch("jet1pt"     ,  &jet1pt_     ,   "jet1pt/F"	);
  tree->Branch("jet2pt"     ,  &jet2pt_     ,   "jet2pt/F"	);
  tree->Branch("jet3pt"     ,  &jet3pt_     ,   "jet3pt/F"	);
  tree->Branch("jet4pt"     ,  &jet4pt_     ,   "jet4pt/F"	);
  tree->Branch("jet1eta"    ,  &jet1eta_    ,   "jet1eta/F"	);
  tree->Branch("jet2eta"    ,  &jet2eta_    ,   "jet2eta/F"	);
  tree->Branch("jet3eta"    ,  &jet3eta_    ,   "jet3eta/F"	);
  tree->Branch("jet4eta"    ,  &jet4eta_    ,   "jet4eta/F"	);
  tree->Branch("jet1phi"    ,  &jet1phi_    ,   "jet1phi/F"	);
  tree->Branch("jet2phi"    ,  &jet2phi_    ,   "jet2phi/F"	);
  tree->Branch("jet3phi"    ,  &jet3phi_    ,   "jet3phi/F"	);
  tree->Branch("jet4phi"    ,  &jet4phi_    ,   "jet4phi/F"	);
  tree->Branch("jet1genpt"  ,  &jet1genpt_  ,   "jet1genpt/F"	);
  tree->Branch("jet2genpt"  ,  &jet2genpt_  ,   "jet2genpt/F"	);
  tree->Branch("jet3genpt"  ,  &jet3genpt_  ,   "jet3genpt/F"	);
  tree->Branch("jet4genpt"  ,  &jet4genpt_  ,   "jet4genpt/F"	);
  tree->Branch("bjet1pt"    ,  &bjet1pt_    ,   "bjet1pt/F"	);
  tree->Branch("bjet2pt"    ,  &bjet2pt_    ,   "bjet2pt/F"	);
  tree->Branch("bjet1eta"   ,  &bjet1eta_   ,   "bjet1eta/F"	);
  tree->Branch("bjet2eta"   ,  &bjet2eta_   ,   "bjet2eta/F"	);
  tree->Branch("bjet1phi"   ,  &bjet1phi_   ,   "bjet1phi/F"	);
  tree->Branch("bjet2phi"   ,  &bjet2phi_   ,   "bjet2phi/F"	);
  tree->Branch("genjetb1pt"     ,  &genjetb1pt_     ,   "genjetb1pt/F"	);
  tree->Branch("genjetb2pt"     ,  &genjetb2pt_     ,   "genjetb2pt/F"	);
  tree->Branch("genjetb1eta"    ,  &genjetb1eta_    ,   "genjetb1eta/F"	);
  tree->Branch("genjetb2eta"    ,  &genjetb2eta_    ,   "genjetb2eta/F"	);
  tree->Branch("genjetb1phi"    ,  &genjetb1phi_    ,   "genjetb1phi/F"	);
  tree->Branch("genjetb2phi"    ,  &genjetb2phi_    ,   "genjetb2phi/F"	);
  tree->Branch("genjetb1recopt"  ,  &genjetb1recopt_  ,   "genjetb1recopt/F"	);
  tree->Branch("genjetb2recopt"  ,  &genjetb2recopt_  ,   "genjetb2recopt/F"	);
  tree->Branch("genjetb1tag"    ,  &genjetb1tag_    ,   "genjetb1tag/I"	);
  tree->Branch("genjetb2tag"    ,  &genjetb2tag_    ,   "genjetb2tag/I"	);
  tree->Branch("st"         ,  &st_         ,   "st/F"		);
  tree->Branch("stlep"      ,  &stlep_      ,   "stlep/F"	);
  tree->Branch("genweight"   ,  &genweight_   ,   "genweight/F"	);
  tree->Branch("xsec"       ,  &xsec_       ,   "xsec/F"	);
  tree->Branch("nevents"    ,  &nevents_    ,   "nevents/I"	);
  tree->Branch("weight"     ,  &weight_     ,   "weight/F"	);
  tree->Branch("nw"         ,  &nw_         ,   "nw/I"		);
  tree->Branch("nh"         ,  &nh_         ,   "nh/I"		);
  tree->Branch("nz"         ,  &nz_         ,   "nz/I"		);
  tree->Branch("ntop"       ,  &ntop_       ,   "ntop/I"	);
  tree->Branch("mt"         ,  &mt_         ,   "mt/F"		);
  tree->Branch("mct"        ,  &mct_        ,   "mct/F"		);
  tree->Branch("mbb"        ,  &mbb_        ,   "mbb/F"		);
  tree->Branch("ptbb"       ,  &ptbb_       ,   "ptbb/F"	);
  tree->Branch("drbb"       ,  &drbb_       ,   "drbb/F"	);
  tree->Branch("drbbgen"    ,  &drbbgen_    ,   "drbbgen/F"	);
  tree->Branch("pthgen"     ,  &pthgen_     ,   "pthgen/F"	);
  tree->Branch("ptc1gen"    ,  &ptc1gen_    ,   "ptc1gen/F"	);
  tree->Branch("genlep1pt"  ,  &genlep1pt_  ,   "genlep1pt/F"	);
  tree->Branch("genlep1eta" ,  &genlep1eta_ ,   "genlep1eta/F"	);
  tree->Branch("genb1pt"    ,  &genb1pt_    ,   "genb1pt/F"	);
  tree->Branch("genb1eta"   ,  &genb1eta_   ,   "genb1eta/F"	);
  tree->Branch("genb2pt"    ,  &genb2pt_    ,   "genb2pt/F"	);
  tree->Branch("genb2eta"   ,  &genb2eta_   ,   "genb2eta/F"	);
  tree->Branch("lep1pt"     ,  &lep1pt_     ,   "lep1pt/F"	);
  tree->Branch("lep1phi"    ,  &lep1phi_    ,   "lep1phi/F"	);
  tree->Branch("lep1eta"    ,  &lep1eta_    ,   "lep1eta/F"	);
  tree->Branch("lep1iso"    ,  &lep1iso_    ,   "lep1iso/F"	);
  tree->Branch("lep1genpt"  ,  &lep1genpt_  ,   "lep1genpt/F"	);
  tree->Branch("lep2pt"     ,  &lep2pt_     ,   "lep2pt/F"	);
  tree->Branch("lep2phi"    ,  &lep2phi_    ,   "lep2phi/F"	);
  tree->Branch("lep2eta"    ,  &lep2eta_    ,   "lep2eta/F"	);
  tree->Branch("lep2iso"    ,  &lep2iso_    ,   "lep2iso/F"	);
  tree->Branch("leptype"    ,  &leptype_    ,   "leptype/I"	);
  tree->Branch("mchi"       ,  &mchi_       ,   "mchi/I"	);
  tree->Branch("mlsp"       ,  &mlsp_       ,   "mlsp/I"	);
  tree->Branch("mwgen"      ,  &mwgen_      ,   "mwgen/F"	);
  tree->Branch("mtwgen"     ,  &mtwgen_     ,   "mtwgen/F"	);
  tree->Branch("mttgen"     ,  &mttgen_     ,   "mttgen/F"	);
  tree->Branch("ptttgen"    ,  &ptttgen_    ,   "ptttgen/F"	);
  tree->Branch("genmet"     ,  &genmet_     ,   "genmet/F"	);
  tree->Branch("genmetphi"  ,  &genmetphi_  ,   "genmetphi/F"	);
  tree->Branch("pujetmet"   ,  &pujetmet_   ,   "pujetmet/F"	);
  tree->Branch("pujetmetphi",  &pujetmetphi_,   "pujetmetphi/F"	);
  tree->Branch("pujetmt"    ,  &pujetmt_    ,   "pujetmt/F"	);
  tree->Branch("puppimet"   ,  &puppimet_   ,   "puppimet/F"	);
  tree->Branch("puppimetphi",  &puppimetphi_,   "puppimetphi/F"	);
  tree->Branch("puppimt"    ,  &puppimt_    ,   "puppimt/F"	);
  tree->Branch("phot1pt"    ,  &phot1pt_    ,   "phot1pt/F"	);
  tree->Branch("phot1phi"   ,  &phot1phi_   ,   "phot1phi/F"	);
  tree->Branch("phot1eta"   ,  &phot1eta_   ,   "phot1eta/F"	);
  tree->Branch("phot1iso"   ,  &phot1iso_   ,   "phot1iso/F"	);
  tree->Branch("bgweight"   ,  &bgweight_   ,   "bgweight/F"	);
  tree->Branch("prodcode"   ,  &prodcode_   ,   "prodcode/I"	);

  // puppi versions of everything..
  tree->Branch("nb_puppi"         ,  &nb_puppi_         ,   "nb_puppi/I"		);
  tree->Branch("njets_puppi"      ,  &njets_puppi_      ,   "njets_puppi/I"	);
  tree->Branch("njets40_puppi"    ,  &njets40_puppi_    ,   "njets40_puppi/I"	);
  tree->Branch("njets50_puppi"    ,  &njets50_puppi_    ,   "njets50_puppi/I"	);
  tree->Branch("njets100_puppi"   ,  &njets100_puppi_   ,   "njets100_puppi/I"	);
  tree->Branch("njetsfwd_puppi"   ,  &njetsfwd_puppi_   ,   "njetsfwd_puppi/I"	);
  tree->Branch("njetsfwd40_puppi" ,  &njetsfwd40_puppi_ ,   "njetsfwd40_puppi/I"	);
  tree->Branch("njetsfwd50_puppi" ,  &njetsfwd50_puppi_ ,   "njetsfwd50_puppi/I"	);
  tree->Branch("njetsfwd100_puppi",  &njetsfwd100_puppi_,   "njetsfwd100_puppi/I"	);
  tree->Branch("jet1pt_puppi"     ,  &jet1pt_puppi_     ,   "jet1pt_puppi/F"	);
  tree->Branch("jet2pt_puppi"     ,  &jet2pt_puppi_     ,   "jet2pt_puppi/F"	);
  tree->Branch("jet3pt_puppi"     ,  &jet3pt_puppi_     ,   "jet3pt_puppi/F"	);
  tree->Branch("jet4pt_puppi"     ,  &jet4pt_puppi_     ,   "jet4pt_puppi/F"	);
  tree->Branch("jet1eta_puppi"    ,  &jet1eta_puppi_    ,   "jet1eta_puppi/F"	);
  tree->Branch("jet2eta_puppi"    ,  &jet2eta_puppi_    ,   "jet2eta_puppi/F"	);
  tree->Branch("jet3eta_puppi"    ,  &jet3eta_puppi_    ,   "jet3eta_puppi/F"	);
  tree->Branch("jet4eta_puppi"    ,  &jet4eta_puppi_    ,   "jet4eta_puppi/F"	);
  tree->Branch("jet1phi_puppi"    ,  &jet1phi_puppi_    ,   "jet1phi_puppi/F"	);
  tree->Branch("jet2phi_puppi"    ,  &jet2phi_puppi_    ,   "jet2phi_puppi/F"	);
  tree->Branch("jet3phi_puppi"    ,  &jet3phi_puppi_    ,   "jet3phi_puppi/F"	);
  tree->Branch("jet4phi_puppi"    ,  &jet4phi_puppi_    ,   "jet4phi_puppi/F"	);
  tree->Branch("jet1genpt_puppi"  ,  &jet1genpt_puppi_  ,   "jet1genpt_puppi/F"	);
  tree->Branch("jet2genpt_puppi"  ,  &jet2genpt_puppi_  ,   "jet2genpt_puppi/F"	);
  tree->Branch("jet3genpt_puppi"  ,  &jet3genpt_puppi_  ,   "jet3genpt_puppi/F"	);
  tree->Branch("jet4genpt_puppi"  ,  &jet4genpt_puppi_  ,   "jet4genpt_puppi/F"	);
  tree->Branch("bjet1pt_puppi"    ,  &bjet1pt_puppi_    ,   "bjet1pt_puppi/F"	);
  tree->Branch("bjet2pt_puppi"    ,  &bjet2pt_puppi_    ,   "bjet2pt_puppi/F"	);
  tree->Branch("bjet1eta_puppi"   ,  &bjet1eta_puppi_   ,   "bjet1eta_puppi/F"	);
  tree->Branch("bjet2eta_puppi"   ,  &bjet2eta_puppi_   ,   "bjet2eta_puppi/F"	);
  tree->Branch("bjet1phi_puppi"   ,  &bjet1phi_puppi_   ,   "bjet1phi_puppi/F"	);
  tree->Branch("bjet2phi_puppi"   ,  &bjet2phi_puppi_   ,   "bjet2phi_puppi/F"	);
  tree->Branch("mct_puppi"        ,  &mct_puppi_        ,   "mct_puppi/F"		);
  tree->Branch("mbb_puppi"        ,  &mbb_puppi_        ,   "mbb_puppi/F"		);
  tree->Branch("ptbb_puppi"       ,  &ptbb_puppi_       ,   "ptbb_puppi/F"	);
  tree->Branch("drbb_puppi"       ,  &drbb_puppi_       ,   "drbb_puppi/F"	);

  //-----------------------------------------------------------------------
  // Create chain of root trees, add appropriate files
  //-----------------------------------------------------------------------

  if (isSignal) xsec_ = 1.;
  else xsec_    = getCrossSection( prefix );

  TChain chain("Delphes");

  // load signal samples
  if( false ){
    //  if( isSignal ){
    char* sigfile = Form("signalSamples/%s.root",prefix.c_str());
    cout << "Loading signal sample " << sigfile << endl;
    chain.Add( sigfile );
  }

  // load list of background samples
  else{
    vector<string> filepaths = fileNames( prefix , nfiles, part );
    
    cout << "Loading " << filepaths.size() << " files" << endl;
    
    for( unsigned int i = 0 ; i < filepaths.size() ; i++ ){
      //cout << "Adding " << filepaths.at(i) << endl;
      chain.Add(filepaths.at(i).c_str());
    }
  }

  nevents_ = chain.GetEntries();

  weight_  = xsec_ / (float) nevents_;
  if (!isSignal) cout << "xsec nevents weight " << xsec_ << " " << nevents_ << " " << weight_ << endl;

  mchi_ = -1;
  mlsp_ = -1;

  // init tool for naturalModel k factors
  McTruthInfo geninfo; //initialize once
  geninfo.setNloKFactor_fromfileName(TString(prefix));


  //--------------------------------------------------------------
  // Book histograms
  //--------------------------------------------------------------
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  TH1 *histJetPT  = new TH1F("jet_pt"  , "jet P_{T} [GeV]"              , 100  , 0.0  , 500.0);
  //TH1 *histMass   = new TH1F("mass"    , "M_{inv}(e_{1}, e_{2}) [GeV]"  , 100  , 40.0 , 140.0);
  TH1 *histMet    = new TH1F("met"     , "E_{T}^{miss} [GeV]"           , 100  , 0.0  , 2000.0);
  TH1 *histHT     = new TH1F("ht"      , "H_{T} [GeV]"                  , 100  , 0.0  , 20000.0);
  TH1 *histNjets  = new TH1F("njets"   , "N_{jets}"                     , 10   , 0    , 10);
  TH1 *histSt     = new TH1F("st"      , "S_{T} [GeV]"                  , 2000 , 0    , 20000);
  TH1 *histStLO   = new TH1F("stlo"    , "S_{T} [GeV]"                  , 2000 , 0    , 20000);
  TH1 *histWeight = new TH1F("weight"  , "event weight"                 , 100  , 0    , 100);

  //--------------------------------------------------------------
  // loop over chains
  //--------------------------------------------------------------

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  int nEventsTotal = 0;

  //--------------------------------------------------------------
  // Get pointers to branches used in this analysis
  //--------------------------------------------------------------

  TClonesArray *branchEvent     = treeReader->UseBranch("Event");
  TClonesArray *branchParticle  = treeReader->UseBranch("Particle");
  TClonesArray *branchJet       = treeReader->UseBranch("Jet");
  TClonesArray *branchPuppiJet  = treeReader->UseBranch("PuppiJet");
  TClonesArray *branchElectron  = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon      = treeReader->UseBranch("Muon");
  TClonesArray *branchPhoton    = treeReader->UseBranch("Photon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchScalarHT  = treeReader->UseBranch("ScalarHT");
  TClonesArray *branchGenJet    = treeReader->UseBranch("GenJet");
  TClonesArray *branchPUJetMissingET = treeReader->UseBranch("PileUpJetIDMissingET");
  TClonesArray *branchPuppiMissingET = treeReader->UseBranch("PuppiMissingET");

  TString currentFile = "";

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
  //for(Int_t entry = 0; entry < 100; ++entry){

    InitVars();

    nEventsTotal++;

    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    // progress feedback to user
    if (nEventsTotal % 1000 == 0){
      
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)){
	
	printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
	       "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(numberOfEntries*0.01));
	fflush(stdout);
      }
    }

    if( nEventsTotal % 10000 == 0 ){
      cout << "Processed " << nEventsTotal << " events" << endl;
    }

    //--------------------------------------------
    // select WZ events from diboson background
    //--------------------------------------------

    /*
    if( !isSignal && TString(prefix).Contains("BB-4p")  ){

      int nW = 0;
      int nZ = 0;

      for( int ip = 0 ; ip < branchParticle->GetEntries() ; ip++ ){
	GenParticle* p = (GenParticle*) branchParticle->At(ip);
	if( abs( p->PID ) == 24 ) nW++;
	if( abs( p->PID ) == 23 ) nZ++;
      }

      if( nW==1 && nZ==1){
	//cout << "Found WZ event" << endl;
      }

      else{
	continue;
      }
    }
    */

    //----------------------------------------
    // get gen masses for signal files
    //----------------------------------------

    // update signal mass point at each new file
    //    if (isSignal && (!currentFile.EqualTo(chain.GetFile()->GetName()) ) ) {
    if ( !currentFile.EqualTo(chain.GetFile()->GetName()) ) {
      currentFile = TString(chain.GetFile()->GetName());
      TString fullname(currentFile);
      std::cout << "-- switched to file: " << fullname << std::endl;
      if (isSignal && (prefix.find("TChiWH") != string::npos)) {
	TString shortname(fullname);
	shortname.Remove(0,shortname.Last('/')+1);
	// assumes name of form "TChiwh_500_1_0_NoPileUp.root"
	TString masses_string(shortname);
	masses_string.Remove(0,masses_string.First('_')+1);
	Ssiz_t split = masses_string.First('_');
	TString mchi_string(masses_string);
	mchi_string.Remove(split);
	TString mlsp_string(masses_string);
	mlsp_string.Remove(0,split+1);
	mlsp_string.Remove(mlsp_string.First('_'));
	std::cout	<< "   found mchi = " << mchi_string << ", mlsp = " << mlsp_string << std::endl;
	mchi_ = mchi_string.Atoi();
	mlsp_ = mlsp_string.Atoi();

	// xsec stored in pb, mult by 1000 for fb
	xsec_ = h_c1n2_xsec->GetBinContent(h_c1n2_xsec->FindBin(mchi_)) * 1000. * 0.56 * 0.33;
	nevents_ = (int) h_nsig->GetBinContent(h_nsig->FindBin(mchi_,mlsp_));
	weight_  = xsec_ / (float) nevents_;
	std::cout << "   xsec nevents weight " << xsec_ << " " << nevents_ << " " << weight_ << std::endl;
      } // if signal
    } // if file changed

    // nlo kfactor for naturalModels
    if (isSignal && (prefix.find("naturalModel2") != string::npos)) {
      xsec_ = 0.05 * 1000.; // 0.05 pb -> fb
      geninfo.Set(branchParticle);
      prodcode_ = geninfo.getSusyProductionProcess();
      double kfactor=geninfo.getNloKFactor(prodcode_);
      //std::cout << "- process code: " << prodcode_ << ", kfactor: " << kfactor << std::endl;
      xsec_ *= kfactor;
      weight_  = xsec_ / (float) nevents_;
    }

    //----------------------------------------
    // event weight
    //----------------------------------------

    genweight_ = 1.0;
    LHEFEvent* myevent = (LHEFEvent*) branchEvent->At(0);
    if( isSignal ) genweight_ = 1.0;
    else           genweight_ = myevent->Weight;
    histWeight->Fill(genweight_);

    //----------------------------------------
    // lepton counting / pt ordering
    // -- must do first to do overlap removal on jets
    //----------------------------------------

    const float iso_cut = 0.2;

    std::vector<unsigned int> els_idx;
    for( int iel = 0 ; iel < branchElectron->GetEntries() ; iel++ ){
      Electron* el = (Electron*) branchElectron->At(iel);
      if (el->IsolationVar > iso_cut) continue;
      stlep_ += el->PT;
      if( el->PT > 10.0 ) els_idx.push_back(iel);
      //      cout << "Electron " << iel << " " << el->PT  << endl;
    }
    nels_ = els_idx.size();

    std::vector<unsigned int> mus_idx;
    for( int imu = 0 ; imu < branchMuon->GetEntries() ; imu++ ){
      Muon* mu = (Muon*) branchMuon->At(imu);
      if (mu->IsolationVar > iso_cut) continue;
      stlep_ += mu->PT;
      if( mu->PT > 10.0 ) mus_idx.push_back(imu);
      //      cout << "Muon " << imu << " " << mu->PT  << endl;
    }
    nmus_ = mus_idx.size();

    nleps_ = nels_ + nmus_;
    TLorentzVector lep1p4;
    TLorentzVector lep2p4;

    if( nleps_ == 1 ){

      if( nels_ == 1 ){
	Electron* el = (Electron *) branchElectron->At(els_idx.at(0));
	leptype_ = 0;
	lep1pt_  = el->PT;
	lep1eta_ = el->Eta;
	lep1phi_ = el->Phi;
	lep1iso_ = el->IsolationVar;
	lep1p4 = el->P4();
      }

      else if( nmus_ == 1 ){
	Muon* mu = (Muon *) branchMuon->At(mus_idx.at(0));
	leptype_ = 1;
	lep1pt_  = mu->PT;
	lep1eta_ = mu->Eta;
	lep1phi_ = mu->Phi;
	lep1iso_ = mu->IsolationVar;
	lep1p4 = mu->P4();
      }
      
      else{ 
	cout << "Couldn't find lepton in 1lep event!" << endl;
	exit(0);
      }

    } // nleps == 1

    else if( nleps_ == 2 ){

      if( nels_ == 2 ){
	Electron* el1 = (Electron *) branchElectron->At(els_idx.at(0));
	leptype_ = 0;
	lep1pt_  = el1->PT;
	lep1eta_ = el1->Eta;
	lep1phi_ = el1->Phi;
	lep1iso_ = el1->IsolationVar;
	lep1p4   = el1->P4();

	Electron* el2 = (Electron *) branchElectron->At(els_idx.at(1));
	lep2pt_  = el2->PT;
	lep2eta_ = el2->Eta;
	lep2phi_ = el2->Phi;
	lep2iso_ = el2->IsolationVar;
	lep2p4   = el2->P4();
      } // ee

      else if( nmus_ == 2 ){
	Muon* mu1 = (Muon *) branchMuon->At(mus_idx.at(0));
	leptype_ = 1;
	lep1pt_  = mu1->PT;
	lep1eta_ = mu1->Eta;
	lep1phi_ = mu1->Phi;
	lep1iso_ = mu1->IsolationVar;
	lep1p4   = mu1->P4();

	Muon* mu2 = (Muon *) branchMuon->At(mus_idx.at(1));
	lep2pt_  = mu2->PT;
	lep2eta_ = mu2->Eta;
	lep2phi_ = mu2->Phi;
	lep2iso_ = mu2->IsolationVar;
	lep2p4   = mu2->P4();
      } // mumu
      
      else if( (nels_ == 1) && (nmus_ == 1) ){
	Electron* el = (Electron *) branchElectron->At(els_idx.at(0));
	Muon* mu = (Muon *) branchMuon->At(mus_idx.at(0));

	if (el->PT > mu->PT) {
	  leptype_ = 0;
	  lep1pt_  = el->PT;
	  lep1eta_ = el->Eta;
	  lep1phi_ = el->Phi;
	  lep1iso_ = el->IsolationVar;
	  lep1p4   = el->P4();

	  lep2pt_  = mu->PT;
	  lep2eta_ = mu->Eta;
	  lep2phi_ = mu->Phi;
	  lep2iso_ = mu->IsolationVar;
	  lep2p4   = mu->P4();
	} else {
	  leptype_ = 1;
	  lep1pt_  = mu->PT;
	  lep1eta_ = mu->Eta;
	  lep1phi_ = mu->Phi;
	  lep1iso_ = mu->IsolationVar;
	  lep1p4   = mu->P4();

	  lep2pt_  = el->PT;
	  lep2eta_ = el->Eta;
	  lep2phi_ = el->Phi;
	  lep2iso_ = el->IsolationVar;
  	  lep2p4   = el->P4();
	}
      } // emu
      
      else{ 
	cout << "Couldn't find leptons in 2lep event!" << endl;
	exit(0);
      }

    } // nleps == 2

    //----------------------------------------
    // loop on photons
    //----------------------------------------

    // only save leading isolated photon
    std::vector<unsigned int> phs_idx;
    for( int iph = 0 ; iph < branchPhoton->GetEntries() ; iph++ ){
      Photon* ph = (Photon*) branchPhoton->At(iph);
      if (ph->IsolationVar > iso_cut) continue;
      phot1pt_  = ph->PT;
      phot1eta_ = ph->Eta;
      phot1phi_ = ph->Phi;
      phot1iso_ = ph->IsolationVar;
      //      cout << "Photon " << iph << " " << ph->PT  << endl;
      break;
    }

    //----------------------------------------
    // PU Jet ID cuts
    //----------------------------------------

    // bar: |eta| < 1.5
    // ec: 1.5 <= |eta| < 2.4
    // fwd: 2.4 <= |eta| < 4.0
    // vfwd: |eta| >= 4.0

    // values from Jul31..
    float cut_beta_bar = 0.13;
    float cut_beta_ec = 0.15;
    float cut_beta_fwd = 0.0;
    float cut_meansqdr_bar = 0.07;
    float cut_meansqdr_ec = 0.07;
    float cut_meansqdr_fwd = 0.07;
    float cut_meansqdr_vfwd = 0.01;
    if (hasFwdTrk) {
      cut_beta_fwd = 0.15;
    }

    // // old values, not sure where these came from..
    // float cut_beta_bar = 0.07;
    // float cut_beta_ec = 0.06;
    // float cut_beta_fwd = 0.0;
    // float cut_meansqdr_bar = 0.13;
    // float cut_meansqdr_ec = 0.07;
    // float cut_meansqdr_fwd = 0.07;
    // float cut_meansqdr_vfwd = 0.01;
    // if (hasFwdTrk) {
    //   cut_beta_fwd = 0.06;
    // }

    //----------------------------------------
    // get leading jet pt and njets
    //----------------------------------------

    unsigned int njetsall = 0;
    int ib1 = -1;
    int ib2 = -1;
    int ij1 = -1;
    int ij2 = -1;

    std::vector<TLorentzVector> saved_jets;

    for( int ijet = 0 ; ijet < branchJet->GetEntries() ; ijet++ ) {
      Jet *jet = (Jet*) branchJet->At(ijet);
      // first check for overlap with leptons
      bool overlap = false;
      for( unsigned int iel = 0 ; iel < els_idx.size() ; iel++ ){
      	Electron* el = (Electron*) branchElectron->At(iel);
      	if (jet->P4().DeltaR(el->P4()) < 0.4) {
	  overlap = true;
	  break;
	}
      } 
      if (overlap) continue;
      for( unsigned int imu = 0 ; imu < mus_idx.size() ; imu++ ){
      	Muon* mu = (Muon*) branchMuon->At(imu);
      	if (jet->P4().DeltaR(mu->P4()) < 0.4) {
	  overlap = true;
	  break;
	}
      } 
      if (overlap) continue;

      // check overlap with previously saved jets
      bool jet_overlap = false;
      for (unsigned int ijet2 = 0; ijet2 < saved_jets.size(); ++ijet2) {
	if (jet->P4().DeltaR(saved_jets.at(ijet2)) < 0.01) {
	  std::cout << "WARNING: JET OVERLAP: jet1 pt: " << saved_jets.at(ijet2).Pt()
		    << ", eta: " << saved_jets.at(ijet2).Eta() << ", phi: " << saved_jets.at(ijet2).Phi()
		    << ",   jet 2 pt: " << jet->PT << ", eta: " << jet->Eta << ", phi: " << jet->Phi
		    << std::endl;
	  jet_overlap = true;
	}
      }
      if (jet_overlap) continue;

      // check PU ID cuts
      float eta = jet->Eta;
      float beta = jet->Beta;
      float meansqdr = jet->MeanSqDeltaR;

      const bool doPUJetID = false;
      if (doPUJetID) {
	if (fabs(eta) < 1.5) {
	  if (beta <= cut_beta_bar) continue;
	  if (meansqdr >= cut_meansqdr_bar) continue;
	} else if (fabs(eta) < 2.4) {
	  if (beta <= cut_beta_ec) continue;
	  if (meansqdr >= cut_meansqdr_ec) continue;
	} else if (fabs(eta) < 4.0) {
	  if (beta <= cut_beta_fwd) continue;
	  if (meansqdr >= cut_meansqdr_fwd) continue;
	} else {
	  if (meansqdr >= cut_meansqdr_vfwd) continue;
	}
      }

      // require min jet pt cut for rest of loop
      if (jet->PT < 30.) continue;
      saved_jets.push_back(jet->P4());

      ++njetsall;
      if ( fabs(jet->Eta) < 2.4 ) {
	if( jet->PT > 30  ) njets_++;
	if( jet->PT > 40  ) njets40_++;
	if( jet->PT > 50  ) njets50_++;
	if( jet->PT > 100 ) njets100_++;
      }
      else {
	if( jet->PT > 30  ) njetsfwd_++;
	if( jet->PT > 40  ) njetsfwd40_++;
	if( jet->PT > 50  ) njetsfwd50_++;
	if( jet->PT > 100 ) njetsfwd100_++;
      }

      // find matching gen jet
      float genjetpt = -1.;
      // for( int igjet = 0 ; igjet < branchGenJet->GetEntries() ; igjet++ ){
      // 	Jet* genjet = (Jet*) branchGenJet->At(igjet);
      // 	if (genjet->P4().DeltaR(jet->P4()) < 0.4) {
      // 	  genjetpt = genjet->PT;
      // 	  break;
      // 	}
      // }

      if (njetsall == 1) {
	jet1pt_  = jet->PT;
	jet1eta_ = jet->Eta;
	jet1phi_ = jet->Phi;
	histJetPT->Fill(jet1pt_,weight_*genweight_);
	jet1genpt_ = genjetpt;
	ij1 = ijet;
      } else if (njetsall == 2) {
	jet2pt_  = jet->PT;
	jet2eta_ = jet->Eta;
	jet2phi_ = jet->Phi;
	jet2genpt_ = genjetpt;
	ij2 = ijet;
      } else if (njetsall == 3) {
	jet3pt_  = jet->PT;
	jet3eta_ = jet->Eta;
	jet3phi_ = jet->Phi;
	jet3genpt_ = genjetpt;
      } else if (njetsall == 4) {
	jet4pt_  = jet->PT;
	jet4eta_ = jet->Eta;
	jet4phi_ = jet->Phi;
	jet4genpt_ = genjetpt;
      } 

      // check for b-tagged jets
      if (jet->PT < 30. || fabs(eta) > 2.4) continue;
      if( jet->BTag & (1 << 1) ){ 
	nb_++; 
	if     ( ib1 < 0 ) ib1 = ijet;
	else if( ib2 < 0 ) ib2 = ijet;
      }

    }

    if( (nb_ > 1) && (ib1 == ib2) ) {
      cout << "WARNING: two b-jets with same index!!!! dumping jets" << endl;
      for (unsigned int ijet = 0; ijet < saved_jets.size(); ++ijet) {
	std::cout << "-- jet " << ijet << ": pt: " << saved_jets.at(ijet).Pt()
		  << ", eta: " << saved_jets.at(ijet).Eta() << ", phi: " << saved_jets.at(ijet).Phi()
		  << std::endl;
      }
    } // check for bjet duplicates

    histNjets->Fill(njets_,weight_*genweight_);

    //----------------------------------------
    // repeat for PUPPI jets
    //----------------------------------------

    unsigned int njetsall_puppi = 0;
    int ib1_puppi = -1;
    int ib2_puppi = -1;
    int ij1_puppi = -1;
    int ij2_puppi = -1;

    std::vector<TLorentzVector> saved_jets_puppi;

    for( int ijet = 0 ; ijet < branchPuppiJet->GetEntries() ; ijet++ ) {
      Jet *jet = (Jet*) branchPuppiJet->At(ijet);
      // first check for overlap with leptons
      bool overlap = false;
      for( unsigned int iel = 0 ; iel < els_idx.size() ; iel++ ){
      	Electron* el = (Electron*) branchElectron->At(iel);
      	if (jet->P4().DeltaR(el->P4()) < 0.4) {
	  overlap = true;
	  break;
	}
      } 
      if (overlap) continue;
      for( unsigned int imu = 0 ; imu < mus_idx.size() ; imu++ ){
      	Muon* mu = (Muon*) branchMuon->At(imu);
      	if (jet->P4().DeltaR(mu->P4()) < 0.4) {
	  overlap = true;
	  break;
	}
      } 
      if (overlap) continue;

      // check overlap with previously saved jets
      bool jet_overlap = false;
      for (unsigned int ijet2 = 0; ijet2 < saved_jets_puppi.size(); ++ijet2) {
	if (jet->P4().DeltaR(saved_jets_puppi.at(ijet2)) < 0.01) {
	  std::cout << "WARNING: PUPPI JET OVERLAP: jet1 pt: " << saved_jets_puppi.at(ijet2).Pt()
		    << ", eta: " << saved_jets_puppi.at(ijet2).Eta() << ", phi: " << saved_jets_puppi.at(ijet2).Phi()
		    << ",   jet 2 pt: " << jet->PT << ", eta: " << jet->Eta << ", phi: " << jet->Phi
		    << std::endl;
	  jet_overlap = true;
	}
      }
      if (jet_overlap) continue;

      // // check PU ID cuts -- not for Puppi jets??
      // float eta = jet->Eta;
      // float beta = jet->Beta;
      // float meansqdr = jet->MeanSqDeltaR;
      // if (fabs(eta) < 1.5) {
      // 	if (beta <= cut_beta_bar) continue;
      // 	if (meansqdr >= cut_meansqdr_bar) continue;
      // } else if (fabs(eta) < 2.4) {
      // 	if (beta <= cut_beta_ec) continue;
      // 	if (meansqdr >= cut_meansqdr_ec) continue;
      // } else if (fabs(eta) < 4.0) {
      // 	if (beta <= cut_beta_fwd) continue;
      // 	if (meansqdr >= cut_meansqdr_fwd) continue;
      // } else {
      // 	if (meansqdr >= cut_meansqdr_vfwd) continue;
      // }

      // require min jet pt cut for rest of loop
      if (jet->PT < 30.) continue;
      saved_jets_puppi.push_back(jet->P4());

      ++njetsall_puppi;
      if ( fabs(jet->Eta) < 2.4 ) {
	if( jet->PT > 30  ) njets_puppi_++;
	if( jet->PT > 40  ) njets40_puppi_++;
	if( jet->PT > 50  ) njets50_puppi_++;
	if( jet->PT > 100 ) njets100_puppi_++;
      }
      else {
	if( jet->PT > 30  ) njetsfwd_puppi_++;
	if( jet->PT > 40  ) njetsfwd40_puppi_++;
	if( jet->PT > 50  ) njetsfwd50_puppi_++;
	if( jet->PT > 100 ) njetsfwd100_puppi_++;
      }

      // find matching gen jet
      float genjetpt = -1.;
      // for( int igjet = 0 ; igjet < branchGenJet->GetEntries() ; igjet++ ){
      // 	Jet* genjet = (Jet*) branchGenJet->At(igjet);
      // 	if (genjet->P4().DeltaR(jet->P4()) < 0.4) {
      // 	  genjetpt = genjet->PT;
      // 	  break;
      // 	}
      // }

      if (njetsall_puppi == 1) {
	jet1pt_puppi_  = jet->PT;
	jet1eta_puppi_ = jet->Eta;
	jet1phi_puppi_ = jet->Phi;
	jet1genpt_puppi_ = genjetpt;
	ij1_puppi = ijet;
      } else if (njetsall_puppi == 2) {
	jet2pt_puppi_  = jet->PT;
	jet2eta_puppi_ = jet->Eta;
	jet2phi_puppi_ = jet->Phi;
	jet2genpt_puppi_ = genjetpt;
	ij2_puppi = ijet;
      } else if (njetsall_puppi == 3) {
	jet3pt_puppi_  = jet->PT;
	jet3eta_puppi_ = jet->Eta;
	jet3phi_puppi_ = jet->Phi;
	jet3genpt_puppi_ = genjetpt;
      } else if (njetsall_puppi == 4) {
	jet4pt_puppi_  = jet->PT;
	jet4eta_puppi_ = jet->Eta;
	jet4phi_puppi_ = jet->Phi;
	jet4genpt_puppi_ = genjetpt;
      } 

      // check for b-tagged jets
      if (jet->PT < 30. || fabs(jet->Eta) > 2.4) continue;
      if( jet->BTag & (1 << 1) ){ 
	nb_puppi_++; 
	if     ( ib1_puppi < 0 ) ib1_puppi = ijet;
	else if( ib2_puppi < 0 ) ib2_puppi = ijet;
      }

    }

    if( (nb_puppi_ > 1) && (ib1_puppi == ib2_puppi) ) {
      cout << "WARNING: two puppi b-jets with same index!!!! dumping jets" << endl;
      for (unsigned int ijet = 0; ijet < saved_jets_puppi.size(); ++ijet) {
	std::cout << "-- jet " << ijet << ": pt: " << saved_jets_puppi.at(ijet).Pt()
		  << ", eta: " << saved_jets_puppi.at(ijet).Eta() << ", phi: " << saved_jets_puppi.at(ijet).Phi()
		  << std::endl;
      }
    } // check for bjet duplicates

    //----------------------------------------
    // number of pt > 30 GeV gen jets
    //----------------------------------------

    for( int igjet = 0 ; igjet < branchGenJet->GetEntries() ; igjet++ ){
      Jet* genjet = (Jet*) branchGenJet->At(igjet);
      //cout << i << " " << Form("%.1f",jet->PT) << " " << Form("%.2f",jet->Eta) << endl;
      if ( abs(genjet->Eta) < 2.4 ) {
	if( genjet->PT > 30 ) ngenjets_++;
      }
      else {
	if( genjet->PT > 30 ) ngenjetsfwd_++;
      }
    }
    
    //----------------------------------------
    // missing et
    //----------------------------------------

    MissingET* met = (MissingET*) branchMissingET->At(0);
    met_ = met->MET;
    metphi_ = met->Phi;
    histMet->Fill(met_,weight_*genweight_);

    //----------------------------------------
    // PUJet missing et
    //----------------------------------------

    MissingET* pujetmet = (MissingET*) branchPUJetMissingET->At(0);
    pujetmet_ = pujetmet->MET;
    pujetmetphi_ = pujetmet->Phi;

    //----------------------------------------
    // PUJet missing et
    //----------------------------------------

    MissingET* puppimet = (MissingET*) branchPuppiMissingET->At(0);
    puppimet_ = puppimet->MET;
    puppimetphi_ = puppimet->Phi;

    //----------------------------------------
    // HT
    //----------------------------------------

    ScalarHT* ht = (ScalarHT*) branchScalarHT->At(0);
    ht_ = ht->HT;
    histHT->Fill(ht_,weight_*genweight_);

    //----------------------------------------
    // add leptons to get STlep
    //----------------------------------------

    st_ = met_ + ht_ + stlep_;

    histSt->Fill(st_,weight_*genweight_);
    histStLO->Fill(st_,weight_);

    //----------------------------------------
    // Count various types of particles
    //----------------------------------------
    
    int ibgen1 = -1;
    int ibgen2 = -1;
    int ilepgen1 = -1;
    int inugen1 = -1;
    int itgen = -1;
    int itbargen = -1;
    int nwplus = 0;
    int nwminus = 0;
    int ngamma = 0;
    int nnu = 0;
    TLorentzVector genmetp4;

    //cout << endl << endl;
    for( int ip = 0 ; ip < branchParticle->GetEntries() ; ip++ ){
      GenParticle* p = (GenParticle*) branchParticle->At(ip);

      if ( p->Status != 3 ) continue;

      // -- not sure what this is about.. Pythia8?
      // if( isSignal && ( p->Status < 20 || p->Status > 30 ) ) continue;

      if( abs( p->PID ) == 25 ){
	nh_++;
	pthgen_ = p->PT;
      }
      if( abs( p->PID ) == 24 ) {
	nw_++;
	mwgen_ = p->Mass;
	if (p->PID == 24) ++nwplus;
	else ++nwminus;
      }
      if( abs( p->PID ) == 23 ) nz_++;
      if( abs( p->PID ) == 22 ) ngamma++;
      if( abs( p->PID ) ==  6 ) {
	ntop_++;
	if ( p->PID == 6 ) itgen = ip;
	else if ( p->PID == -6 ) itbargen = ip;
      }
      if( abs( p->PID ) == 11 ) {
	ngenels_++;
	ilepgen1 = ip;
      }
      if( abs( p->PID ) == 13 ) {
	ngenmus_++;
	ilepgen1 = ip;
      }
      if( abs( p->PID ) == 15 ) ngentaus_++;
      if( abs( p->PID ) == 12 || abs( p->PID ) == 14 || abs( p->PID ) == 16 ) {
	++nnu;
	genmetp4 += p->P4();
	if( abs( p->PID ) == 12 || abs( p->PID ) == 14 ) {
	  inugen1 = ip;
	}
      }
      if( abs( p->PID ) == 1000024 ) ptc1gen_ = p->PT;
      if( abs( p->PID ) == 1000022 ) genmetp4 += p->P4();

      if( abs( p->PID ) ==  5 ){
	nbgen_++;
	if     ( ibgen1 < 0 ) ibgen1 = ip;
	else if( ibgen2 < 0 ) ibgen2 = ip;
      }

      if( abs( p->PID ) ==  4 ){
	++ncgen_;
      }

      //cout << ip << " ID " << p->PID << " status " << p->Status << endl;
    }

    if ( genmetp4.Pt() > 0. ) {
      genmet_ = genmetp4.Pt();
      genmetphi_ = genmetp4.Phi();
    }

    if( nbgen_ == 2 ){
      GenParticle* genb1 = (GenParticle*) branchParticle->At(ibgen1);      
      GenParticle* genb2 = (GenParticle*) branchParticle->At(ibgen2);      

      if (genb1->PT > genb2->PT) {
	genb1pt_ = genb1->PT;
	genb1eta_ = genb1->Eta;
	genb2pt_ = genb2->PT;
	genb2eta_ = genb2->Eta;
      } else {
	genb1pt_ = genb2->PT;
	genb1eta_ = genb2->Eta;
	genb2pt_ = genb1->PT;
	genb2eta_ = genb1->Eta;
      }

      float deta = genb1->Eta - genb2->Eta;
      float dphi = acos( cos ( genb1->Phi - genb2->Phi ) );
      drbbgen_ = sqrt( deta*deta + dphi*dphi );

      // // loop over gen jets and find matching jets
      // int ib1_gen = -1;
      // int ib2_gen = -1;
      // for( int igjet = 0 ; igjet < branchGenJet->GetEntries() ; igjet++ ){
      // 	Jet* genjet = (Jet*) branchGenJet->At(igjet);
      // 	float drb1 = genb1->P4().DeltaR(genjet->P4()); 
      // 	float drb2 = genb2->P4().DeltaR(genjet->P4()); 
      // 	if ((drb1 < 0.5) || (drb2 < 0.5)) {
      // 	  if     ( ib1_gen < 0 ) ib1 = igjet;
      // 	  else if( ib2_gen < 0 ) ib2 = igjet;
      // 	}
      // } // gen jet loop

      // if (ib1_gen >= 0) {
      // 	Jet* genjet = (Jet*) branchGenJet->At(ib1_gen);
      // 	genjetb1pt_  = genjet->PT;
      // 	genjetb1eta_ = genjet->Eta;
      // 	genjetb1phi_ = genjet->Phi;
      // 	for( int ijet = 0 ; ijet < branchJet->GetEntries() ; ijet++ ){
      // 	  Jet* jet = (Jet*) branchJet->At(ijet);
      // 	  if (genjet->P4().DeltaR(jet->P4()) < 0.5) {
      // 	    genjetb1recopt_ = jet->PT;
      // 	    genjetb1tag_ = ( jet->BTag & (1 << 1) ) ? 1 : 0;
      // 	    break;
      // 	  }
      // 	} // reco jet loop
      // } // gen jet 1

      // if (ib2_gen >= 0) {
      // 	Jet* genjet = (Jet*) branchGenJet->At(ib2_gen);
      // 	genjetb2pt_  = genjet->PT;
      // 	genjetb2eta_ = genjet->Eta;
      // 	genjetb2phi_ = genjet->Phi;
      // 	for( int ijet = 0 ; ijet < branchJet->GetEntries() ; ijet++ ){
      // 	  Jet* jet = (Jet*) branchJet->At(ijet);
      // 	  if (genjet->P4().DeltaR(jet->P4()) < 0.5) {
      // 	    genjetb2recopt_ = jet->PT;
      // 	    genjetb2tag_ = ( jet->BTag & (1 << 1) ) ? 1 : 0;
      // 	    break;
      // 	  }
      // 	} // reco jet loop
      // } // gen jet 2
    } // 2 gen b
 
    if ( nw_ >= 1 && ilepgen1 > -1 && inugen1 > -1 ) {
      GenParticle* genlep = (GenParticle*) branchParticle->At(ilepgen1);      
      GenParticle* gennu = (GenParticle*) branchParticle->At(inugen1);      

      genlep1pt_ = genlep->PT;
      genlep1eta_ = genlep->Eta;
      mtwgen_ = sqrt( 2 * gennu->PT * genlep->PT * ( 1 - cos( gennu->Phi - genlep->Phi) ) );
    }

    if ( itgen > -1 && itbargen > -1 ) {
      GenParticle* gent = (GenParticle*) branchParticle->At(itgen);      
      GenParticle* gentbar = (GenParticle*) branchParticle->At(itbargen);      

      mttgen_ = ( (gent->P4()) + (gentbar->P4()) ).M();
      ptttgen_ = ( (gent->P4()) + (gentbar->P4()) ).Pt();
    }

    ngenleps_ = ngenels_ + ngenmus_ + ngentaus_;

    // // BUGFIX for weights in ttbar and V+jets samples.. Jun14 version
    // // -- weights taken from: https://github.com/hatakeyamak/DelphesAnalysisTools/blob/master/DelWeight.cc
    // if (prefix.find("tt-4p") != string::npos) {
    //   if (ngenleps_ == 2) genweight_ = 0.38;
    //   else if (ngenleps_ == 1) genweight_ = 1.15;
    //   else genweight_ = 3.45;
    // } // bugfix for tt-4p sample
    // else if (prefix.find("Bj-4p") != string::npos) {
    //   if (nwplus == 1) {
    // 	if (ngenleps_ == 1) genweight_ = 0.65;
    // 	else genweight_ = 1.95;
    //   }
    //   else if (nwminus == 1) {
    // 	if (ngenleps_ == 1) genweight_ = 0.66;
    // 	else genweight_ = 2.00;
    //   }
    //   else if (nz_ == 1) {
    // 	if (ngenleps_ == 2) genweight_ = 0.445;
    // 	else if (nnu == 2) genweight_ = 0.885;
    // 	else genweight_ = 1.93;
    // 	// should technically be about 1.5 for up-type, 1.9x for down-type
    // 	// don't care for my analysis
    //   }
    //   else if (ngamma >= 1) {
    // 	genweight_ = 1.91;
    //   }
    // } // bugfix for Bj-4p sample

    //----------------------------------------
    // look at events with 2 b-jets
    //----------------------------------------

    if( nb_ >= 2 ){
      if( ib1 < 0 || ib2 < 0 ) cout << "Negative b-jet index" << endl;

      Jet* bjet1 = (Jet*) branchJet->At(ib1);      
      Jet* bjet2 = (Jet*) branchJet->At(ib2);      

      mbb_  = ( (bjet1->P4()) + (bjet2->P4()) ).M();
      ptbb_ = ( (bjet1->P4()) + (bjet2->P4()) ).Pt();

      float deta = bjet1->Eta - bjet2->Eta;
      float dphi = acos( cos ( bjet1->Phi - bjet2->Phi ) );
      drbb_ = sqrt( deta*deta + dphi*dphi );
      mct_ = sqrt(2 * bjet1->PT * bjet2->PT * (1 + cos(dphi) ) );

      bjet1pt_  = bjet1->PT;
      bjet1eta_ = bjet1->Eta;
      bjet1phi_ = bjet1->Phi;

      bjet2pt_  = bjet2->PT;
      bjet2eta_ = bjet2->Eta;
      bjet2phi_ = bjet2->Phi;
    }

    // if event doesn't have two btags, still fill these vars but with the highest pt jets
    else if (njetsall >= 2) {
      if( ij1 < 0 || ij2 < 0 ) {
	cout << "Negative leading jet indices: njetsall: " << njetsall << ", ij1: " << ij1 
	     << ", ij2: " << ij2 << endl;
      }

      Jet* bjet1 = (Jet*) branchJet->At(ij1);      
      Jet* bjet2 = (Jet*) branchJet->At(ij2);      

      mbb_  = ( (bjet1->P4()) + (bjet2->P4()) ).M();
      ptbb_ = ( (bjet1->P4()) + (bjet2->P4()) ).Pt();

      float deta = bjet1->Eta - bjet2->Eta;
      float dphi = acos( cos ( bjet1->Phi - bjet2->Phi ) );
      drbb_ = sqrt( deta*deta + dphi*dphi );
      mct_ = sqrt(2 * bjet1->PT * bjet2->PT * (1 + cos(dphi) ) );

      bjet1pt_  = bjet1->PT;
      bjet1eta_ = bjet1->Eta;
      bjet1phi_ = bjet1->Phi;

      bjet2pt_  = bjet2->PT;
      bjet2eta_ = bjet2->Eta;
      bjet2phi_ = bjet2->Phi;
    }

    // background weight for data-driven W+jets estimate
    //  light mistag rate squared
    const float mistag_rate = 0.02;
    if (prefix.find("Bj-4p") != string::npos) {
      if (nb_ == 0) {
	bgweight_ = mistag_rate * mistag_rate;
      }
    }

    //----------------------------------------
    // look at events with 2 PUPPI b-jets
    //----------------------------------------

    if( nb_puppi_ >= 2 ){
      if( ib1_puppi < 0 || ib2_puppi < 0 ) cout << "Negative puppi b-jet index" << endl;

      Jet* bjet1 = (Jet*) branchPuppiJet->At(ib1_puppi);      
      Jet* bjet2 = (Jet*) branchPuppiJet->At(ib2_puppi);      

      mbb_puppi_  = ( (bjet1->P4()) + (bjet2->P4()) ).M();
      ptbb_puppi_ = ( (bjet1->P4()) + (bjet2->P4()) ).Pt();

      float deta = bjet1->Eta - bjet2->Eta;
      float dphi = acos( cos ( bjet1->Phi - bjet2->Phi ) );
      drbb_puppi_ = sqrt( deta*deta + dphi*dphi );
      mct_puppi_ = sqrt(2 * bjet1->PT * bjet2->PT * (1 + cos(dphi) ) );

      bjet1pt_puppi_  = bjet1->PT;
      bjet1eta_puppi_ = bjet1->Eta;
      bjet1phi_puppi_ = bjet1->Phi;

      bjet2pt_puppi_  = bjet2->PT;
      bjet2eta_puppi_ = bjet2->Eta;
      bjet2phi_puppi_ = bjet2->Phi;
    }

    // if event doesn't have two btags, still fill these vars but with the highest pt jets
    else if (njetsall_puppi >= 2) {
      if( ij1_puppi < 0 || ij2_puppi < 0 ) cout << "Negative puppi leading jet indices" << endl;

      Jet* bjet1 = (Jet*) branchPuppiJet->At(ij1_puppi);      
      Jet* bjet2 = (Jet*) branchPuppiJet->At(ij2_puppi);      

      mbb_puppi_  = ( (bjet1->P4()) + (bjet2->P4()) ).M();
      ptbb_puppi_ = ( (bjet1->P4()) + (bjet2->P4()) ).Pt();

      float deta = bjet1->Eta - bjet2->Eta;
      float dphi = acos( cos ( bjet1->Phi - bjet2->Phi ) );
      drbb_puppi_ = sqrt( deta*deta + dphi*dphi );
      mct_puppi_ = sqrt(2 * bjet1->PT * bjet2->PT * (1 + cos(dphi) ) );

      bjet1pt_puppi_  = bjet1->PT;
      bjet1eta_puppi_ = bjet1->Eta;
      bjet1phi_puppi_ = bjet1->Phi;

      bjet2pt_puppi_  = bjet2->PT;
      bjet2eta_puppi_ = bjet2->Eta;
      bjet2phi_puppi_ = bjet2->Phi;
    }

    //----------------------------------------
    // event-level quantities
    //----------------------------------------

    mt_ = sqrt( 2 * met_ * lep1pt_ * ( 1 - cos( metphi_ - lep1phi_) ) );
    pujetmt_ = sqrt( 2 * pujetmet_ * lep1pt_ * ( 1 - cos( pujetmetphi_ - lep1phi_) ) );
    puppimt_ = sqrt( 2 * puppimet_ * lep1pt_ * ( 1 - cos( puppimetphi_ - lep1phi_) ) );

    // check if event would be in signal region, print out a few values
    //  -- for PUJetMET checks in Bj samples

    // if ((nleps_ == 1) && (lep1pt_ > 40.) && (fabs(lep1eta_) < 2.4) && (njets40_ == 2) && (njets_ == 2) && (nb_ == 2) && (bjet1pt_ > 40.) && (bjet2pt_ > 40.) &&  (fabs(bjet1eta_) < 2.4) && (fabs(bjet2eta_) < 2.4) && (mbb_ > 90.0 && mbb_ < 150.0) && (mt_ > 100.0) &&(mct_ > 160.0) && (met_ > 200.) ) {
    //   std::cout << "-- SIGNAL REGION EVENT: regular MET = " << oldmet_ << ", PUJetMET = " << met_ << std::endl;
    // }

    // // check gen match for reco lepton
    // if (nleps_ >= 1 && ilepgen1 >= 0) {
    //   GenParticle* genlep = (GenParticle*) branchParticle->At(ilepgen1);      
    //   if (abs(genlep->PID) == 11 && leptype_ == 1) {
    // 	cout << "WARNING: generated electron and found reco muon!! nels gen/reco == " << ngenels_ << "/" << nels_
    // 	     << ", nmus gen/reco == " << ngenmus_ << "/" << nmus_ << endl;
    //   } else if (abs(genlep->PID) == 13 && leptype_ == 0) {
    // 	cout << "WARNING: generated muon and found reco electron!! nels gen/reco == " << ngenels_ << "/" << nels_
    // 	     << ", nmus gen/reco == " << ngenmus_ << "/" << nmus_ << endl;
    //   } else {
    // 	if (genlep->P4().DeltaR(lep1p4) < 0.4) {
    // 	  lep1genpt_ = genlep->PT;
    // 	} else {
    // 	  cout << "WARNING: generated lepton doesn't match in dR with reco lepton!!" << endl;
    // 	}
    //   }
    // }

    tree->Fill();

  } // end loop over events in chain
    //  } // end loop over chains

  fbaby->cd();
  tree->Write();
  fbaby->Close();

  TString histname = Form("output/%s/%s.root",version,prefix.c_str());
  if (part > 0) histname = Form("output/%s/%s_part%d.root",version,prefix.c_str(),part);

  cout << "baby filename: " << outfilename << endl;
  cout << "hist filename: " << histname << endl;

  TFile *fout = TFile::Open( histname ,"RECREATE" );

  fout->cd();

  histMet->Write();
  histHT->Write();
  histJetPT->Write();
  histNjets->Write();
  histSt->Write();
  histStLO->Write();

  fout->Close();

}
