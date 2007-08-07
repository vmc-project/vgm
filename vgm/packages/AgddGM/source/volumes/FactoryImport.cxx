// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/volumes/Factory.h>
#include <AgddGM/volumes/Placement.h>
#include <AgddGM/volumes/Volume.h>
#include <AgddGM/materials/MaterialFactory.h>
#include <AGDD/AGDD_Material_Model.hh>
#include <AGDD/AGDD_Model.hh>

#include <AgddGM/solids/Torus.h>
#include <AgddGM/solids/Sphere.h>
#include <AgddGM/solids/Box.h>
#include <AgddGM/solids/Cons.h>
#include <AgddGM/solids/Polycone.h>
#include <AgddGM/solids/Trap.h>
#include <AgddGM/solids/Trd.h>
#include <AgddGM/solids/Tubs.h>
#include <AgddGM/solids/BooleanSolid.h>


#include <iostream>
#include <sstream>
using namespace std;
using namespace agdd;

// This machinery might be best moved into BaseVGM
#include "BaseVGM/common/utilities.h"
static ostream& debug()
{
    BaseVGM::DebugInfo();
    return cout;                // should match what is used in DebugInfo!
}
static ostream& warn() { return cerr << "VGM warning:  "; }
#define DEBUG \
    if(! Debug()) {;}\
    else debug()
bool Warn () { return true; }   // always
#define WARN \
    if (! Warn()) {;}\
    else warn()


// import/export
//
bool AgddGM::Factory::Import(void* blech)
{
    // Hail mary, full of grace....
    return Import(static_cast<AGDD*>(blech));
}

bool AgddGM::Factory::Import(AGDD* agdd)
{
    if (fAgdd) fTop = 0;
    fAgdd = agdd;

    {
	size_t siz = agdd->m_materials.size();
	VGM::IMaterialFactory *imf = this->MaterialFactory();
	AgddGM::MaterialFactory* material_factory =
	    dynamic_cast<AgddGM::MaterialFactory*>(imf);
	assert(material_factory);
	for (size_t ind=0; ind<siz; ++ind) {
	    material_factory->AddMaterials(agdd->m_materials[ind]);
	}
	if (!imf->Import()) return false;
    }

    {
	size_t siz = agdd->m_sections.size();
	for (size_t ind=0; ind<siz; ++ind) {
	    if (!ImportSection(agdd->m_sections[ind])) return false;
	}
    }
    return true;
}

/* Importing section assumptions:

- Only one section is supported

- Either the sections's top level volume must be a composition with an
envelope and the envelope must be directly a solid (not another
composition) or the top volume must be directly a solid.  This solid
will become the world volume.

- Other compositions may but need not have envelopes.

*/

bool AgddGM::Factory::ImportSection(AGDD_Section* sec)
{
    if (fTop) {
	WARN << "already imported a section, whill not import another.\n";
	return false;
    }

    AGDD_Solid* top =
	dynamic_cast<AGDD_Solid*>(sec->m_top_volume);
    if (!top) {
	AGDD_Composition* top_comp =
	    dynamic_cast<AGDD_Composition*>(sec->m_top_volume);
	if (top_comp) {
	    top = dynamic_cast<AGDD_Solid*>(top_comp->m_envelope);
	}
    }

    if (!top) {
	WARN << "top volume of first section must either be a solid or a composition with a solid envelope\n";
	return false;
    }


    AgddGM::Volume* top_vol = this->ImportSolid(top);
    if (!top_vol) {
	cerr << "Error: failed to import a top volume!\n";
	return false;
    }
    DEBUG << "Top volume is " << top_vol->Name() << endl;

    HepGeom::Transform3D transform;
    transform.setIdentity();
    fTop = new AgddGM::Placement(top->getName(),top_vol,0,transform);

    // First, slurp in all solid and boolean volumes
    vector<AGDD_Volume*> todo;
    size_t siz = sec->m_volumes.size();
    for (size_t ind=0; ind<siz; ++ind) {
	AGDD_Volume* vol = sec->m_volumes[ind];

	if (AGDD_Solid* solid = dynamic_cast<AGDD_Solid*>(vol)) {
	    this->ImportSolid(solid);
	}
	else if (AGDD_BooleanVolume* bol = dynamic_cast<AGDD_BooleanVolume*>(vol)) {
	    this->ImportBoolean(bol);
	}
	else todo.push_back(vol);
    }

    siz = todo.size();
    for (size_t ind=0; ind<siz; ++ind) {
	AGDD_Volume* vol = todo[ind];

	AGDD_Composition* comp = dynamic_cast<AGDD_Composition*>(vol);
	if (!comp) {
	    WARN << "ImportSection: skipping non composition \""
		 << vol->getName() << "\"\n";
	    continue;
	}
	if (!comp->m_envelope) {
	    WARN << "ImportSection: skipping composition \""
		 << vol->getName() << "\" w/out envelope\n";
	    continue;
	}

	WARN << "ImportSection: importing AGDD_composition \""
	     << vol->getName() << "\"\n";

	this->ImportComposition(comp,transform,top_vol);
    }

    return true;
}


/** A composition is a little goofy in that it specifies both what is
 * inside it (positions of volumes) and what is outside it (envelope)
 * and it, itself can be referenced as a volume.  Since the envelope
 * is optional as long as there is a parent (and vice versa) the
 * caller must treat the returned volume differently depending on how
 * the composition is defined.  Specifically:
 *
 * If no parent and no envelope, error, return 0.
 *
 * If a composition envelope exists the passed in parent and transform
 * will be ignored.  All positions will be relative to the envelope.
 * The envelope will be returned.  The envelope is not placed (but
 * should be by the caller).
 *
 * O.w. the passed in parent will be used and all positions will have
 * the transform additionally applied.  The parent will be returned.
 *
 */

AgddGM::Volume*
AgddGM::Factory::ImportComposition(AGDD_Composition* comp,
				   const HepGeom::Transform3D& pretrans,
				   AgddGM::Volume* parent_vol)
{
    AGDD_Solid* envelope_sol =
	dynamic_cast<AGDD_Solid*>(comp->m_envelope);
    if (!parent_vol && !envelope_sol) {
	WARN << "ImportComposition \"" << comp->getName()
	     << "\" neither parent nor envelope given\n";
	return 0;
    }
    DEBUG << "ImportComposition \"" << comp->getName() << "\"\n";
    
    HepGeom::Transform3D transform = pretrans;
    if (envelope_sol) {
	parent_vol = this->ImportSolid(envelope_sol);
	transform.setIdentity();
    }

    size_t siz = comp->m_positions.size();
    for (size_t ind=0; ind<siz; ++ind) {
	const AGDD_Position* pos = comp->m_positions[ind];
	this->ImportPosition(pos,parent_vol,transform);
    }

    return parent_vol;
}

// Like a composition, but never has an envelope
AgddGM::Volume* AgddGM::Factory::ImportStack(AGDD_Stack* stk,
					     const HepGeom::Transform3D& transform,
					     AgddGM::Volume* parent_vol)
{
    if (!parent_vol) {
	WARN << "ImportStack \"" << stk->getName() << "\" not given a parent\n";
	return 0;
    }
    
    size_t siz = stk->m_positions.size();
    for (size_t ind=0; ind<siz; ++ind) {
	const AGDD_RelativePosition* pos = stk->m_positions[ind];
	this->ImportPosition(pos,parent_vol,transform);
    }

    return parent_vol;
}

#include <cfloat>
static string dump(const HepGeom::Transform3D& trans)
{
    CLHEP::HepRotation rotation = trans.getRotation();
    CLHEP::Hep3Vector t = trans.getTranslation();

    double angleX;
    double angleY;
    double angleZ;
    double cosb = sqrt(rotation.xx()*rotation.xx() + rotation.yx()*rotation.yx());
    if (cosb > 16*FLT_EPSILON) {
	angleX = atan2( rotation.zy(), rotation.zz());
	angleY = atan2(-rotation.zx(), cosb);
	angleZ = atan2( rotation.yx(), rotation.xx());
    }
    else{
	angleX = atan2(-rotation.yz(), rotation.yy());
	angleY = atan2(-rotation.zx(), cosb);
	angleZ = 0.;
    }

    stringstream ss;
    ss<<"["<<t.x()<<","<<t.y()<<","<<t.z()<<"]"
      <<"->"
      <<"("<<angleX<<","<<angleY<<","<<angleZ<<")";
    return ss.str();
}
AgddGM::BooleanSolid* AgddGM::Factory::BuildBoolean(AGDD_BooleanVolume* bol, int index)
{
    VGM::BooleanType type = VGM::kUnknownBoolean;
    //VGM::ISolid *a, VGM::ISolid *b,
    //const VGM::Transform& trans);    
    if (dynamic_cast<AGDD_Intersection*>(bol)) {
	type = VGM::kIntersection;
    }
    if (dynamic_cast<AGDD_Subtraction*>(bol)) {
	type = VGM::kSubtraction;
    }
    if (dynamic_cast<AGDD_Union*>(bol)) {
	type = VGM::kUnion;
    }

    AGDD_SinglePosition* posa = bol->m_positions[index];
    AGDD_SinglePosition* posb = bol->m_positions[index+1];

    HepGeom::Transform3D trana = posa->getTransform (0);
    HepGeom::Transform3D tranb = posb->getTransform (0);

    VGM::ISolid* solida = this->MakeSolid(dynamic_cast<AGDD_Solid*>(posa->m_volume.m_ref));
    VGM::ISolid* solidb = 0;
    if (bol->m_positions.size() - index > 2) {
	solidb = BuildBoolean(bol,index+1);
    }
    else {
	solidb = this->MakeSolid(dynamic_cast<AGDD_Solid*>(posb->m_volume.m_ref));
    }

    
    AgddGM::BooleanSolid* vgm_bs =
	new AgddGM::BooleanSolid(type,solida,solidb,trana,tranb);
    // fixme: do I need to put each on the SolidStore?

    return vgm_bs;
}

static string boolean_name(AGDD_BooleanVolume* bol)
{
    if (dynamic_cast<AGDD_Intersection*>(bol)) {
	return "intersection";
    }
    if (dynamic_cast<AGDD_Subtraction*>(bol)) {
	return "subtraction";
    }
    if (dynamic_cast<AGDD_Union*>(bol)) {
	return "union";
    }
    return "boolean";
}

AgddGM::Volume*
AgddGM::Factory::ImportBoolean(AGDD_BooleanVolume* bol)
{
    AgddGM::Volume* vgm_vol = fV2V[bol];
    if (vgm_vol) return vgm_vol;

    // Do a check first and build up a name
    size_t siz = bol->m_positions.size();
    stringstream ss;
    ss << boolean_name(bol);
    for (size_t ind=0; ind<siz; ++ind) {
	AGDD_SinglePosition* pos = bol->m_positions[ind];
	AGDD_Volume* vol = pos->m_volume.m_ref;
	if (!dynamic_cast<AGDD_Solid*>(vol)) {
	    WARN << "ImportBoolean: no support for non-solid volume, can't import \""
		 << vol->getName() << "\"\n";
	    return 0;
	}
	ss << "_" << vol->getName();
    }
    string name = ss.str();

    AgddGM::BooleanSolid* vgm_bol = this->BuildBoolean(bol,0);
    SolidStore().push_back(vgm_bol);
    vgm_bol->SetName(name);
    
    // Use first solid to feed to AgddGM::Volume
    AGDD_SinglePosition* pos0 = bol->m_positions[0];
    AGDD_Volume* vol0 = pos0->m_volume.m_ref;
    AGDD_Solid* sol0 = dynamic_cast<AGDD_Solid*>(vol0);

    vgm_vol = new AgddGM::Volume(vgm_bol,sol0);
    vgm_vol->SetName(name);
    VolumeStore().push_back(vgm_vol);

    fV2V[bol] = vgm_vol;
    return vgm_vol;

} // ImportBoolean

// Evaluate position, placing it's volumes in the given parent and
// applying the given transform in addition to the positioned one.

int AgddGM::Factory::ImportPosition(const AGDD_Position* pos,
				    AgddGM::Volume* parent,
				    const HepGeom::Transform3D& transform)
{
    AGDD_Volume* agdd_vol = pos->m_volume.m_ref;
    string name = agdd_vol->getName();

    int npos = fP2C[pos];
    if (npos) {
	WARN << "ImportPosition already imported pos " << (void*)pos << " volume \""
	     << name << "\" cardinality=" << npos << endl;
	return npos;
    }
    npos = pos->getCardinality();
    fP2C[pos] = npos;


    /* agdd_vol is either a solid, boolean or composition.
     *
     * if composition it either has an envelope or it doesn't
     */

    DEBUG << "ImportPosition "<<(void*)pos<<" volume \""
	 << name << "\" cardinality " << npos
	 << " parent \"" << (parent?parent->Name():"TOP") << "\"\n";


    for (int ipos=0; ipos<npos; ++ipos) {

	HepGeom::Transform3D trans = transform * pos->getTransform(ipos);

	AgddGM::Volume* vgm_vol = this->ImportVolume(agdd_vol,parent,trans);

	if (!vgm_vol || vgm_vol == parent) continue;

	DEBUG << "ImportingPosition with volume \""
	     << vgm_vol->Name() << "\" (\""<< name << "\") trans="
	     << dump(trans)
	     << "\n";
	
	new AgddGM::Placement(name,vgm_vol,parent,trans);
    }

    return npos;

} // ImportPosition



VGM::ISolid* AgddGM::Factory::FindSolid(string name)
{
    VGM::SolidStore& ss = SolidStore();

    size_t siz=ss.size();
    for(size_t ind=0; ind<siz; ++ind) {
	if (ss[ind]->Name() == name) return ss[ind];
    }
    return 0;
}
AgddGM::Volume* AgddGM::Factory::FindVolume(string name)
{
    VGM::VolumeStore& vs = VolumeStore();

    size_t siz=vs.size();
    for(size_t ind=0; ind<siz; ++ind) {
	if (vs[ind]->Name() != name) continue;
	return dynamic_cast<AgddGM::Volume*>(vs[ind]);
    }
    return 0;
}

AgddGM::Volume* AgddGM::Factory::ImportVolume(AGDD_Volume* vol,
					      AgddGM::Volume* parent,
					      const HepGeom::Transform3D& transform)
{
    AgddGM::Volume* ret = fV2V[vol];
    if (ret) return ret;

    //ret = this->FindVolume(vol->getName());
    //if (ret) return ret;

    if (AGDD_Solid* solid = dynamic_cast<AGDD_Solid*>(vol)) {
	ret = this->ImportSolid(solid);
    }

    else if (AGDD_Composition* comp = dynamic_cast<AGDD_Composition*>(vol)) {
	ret = this->ImportComposition(comp,transform,parent);
    }

#if 0
    else if (AGDD_Compact* comp = dynamic_cast<AGDD_Compact*>(vol)) {
        cerr<< "Not importing compact volume " << vol->getName() << endl;
	assert(0);
        ret = 0;
    }
#endif

    else if (AGDD_Stack* stk = dynamic_cast<AGDD_Stack*>(vol)) {
        ret = this->ImportStack(stk,transform,parent);
    }

    else if (AGDD_BooleanVolume* bol = dynamic_cast<AGDD_BooleanVolume*>(vol)) {
        ret = this->ImportBoolean(bol);
    }
    else { ret = 0; }
    if (!ret) return ret;

    return ret;
}

VGM::ISolid* AgddGM::Factory::MakeSolid(AGDD_Solid* solid)
{
    string solname = solid->getName();
    VGM::ISolid* vgm_sol = FindSolid(solname);
    if (vgm_sol) return vgm_sol;


    if (AGDD_Torus* torus = dynamic_cast<AGDD_Torus*>(solid)) {
	vgm_sol = new AgddGM::Torus(torus);
    }
    else if (AGDD_Sphere* sphere = dynamic_cast<AGDD_Sphere*>(solid)) {
	vgm_sol = new AgddGM::Sphere(sphere);
    }
    else if (AGDD_Box* box = dynamic_cast<AGDD_Box*>(solid)) {
	vgm_sol = new AgddGM::Box(box);
    }
    else if (AGDD_Trapezoid* trap = dynamic_cast<AGDD_Trapezoid*>(solid)) {
	vgm_sol = new AgddGM::Trd(trap);
    }
    else if (AGDD_GeneralTrapezoid* trap =
	     dynamic_cast<AGDD_GeneralTrapezoid*>(solid)) {
	vgm_sol = new AgddGM::Trap(trap);
    }
    else if (AGDD_Tube* tub = dynamic_cast<AGDD_Tube*>(solid)) {
	vgm_sol = new AgddGM::Tubs(tub);
    }
    else if (AGDD_Cone* cone = dynamic_cast<AGDD_Cone*>(solid)) {
	vgm_sol = new AgddGM::Cons(cone);
    }
    else if(AGDD_Pcon* pcon = dynamic_cast<AGDD_Pcon*>(solid)) {
	vgm_sol = new AgddGM::Polycone(pcon);
    }
    else vgm_sol = 0;

    if (vgm_sol) SolidStore().push_back(vgm_sol);
    return vgm_sol;
}

AgddGM::Volume* AgddGM::Factory::ImportSolid(AGDD_Solid* sol)
{
    AgddGM::Volume* vgm_vol = fV2V[sol];
    if (vgm_vol) return vgm_vol;
    

    VGM::ISolid* vgm_sol = MakeSolid(sol);
    if (!vgm_sol) {
	WARN << "Can not import AGDD_Solid \"" << sol->getName() << "\"\n";
	return 0;
    }
    vgm_vol = new AgddGM::Volume(vgm_sol,sol);
    VolumeStore().push_back(vgm_vol);
    fV2V[sol] = vgm_vol;

    return vgm_vol;
}

