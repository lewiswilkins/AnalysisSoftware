'''
Created on Nov 23, 2011

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
import os
from ROOT import *
from tdrStyle import *

jetBinsLatex = {'0jet':'0 jet', '0orMoreJets':'#geq 0 jets', '1jet':'1 jet', '1orMoreJets':'#geq 1 jet',
                    '2jets':'2 jets', '2orMoreJets':'#geq 2 jets', '3jets':'3 jets', '3orMoreJets':'#geq 3 jets',
                    '4orMoreJets':'#geq 4 jets'}

BjetBinsLatex = {'0btag':'0 b-tags', '0orMoreBtag':'#geq 0 b-tags', '1btag':'1 b-tags',
                    '1orMoreBtag':'#geq 1 b-tags',
                    '2btags':'2 b-tags', '2orMoreBtags':'#geq 2 b-tags',
                    '3btags':'3 b-tags', '3orMoreBtags':'#geq 3 b-tags',
                    '4orMoreBtags':'#geq 4 b-tags'}

defaultCanvasWidth = 1200
defaultCanvasHeight = 900

class Plot():
    '''
    Plot unites the tuning parameters for plot style
    '''


    def __init__(self):
        self.rebin = 1
        self.scale = 1
        self.UserRange = (0, 0)
        self.name = ""
        self.location = ""
        self.jetBins = []
        self.bJetBins = []
        self.qcdShapeFrom = ""
        self.qcdEstimate = 0 
        
def compareShapes(histograms=[], histogramlables=[], styles=[], maxfactor = 1.3):
    leg = TLegend(0.6, 0.7, 0.94, 0.92);
    leg.SetBorderSize(0);
    leg.SetLineStyle(0);
    leg.SetTextFont(42);
    leg.SetFillStyle(0);
    AddLegendEntry = leg.AddEntry 
    
    c = TCanvas("compareShapes", 'compareShapes', defaultCanvasWidth, defaultCanvasHeight)
    c.cd()

    for hist, label, style in zip(histograms,histogramlables,styles):
        hist.Sumw2()
        hist = normalise(hist)
        hist.SetLineColor(style['color'])
        hist.SetLineWidth(4)
        
        AddLegendEntry(hist, label, "f")
        
    index = 0
    max = getMax(histograms)
    for hist in histograms:
        if index == 0:
            hist.GetYaxis().SetRangeUser(0, max*maxfactor)
            hist.Draw('histe')
        else:
            hist.Draw('histe same')
        index += 1
    
    return c, leg

def get_cms_label(lumiInInvPb, njet="4orMoreJets", nbjet="0orMoreBtag", channel="e"):
    mytext = TPaveText(0.35, 0.7, 0.7, 0.93, "NDC");
    mytext.AddText("CMS Preliminary");
    mytext.AddText("%.2f fb^{-1} at  #sqrt{s} = 7 TeV" % (lumiInInvPb / 1000));
    if njet != "":
        mytext.AddText(channel + ", %s, %s" % (jetBinsLatex[njet], BjetBinsLatex[nbjet]))   
             
    mytext.SetFillStyle(0);
    mytext.SetBorderSize(0);
    mytext.SetTextFont(42);
    mytext.SetTextAlign(13);
    
    return mytext

def saveAs(canvas, name, outputFormats=['png'], outputFolder=''):
    canvas.RedrawAxis()
    if not outputFolder == '' and not outputFolder.endswith('/'):
        outputFolder += '/'
    for outputFormat in outputFormats:
        fullFileName = outputFolder + name + '.' + outputFormat
        if '/' in fullFileName:
            path = fullFileName[:fullFileName.rfind('/')]
            createFolderIfDoesNotExist(path)
        
        canvas.SaveAs(fullFileName)
        
def createFolderIfDoesNotExist(path):
    if not os.path.exists(path):
        os.makedirs(path)
        
def normalise(histogram):
    if histogram and histogram.Integral() > 0:
        histogram.Scale(1 / histogram.Integral())
    return histogram

def rebin(hists, nbins, histname):
    for sample in hists.keys():
        if len(hists[sample].keys()) == 0 or 'Stack' in sample:
            continue
        if '*' in histname:
            nameToken = histname.replace('*', '')
            histlist = hists[sample]
            for name in histlist.keys():
                if nameToken in name:
                    hists[sample][name].Rebin(nbins)
        elif hists[sample].has_key(histname):
            hists[sample][histname].Rebin(nbins)
    return hists

def setXRange(hists, limits=(0, 5000), histname=''):
    for sample in hists.keys():
        if len(hists[sample].keys()) == 0 or 'Stack' in sample:
            continue
        if '*' in histname:
            nameToken = histname.replace('*', '')
            histlist = hists[sample]
            for name in histlist.keys():
                if nameToken in name:
                    if hists[sample][name] and hists[sample][name].GetXaxis():
                        hists[sample][name].GetXaxis().SetRangeUser(limits[0], limits[1])
                    else:
                        print "Can't find histogram", sample, name
        elif hists[sample].has_key(histname):
            if hists[sample][name]:
                hists[sample][histname].GetXaxis().SetRangeUser(limits[0], limits[1]);
            else:
                print "Can't find histogram", sample, name
    return hists

def setYRange(hists, limits=(0, 5000), histname=''):
    for sample in hists.keys():
        if len(hists[sample].keys()) == 0 or 'Stack' in sample:
            continue
        if '*' in histname:
            nameToken = histname.replace('*', '')
            histlist = hists[sample]
            for name in histlist.keys():
                if nameToken in name:
                    if hists[sample][name] and hists[sample][name].GetYaxis():
                        hists[sample][name].GetYaxis().SetRangeUser(limits[0], limits[1])
                    else:
                        print "Can't find histogram", sample, name
        elif hists[sample].has_key(histname):
            if hists[sample][name]:
                hists[sample][histname].GetYaxis().SetRangeUser(limits[0], limits[1]);
            else:
                print "Can't find histogram", sample, name
    return hists
    
def setXTitle(hists, title, histname=''):
    for sample in hists.keys():
        if len(hists[sample].keys()) == 0 or 'Stack' in sample:
            continue
        if '*' in histname:
            nameToken = histname.replace('*', '')
            histlist = hists[sample]
            for name in histlist.keys():
                if nameToken in name:
                    hists[sample][name].SetXTitle(title)
        elif hists[sample].has_key(histname):
            hists[sample][histname].SetXTitle(title);
    return hists

def setYTitle(hists, title, histname=''):
    for sample in hists.keys():
        if len(hists[sample].keys()) == 0 or 'Stack' in sample:
            continue
        if '*' in histname:
            nameToken = histname.replace('*', '')
            histlist = hists[sample]
            for name in histlist.keys():
                if nameToken in name:
                    hists[sample][name].SetYTitle(title)
        elif hists[sample].has_key(histname):
            hists[sample][histname].SetYTitle(title);
    return hists   

def setStyle():
    tdrStyle = setTDRStyle();

    #slight adaptation
    tdrStyle.SetPadRightMargin(0.05); #originally was 0.02, too narrow!
    tdrStyle.SetStatH(0.2);
    #tdrStyle.SetOptStat(1110);//off title
    tdrStyle.SetOptStat(0);#off title
    tdrStyle.SetOptFit(0);#off title
    tdrStyle.cd();
    gROOT.ForceStyle();     
    
def getMax(histograms):
    maximum = 0
    for hist in histograms:
        max = hist.GetMaximum()
        if max > maximum:
            maximum = max
    return max
        
