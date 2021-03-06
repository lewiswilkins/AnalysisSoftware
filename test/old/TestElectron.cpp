#include "TestElectron.h"

TestElectron::TestElectron() :
		isolatedElectron(TestObjectFactory::goodIsolatedElectron()), //
		goodElectron(TestObjectFactory::goodCaloElectron()), //
		badEtElectron(TestObjectFactory::badEtElectron()), //
		badEtaElectron(TestObjectFactory::badEtaElectron()), //
		badInCrackElectron(TestObjectFactory::badInCrackElectron()), //
		badD0Electron(TestObjectFactory::badD0Electron()), //
		badElectronWithMissingInnerLayerHit(TestObjectFactory::electronWithMissingInnerLayerHit()), //
		badElectronWithPartnerTrack(TestObjectFactory::electronWithMatchingPartnerTrack()), //
		looseElectron(TestObjectFactory::goodLooseElectron()), //
		badLooseElectronNoID(TestObjectFactory::badLooseElectronNoID()), //
		badElectronNoID(TestObjectFactory::badElectronNoID()) //
{

}

void TestElectron::testEcalIsolation() {
	ASSERT_EQUAL_DELTA(0.3, isolatedElectron->ecalIsolation(), 0.01);
}

void TestElectron::testHcalIsolation() {
	ASSERT_EQUAL_DELTA(0.5, isolatedElectron->hcalIsolation(), 0.01);
}

void TestElectron::testTrackerIsolation() {
	ASSERT_EQUAL_DELTA(0.4, isolatedElectron->trackerIsolation(), 0.01);
}

void TestElectron::testRelativeIsolation() {
	float isoSum = isolatedElectron->trackerIsolation() + isolatedElectron->ecalIsolation()
			+ isolatedElectron->hcalIsolation();
	ASSERT_EQUAL_DELTA(isoSum / isolatedElectron->et(), isolatedElectron->relativeIsolation(), 0.01);
	ASSERT(isolatedElectron->relativeIsolation() < 0.1);
}

void TestElectron::testVBTFWP70Barrel() {
	Electron electron = Electron(50, 40, 30, 0);
	electron.setSigmaIEtaIEta(0.01 - 0.01 * 0.01);
	electron.setDPhiIn(0.03 - 0.01 * 0.03);
	electron.setDEtaIn(0.004 - 0.01 * 0.004);
	electron.setHadOverEm(0.025 - 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelNegativeValues() {
	Electron electron = Electron(50, 40, 30, 0);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelNegativeSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 - 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailNegativeDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 - 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailNegativeDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 - 0.01 * 0.004);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelFailHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70BarrelNegativeHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.03 + 0.01 * 0.03);
	electron.setDEtaIn(-0.004 + 0.01 * 0.004);
	electron.setHadOverEm(-0.025 - 0.01 * 0.025);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70Endcap() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(0.03 - 0.01 * 0.03);
	electron.setDPhiIn(0.02 - 0.01 * 0.02);
	electron.setDEtaIn(0.005 - 0.01 * 0.005);
	electron.setHadOverEm(0.025 - 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapNegativeValues() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapFailSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapNegativeSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 - 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapFailDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapFailNegativeDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 - 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(0.005 - 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	//expect true, dEtaIn cut is not used in the endcap at the moment
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapNegativeDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	//expect true, dEtaIn cut is not used in the endcap at the moment
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapFailHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(0.025 + 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP70EndcapNegativeHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.02 + 0.01 * 0.02);
	electron.setDEtaIn(-0.005 + 0.01 * 0.005);
	electron.setHadOverEm(-0.025 - 0.01 * 0.025);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP70_ElectronID());
}

void TestElectron::testVBTFWP95Barrel() {
	Electron electron = Electron(50, 40, 30, 0);
	electron.setSigmaIEtaIEta(0.01 - 0.01 * 0.01);
	electron.setDPhiIn(0.8 - 0.01 * 0.8);
	electron.setDEtaIn(0.007 - 0.01 * 0.007);
	electron.setHadOverEm(0.15 - 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelNegativeValues() {
	Electron electron = Electron(50, 40, 30, 0);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelNegativeSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 - 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailNegativeDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 - 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailNegativeDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 - 0.01 * 0.007);
	electron.setHadOverEm(-0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelFailHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(0.15 + 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95BarrelNegativeHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.01 + 0.01 * 0.01);
	electron.setDPhiIn(-0.8 + 0.01 * 0.8);
	electron.setDEtaIn(-0.007 + 0.01 * 0.007);
	electron.setHadOverEm(-0.15 - 0.01 * 0.15);
	electron.setSuperClusterEta(0);
	assert(electron.isInBarrelRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95Endcap() {
	Electron electron = Electron(50, 3, 0, 49);
	electron.setSigmaIEtaIEta(0.03 - 0.01 * 0.03);
	electron.setDPhiIn(0.7 - 0.01 * 0.7);
	electron.setDEtaIn(0.01 - 0.01 * 0.01);
	electron.setHadOverEm(0.07 - 0.01 * 0.07);
	electron.setSuperClusterEta(2.4);

	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapNegativeValues() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.4);

	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapFailSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.4);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() > 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapNegativeSigmaIEtaIEta() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 - 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapFailDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) > 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	assert(electron.isInEndCapRegion());
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapFailNegativeDPhiIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 - 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) > 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(0.01 - 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapNegativeDEtaIn() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	//expect true, dEtaIn cut is not used in the endcap at the moment
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapFailHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(0.07 + 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() > 0.07);
	ASSERT_EQUAL(false, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testVBTFWP95EndcapNegativeHadOverEm() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setSigmaIEtaIEta(-0.03 + 0.01 * 0.03);
	electron.setDPhiIn(-0.7 + 0.01 * 0.7);
	electron.setDEtaIn(-0.01 + 0.01 * 0.01);
	electron.setHadOverEm(-0.07 - 0.01 * 0.07);
	electron.setSuperClusterEta(2.6);
	assert(electron.isInEndCapRegion());
	assert(electron.sigmaIEtaIEta() < 0.03);
	assert(fabs(electron.dPhiIn()) < 0.7);
	assert(fabs(electron.dEtaIn()) < 0.01);
	assert(electron.HadOverEm() < 0.07);
	ASSERT_EQUAL(true, electron.VBTF_WP95_ElectronID());
}

void TestElectron::testElectronCharge() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setCharge(2);
	ASSERT_EQUAL(2, electron.charge());
}

void TestElectron::testElectronChargeInCopy() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setCharge(2);
	Electron copyElectron(electron);
	ASSERT_EQUAL(2, copyElectron.charge());
}

void TestElectron::testElectronInCollection() {
	ElectronCollection coll;
	ElectronPointer electron(new Electron(50, 3, 0, 40));
	ElectronPointer electron2(new Electron(50, 3, 0, 40));
	electron->setCharge(2);
	electron2->setCharge(2);
	coll.push_back(electron);
	coll.push_back(electron2);
	ASSERT_EQUAL(2, coll.front()->charge());
}

void TestElectron::testElectronInSTDCollection() {
	std::vector<Electron> coll;
	Electron electron(50, 3, 0, 40);
	Electron electron2(50, 3, 0, 40);
	electron.setCharge(2);
	electron2.setCharge(2);
	coll.push_back(electron);
	coll.push_back(electron2);
	ASSERT_EQUAL(2, coll.front().charge());
}

void TestElectron::testElectronSetMass() {
	Electron electron = Electron(50, 3, 0, 40);
	electron.setMass(500);
	ASSERT_EQUAL(500, electron.mass());
}

void TestElectron::testGSFTrack() {
	TrackPointer track = TrackPointer(new Track(20, 20, 0, 0));
	goodElectron->setGSFTrack(track);
	ASSERT_EQUAL(track, goodElectron->GSFTrack());
}

cute::suite make_suite_TestElectron() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestElectron, testRelativeIsolation));
	s.push_back(CUTE_SMEMFUN(TestElectron, testEcalIsolation));
	s.push_back(CUTE_SMEMFUN(TestElectron, testHcalIsolation));
	s.push_back(CUTE_SMEMFUN(TestElectron, testTrackerIsolation));

	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70Barrel));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelNegativeValues));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelNegativeSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailNegativeDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailNegativeDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelFailHadOverEm));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70BarrelNegativeHadOverEm));

	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70Endcap));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapNegativeValues));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapFailSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapNegativeSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapFailDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapFailNegativeDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapNegativeDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapFailHadOverEm));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP70EndcapNegativeHadOverEm));

	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95Barrel));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelNegativeValues));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelNegativeSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailNegativeDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailNegativeDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelFailHadOverEm));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95BarrelNegativeHadOverEm));

	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95Endcap));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapNegativeValues));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapFailSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapNegativeSigmaIEtaIEta));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapFailDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapFailNegativeDPhiIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapNegativeDEtaIn));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapFailHadOverEm));
	s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFWP95EndcapNegativeHadOverEm));

	s.push_back(CUTE_SMEMFUN(TestElectron, testElectronCharge));
	s.push_back(CUTE_SMEMFUN(TestElectron, testElectronChargeInCopy));
	s.push_back(CUTE_SMEMFUN(TestElectron, testElectronInCollection));
	s.push_back(CUTE_SMEMFUN(TestElectron, testElectronSetMass));
	s.push_back(CUTE_SMEMFUN(TestElectron, testElectronInSTDCollection));

	s.push_back(CUTE_SMEMFUN(TestElectron, testGSFTrack));
	return s;
}
