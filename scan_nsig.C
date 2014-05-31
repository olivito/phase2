void scan_nsig(TString infile, TString output) {

  TFile* f = new TFile(infile);
  TTree* t = f->Get("t");

  TFile* fout = new TFile(output,"RECREATE");

  TH2F* hevts = new TH2F("hevts","", 11, -50, 1050, 11, -50, 1050);
  t->Draw("mlsp:mchi>>hevts");

  fout->Write();
  fout->Close();

}
