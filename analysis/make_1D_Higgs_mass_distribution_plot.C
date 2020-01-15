//
//
// Author: Stephanie Kwan

#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"

int make_1D_Higgs_mass_distribution_plot(void)
{
  // Get the file and tree
  TFile* file = new TFile("objects_gg_HH_bbbb_SM.root");
  TTree* tree = (TTree*)file->Get("bbbbTree");
  
  // Set up canvas and legend
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);

  // Draw a branch
  TH1F *h1Mass = new TH1F("h1Mass", "H1 Mass", 200, 0, 800);
  tree->Draw("H1_m>>+h1Mass");

  // Set plot style
  h1Mass->SetMarkerColor(0);
  h1Mass->SetFillStyle(1001);
  h1Mass->SetFillColorAlpha(kBlue+2, 0.1);
  h1Mass->SetLineWidth(1);
  h1Mass->SetLineColor(kBlue+2);

  h1Mass->Draw("HIST");

  // Format the legend
  leg->AddEntry(h1Mass, "H1 Mass", "l");
  leg->Draw();


  // Save the file and exit
  Tcan->SaveAs("test.png");
  delete Tcan;

  return 1;
}

 
