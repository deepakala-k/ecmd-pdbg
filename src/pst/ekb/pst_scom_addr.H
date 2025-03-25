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
/// @file pst_scom_addr.H
/// @brief PST SCOM address class
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: Cronus, HB
///

#ifndef PST_SCOM_ADDR_H
#define PST_SCOM_ADDR_H

// includes
#include <stdint.h>
#include <vector>
#include "pst_cu.H"

extern "C"
{
    /// Constants
    const uint32_t NUM_CORES_PER_EQ   = 4;
    const uint32_t NUM_TBUSL_PER_TBUS = 2;
    const uint32_t NUM_MCC_PER_CPLT   = 4;
    const uint32_t NUM_OMI_PER_CPLT   = 8;
    const uint32_t NUM_PAU_PER_CPLT   = 4;
    const uint32_t NUM_PHB_PER_PEC6P_CPLT = 6;
    const uint32_t NUM_PHB_PER_PEC2P_CPLT = 3;
    const uint32_t NUM_OMI_PER_GRP = 2;
    const uint32_t NUM_TX_LANES_PER_OMI = 4;
    const uint32_t NUM_RX_LANES_PER_OMI = 8;
    const uint32_t NUM_TBUSL_PER_CPLT = 2;
    const uint32_t NUM_GRPS_PER_TBUSL = 2;
    const uint32_t NUM_IOHS_PER_CPLT = 2;

    typedef enum
    {
        PT = 0,
        PS = 1,
        UNDEFINED_CHIP = 99,
    } pstChipTypes_t;

    // Modes of translation
    typedef enum
    {
        DEFAULT_MODE = 0,       // Default platform behavior
        ENGD_BUILD_MODE = 1,    // Apply customization for ENGD build
    } pstTranslationMode_t;

    /// PST Spinal Chiplet ID enumeration
    enum class psChipletId_t : uint8_t
    {
        PIB_CHIPLET_ID   = 0x00,    ///< PIB chiplet (FSI)
        PERV_CHIPLET_ID  = 0x01,    ///< TP chiplet
        N0_CHIPLET_ID    = 0x04,
        N1_CHIPLET_ID    = 0x05,
        N2_CHIPLET_ID    = 0x06,
        MC0_CHIPLET_ID   = 0x08,
        MC1_CHIPLET_ID   = 0x09,
        MC2_CHIPLET_ID   = 0x0A,
        MC3_CHIPLET_ID   = 0x0B,
        PX00_CHIPLET_ID  = 0x10,
        PX01_CHIPLET_ID  = 0x11,
        PX02_CHIPLET_ID  = 0x12,
        PX03_CHIPLET_ID  = 0x13,
        PX04_CHIPLET_ID  = 0x14,
        PX05_CHIPLET_ID  = 0x15,
        PX06_CHIPLET_ID  = 0x16,
        PX07_CHIPLET_ID  = 0x17,
        PX08_CHIPLET_ID  = 0x18,
        PX09_CHIPLET_ID  = 0x19,
        PX10_CHIPLET_ID  = 0x1A,
        PX11_CHIPLET_ID  = 0x1B,
        PCI0_CHIPLET_ID  = 0x20,
        PCI1_CHIPLET_ID  = 0x21,
        PCI2_CHIPLET_ID  = 0x22,
        PCI3_CHIPLET_ID  = 0x23,
        PCI4_CHIPLET_ID  = 0x24,
        PCI5_CHIPLET_ID  = 0x25,
        TBUS0_CHIPLET_ID = 0x28,
        TBUS1_CHIPLET_ID = 0x29,
        TBUS2_CHIPLET_ID = 0x2A,
        TBUS3_CHIPLET_ID = 0x2B

    };

    /// PST Tap Chiplet ID enumeration
    enum class ptChipletId_t : uint8_t
    {
        PIB_CHIPLET_ID   = 0x00,    ///< PIB chiplet (FSI)
        PERV_CHIPLET_ID  = 0x01,    ///< TP chiplet
        N0_CHIPLET_ID    = 0x02,
        TBUS0_CHIPLET_ID = 0x03,
        EQ0_CHIPLET_ID   = 0x20,
        EQ1_CHIPLET_ID   = 0x21,

    };

    typedef uint8_t pstChipletId_t;

    const uint8_t TapPervTargetChipletIdTable[] =
    {
        (uint8_t)ptChipletId_t::PIB_CHIPLET_ID   ,
        (uint8_t)ptChipletId_t::PERV_CHIPLET_ID  ,
        (uint8_t)ptChipletId_t::N0_CHIPLET_ID    ,
        (uint8_t)ptChipletId_t::TBUS0_CHIPLET_ID ,
        (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID   ,
        (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID   ,
    };

    const uint8_t SpinalPervTargetChipletIdTable[] =
    {
        (uint8_t)psChipletId_t::PIB_CHIPLET_ID   ,
        (uint8_t)psChipletId_t::PERV_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::N0_CHIPLET_ID    ,
        (uint8_t)psChipletId_t::N1_CHIPLET_ID    ,
        (uint8_t)psChipletId_t::N2_CHIPLET_ID    ,
        (uint8_t)psChipletId_t::MC0_CHIPLET_ID   ,
        (uint8_t)psChipletId_t::MC1_CHIPLET_ID   ,
        (uint8_t)psChipletId_t::MC2_CHIPLET_ID   ,
        (uint8_t)psChipletId_t::MC3_CHIPLET_ID   ,
        (uint8_t)psChipletId_t::PX00_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX01_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX02_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX03_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX04_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX05_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX06_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX07_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX08_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX09_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX10_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PX11_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI0_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI1_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI2_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI3_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI4_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::PCI5_CHIPLET_ID  ,
        (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID ,
        (uint8_t)psChipletId_t::TBUS1_CHIPLET_ID ,
        (uint8_t)psChipletId_t::TBUS2_CHIPLET_ID ,
        (uint8_t)psChipletId_t::TBUS3_CHIPLET_ID ,
    };

    typedef enum
    {
        CHIPLET_CTRL_ENDPOINT   = 0x0,    ///< Chiplet Control
        PSCOM_ENDPOINT          = 0x1,    ///< EQ:PSCOM (L3), others: PSCOM
        PSCOM_2_ENDPOINT        = 0x2,    ///< EQ:PSCOM (Core/L2), TP:ITR, Nest:TOD (Time Of Day)
        CLOCK_CTRL_ENDPOINT     = 0x3,    ///< Clock controller
        FIR_ENDPOINT            = 0x4,    ///< FIR
        THERMAL_ENDPOINT        = 0x5,    ///< Thermal
        DPLL_ENDPOINT           = 0x6,    ///< TP (only): DPLL
        CHIPLET_2_CTRL_ENDPOINT = 0x9,    ///< Chiplet Control
        QME_ENDPOINT            = 0xE,    ///< EQ (only): QME
        PCBSLV_ENDPOINT         = 0xF,    ///< PCB Slave registers
    } pstEndpointID_t;

    /// PST EQ chiplet ring ID enumeration
    typedef enum
    {
        QME_RING_ID = 0x2,
        L3_RING_ID = 0x3,
        RNG_RING_ID = 0x4,
        AN_RING_ID = 0x5,
    } pst_EQ_PSCOM_RingId_t;

    typedef enum
    {
        L2_RING_ID = 0x0,
        C_0_RING_ID = 0x2,
        C_1_RING_ID = 0x3,
        C_3_RING_ID = 0x5,
    } pst_EQ_PSCOM2_RingId_t;

    /// PERV chiplet and PSCOM ring ID enumeration
    typedef enum
    {
        PSCOM_RING_ID = 0x0,
        PERV_RING_ID  = 0x1,
        PBA_RING_ID   = 0x3,
    } pst_PSCOM_PERV_RingId_t;

    /// IOHS ring id
    typedef enum
    {
        IOHS_RING_ID = 0xA,
    } pst_PAX_RING_RingId_t;

    /// PAXO ring id
    typedef enum
    {
        PAXO_RING_ODL2C4 = 0x3,
    } pst_PAXO_RING_RingId_t;

    /// region select (CoreId/One-hot)
    typedef enum
    {
        EQ_REGION_SEL       = 0x0,
        MULTI_HOT_SELECT_C0 = 0x8,
        MULTI_HOT_SELECT_C1 = 0x4,
        MULTI_HOT_SELECT_C2 = 0x2,
        MULTI_HOT_SELECT_C3 = 0x1,
    } pstRegionSelect_t;

    typedef enum
    {
        L3TRACE_COMMON_SAT_ID = 0x0,
        L3TRACE_SAT_ID = 0x1,
        CLKADJ_SAT_ID = 0x6,
        SKEWADJ_SAT_ID = 0x7,
    } pst_EQ_SatId_t;

    typedef enum
    {
        N2_RING_TRA = 1,
        N2_RING_PB = 3,
        N2_RING_PBBR = 4,
        N2_RING_PBAF = 5,
        N2_RING_INT0 = 6,
        N2_RING_INT1 = 7,
        N2_RING_MCD0 = 8,
        N2_RING_MCD1 = 9,
        N2_RING_MCS0 = 12,
        N2_RING_MCS1 = 13,
        N2_RING_MCS2 = 14,
        N2_RING_MCS3 = 15,
        N2_RING_MCS4 = 16,
        N2_RING_MCS5 = 17,
        N2_RING_MCS6 = 18,
        N2_RING_MCS7 = 19,
    } ps_n2_ring_id_t;

    typedef enum
    {
        MC_RING     = 0,
        MC_RING_TRA = 1,
        MC_RING_OMI0 = 2,
        MC_RING_OMI1 = 3,
        MC_RING_OMI2 = 4,
        MC_RING_OMI3 = 5,
        MC_RING_MCA0 = 6,
        MC_RING_MCA1 = 7,
        MC_RING_IOPPE = 10,
    } ps_mc_ring_id_t;

    typedef enum
    {
        MCS_SATID_PMU = 0x2,     //MI target only
        MCS_SATID_PBI_EXT = 0x4, //MI target only
        MCS_SATID_MC0_PBI = 0x0, // MCC target synchronous
        MCS_SATID_MC1_PBI = 0x8, // MCC target synchronous
        MCS_SATID_MC0_CL = 0x1,  // MCC target synchronous
        MCS_SATID_MC1_CL = 0x9,  // MCC target synchronous
    } ps_mcs_sat_id_t;

    typedef enum
    {
        MCA_SATID_MC0_USTL = 0x2,
        MCA_SATID_MC0_DECR = 0x6,//BUG was 0x5
        MCA_SATID_MC0_READ = 0x0,
        MCA_SATID_MC0_WDF = 0x3,
        MCA_SATID_MC0_WRT = 0x4,
        MCA_SATID_MC0_ENCR = 0x5,
        MCA_SATID_MC0_DSTL = 0x1,
        MCA_SATID_MC0_MISC = 0x7,
        MCA_SATID_MC1_USTL = 0xA,
        MCA_SATID_MC1_DECR = 0xE,//BUG was 0xD
        MCA_SATID_MC1_READ = 0x8,
        MCA_SATID_MC1_WDF = 0xB,
        MCA_SATID_MC1_WRT = 0xC,
        MCA_SATID_MC1_ENCR = 0xD,
        MCA_SATID_MC1_DSTL = 0x9,
        MCA_SATID_MC1_MISC = 0xF,
    } ps_mca_sat_id_t;

    typedef enum
    {
        TBUS_RING_TRA = 1,
        TBUS_RING_TTL = 2,
        TBUS_RING_SF0 = 6,
        TBUS_RING_SF1 = 7,
        TBUS_RING_PPE = 10,
    } ps_tbus_ring_id_t;

    typedef enum
    {
        MM0_SAT_ID = 0,
        MM1_SAT_ID = 1,
    } ps_nmmu_sat_id_t;

    const uint32_t NUM_RINGS_PER_PAU = 3;
    typedef enum
    {
        N01_RING_TRA = 1,
        N01_RING_MM = 2,
        N01_RING_NXV = 3,
        N01_RING_ADLQ0 = 4,
        N01_RING_MMQ0 = 5,
        N01_RING_ADLQ1 = 6,
        N01_RING_MMQ1 = 7,
        N01_RING_PAXO = 8,
        N01_RING_SBQ0 = 9,
        N01_RING_SBQ1 = 10,
        N01_RING_OTLC0 = 11,
        N01_RING_OTLC1 = 12,
        N01_RING_OTLC2 = 13,
        N01_RING_OTLC3 = 14,
        N01_RING_SBC = 15,
        N01_RING_PAUN0 = 16,
        N01_RING_PAUN1 = 17,
        N01_RING_PAUN2 = 18,
        N01_RING_PAU0Q0_0 = 19,
        N01_RING_PAU0Q0_1 = 20,
        N01_RING_PAU0Q0_2 = 21,
        N01_RING_PAU1Q0_0 = 22,
        N01_RING_PAU1Q0_1 = 23,
        N01_RING_PAU1Q0_2 = 24,
        N01_RING_PAU0Q2_0 = 25,
        N01_RING_PAU0Q2_1 = 26,
        N01_RING_PAU0Q2_2 = 27,
        N01_RING_PAU1Q2_0 = 28,
        N01_RING_PAU1Q2_1 = 29,
        N01_RING_PAU1Q2_2 = 30,
        N01_RING_SBN = 31,
    } ps_n0_ring_id_t;

    typedef enum
    {
        NX_SATID_0 = 0x0,
        NX_SATID_1 = 0x1,
        NX_SATID_DBG = 0x4,
        NX_SATID_DMA = 0x1,
        NX_SATID_PBI_CQ = 0x2,
        NX_SATID_PBI_UMAC = 0x3,
        NX_SATID_CH4 = 0x5,
        NX_SATID_6 = 0x6,
    } ps_nx_satid_t;

    typedef enum
    {
        PCIQ_RING_TRA = 1,
        PCIQ_RING_PEQ = 2,
        PCIQ_RING_CXL0 = 6,
        PCIQ_RING_CXL1 = 7,
        PCIQ_RING_CXL2 = 8,
        PCIQ_RING_CXL3 = 9,
        PCIQ_RING_CXL4 = 10,
        PCIQ_RING_CXL5 = 11,
    } ps_pciq_ring_id_t;

    typedef enum
    {
        PCIC_RING_TRA = 1,
        PCIC_RING_PEC0 = 2,
        PCIC_RING_PEC1 = 3,
        PCIC_RING_PEC2 = 4,
        PCIC_RING_CXL0 = 6,
        PCIC_RING_CXL1 = 7,
        PCIC_RING_CXL2 = 8,
    } ps_pcic_ring_id_t;

    const uint32_t NUM_SAT_PER_PCIQ_PE = 2;
    typedef enum
    {
        PCIQ_SAT_PE0 = 0,
        PCIQ_SAT_PE0_ETU = 1,
        PCIQ_SAT_PE1 = 2,
        PCIQ_SAT_PE1_ETU = 3,
        PCIQ_SAT_PE2 = 4,
        PCIQ_SAT_PE2_ETU = 5,
        PCIQ_SAT_PE3 = 6,
        PCIQ_SAT_PE3_ETU = 7,
        PCIQ_SAT_PE4 = 8,
        PCIQ_SAT_PE4_ETU = 9,
        PCIQ_SAT_PE5 = 10,
        PCIQ_SAT_PE5_ETU = 11,
    } ps_pciq_satid_t;

    const uint32_t NUM_REGS_PER_DL = 16;
    typedef enum
    {
        DL0_REG_OFFSET0 = 16,
        DL0_REG_OFFSET15 = 31,
        DL1_REG_OFFSET0 = 32,
        DL1_REG_OFFSET15 = 47,
    } ps_dlm_regs_t;

    class pst_scom_addr
    {
        public:
            /// @brief Construct a SCOM address object
            /// @param[in] i_addr 64-bit raw SCOM address
            pst_scom_addr(const uint64_t i_addr, const pstChipTypes_t i_chip_type)
                : iv_addr(i_addr), iv_chip_type(i_chip_type)
            {
            }

            /// @brief Set full/raw SCOM address
            /// @param[in] i_addr 64-bit SCOM address
            /// @retval none
            inline void setAddr(const uint64_t i_addr)
            {
                iv_addr = i_addr;
                return;
            }

            /// @brief Retrieve full/raw SCOM address
            /// @retval uint64_t 64-bit SCOM address
            inline uint64_t getAddr() const
            {
                return (iv_addr);
            }

            /// @brief Determine if SCOM address is direct-form (bit 0)
            /// @retval bool True if SCOM address is direct-form, false otherwise
            inline bool isDirect() const
            {
                return (((iv_addr >> 63) & 0x1) == 0x0);
            }

            /// @brief Determine if SCOM address is indirect-form
            /// @retval bool True if SCOM address is indirect-form, false otherwise
            inline bool isIndirect() const
            {
                return (!isDirect());
            }

            /// @brief Determine if SCOM address is multicast (bit 1)
            /// @retval bool True if SCOM address is multicast, false otherwise
            inline bool isMulticast() const
            {
                return (((iv_addr >> 30) & 0x1) == 0x1);
            }

            /// @brief Determine if SCOM address is unicast
            /// @retval bool True if SCOM address is unicast, false otherwise
            inline bool isUnicast() const
            {
                return (!(isMulticast()));
            }

            /// @brief Extract pervasive chiplet ID from SCOM address (bits 2:7)
            /// @retval uint8_t Pervasive chiplet ID value
            inline uint8_t getChipletId() const
            {
                return ((iv_addr >> 24) & 0x3F);
            }

            /// @brief Modify SCOM address, update pervasive chiplet ID
            /// @param[in] i_chiplet_id Chiplet ID value to write
            /// @retval none
            inline void setChipletId(const uint8_t i_chiplet_id)
            {
                iv_addr &= 0xFFFFFFFFC0FFFFFFULL;
                iv_addr |= ((i_chiplet_id & 0x3F) << 24);
                return;
            }

            /// @brief Extract Endpoint field from SCOM address (bits 12:15)
            /// @retval uint8_t Endpoint field value
            inline uint8_t getEndpoint() const
            {
                return ((iv_addr >> 16) & 0xF);
            }

            /// @brief Modify the Endpoint field from SCOM address
            /// @retval none
            inline void setEndpoint(const uint8_t i_port)
            {
                iv_addr &= 0xFFFFFFFFFFF0FFFFULL;
                iv_addr |= ((i_port & 0xF) << 16);
                return;
            }

            /// @brief Extract region select field (core id) from SCOM address (bits 16:19)
            /// @retval uint8_t Region select value
            inline uint8_t getRegionSelect() const
            {
                return ((iv_addr >> 12) & 0xF);
            }

            /// @brief Modify the region select field (core id) from SCOM address
            /// @retval none
            inline void setRegionSelect(const uint8_t i_regionSelect)
            {
                iv_addr &= 0xFFFFFFFFFFFF0FFFULL;
                iv_addr |= ((i_regionSelect & 0xF) << 12);
                return;
            }

            /// @brief Extract ring field from SCOM address (bits 18:21)
            /// @retval uint8_t Ring id value
            inline uint8_t getRingId() const
            {
                return ((iv_addr >> 10) & 0x1F);
            }

            /// @brief Extract EQ ring field from SCOM address (bits 20:22)
            /// @retval uint8_t Ring id value
            inline uint8_t getEQRingId() const
            {
                return ((iv_addr >> 9) & 0x7);
            }

            /// @brief Get the QME Per Core value (bit 20, EQ/Core only)
            /// Function prereq: Address must belong to EQ or Core target type
            /// @retval uint8_t QME Per Core value
            inline uint8_t getQMEPerCore()
            {
                return (iv_addr >> 11) & 0x1;
            }

            /// @brief Get the QME Sat Enable value (bit 21, EQ/Core only)
            /// Function prereq: Address must belong to EQ or Core target type
            /// @retval uint8_t QME Sat Enable value
            inline uint8_t getQMESatEn()
            {
                return (iv_addr >> 10) & 0x1;
            }

            /// @brief Get the QME Sat Select value (bit 22:23, EQ/Core only)
            /// Function prereq: Address must belong to EQ or Core target type
            /// @retval uint8_t QME Sat Sel value
            inline uint8_t getQMESatSel()
            {
                return (iv_addr >> 8) & 0x3;
            }

            /// @brief Get the QME reg value (bit 24:31, EQ/Core only)
            /// Function prereq: Address must belong to EQ or Core target type
            /// @retval uint8_t QME reg value
            inline uint8_t getQMEReg()
            {
                return (iv_addr & 0xFF);
            }

            /// @brief Modify SCOM address, update ring field value (bits 18:21)
            /// @param[in] i_ring Ring field value to write
            /// @retval none
            inline void setRingId(const uint8_t i_ring)
            {
                iv_addr &= 0xFFFFFFFFFFFF83FFULL;
                iv_addr |= ((i_ring & 0x1F) << 10);
                return;
            }

            /// @brief Extract satellite ID field from SCOM address (bits 22:25)
            /// @retval uint8_t Satellite ID field value
            inline uint8_t getSatId() const
            {
                return ((iv_addr >> 6) & 0xF);
            }

            /// @brief Extract EQ satellite ID field from SCOM address (bits 23:25)
            /// @retval uint8_t Ring id value
            inline uint8_t getEQSatId() const
            {
                return ((iv_addr >> 6) & 0x7);
            }

            /// @brief Modify SCOM address, update satellite ID field
            /// @param[in] i_sat_id Satellite ID value to write
            /// @retval none
            inline void setSatId(const uint8_t i_satId)
            {
                iv_addr &= 0xFFFFFFFFFFFFFC3FULL;
                iv_addr |= ((i_satId & 0xF) << 6);
                return;
            }

            /// @brief Modify SCOM address, update upper bit of sat_id for MC
            /// @param[in] i_chipUnitNum the mcc/mi target number
            /// @retval none
            inline void setMCCSatId(const uint8_t i_chipUnitNum)
            {
                iv_addr &= 0xFFFFFFFFFFFFFDFFULL;
                iv_addr |= (i_chipUnitNum % 2) << 9;
                return;
            }


            /// @brief Extract satellite register offset field from SCOM address (bits 26:31)
            /// @retval uint8_t Satellite register offset field value
            inline uint8_t getSatOffset() const
            {
                return (iv_addr & 0x3F);
            }

            /// @brief Modify SCOM address, update satellite offset field
            /// @param[in] i_sat_offset Satellite offset value to write
            /// @retval none
            inline void setSatOffset(const uint8_t i_sat_offset)
            {
                iv_addr &= 0xFFFFFFFFFFFFFFC0ULL;
                iv_addr |= (i_sat_offset & 0x3F);
                return;
            }

            /// @brief Get the OBUS Super Wrapper Group address (bits 22:26) of
            ///        an indirect scom address
            /// @retval uint8_t Group address
            inline uint8_t getIoGroupAddr() const
            {
                return ((iv_addr >> 37) & 0x1F);
            }

            /// @brief Set the OBUS Super Wrapper Group address (bits 22:26) of
            ///        an indirect scom address
            /// @param[in] i_group_addr Group address value to write
            /// @retval none
            inline void setIoGroupAddr(const uint8_t i_group_addr)
            {
                iv_addr &= 0xFFFFFC1FFFFFFFFFULL;
                iv_addr |= ( ((uint64_t)i_group_addr & 0x1F) << 37 );
                return;
            }

            /// @brief Get Super Wrapper Register address (bits 12:20)
            ///        of an indirect scom address
            /// @retval uint32_t Register address
            inline uint32_t getIoRegAddr() const
            {
                return ((iv_addr >> 43) & 0x1FF);
            }

            /// @brief Get the OBUS Super Wrapper TX/RX bit (bit 21)
            ///        of an indirect scom address
            /// @retval uint8_t TX/RX bit
            inline uint32_t getIoTxRxBit() const
            {
                return ((iv_addr >> 42) & 0x1);
            }

            /// @brief Get the OBUS Super Wrapper Lane (bits 27:31)
            ///        of an indirect scom address
            /// @retval uint8_t Lane
            inline uint32_t getIoLane() const
            {
                return ((iv_addr >> 32) & 0x1F);
            }

            /// @brief Set the OBUS Super Wrapper Lane (bits 27:31)
            ///        of an indirect scom address
            /// @retval uint8_t Lane
            inline void setIoLane(const uint8_t i_lane)
            {
                iv_addr &= 0xFFFFFFE0FFFFFFFFULL;
                iv_addr |= ( ((uint64_t)i_lane & 0x1F) <<  32);
            }

            /// @brief Determine if this address belongs to PERV target type
            /// @retval true or false.
            bool isPervTarget();

            /// @brief Determine the PERV instance for this address
            /// Function prereq: Address must belong to PERV target type
            /// @retval uint8_t PERV target instance.
            uint8_t getPervTargetInstance();

            /// @brief Helper function to determine if the provided SCOM address correlates to a perv chip unit
            ///               (for both pt or ps, if so creates a list of chipUnitPairing structures which correspond)
            /// @param[in] i_ecLevel            Chip EC level represented in HEX digit value.  Example: i_ecLevel = 0x12 --> EC level 1.2
            /// @param[out] o_chipUnitRelated   Returns true if SCOM address is associated with any chip units
            /// @param[out] o_chipUnitPairing   Collection of chipUnitPairing enums
            /// @param[in] i_mode               Translation mode, specifying different addr translation methods.
            /// @retval uint32_t Return non-zero for error
            void pervChipUnitScom(const uint8_t i_ecLevel,
                                  bool& o_chipUnitRelated,
                                  std::vector<pst_chipUnitPairing_t>& o_chipUnitPairing,
                                  const pstTranslationMode_t i_mode = DEFAULT_MODE);

            /// @brief Determine if this address belongs to EQ target type
            /// @retval true or false.
            bool isEqTarget();

            /// @brief  Determine if this address belongs to per core/L3 resource which scans at EQ chiplet
            /// @retval true or false.
            bool isEQPerSliceRegister();

            /// @brief  Determine if this address belongs to per L3 resource which scans at EQ chiplet
            /// @retval true or false.
            bool isEQPerL3Register();

            /// @brief  Determine if this address belongs to core target type
            /// @retval true or false.
            bool isCoreTarget();

            /// @brief  Determine if this address belongs to L3 target type
            /// @retval true or false.
            bool isL3Target();

            /// @brief  Determine if this address belongs to tbus link target type
            /// @retval true or false.
            bool isTbuslTarget();

            /// @brief  Determine if this address belongs to tbus target type
            /// @retval true or false.
            bool isTbusTarget();

            /// @brief  Determine if this address belongs to PAX target type
            /// @retval true or false.
            bool isPaxTarget();

            /// @brief  Determine if this address belongs to PAXO target type
            /// @retval true or false.
            bool isPaxoTarget();

            /// @brief  Determine if this address belongs to IOHS target type
            /// @retval true or false.
            bool isIohsTarget();

            /// @brief Determine the EQ instance for this address
            /// Function prereq: Address must belong to EQ target type
            /// @retval uint8_t EQ target instance
            uint8_t getEqTargetInstance();

            /// @brief Determine the TBUS link instance for this address
            /// Function prereq: Address must belong to TBUS link target type
            /// @retval uint8_t TBUS link target instance
            uint8_t getTbuslTargetInstance();

            /// @brief Set the group number for the target
            /// Function prereq: Address must belong to TBUSL link target type
            /// @param[in] i_chipUnitNum  The tbusl instance number
            void setTbuslGroup(uint8_t i_chipUnitNum);

            /// @brief Determine the TBUS instance for this address
            /// Function prereq: Address must belong to TBUS target type
            /// @retval uint8_t TBUS target instance
            uint8_t getTbusTargetInstance();

            /// @brief  Determine the core instance for this address.
            /// Function prereq: Address must belong to core target type
            /// @retval uint8_t Core target instance
            uint8_t getCoreTargetInstance();

            /// @brief Get the chiplet ID for a chip unit instance based on
            ///        pst_scom_addr object and chip unit type
            /// @param[in]  i_chipUnitNum   Instance number
            /// @param[in]  i_chipUnitType  Chip unit type
            /// @param[out] o_chipletId     Output chiplet id
            /// @retval Non-zero if error
            uint8_t getChipletId(const uint8_t i_chipUnitNum,
                                 const pstChipUnits_t i_chipUnitType,
                                 uint8_t& o_chipletId);

        private:
            uint64_t iv_addr;   ///< 64-bit raw SCOM address
            pstChipTypes_t iv_chip_type;
    };

} // extern "C"

#endif /* PST_SCOM_ADDR_H */
