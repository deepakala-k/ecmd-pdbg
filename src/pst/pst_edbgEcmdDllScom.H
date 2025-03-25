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

#ifndef pst_edbgEcmdDllScom_H
#define pst_edbgEcmdDllScom_H

#include <odyssey_edbgEcmdDllScom.H>
#include <odyssey_scominfo.H>
#include <pst_scominfo.H>
#include <pst_cu.H>

struct pst_chipUnit_t {
  pstChipUnits_t ekbChipUnit;
  std::string chipUnitType;
  std::string pdbgClassType;
};

// mapping table for ekb, ecmd and pdbg
const pst_chipUnit_t PST_ChipUnitTable[] = {
  //TODO - PST : Fix it to PST_NO_CU after getting the translation files
    {NO_CU, "", "pib"}, // chip unit not passed. Then,use pib.
};

uint32_t pst_dllQueryScom(const ecmdChipTarget &i_target,
                          std::list<ecmdScomData> &o_queryData,
                          uint64_t i_address, ecmdQueryDetail_t i_detail);

uint32_t pst_dllGetScom(const ecmdChipTarget &i_target, uint64_t i_address,
                        ecmdDataBuffer &o_data);

uint32_t pst_dllPutScom(const ecmdChipTarget &i_target, uint64_t i_address,
                        const ecmdDataBuffer &i_data);

uint32_t pst_dllPutScomUnderMask(const ecmdChipTarget &i_target,
                                 uint64_t i_address,
                                 const ecmdDataBuffer &i_data,
                                 const ecmdDataBuffer &i_mask);

uint32_t pst_convertPDBGClassString_to_CUString(std::string pdbgClassType,
                                                 std::string &o_chipUnitType);

#endif
