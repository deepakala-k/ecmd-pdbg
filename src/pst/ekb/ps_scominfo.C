/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* Host Firmware for POWER Systems Project                                */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2018,2024                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
///
/// @file ps_scominfo.C
/// @brief PS chip unit SCOM address platform translation code
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: Cronus, HB, HWSV
///

// includes
#include <ps_scominfo.H>
#include <pst_scom_addr.H>
#include <pst_scominfo.H>
#ifndef __SBE__
    #include <stdio.h>
#endif

#define PS_SCOMINFO_C

extern "C"
{
    // See header file for function description
    uint64_t ps_scominfo_createChipUnitScomAddr(
        const pstChipUnits_t i_psCU,
        const uint8_t i_ecLevel,
        const uint8_t i_chipUnitNum,
        const uint64_t i_scomAddr,
        const pstTranslationMode_t i_mode)
    {
        uint8_t l_rc = 0;
        pst_scom_addr l_scom(i_scomAddr, PS);
        uint8_t l_chipletId = 0;
        uint8_t l_sat = l_scom.getSatId();
        uint8_t l_ring = l_scom.getRingId();

        do
        {
            // If chip unit type is a chip, return input address
            if (i_psCU == NO_CU)
            {
                l_scom.setAddr(i_scomAddr);
                break;
            }

            // Set the chiplet ID
            l_rc = l_scom.getChipletId(i_chipUnitNum, i_psCU, l_chipletId);

            if (l_rc)
            {
                break;
            }

            l_scom.setChipletId(l_chipletId);

            // Set other address fields (ringId, satId, etc...)
            // for Chip unit types that are needed.
            switch (i_psCU)
            {
                case TBUSL_CHIPUNIT:
                    if (l_scom.isIndirect())
                    {
                        l_scom.setTbuslGroup(i_chipUnitNum);
                    }
                    else
                    {
                        l_scom.setRingId(TBUS_RING_SF0 + (i_chipUnitNum % NUM_TBUSL_PER_TBUS));
                    }

                    break;

                case OMI_CHIPUNIT:
                    {
                        uint8_t l_cplt_omi = i_chipUnitNum % NUM_OMI_PER_CPLT;
                        uint8_t l_grp = l_cplt_omi / NUM_OMI_PER_GRP;
                        uint8_t l_lane = 0;
                        uint8_t l_reg = l_scom.getSatOffset() - DL0_REG_OFFSET0;

                        if (MC_RING_OMI0 <= l_ring && l_ring <= MC_RING_OMI3)
                        {
                            l_scom.setRingId(MC_RING_OMI0 + ((i_chipUnitNum / NUM_OMI_PER_GRP) % NUM_MCC_PER_CPLT));
                            l_scom.setSatOffset((l_reg % NUM_REGS_PER_DL) +
                                                ((i_chipUnitNum % NUM_OMI_PER_GRP) * NUM_REGS_PER_DL) +
                                                DL0_REG_OFFSET0);
                        }
                        else
                        {
                            if (l_scom.getIoTxRxBit())
                            {
                                //TX
                                l_lane = (l_scom.getIoLane() % NUM_TX_LANES_PER_OMI) + ((l_cplt_omi % NUM_OMI_PER_GRP) * NUM_TX_LANES_PER_OMI);
                            }
                            else
                            {
                                //RX
                                l_lane = (l_scom.getIoLane() % NUM_RX_LANES_PER_OMI) + ((l_cplt_omi % NUM_OMI_PER_GRP) * NUM_RX_LANES_PER_OMI);
                            }

                            l_scom.setIoGroupAddr(l_grp);
                            l_scom.setIoLane(l_lane);
                        }
                    }
                    break;

                case INT_CHIPUNIT:
                    l_scom.setRingId(N2_RING_INT0 + i_chipUnitNum);
                    break;

                case PAU_CHIPUNIT:
                    if (l_scom.getRingId() == N01_RING_MMQ0 || l_scom.getRingId() == N01_RING_MMQ1)
                    {
                        if (i_chipUnitNum % 4 < 2)
                        {
                            l_scom.setRingId(N01_RING_MMQ0);
                        }
                        else
                        {
                            l_scom.setRingId(N01_RING_MMQ1);
                        }

                        l_scom.setSatId(i_chipUnitNum % 2);
                    }
                    else if (l_scom.getRingId() >= N01_RING_PAU0Q0_0 &&
                             l_scom.getRingId() <= N01_RING_PAU1Q2_2)
                    {
                        l_scom.setRingId(N01_RING_PAU0Q0_0 +
                                         ((l_ring - N01_RING_PAU0Q0_0) % NUM_RINGS_PER_PAU) +
                                         ((i_chipUnitNum % NUM_PAU_PER_CPLT)*NUM_RINGS_PER_PAU));
                    }

                    break;

                case PHB248X_CHIPUNIT:
                    if (PCIQ_RING_CXL0 <= l_ring && l_ring <= PCIQ_RING_CXL5)
                    {
                        l_scom.setRingId(PCIQ_RING_CXL0 + (i_chipUnitNum % NUM_PHB_PER_PEC6P_CPLT));
                    }
                    else
                    {
                        l_scom.setSatId(PCIQ_SAT_PE0 +
                                        ((i_chipUnitNum % NUM_PHB_PER_PEC6P_CPLT)*NUM_SAT_PER_PCIQ_PE) +
                                        (l_sat % NUM_SAT_PER_PCIQ_PE));
                    }

                    break;

                case PHB16X_CHIPUNIT:
                    if (PCIC_RING_CXL0 <= l_ring && l_ring <= PCIC_RING_CXL2)
                    {
                        l_scom.setRingId(PCIC_RING_CXL0 + (i_chipUnitNum % NUM_PHB_PER_PEC2P_CPLT));
                    }
                    else
                    {
                        l_scom.setRingId(PCIC_RING_PEC0 + (i_chipUnitNum % NUM_PHB_PER_PEC2P_CPLT));
                    }

                    break;

                case MCC_CHIPUNIT:

                    //mc_top_dual.vhdl
                    if (l_chipletId == (uint8_t)psChipletId_t::N2_CHIPLET_ID)
                    {
                        //Sychronous portion of MCC
                        l_scom.setRingId(N2_RING_MCS0 + (i_chipUnitNum / 2));
                        l_scom.setMCCSatId(i_chipUnitNum);
                    }
                    else
                    {
                        if (l_ring == MC_RING_MCA0 || l_ring == MC_RING_MCA1)
                        {
                            l_scom.setRingId(MC_RING_MCA0 + ((i_chipUnitNum % 4) / 2));
                            l_scom.setMCCSatId(i_chipUnitNum);
                        }
                        else if (MC_RING_OMI0 <= l_ring && l_ring <= MC_RING_OMI3)
                        {
                            l_scom.setRingId(MC_RING_OMI0 + (i_chipUnitNum % 4));
                        }
                        else
                        {
                            l_rc = 1;
                        }
                    }

                    break;

                case MI_CHIPUNIT:
                    l_scom.setRingId(N2_RING_MCS0 + i_chipUnitNum);
                    break;

                case PAXO_CHIPUNIT:
                    if ( (l_ring == PAXO_RING_ODL2C4) && (i_chipUnitNum % 2) )
                    {
                        l_scom.setSatId(1);
                    }

                case PAX_CHIPUNIT:
                    if ( l_chipletId == (uint8_t)psChipletId_t::N0_CHIPLET_ID ||
                         l_chipletId == (uint8_t)psChipletId_t::N1_CHIPLET_ID )
                    {
                        l_scom.setSatId(i_chipUnitNum % 2);

                        if (i_chipUnitNum < 4)
                        {
                            l_scom.setRingId(ps_n0_ring_id_t::N01_RING_ADLQ0);
                        }
                        else
                        {
                            l_scom.setRingId(ps_n0_ring_id_t::N01_RING_ADLQ1);
                        }
                    }

                    break;

                default:
                    break;
            }

        }
        while (0);

        if (l_rc)
        {
            l_scom.setAddr(PST_FAILED_TRANSLATION);
        }

        return l_scom.getAddr();
    }

    // See header file for function description
    uint32_t ps_scominfo_isChipUnitScom(const pstChipUnits_t i_psCU,
                                        const uint8_t i_ecLevel,
                                        const uint64_t i_scomAddr,
                                        bool& o_chipUnitRelated,
                                        std::vector<pst_chipUnitPairing_t>& o_chipUnitPairing,
                                        const pstTranslationMode_t i_mode)
    {
        uint32_t l_rc = 0;
        pst_scom_addr l_addr(i_scomAddr, PS);
        o_chipUnitRelated = false;
        o_chipUnitPairing.clear();

        uint8_t l_chiplet = l_addr.getChipletId();
        uint8_t l_ring = l_addr.getRingId();
        uint8_t l_sat = l_addr.getSatId();
        uint8_t l_endpt = l_addr.getEndpoint();

        // ================ PEC2P =================
        if ((uint8_t)psChipletId_t::PCI4_CHIPLET_ID <= l_chiplet &&
            l_chiplet <= (uint8_t)psChipletId_t::PCI5_CHIPLET_ID)
        {
            if ( (l_endpt == CHIPLET_CTRL_ENDPOINT) || // 0x0
                 (l_endpt == PSCOM_ENDPOINT) ||        // 0x1
                 (l_endpt == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                 (l_endpt == FIR_ENDPOINT) ||          // 0x4
                 (l_endpt == THERMAL_ENDPOINT) ||      // 0x5
                 (l_endpt == PCBSLV_ENDPOINT) )        // 0xF

            {
                // Returns PEC2P_CHIPUNIT related if normal mode or
                // if ENGD_BUILD_MODE and end point is not PCBSLV_ENDPOINT or end point is not PSCOM and Ring IDs 2,3,4,6,7,8
                if ( (i_mode != ENGD_BUILD_MODE) ||
                     !((l_endpt == PCBSLV_ENDPOINT) ||
                       ((l_endpt == PSCOM_ENDPOINT) && (l_ring >= PCIC_RING_PEC0 && l_ring <= PCIC_RING_CXL2))))
                {
                    // ================ PEC2P =================
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PEC2P_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::PCI4_CHIPLET_ID));
                }

                // The only valid endpoint for PHB targets is PSCOM.
                if (l_endpt == PSCOM_ENDPOINT)
                {
                    // ================ PHB16X =================
                    if (PCIC_RING_CXL0 <= l_ring && l_ring <= PCIC_RING_CXL2)
                    {
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PHB16X_CHIPUNIT,
                                                    ((l_chiplet - (uint8_t)psChipletId_t::PCI4_CHIPLET_ID)*NUM_PHB_PER_PEC2P_CPLT) +
                                                    (l_ring - PCIC_RING_CXL0)));
                    }
                    else if ( PCIC_RING_PEC0 <= l_ring)
                    {
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PHB16X_CHIPUNIT,
                                                    ((l_chiplet - (uint8_t)psChipletId_t::PCI4_CHIPLET_ID)*NUM_PHB_PER_PEC2P_CPLT) +
                                                    (l_ring - PCIC_RING_PEC0)));
                    }
                }
            }
        }

        // ================ PEC6P =================
        if ((uint8_t)psChipletId_t::PCI0_CHIPLET_ID <= l_chiplet &&
            l_chiplet <= (uint8_t)psChipletId_t::PCI3_CHIPLET_ID)
        {
            if ( (l_endpt == CHIPLET_CTRL_ENDPOINT) || // 0x0
                 (l_endpt == PSCOM_ENDPOINT) ||        // 0x1
                 (l_endpt == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                 (l_endpt == FIR_ENDPOINT) ||          // 0x4
                 (l_endpt == THERMAL_ENDPOINT) ||      // 0x5
                 (l_endpt == PCBSLV_ENDPOINT) )        // 0xF
            {
                o_chipUnitRelated = true;
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PEC6P_CHIPUNIT,
                                            l_chiplet - (uint8_t)psChipletId_t::PCI0_CHIPLET_ID));

                // The only valid endpoint for PHB targets is PSCOM.
                if ( (l_endpt == PSCOM_ENDPOINT) && (i_mode != ENGD_BUILD_MODE) )
                {
                    // ================ PHB248X =================
                    if (PCIQ_RING_CXL0 <= l_ring && l_ring <= PCIQ_RING_CXL5)
                    {
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PHB248X_CHIPUNIT,
                                                    ((l_chiplet - (uint8_t)psChipletId_t::PCI0_CHIPLET_ID)*NUM_PHB_PER_PEC6P_CPLT) +
                                                    (l_ring - PCIQ_RING_CXL0)));
                    }

                    if ( (l_ring == PCIQ_RING_PEQ) &&
                         ( PCIQ_SAT_PE0 <= l_sat && l_sat <= PCIQ_SAT_PE5_ETU ) )
                    {
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PHB248X_CHIPUNIT,
                                                    ((l_chiplet - (uint8_t)psChipletId_t::PCI0_CHIPLET_ID)*NUM_PHB_PER_PEC6P_CPLT) +
                                                    (l_sat / NUM_SAT_PER_PCIQ_PE + PCIQ_SAT_PE0)));
                    }
                }
            }
        }

        // ================ PAX =================
        if ( l_addr.isPaxTarget() )
        {
            o_chipUnitRelated = true;

            if ( (l_addr.getChipletId() >= (uint8_t)psChipletId_t::PX00_CHIPLET_ID) &&
                 (l_addr.getChipletId() <= (uint8_t)psChipletId_t::PX07_CHIPLET_ID) )
            {
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PAX_CHIPUNIT,
                                            l_chiplet - (uint8_t)psChipletId_t::PX00_CHIPLET_ID));
            }
            else    //ADL
            {
                //ChipletId: 0x04 RingId: 0x4 SatId: 0x0 ECAPQ0_ADL0  paxo0001 OVW
                //ChipletId: 0x04 RingId: 0x4 SatId: 0x1 ECAPQ0_ADL1  paxo0001 OVW
                //ChipletId: 0x05 RingId: 0x4 SatId: 0x0 ECAPQ1_ADL0  paxo0203 OVW
                //ChipletId: 0x05 RingId: 0x4 SatId: 0x1 ECAPQ1_ADL1  paxo0203 OVW
                //ChipletId: 0x04 RingId: 0x6 SatId: 0x0 ECAPQ2_ADL0  paxo0405 OVW
                //ChipletId: 0x04 RingId: 0x6 SatId: 0x1 ECAPQ2_ADL1  paxo0405 OVW
                //ChipletId: 0x05 RingId: 0x6 SatId: 0x0 ECAPQ3_ADL0  paxo0607 OVW
                //ChipletId: 0x05 RingId: 0x6 SatId: 0x1 ECAPQ3_ADL1  paxo0607 OVW
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PAX_CHIPUNIT,
                                            ((l_addr.getChipletId() % 2) * 2) +
                                            l_addr.getSatId() +
                                            ((l_addr.getRingId() / ps_n0_ring_id_t::N01_RING_ADLQ1) * 4)));

            }
        }

        // ================ PAXO =================
        if ( l_addr.isPaxoTarget() )
        {
            o_chipUnitRelated = true;
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PAXO_CHIPUNIT,
                                        l_chiplet - (uint8_t)psChipletId_t::PX08_CHIPLET_ID));
        }

        // ================ IOHS =================
        if ( l_addr.isIohsTarget() )
        {
            if (i_mode != ENGD_BUILD_MODE)
            {
                o_chipUnitRelated = true;
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(IOHS_CHIPUNIT,
                                            l_chiplet - (uint8_t)psChipletId_t::PX00_CHIPLET_ID));
            }
        }

        // ================ N0/N1 chiplet IDs =================
        if (l_chiplet == (uint8_t)psChipletId_t::N0_CHIPLET_ID ||
            l_chiplet == (uint8_t)psChipletId_t::N1_CHIPLET_ID)
        {
            // ================ NX =================
            if (l_ring == N01_RING_NXV)
            {
                if (NX_SATID_DMA <= l_sat && l_sat <= NX_SATID_CH4)
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(NX_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID));
                }

                if ( (l_sat == NX_SATID_0) || (l_sat == NX_SATID_6) )
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(NX_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID));
                }
            }

            if (N01_RING_PAUN0 <= l_ring && l_ring <= N01_RING_PAUN2)
            {
                o_chipUnitRelated = true;
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(NX_CHIPUNIT,
                                            l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID));
            }

            if (l_ring == N01_RING_MM)  // 0x2
            {
                if ( l_sat == NX_SATID_1)
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(NX_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID));
                }
            }

            if (l_ring == N01_RING_SBN)  // 0x1F
            {
                if ( l_sat == NX_SATID_0)
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(NX_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID));
                }
            }

            // ================ PAU =================
            if ( (N01_RING_PAU0Q0_0 <= l_ring && l_ring <= N01_RING_PAU1Q2_2) && (l_endpt == PSCOM_ENDPOINT))
            {
                o_chipUnitRelated = true;
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PAU_CHIPUNIT,
                                            (l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID)*NUM_PAU_PER_CPLT +
                                            ((l_ring - N01_RING_PAU0Q0_0) / NUM_RINGS_PER_PAU)));
            }

            if ((l_ring == N01_RING_MMQ0 || l_ring == N01_RING_MMQ1) && (l_endpt == PSCOM_ENDPOINT))
            {
                o_chipUnitRelated = true;
                uint8_t l_pau_inst = l_sat;

                if (l_ring == N01_RING_MMQ1)
                {
                    l_pau_inst += 2;
                }

                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PAU_CHIPUNIT,
                                            (l_chiplet - (uint8_t)psChipletId_t::N0_CHIPLET_ID)*NUM_PAU_PER_CPLT +
                                            l_pau_inst));

            }

        }

        // ================ N2 chiplet ID =================
        if (l_chiplet == (uint8_t)psChipletId_t::N2_CHIPLET_ID)
        {
            // ================ INT =================
            if (l_ring == N2_RING_INT0 || l_ring == N2_RING_INT1)
            {
                o_chipUnitRelated = true;
                o_chipUnitPairing.push_back(pst_chipUnitPairing_t(INT_CHIPUNIT,
                                            l_ring - N2_RING_INT0));
            }

            if (N2_RING_MCS0 <= l_ring && l_ring <= N2_RING_MCS7 && (i_mode != ENGD_BUILD_MODE))
            {
                // ================ MI =================
                if (l_sat == MCS_SATID_PBI_EXT || l_sat == MCS_SATID_PMU)
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MI_CHIPUNIT,
                                                l_ring - N2_RING_MCS0));
                }

                // ================ N2 MCC =================
                uint8_t l_sat_3b = l_sat & 0x7;

                if (l_sat_3b == MCS_SATID_MC0_PBI || l_sat_3b == MCS_SATID_MC0_CL)
                {
                    uint8_t l_mod2 = l_addr.getSatId() >> 3;
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MCC_CHIPUNIT,
                                                (l_ring - N2_RING_MCS0) * 2 + l_mod2));
                }
            }
        }

        // ================ MC chiplet ID =================
        if ((uint8_t)psChipletId_t::MC0_CHIPLET_ID <= l_chiplet &&
            l_chiplet <= (uint8_t)psChipletId_t::MC3_CHIPLET_ID)
        {
            if ( (l_endpt == CHIPLET_CTRL_ENDPOINT) || // 0x0
                 (l_endpt == PSCOM_ENDPOINT) ||        // 0x1
                 (l_endpt == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                 (l_endpt == FIR_ENDPOINT) ||          // 0x4
                 (l_endpt == THERMAL_ENDPOINT) ||      // 0x5
                 (l_endpt == PCBSLV_ENDPOINT) )        // 0xF
            {

                // ================ MCC =================
                if (l_ring == MC_RING_MCA0 || l_ring == MC_RING_MCA1)
                {
                    if (i_mode != ENGD_BUILD_MODE)
                    {
                        uint8_t l_mod2 = l_addr.getSatId() >> 3;
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MCC_CHIPUNIT,
                                                    (l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID) * 4 +
                                                    (l_ring - MC_RING_MCA0) * 2 + l_mod2));
                    }
                    else
                    {
                        // MCC is not scannable, return parent MC
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MC_CHIPUNIT,
                                                    l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID));
                    }
                }

                if (MC_RING_OMI0 <= l_ring && l_ring <= MC_RING_OMI3)
                {
                    if (i_mode != ENGD_BUILD_MODE)
                    {
                        uint8_t l_reg = l_addr.getSatOffset();
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MCC_CHIPUNIT,
                                                    (l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID) * NUM_MCC_PER_CPLT +
                                                    (l_ring - MC_RING_OMI0)));

                        if (DL0_REG_OFFSET0 <= l_reg && l_reg <= DL1_REG_OFFSET15)
                        {
                            //OMI
                            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(OMI_CHIPUNIT,
                                                        ((l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID) * NUM_OMI_PER_CPLT) +
                                                        ((l_ring - MC_RING_OMI0) * NUM_OMI_PER_GRP) +
                                                        ((l_reg - DL0_REG_OFFSET0) / NUM_REGS_PER_DL)));
                        }
                    }
                    else
                    {
                        // OMI is not scannable, return parent MC
                        o_chipUnitRelated = true;
                        o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MC_CHIPUNIT,
                                                    l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID));
                    }
                }

                // ================ OMIC =================
                if (l_ring == MC_RING_IOPPE)
                {
                    // There is a singular IOPPE per MC chiplet, so use the MC_CHIPUNIT association
                    // instead of OMIC_CHIPUNIT.
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MC_CHIPUNIT,
                                                (l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID)));

                    if (l_addr.isIndirect())
                    {
                        // ================ OMI =================
                        uint8_t l_grp = l_addr.getIoGroupAddr();
                        uint8_t l_lane = l_addr.getIoLane();
                        uint8_t l_omi_num = ((l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID) * NUM_OMI_PER_CPLT) +
                                            (l_grp * NUM_OMI_PER_GRP);

                        if (l_addr.getIoTxRxBit())
                        {
                            //TX
                            l_omi_num += (l_lane / NUM_TX_LANES_PER_OMI);
                        }
                        else
                        {
                            //RX
                            l_omi_num += (l_lane / NUM_RX_LANES_PER_OMI);
                        }

                        if (i_mode != ENGD_BUILD_MODE)
                        {
                            o_chipUnitRelated = true;
                            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(OMI_CHIPUNIT, l_omi_num));
                        }
                    }
                }

                // ================ MC =================
                if (l_ring == MC_RING || l_ring == MC_RING_TRA) // 0x0 or 0x1
                {
                    o_chipUnitRelated = true;
                    o_chipUnitPairing.push_back(pst_chipUnitPairing_t(MC_CHIPUNIT,
                                                l_chiplet - (uint8_t)psChipletId_t::MC0_CHIPLET_ID));
                }
            }
        }

        // ================= TBUS ==================
        if ( l_addr.isTbusTarget() )
        {
            o_chipUnitRelated = true;
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(TBUS_CHIPUNIT,
                                        (l_chiplet - (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID)));
        }

        // ================= TBUSL ==================
        if ( l_addr.isTbuslTarget() )
        {
            o_chipUnitRelated = true;
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(TBUSL_CHIPUNIT,
                                        l_addr.getTbuslTargetInstance()));
        }

        //This must be done last
        // ================= PERV ==================
        if (l_addr.isPervTarget())
        {
            l_addr.pervChipUnitScom(i_ecLevel, o_chipUnitRelated, o_chipUnitPairing, i_mode);
        }

        return l_rc;
    }

    uint32_t ps_scominfo_fixChipUnitScomAddrOrTarget(const pstChipUnits_t i_psCU,
            const uint8_t i_ecLevel,
            const uint32_t i_targetChipUnitNum,
            const uint64_t i_scomaddr,
            uint64_t& o_modifiedScomAddr,
            pstChipUnits_t& o_psCU,
            uint32_t& o_modifiedChipUnitNum,
            const pstTranslationMode_t i_mode)
    {
        uint32_t l_rc = 0;
        return l_rc;
    }

} // extern "C"

#undef PS_SCOMINFO_C
