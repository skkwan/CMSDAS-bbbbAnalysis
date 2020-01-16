/*****************************************************/
/* plot1DHists.C                                     */
/* Usage: root -l -b -q plot1DHists.C                */
/* Description: Contains helper functions to create
   TH1Fs of any variable/ arbitrary cuts with the 
   weights/lumi/cross-sections necessary for the 
   resulting histogram to be number of events.       */
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

#ifndef PLOT1DHISTS_C_INCL
#define PLOT1DHISTS_C_INCL

/*****************************************************/

/* Using the file located at inputDirectory and the tree
   treePath, draws the branch "variable" into a TH1F
   with the name histName and returns a pointer to the TH1F.
   Applies the TStrings cut and weight. The resulting
   TH1F has (bins) number of bins
   and ranges from the values low to high. */

TH1F* makeHistogram(TString variable,
		    TString histName,
		    TCut cut,
		    TCut weight,
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

/* Takes TH1Fs h_data and h_MC_bkg, plots variable 
   and saves plot with axes labels xLabel and yLabel
   to the output file directory. */

int makeOverlayHistPlot(TH1F *h_data,
			TH1F *h_MC_bkg,
			TString variable,
			TString outfileDirectory)
{
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  // Change colors, marker style, etc.
  h_data->SetMarkerColor(kAzure-3);
  h_data->SetMarkerSize(0.4);
  h_data->SetMarkerStyle(8);
  h_data->SetLineWidth(1);

  h_MC_bkg->SetMarkerColor(kRed-3);
  h_MC_bkg->SetLineWidth(1);
  h_MC_bkg->SetLineColor(kRed-10);

  // To draw the error bars as shaded regions, we need to clone the 
  // original histogram. So we do this for the backgrond histogram:
  TH1F *h_bkgClone = (TH1F*) h_MC_bkg->Clone("bkgClone");
  h_bkgClone->SetFillStyle(3001);
  h_bkgClone->SetFillColor(kGray);

  // Suppress stats box                                                                             
  h_data->SetStats(0);
  h_bkgClone->SetStats(0);
  h_MC_bkg->SetStats(0);

  // Set axes labels
  h_MC_bkg->GetXaxis()->SetTitle(variable);
  h_MC_bkg->GetYaxis()->SetTitle("Events");

  // Need this line to set the title
  h_MC_bkg->SetTitle(variable);

  // Drawing
  h_MC_bkg->Draw("HIST");     // draw background as normal histogram
  h_bkgClone->Draw("E3 SAME");  // E3 is the shading
  h_data->Draw("EP Z SAME");  // draw signal as dots
  
  // Format and draw the legend                          
  leg->AddEntry(h_data, "Data", "l");
  leg->AddEntry(h_MC_bkg, "MC background (tt and QCD)", "l");
  leg->Draw();

  Tcan->SaveAs(outfileDirectory);

  delete Tcan;
  
  
  return 0;

}

/*****************************************************/

/* Creates TH1Fs of variable, saves them to a ROOT file
   (one TH1F for data, one for signal, and one for
   backgrond (QCD + TT), and plots them. */

int makeDataBkgHists(TString variable,
		     TString outputFileDirectory,
		     TCut cutData,
		     TCut cutBkg,
		     int nBins,
		     int low,
		     int high)
{
  // Data: weight is 1
  TH1F *h_data = makeHistogram(variable, "data", cutData, "1",
			     "bbbbTree",
			     "/uscms/home/menendez/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_data_BTagCSV_Run2016_ALL.root",
			     nBins, low, high);
  
  // TT: weight is norm_weight times cross-section (xs) times the luminosity (in femtobarns)
  TH1F *h_tt = makeHistogram(variable, "tt", cutBkg, "norm_weight * xs * 35920",
				  "bbbbTree",
				  "/uscms/home/menendez/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root",
				  nBins, low, high);

  // QCD: weight is norm_weight times cross-section (xs) times the luminosity (in femtobarns)
  TH1F *h_QCD = makeHistogram(variable, "qcd", cutBkg, "norm_weight * xs * 35920",
			      "bbbbTree",
			      "/uscms/home/skwan/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_QCD_HTall_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
			      nBins, low, high);

  // Plotting overlay: SM and backgrounds
  TH1F *h_bkg = (TH1F*) h_tt->Clone("bkg");
  h_bkg->Add(h_QCD);

  // Create an output ROOT file, writing histograms to the file    
  TFile *fOut = new TFile(outputFileDirectory, "RECREATE"); 
  if ( fOut->IsOpen() ) printf("File opened successfully\n");
  fOut->cd(); 
  h_data->Write();
  h_bkg->Write();
  fOut->Close();

  makeOverlayHistPlot(h_data, h_bkg, variable,
		      variable + "_overlay.png");

  return 0;
}

/*****************************************************/

int plot1DHists(void)
{

  makeDataBkgHists("H1_m", "H1_m_histograms.root", "", "", 300, 0, 800);


  return 0;
}


#endif
