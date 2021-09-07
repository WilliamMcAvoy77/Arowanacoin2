// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Arowanacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <arith_uint256.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.

 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Arowanacoin: A Post-Quantum Security Coin";
    const CScript genesisOutputScript = CScript() << ParseHex("0462bca510e911943f4b0dce26040594f924005d505539252c948da65851d8f00996b340c316a543e06db9ccd833351007c2496bf7a9e89f68d035634940a6820b") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network

CBlock(hash=2ab2f920e276f224ed303a7de25ed5c456a20f2004cbda13a4df23d48fecfa43, ver=0x00000001, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=82e04932f2794c9f6e26f1bc3d32e5694c39996bc929f43653476659ca3c19ab, nTime=1623566857, nBits=1f0fffff, nNonce=4771, vtx=1)
  CTransaction(hash=82e04932f2, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01042941726f77616e61636f696e3a204120506f73742d5175616e74756d20536563757269747920436f696e)
    CScriptWitness()
    CTxOut(nValue=1800.00000000, scriptPubKey=410462bca510e911943f4b0dce2604)



 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Exception = uint256S("0x2ab2f920e276f224ed303a7de25ed5c456a20f2004cbda13a4df23d48fecfa43");
        consensus.BIP34Height = 17;
        consensus.BIP34Hash = uint256S("0x");
        consensus.BIP65Height = 0; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 0; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931
        consensus.CSVHeight = 0; // 000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5
        consensus.SegwitHeight = 0; // 0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893
        consensus.MinBIP9WarningHeight = 0; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("0x001fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // 5 day
        consensus.nPowTargetSpacing = 90;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1815; // 90% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x01");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x2ab2f920e276f224ed303a7de25ed5c456a20f2004cbda13a4df23d48fecfa43"); 

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xdd;
        pchMessageStart[3] = 0xbf;
        nDefaultPort = 12631;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 280;
        m_assumed_chain_state_size = 4;

        uint32_t nTime = 1623566857;
        uint32_t nNonce = 4771;
        genesis = CreateGenesisBlock(nTime, nNonce, 0x1f0fffff, 1, 1800 * COIN);


        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x2ab2f920e276f224ed303a7de25ed5c456a20f2004cbda13a4df23d48fecfa43"));
        assert(genesis.hashMerkleRoot == uint256S("0x82e04932f2794c9f6e26f1bc3d32e5694c39996bc929f43653476659ca3c19ab"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("49.51.99.214"); // Pieter Wuille, only supports x1, x5, x9, and xd


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,53);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "aw";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x2ab2f920e276f224ed303a7de25ed5c456a20f2004cbda13a4df23d48fecfa43")},
                { 65238, uint256S("0x4462fc8729fb272ff7f99f5ec190440c87cff3c0e1fecb72a15190ac2f297947")},

            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000000000000005f8920febd3925f8272a6a71237563d78c2edfdd09ddf
            /* nTime    */ 1629710499,
            /* nTxCount */ 70419,
            /* dTxRate  */ 0.01175358655642892,
        };
    }
};

/**
 * Testnet (v3)

CBlock(hash=4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b, ver=0x00000001, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=82e04932f2794c9f6e26f1bc3d32e5694c39996bc929f43653476659ca3c19ab, nTime=1623566957, nBits=1f0fffff, nNonce=529, vtx=1)
  CTransaction(hash=82e04932f2, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01042941726f77616e61636f696e3a204120506f73742d5175616e74756d20536563757269747920436f696e)
    CScriptWitness()
    CTxOut(nValue=1800.00000000, scriptPubKey=410462bca510e911943f4b0dce2604)


 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Exception = uint256S("0x4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b");
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 0; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 0; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 0; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("0x000fffffffffffffffffffffffffffffffffffffffffffffffffffffffff1111");
        consensus.nPowTargetTimespan = 5* 24 * 60 * 60; // 5 days
        consensus.nPowTargetSpacing = 90;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x01");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b"); // 1580000

        pchMessageStart[0] = 0xee;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xb7;
        nDefaultPort = 10831;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 30;
        m_assumed_chain_state_size = 2;



        uint32_t nTime = 1623566957;
        uint32_t nNonce = 529;
        genesis = CreateGenesisBlock(nTime, nNonce, 0x1f0fffff, 1, 1800 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b"));
        assert(genesis.hashMerkleRoot == uint256S("0x82e04932f2794c9f6e26f1bc3d32e5694c39996bc929f43653476659ca3c19ab"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("49.51.99.214"); // Pieter Wuille, only supports x1, x5, x9, and xd


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,120);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tarwn";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;


        checkpointData = {
            {
                {0, uint256S("0x4529e3ddc713630723fe4794e4ef5b4c329d088d36d9a9a4617fd0419a22f39b")},
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000000000b7ab6ce61eb6d571003fbe5fe892da4c9b740c49a07542462d
            /* nTime    */ 0,
            /* nTxCount */ 0,
            /* dTxRate  */ 0,
        };
    }
};


class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 0; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 0; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 1; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 1; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 1;
        consensus.powLimit = uint256S("0x000fffffffffffffffffffffffffffffffffffffffffffffffffffffffff1111");
        consensus.nPowTargetTimespan = 5 * 24 * 60 * 60; 
        consensus.nPowTargetSpacing = 90;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0xd6;
        nDefaultPort = 10931;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);



        uint32_t nTime = 1623566999;
        uint32_t nNonce = 551;

        genesis = CreateGenesisBlock(nTime, nNonce, 0x1f0fffff, 1, 1800 * COIN);


        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xdd697481d6c36497d19129cd1bb9d2f01436039ee17fe11aa93cda67f4c77ecb"));
        assert(genesis.hashMerkleRoot == uint256S("0x82e04932f2794c9f6e26f1bc3d32e5694c39996bc929f43653476659ca3c19ab"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,88);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,125);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rtwn";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
