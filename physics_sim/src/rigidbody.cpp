extern "C"
{
#include "math/vmath.h"
#include "math/qmath.h"
}

#include "rigidbody.hpp"

void Rigidbody::UpdateAttitude(double timestep)
{
    const double mag = vec3_mag(&this->ang_vel);
    if(mag == 0)
        return; // otherwise assert will fail on normalization

    quat rot = quat_from_axis(&this->ang_vel, mag * timestep);
    quat tot_q = quat_mul(&rot, &this->attit);

    this->attit = quat_norm(&tot_q); // prevent error buildup
}

void Rigidbody::UpdateAngVel(const vec3 &moment, double timestep)
{
    const vec3 ang_impulse = vec3_smul(&moment, timestep);
    this->ang_vel = vec3_add(&this->ang_vel, &ang_impulse);
}