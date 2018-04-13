#include "PixDetector.hh"
#include <G4VSensitiveDetector.hh>

#include <G4MultiFunctionalDetector.hh>
#include <G4SDParticleFilter.hh>
#include <G4VPrimitiveScorer.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4PSNofSecondary.hh>
#include <G4PSMinKinEAtGeneration.hh>
#include <G4PSTrackLength.hh>
#include <G4PSNofStep.hh>

PixDetector::PixDetector(G4String name, G4int depth=0) : G4MultiFunctionalDetector(name)
{
	G4String filterName, particleName;
	G4SDParticleFilter* gammaFilter = new G4SDParticleFilter(
			filterName = "gammaFilter",
			particleName = "gamma");
	G4SDParticleFilter* electronFilter = new G4SDParticleFilter(
			filterName = "electronFilter",
			particleName = "e-");
	G4SDParticleFilter* positronFilter = new G4SDParticleFilter(
			filterName = "positronFilter",
			particleName = "e+");
	G4SDParticleFilter* epFilter = new G4SDParticleFilter(
			filterName = "epFilter");
	epFilter->add(particleName="e-");
	epFilter->add(particleName="e+");
	/* Register primitives on construction
	 *
	 * The second argument in each primitive means the "level" of geometrical hierarchy,
	 * the copy number of that level is used as the key of the G4THitsMap.
	 * For absorber (j = 0), the copy number of its own physical volume is used.
	 * For gap (j = 1), the copy number of its mother physical volume is used, since there
	 * is only one physical volume of gap is placed with respect to its mother. */
	G4VPrimitiveScorer* primitive;
	primitive = new G4PSEnergyDeposit("eDep",depth);
	this->RegisterPrimitive(primitive);
	/*
	primitive = new G4PSNofSecondary("nGamma",depth);
	primitive->SetFilter(gammaFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSNofSecondary("nElectron",depth);
	primitive->SetFilter(electronFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSNofSecondary("nPositron",depth);
	primitive->SetFilter(positronFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSMinKinEAtGeneration("minEkinGamma",depth);
	primitive->SetFilter(gammaFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSMinKinEAtGeneration("minEkinElectron",depth);
	primitive->SetFilter(electronFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSMinKinEAtGeneration("minEkinPositron",depth);
	primitive->SetFilter(positronFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSTrackLength("trackLength",depth);
	primitive->SetFilter(epFilter);
	this->RegisterPrimitive(primitive);
	primitive = new G4PSNofStep("nStep",depth);
	primitive->SetFilter(epFilter);
	this->RegisterPrimitive(primitive);
	*/

}

PixDetector::~PixDetector()
{
	;
}
