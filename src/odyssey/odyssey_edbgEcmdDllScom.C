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

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

// Headers from pdbg
extern "C" {
    #include <libpdbg.h>
    }
    
    // Headers from ecmd-pdbg
    #include <edbgCommon.H>
    #include <edbgOutput.H>
    #include <odyssey_edbgEcmdDllScom.H>
    #include <odyssey_scominfo.H>
    
    #include <assert.h>
    
    #ifndef ECMD_REMOVE_SCOM_FUNCTIONS
    
    uint32_t odyssey_convertCUEnum_to_String(odysseyChipUnits_t i_odysseyCU,
                                             std::string &o_chipUnitType) {
      uint32_t rc = ECMD_SUCCESS;
      uint32_t l_index;
    
      for (l_index = 0;
           l_index < (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t));
           l_index++) {
        // Looking for input ekb chip unit in table
        if (i_odysseyCU == OdysseyChipUnitTable[l_index].ekbChipUnit)
          break;
      }
      // Can't find i_odysseyCU in table
      if (l_index >= (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t))) {
        return out.error(EDBG_GENERAL_ERROR, FUNCNAME,
                         "Unknown chip unit enum:%d\n", i_odysseyCU);
      }
      o_chipUnitType = OdysseyChipUnitTable[l_index].chipUnitType;
      return rc;
    }
    
    // convert chipunit string to pdbg class type, as pdbg does not accept ecmd
    // strings
    uint32_t
    odyssey_convertCUString_to_pdbgClassString(std::string cuString,
                                               std::string &o_pdbgClassType) {
      uint32_t rc = ECMD_SUCCESS;
      uint32_t l_index;
    
      for (l_index = 0;
           l_index < (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t));
           l_index++) {
        // Looking for input chip unit type in table
        if (cuString == OdysseyChipUnitTable[l_index].chipUnitType)
          break;
      }
      // Can't find cuString in table
      if (l_index >= (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t))) {
        return out.error(EDBG_GENERAL_ERROR, FUNCNAME, "Unknown chip unit:%S\n",
                         cuString.c_str());
      }
    
      o_pdbgClassType = OdysseyChipUnitTable[l_index].pdbgClassType;
      return rc;
    }
    
    // convert chipunit string to pdbg class type, as pdbg does not accept ecmd
    // strings
    uint32_t
    odyssey_convertPDBGClassString_to_CUString(std::string pdbgClassType,
                                               std::string &o_chipUnitType) {
    
      uint32_t rc = ECMD_SUCCESS;
      uint32_t l_index;
    
      for (l_index = 0;
           l_index < (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t));
           l_index++) {
        // Looking for input chip unit type in table
        if (pdbgClassType == OdysseyChipUnitTable[l_index].pdbgClassType)
          break;
      }
      // Can't find pdbgClassType in table
      if (l_index >= (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t))) {
        return out.error(EDBG_GENERAL_ERROR, FUNCNAME,
                         "Unknown pdbg class unit:%s\n", pdbgClassType.c_str());
      }
    
      o_chipUnitType = OdysseyChipUnitTable[l_index].chipUnitType;
      return rc;
    }
    
    // convert chipunit string to ekb chip unit
    uint32_t odyssey_convertCUString_to_CUEnum(std::string i_chipUnitType,
                                               odysseyChipUnits_t o_odysseyCU) {
    
      uint32_t rc = ECMD_SUCCESS;
      uint32_t l_index;
    
      for (l_index = 0;
           l_index < (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t));
           l_index++) {
        // Looking for input ekb chip unit in table
        if (i_chipUnitType == OdysseyChipUnitTable[l_index].chipUnitType)
          break;
      }
      // Can't find i_odysseyCU in table
      if (l_index >= (sizeof(OdysseyChipUnitTable) / sizeof(odyssey_chipUnit_t))) {
        return out.error(EDBG_GENERAL_ERROR, FUNCNAME,
                         "Unknown chip unit string:%s\n", i_chipUnitType);
      }
      o_odysseyCU = OdysseyChipUnitTable[l_index].ekbChipUnit;
      return rc;
    }
    
    #endif // ECMD_REMOVE_SCOM_FUNCTIONS
    