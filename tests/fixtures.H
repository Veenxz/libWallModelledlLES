/*---------------------------------------------------------------------------* \
License
    This file is part of libWallModelledLES.

    libWallModelledLES is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libWallModelledLES is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with libWallModelledLES. 
    If not, see <http://www.gnu.org/licenses/>.

Description
    Various helper functions for testing the software.
    
Contributors/Copyright:
    2019 Timofey Mukha

SourceFiles
    fixtures.C

\*---------------------------------------------------------------------------*/

#include "codeRules.H"
#include "fvCFD.H"
#undef Log
#include "gtest.h"
#include "gmock/gmock.h"


// construct h given mesh
void createSamplingHeightField(const Foam::fvMesh & mesh);

// construct U given mesh
void createVelocityField(const Foam::fvMesh & mesh);

// construct nut given mesh
void createNutField(const Foam::fvMesh & mesh);

// construct nu given mesh and nut (used for bcs)
void createNuField
(
    const Foam::fvMesh & mesh,
    const Foam::volScalarField & nut
);

// Create a fvMesh
Foam::autoPtr<Foam::fvMesh> createMesh(const Foam::Time & runTime);

// Create subregistry for sampled fields for a given patch
void createWallModelSubregistry(const fvMesh & mesh, const fvPatch & patch);

class ChannelFlow : public ::testing::Test
{


    public:
        ChannelFlow()
        {
            system("cp -r testCases/channel_flow/system .");
            system("cp -r testCases/channel_flow/constant .");
            system("cp -r testCases/channel_flow/0 .");

        }

        virtual ~ChannelFlow()
        {
            system("rm -r system");
            system("rm -r constant");
            system("rm -r 0");
        }
};

