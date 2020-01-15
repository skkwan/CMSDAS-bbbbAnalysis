/*****************************************************/


#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include <math.h>
#include <iostream>
#include <string>

#ifndef MAKEHISTS_C_INCL
#define MAKEHISTS_C_INCL

/*****************************************************/

TH1F* makeHistogram(TString variable,
		    TString histName,
		    TString cut,
		    TString weight,
		    TString treePath,
		    TString inputDirectory,
		    int bins,
		    int low, 
		    int high)
{
  TFile *file = new TFile(inputDirectory);
 
  TTree* tree = (TTree*)file->Get(treePath);

  TH1F* hist = new TH1F(histName, histName, bins, low, high);
  
  if ((cut != "") && (weight != ""))
    tree->Draw(variable+">>+"+histName, cut + "*" + weight);
  else if (cut != "")
    tree->Draw(variable+">>+"+histName, cut);
  else if (weight != "")
    tree->Draw(variable+">>+"+histName, weight);
  else
    tree->Draw(variable+">>+"+histName);

  return hist;

}

/*****************************************************/

/* Apply template style to a TPad* pad1. */
void applyPadStyle(TPad* pad1)
{
  pad1->SetFillColor(0);
  pad1->Draw();  pad1->cd();  pad1->SetLeftMargin(0.2);  pad1->SetBottomMargin(0.13); pad1->SetRightMargin(0.1);
  //pad1->SetGrid(); 
  pad1->SetGrid(10,10); 
}

/*****************************************************/

/* Apply legend style to a TLegend *leg. */
void applyLegStyle(TLegend *leg)
{
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetHeader("");
  leg->SetShadowColor(0);
}

/*****************************************************/


int makeHistPlot(TH1F *h,
		 TString xLabel,
		 TString yLabel,
		 TString legendEntry,
		 TString outfileDirectory)
{
  gROOT->LoadMacro("CMS_lumi.C");

  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  h->Draw("HIST");

  h->GetXaxis()->SetTitle(xLabel);
  h->GetYaxis()->SetTitle(yLabel);

  leg->AddEntry(h, legendEntry, "l");
  leg->Draw();
  
  Tcan->SaveAs(outfileDirectory);
  
  delete Tcan;
  return 0;

}

/*****************************************************/

int plotHists(void)
{
  // Make the histogram
  TH1F *h_H1_m = makeHistogram("H1_m", "H1_m", "", "",
			       "bbbbTree",
			       "/uscms/home/menendez/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_data_BTagCSV_Run2016_ALL.root",
			       300, 0, 800);
  // Plot it
  makeHistPlot(h_H1_m, "H1_m", "Events", "Higgs 1 mass", "test.png");

  return 0;
}

#endif
