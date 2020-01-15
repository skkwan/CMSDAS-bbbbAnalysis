/*****************************************************/
/* plotHists.C                                       */
/* Usage: root -l -b -q plotHists.C                  */
/* Description: Contains helper functions to create
   TH1Fs of any variable/ arbitrary cuts with the 
   weights/lumi/cross-sections necessary for the 
   resulting histogram to be number of events.

   The main function plotHists.C illustrates how to do
   this for the H1_m variable, and writes the TH1Fs
   to an output ROOT file and saves each sample's
   histogram to images.                              */
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

/* Using the file located at inputDirectory and the tree
   treePath, draws the branch "variable" into a TH1F
   with the name histName and returns a pointer to the TH1F.
   Applies the TStrings cut and weight. The resulting
   TH1F has (bins) number of bins
   and ranges from the values low to high. */

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

/* Plots histogram TH1F h, with axes labels xLabel and
   yLabel, with the legend entry legendEntry and saves it
   to a file with the directory and name outfileDirectory
   (include the extension). */

int makeHistPlot(TH1F *h,
		 TString xLabel,
		 TString yLabel,
		 TString legendEntry,
		 TString outfileDirectory)
{
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  h->Draw("E HIST");

  // Suppress statistics box
  h->SetStats(0);

  // Set axes labels
  h->GetXaxis()->SetTitle(xLabel);
  h->GetYaxis()->SetTitle(yLabel);

  // Format the legend
  leg->AddEntry(h, legendEntry, "l");
  leg->Draw();
  
  Tcan->SaveAs(outfileDirectory);
  
  delete Tcan;
  return 0;

}

/*****************************************************/


int makeOverlayHistPlot(TH1F *h_data,
			TH1F *h_MC_bkg,
			TString xLabel,
			TString yLabel,
			TString outfileDirectory)
{
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  // Set axes labels                                                                                   
  h_data->GetXaxis()->SetTitle(xLabel);
  h_data->GetYaxis()->SetTitle(yLabel);

  // Change colors
  h_data->SetMarkerColor(kBlue);
  h_data->SetLineWidth(1);
  h_data->SetLineColor(kBlue+2);

  h_MC_bkg->SetMarkerColor(kRed);
  h_MC_bkg->SetLineWidth(1);
  h_MC_bkg->SetLineColor(kRed+2);

  h_data->Draw("E HIST");
  h_MC_bkg->Draw("E HIST SAME");
  

  // Format and draw the legend                          
  leg->AddEntry(h_data, "Data", "l");
  leg->AddEntry(h_MC_bkg, "MC background (tt and QCD)", "l");
  leg->Draw();

  Tcan->SaveAs(outfileDirectory);

  delete Tcan;
  
  
  return 0;

}
/*****************************************************/

/* Creates TH1F objects, writes them to a file, and plots
   each one separately. */

int plotHists(void)
{
  // The histograms will be written into this ROOT file.
  TString outputFileDirectory = "histograms.root";

  // SIGNAL: weight is 1
  TH1F *h_H1_m_data = makeHistogram("H1_m", "H1_m_data", "", "1",
				    "bbbbTree",
				    "/uscms/home/menendez/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_data_BTagCSV_Run2016_ALL.root",
				    300, 0, 800);
  
  // TT: weight is norm_weight times cross-section (xs) times the luminosity (in femtobarns)
  TH1F *h_H1_m_tt = makeHistogram("H1_m", "H1_m_tt", "", "norm_weight * xs * 35920",
				  "bbbbTree",
				  "/uscms/home/menendez/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root",
				  300, 0, 800);

  // QCD: weight is norm_weight times cross-section (xs) times the luminosity (in femtobarns)
  TH1F *h_H1_m_QCD = makeHistogram("H1_m", "H1_m_QCD", "", "norm_weight * xs * 35920",
				   "bbbbTree",
				   "/uscms/home/skwan/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_QCD_HTall_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
				   300, 0, 800);

  // Create an output ROOT file, writing histograms to the file
  TFile *fOut = new TFile(outputFileDirectory, "RECREATE");
  if ( fOut->IsOpen() ) printf("File opened successfully\n");
  fOut->cd();
  h_H1_m_data->Write();
  h_H1_m_tt->Write();
  h_H1_m_QCD->Write();
  fOut->Close();

  // Plotting separately
  makeHistPlot(h_H1_m_data, "H1_m_data", "Events", "Higgs 1 mass", "H1_m_data.png");
  makeHistPlot(h_H1_m_tt, "H1_m_tt", "Events", "Higgs 1 mass", "H1_m_tt.png");
  makeHistPlot(h_H1_m_QCD, "H1_m_QDC", "Events", "Higgs 1 mass", "H1_m_QCD.png");

  // Plotting overlay: SM and backgrounds
  TH1F *bkg = (TH1F*) h_H1_m_tt->Clone("bkg");
  bkg->Add(h_H1_m_QCD);

  makeOverlayHistPlot(h_H1_m_data, bkg, "Higgs 1 mass", "Events",
		      "overlay.png");

  return 0;
}



#endif
