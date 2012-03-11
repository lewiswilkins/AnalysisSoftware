/*
 * Lepton.cpp
 *
 *  Created on: 30 Oct 2011
 *      Author: kreczko
 */

#include "../../interface/RecoObjects/Lepton.h"

namespace BAT {
const double initialBigValue = 123456789;

Lepton::Lepton() : //
		Particle(), //
		ecal_Isolation_DR03_(initialBigValue), //
		hcal_Isolation_DR03_(initialBigValue), //
		tracker_Isolation_DR03_(initialBigValue), //
		ecal_Isolation_DR04_(initialBigValue), //
		hcal_Isolation_DR04_(initialBigValue), //
		tracker_Isolation_DR04_(initialBigValue), //
		ecal_Isolation_DR05_(initialBigValue), //
		hcal_Isolation_DR05_(initialBigValue), //
		tracker_Isolation_DR05_(initialBigValue), //
		PFGamma_Isolation_DR03_(initialBigValue), //
		PFChargedHadron_Isolation_DR03_(initialBigValue), //
		PFNeutralHadron_Isolation_DR03_(initialBigValue), //
		PFGamma_Isolation_DR04_(initialBigValue), //
		PFChargedHadron_Isolation_DR04_(initialBigValue), //
		PFNeutralHadron_Isolation_DR04_(initialBigValue), //
		PFGamma_Isolation_DR05_(initialBigValue), //
		PFChargedHadron_Isolation_DR05_(initialBigValue), //
		PFNeutralHadron_Isolation_DR05_(initialBigValue), //
		zDistanceToPrimaryVertex_(initialBigValue), //
		directionalIsolation_DR02_(initialBigValue), //
		directionalIsolation_DR03_(initialBigValue), //
		directionalIsolation_GaussianFallOff_DR02_(initialBigValue), //
		directionalIsolation_GaussianFallOff_DR03_(initialBigValue), //
		pfIsolation_GaussianFallOff_DR02_(initialBigValue), //
		pfIsolation_GaussianFallOff_DR03_(initialBigValue) {
}

Lepton::Lepton(double energy, double px, double py, double pz) : //
		Particle(energy, px, py, pz), //
		ecal_Isolation_DR03_(initialBigValue), //
		hcal_Isolation_DR03_(initialBigValue), //
		tracker_Isolation_DR03_(initialBigValue), //
		ecal_Isolation_DR04_(initialBigValue), //
		hcal_Isolation_DR04_(initialBigValue), //
		tracker_Isolation_DR04_(initialBigValue), //
		ecal_Isolation_DR05_(initialBigValue), //
		hcal_Isolation_DR05_(initialBigValue), //
		tracker_Isolation_DR05_(initialBigValue), //
		PFGamma_Isolation_DR03_(initialBigValue), //
		PFChargedHadron_Isolation_DR03_(initialBigValue), //
		PFNeutralHadron_Isolation_DR03_(initialBigValue), //
		PFGamma_Isolation_DR04_(initialBigValue), //
		PFChargedHadron_Isolation_DR04_(initialBigValue), //
		PFNeutralHadron_Isolation_DR04_(initialBigValue), //
		PFGamma_Isolation_DR05_(initialBigValue), //
		PFChargedHadron_Isolation_DR05_(initialBigValue), //
		PFNeutralHadron_Isolation_DR05_(initialBigValue), //
		zDistanceToPrimaryVertex_(initialBigValue), //
		directionalIsolation_DR02_(initialBigValue), //
		directionalIsolation_DR03_(initialBigValue), //
		directionalIsolation_GaussianFallOff_DR02_(initialBigValue), //
		directionalIsolation_GaussianFallOff_DR03_(initialBigValue), //
		pfIsolation_GaussianFallOff_DR02_(initialBigValue), //
		pfIsolation_GaussianFallOff_DR03_(initialBigValue) {

}

void Lepton::setEcalIsolation(double isolation, double coneSize) {
	if (coneSize == 0.3)
		ecal_Isolation_DR03_ = isolation;
	else if (coneSize == 0.4)
		ecal_Isolation_DR04_ = isolation;
	else if (coneSize == 0.5)
		ecal_Isolation_DR05_ = isolation;
	else {
		std::cout << "Lepton::setEcalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

void Lepton::setHcalIsolation(double isolation, double coneSize) {
	if (coneSize == 0.3)
		hcal_Isolation_DR03_ = isolation;
	else if (coneSize == 0.4)
		hcal_Isolation_DR04_ = isolation;
	else if (coneSize == 0.5)
		hcal_Isolation_DR05_ = isolation;
	else {
		std::cout << "Lepton::setHcalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

void Lepton::setTrackerIsolation(double isolation, double coneSize) {
	if (coneSize == 0.3)
		tracker_Isolation_DR03_ = isolation;
	else if (coneSize == 0.4)
		tracker_Isolation_DR04_ = isolation;
	else if (coneSize == 0.5)
		tracker_Isolation_DR05_ = isolation;
	else {
		std::cout << "Lepton::setTrackerIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

double Lepton::trackerIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = tracker_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = tracker_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = tracker_Isolation_DR05_;
	else {
		std::cout << "Lepton::trackerIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::hcalIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = hcal_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = hcal_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = hcal_Isolation_DR05_;
	else {
		std::cout << "Lepton::hcalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::ecalIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = ecal_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = ecal_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = ecal_Isolation_DR05_;
	else {
		std::cout << "Lepton::ecalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

void Lepton::setPFGammaIsolation(double pfGammaIso, double coneSize) {
	if (coneSize == 0.3)
		PFGamma_Isolation_DR03_ = pfGammaIso;
	else if (coneSize == 0.4)
		PFGamma_Isolation_DR04_ = pfGammaIso;
	else if (coneSize == 0.5)
		PFGamma_Isolation_DR05_ = pfGammaIso;
	else {
		std::cout << "Lepton::setPFGammaIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

void Lepton::setPFChargedHadronIsolation(double chargedHadronIso, double coneSize) {
	if (coneSize == 0.3)
		PFChargedHadron_Isolation_DR03_ = chargedHadronIso;
	else if (coneSize == 0.4)
		PFChargedHadron_Isolation_DR04_ = chargedHadronIso;
	else if (coneSize == 0.5)
		PFChargedHadron_Isolation_DR05_ = chargedHadronIso;
	else {
		std::cout << "Lepton::setPFChargedHadronIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

void Lepton::setPFNeutralHadronIsolation(double neutralHadronIso, double coneSize) {
	if (coneSize == 0.3)
		PFNeutralHadron_Isolation_DR03_ = neutralHadronIso;
	else if (coneSize == 0.4)
		PFNeutralHadron_Isolation_DR04_ = neutralHadronIso;
	else if (coneSize == 0.5)
		PFNeutralHadron_Isolation_DR05_ = neutralHadronIso;
	else {
		std::cout << "Lepton::setPFNeutralHadronIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

double Lepton::PFGammaIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = PFGamma_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = PFGamma_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = PFGamma_Isolation_DR05_;
	else {
		std::cout << "Lepton::PFGammaIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::PFChargedHadronIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = PFChargedHadron_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = PFChargedHadron_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = PFChargedHadron_Isolation_DR05_;
	else {
		std::cout << "Lepton::PFChargedHadronIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::PFNeutralHadronIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.3)
		isolation = PFNeutralHadron_Isolation_DR03_;
	else if (coneSize == 0.4)
		isolation = PFNeutralHadron_Isolation_DR04_;
	else if (coneSize == 0.5)
		isolation = PFNeutralHadron_Isolation_DR05_;
	else {
		std::cout << "Lepton::PFNeutralHadronIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::relativeIsolation(double coneSize) const {
	return (ecalIsolation(coneSize) + hcalIsolation(coneSize) + trackerIsolation(coneSize)) / pt();
}

double Lepton::pfRelativeIsolation(double coneSize) const {
	return (PFChargedHadronIsolation(coneSize) + PFNeutralHadronIsolation(coneSize) + PFGammaIsolation(coneSize)) / pt();
}

void Lepton::setZDistanceToPrimaryVertex(double dist) {
	zDistanceToPrimaryVertex_ = dist;
}

void Lepton::setDirectionalIsolation(double iso, double coneSize) {
	if (coneSize == 0.2)
		directionalIsolation_DR02_ = iso;
	else if (coneSize == 0.3)
		directionalIsolation_DR03_ = iso;
	else {
		std::cout << "Lepton::setDirectionalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
}

void Lepton::setDirectionalIsolationWithGaussianFallOff(double iso, double coneSize) {
	if (coneSize == 0.2)
		directionalIsolation_GaussianFallOff_DR02_ = iso;
	else if (coneSize == 0.3)
		directionalIsolation_GaussianFallOff_DR03_ = iso;
	else {
		std::cout << "Lepton::setDirectionalIsolationWithGaussianFallOff: Unknown cone of deltaR = " << coneSize
				<< std::endl;
	}
}

void Lepton::setPFIsolationWithGaussianFallOff(double iso, double coneSize) {
	if (coneSize == 0.2)
		pfIsolation_GaussianFallOff_DR02_ = iso;
	else if (coneSize == 0.3)
		pfIsolation_GaussianFallOff_DR03_ = iso;
	else {
		std::cout << "Lepton::setPFRelativeIsolationWithGaussianFallOff: Unknown cone of deltaR = " << coneSize
				<< std::endl;
	}
}

double Lepton::directionalIsolation(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.2)
		isolation = directionalIsolation_DR02_;
	else if (coneSize == 0.3)
		isolation = directionalIsolation_DR03_;
	else {
		std::cout << "Lepton::directionalIsolation: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::directionalIsolationWithGaussianFallOff(double coneSize) const {
	double isolation(initialBigValue);
	if (coneSize == 0.2)
		isolation = directionalIsolation_GaussianFallOff_DR02_;
	else if (coneSize == 0.3)
		isolation = directionalIsolation_GaussianFallOff_DR03_;
	else {
		std::cout << "Lepton::directionalIsolationWithGaussianFallOff: Unknown cone of deltaR = " << coneSize << std::endl;
	}
	return isolation;
}

double Lepton::pfIsolationWithGaussianFallOff(double coneSize) const {
	double isolation(initialBigValue);
		if (coneSize == 0.2)
			isolation = pfIsolation_GaussianFallOff_DR02_;
		else if (coneSize == 0.3)
			isolation = pfIsolation_GaussianFallOff_DR03_;
		else {
			std::cout << "Lepton::pfIsolationWithGaussianFallOff: Unknown cone of deltaR = " << coneSize << std::endl;
		}
		return isolation;
}

double Lepton::ZDistanceToPrimaryVertex() const {
	return zDistanceToPrimaryVertex_;
}

Lepton::~Lepton() {
}

} /* namespace BAT */
