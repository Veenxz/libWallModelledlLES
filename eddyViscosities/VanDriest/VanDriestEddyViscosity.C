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

\*---------------------------------------------------------------------------*/

#include "VanDriestEddyViscosity.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{
    defineTypeNameAndDebug(VanDriestEddyViscosity, 0);
    addToRunTimeSelectionTable(EddyViscosity, VanDriestEddyViscosity, Dictionary);
    addToRunTimeSelectionTable(EddyViscosity, VanDriestEddyViscosity, TypeAndDictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::VanDriestEddyViscosity::VanDriestEddyViscosity
(
    const dictionary & dict,
    Sampler & sampler
)
:
    EddyViscosity(dict, sampler),
    APlus_(dict.lookupOrDefault<scalar>("APlus", 18)),
    kappa_(dict.lookupOrDefault<scalar>("kappa", 0.4))
{
    if (debug)
    {        
        printCoeffs();
    }
    
}

Foam::VanDriestEddyViscosity::VanDriestEddyViscosity
(
    const word & modelName,
    const dictionary & dict,
    Sampler & sampler
)
:
    EddyViscosity(modelName, dict, sampler),
    APlus_(dict.lookupOrDefault<scalar>("APlus", 18)),
    kappa_(dict.lookupOrDefault<scalar>("kappa", 0.4))
{
    if (debug)
    {        
        printCoeffs();
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::VanDriestEddyViscosity::printCoeffs() const
{
    Info<< nl << "VanDriest eddy viscosity model" << nl;
    Info<< token::BEGIN_BLOCK << incrIndent << nl;
    Info<< indent << "APlus" << indent << APlus_ << nl;
    Info<< indent << "kappa" << indent <<  kappa_ << nl;
    Info<< token::END_BLOCK << nl << nl;
}

Foam::scalarList Foam::VanDriestEddyViscosity::value
(
    label index, 
    const scalarList & y,
    scalar uTau,
    scalar nu
) const
{  
    const scalarList yPlus = y*uTau/nu;
    
    scalarList values(y.size(), 0.0);
     
    forAll(values, i)
    {
        values[i] = kappa_*uTau*y[i]*sqr(1 - exp(-yPlus[i]/APlus_));
    }
    return values;
}

// ************************************************************************* //
