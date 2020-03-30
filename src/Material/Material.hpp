#pragma once

#include "Common/CommonIncludes.hpp"
#include "ONB.hpp"

class Material {
public: 
    virtual bool Emits() const {return false;}

    virtual rgb EmittedRadiance(const ONB& onb, const vector3& outGoing) { return rgb(0,0,0); }

    virtual rgb AmbientResponse(const ONB& onb, const vector3& incident) { return rgb(0,0,0); }

    virtual bool ExplicitBrdf(const ONB& onb, const vector3& outGoing0, const vector3& outGoing1, rgb& outAlbedo, real& brdfValue) { return false; }

    virtual bool DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf, real& brdf) { return false; }

    virtual bool SpecularDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf) { return false; }

    virtual bool TransmissionDirection(const ONB& onb, const vector3& incident) { return false; }


    virtual bool IsDiffuse() {return false;}
    virtual bool isSpecular() {return false;}
    virtual bool isTransmissive() {return false;}
    virtual int  causticPhotons() {return 0;}
    virtual int  globalPhotons() {return 0;}
    virtual rgb  photonColor() {return rgb(0);}

};
