// IBM_PROLOG_BEGIN_TAG
/*
 * eCMD for pdbg Project
 *
 * Copyright 2017,2018 IBM International Business Machines Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// IBM_PROLOG_END_TAG

#ifndef odyssey_edbgEcmdDllScom_H
#define odyssey_edbgEcmdDllScom_H

#include <odyssey_scominfo.H>

struct odyssey_chipUnit_t {
  odysseyChipUnits_t ekbChipUnit;
  std::string chipUnitType;
  std::string pdbgClassType;
};

// mapping table for ekb, ecmd and pdbg
const odyssey_chipUnit_t OdysseyChipUnitTable[] = {
    {ODYSSEY_NO_CU, "", ""},
    {ODYSSEY_MEMPORT_CHIPUNIT, "mp", "mem_port"},
    {ODYSSEY_PERV_CHIPUNIT, "perv", "ody_chiplet"},
    {ODYSSEY_OMI_CHIPUNIT, "omi", "omi"},
};

// convert ekb chip unit enum to ecmd chinpunit string
uint32_t odyssey_convertCUEnum_to_String(odysseyChipUnits_t i_odysseyCU,
                                         std::string &o_chipUnitType);

// convert ecmd chipunit string to pdbg class type, as pdbg does not accept ecmd
// strings
uint32_t
odyssey_convertCUString_to_pdbgClassString(std::string cuString,
                                           std::string &o_pdbgClassType);

// convert emcd chipunit string to pdbg class type, as pdbg does not accept ecmd
// strings
uint32_t
odyssey_convertPDBGClassString_to_CUString(std::string pdbgClassType,
                                           std::string &o_chipUnitType);

// convert ecmd chipunit string to ekb chip unit
uint32_t odyssey_convertCUString_to_CUEnum(std::string i_chipUnitType,
                                           odysseyChipUnits_t o_odysseyCU);

#endif
