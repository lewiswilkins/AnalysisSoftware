/*
 * Muon.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Muon.h"
#include "../../interface/GlobalVariables.h"


#include <iostream>

namespace BAT {
const double initialBigValue = 123456789;

Muon::Muon() :
		Lepton(), //
		usedAlgorithm_(MuonAlgorithm::Default), //
		isGlobalMuon_(false), //
		isTrackerMuon_(false), //
		isPFMuon_(false), //
		normalisedChi2_(initialBigValue), //
		numberOfValidMuonHits_(-1), //
		numberOfValidPixelHits_(-1), //
		numberOfValidHits_(-1), //
		pixelLayersWithMeasurement_(-1), //
		trackerLayersWithMeasurement_(-1), //
		numberOfMatches_(-1), //
		numberOfMatchedStations_(-1) {

}

Muon::Muon(double energy, double px, double py, double pz) :
		Lepton(energy, px, py, pz), //
		usedAlgorithm_(MuonAlgorithm::Default), //
		isGlobalMuon_(false), //
		isTrackerMuon_(false), //
		isPFMuon_(false), //
		normalisedChi2_(initialBigValue), //
		numberOfValidMuonHits_(-1), //
		numberOfValidPixelHits_(-1), //
		numberOfValidHits_(-1), //
		pixelLayersWithMeasurement_(-1), //
		trackerLayersWithMeasurement_(-1), //
		numberOfMatches_(-1), //
		numberOfMatchedStations_(-1) {

}

Muon::~Muon() {
}

bool Muon::isGlobal() const {
	return isGlobalMuon_;
}

bool Muon::isTracker() const {
	return isTrackerMuon_;
}

bool Muon::isPFMuon() const {
	return isPFMuon_;
}

void Muon::makeGlobal(bool global) {
	isGlobalMuon_ = global;
}

void Muon::setTrackerMuon(bool isTrackerMuon) {
	isTrackerMuon_ = isTrackerMuon;
}

void Muon::setPFMuon(bool pf) {
	isPFMuon_ = pf;
}

void Muon::setNormalisedChi2(double normChi2) {
	normalisedChi2_ = normChi2;
}

void Muon::setNumberOfValidHits(int nValidHits) {
	numberOfValidHits_ = nValidHits;
}

void Muon::setNumberOfValidMuonHits(int nValidHits) {
	numberOfValidMuonHits_ = nValidHits;
}

void Muon::setNumberOfValidPixelHits(int nValidHits) {
	numberOfValidPixelHits_ = nValidHits;
}

void Muon::setPixelLayersWithMeasurement(int pixelLayers) {
	pixelLayersWithMeasurement_ = pixelLayers;
}

void Muon::setNumberOfMatchedStations(int nMatchedStations) {
	numberOfMatchedStations_ = nMatchedStations;
}

void Muon::setNumberOfMatches(int nMatches) {
	numberOfMatches_ = nMatches;
}

bool Muon::isPFLepton() const {
	return usedAlgorithm_ == MuonAlgorithm::ParticleFlow;
}

void Muon::setUsedAlgorithm(MuonAlgorithm::value algorithm) {
	usedAlgorithm_ = algorithm;
}

void Muon::setTrackerLayersWithMeasurement(int layers) {
	trackerLayersWithMeasurement_ = layers;
}

int Muon::trackerLayersWithMeasurement() const {
	return trackerLayersWithMeasurement_;
}

int Muon::numberOfMatchedStations() const {
	return numberOfMatchedStations_;
}

int Muon::numberOfMatches() const {
	return numberOfMatches_;
}

int Muon::numberOfValidHits() const {
	return numberOfValidHits_;
}

int Muon::numberOfValidMuonHits() const {
	return numberOfValidMuonHits_;
}

int Muon::numberOfValidPixelHits() const {
	return numberOfValidPixelHits_;
}

int Muon::pixelLayersWithMeasurement() const {
	return pixelLayersWithMeasurement_;
}

double Muon::normChi2() const {
	return normalisedChi2_;
}

double Muon::getEfficiencyCorrection( int muon_scale_factor_systematic ) const {
	if ( muon_scale_factor_systematic == 0 ) {
		return 1.;
	}
	else if ( muon_scale_factor_systematic == -1 ) {
		return 0.99;
	}
	else if ( muon_scale_factor_systematic == 1 ) {
		return 1.01;
	}

	return 0.;
}
}
