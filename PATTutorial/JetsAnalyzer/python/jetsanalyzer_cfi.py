import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('JetsAnalyzer',
                      electronTag = cms.untracked.InputTag("selectedLayer1Electrons"),
                      tauTag      = cms.untracked.InputTag("selectedLayer1Taus"),
                      muonTag     = cms.untracked.InputTag("selectedLayer1Muons"),
                      jetTag      = cms.untracked.InputTag("selectedLayer1Jets"),
                      metTag      = cms.untracked.InputTag("selectedLayer1METs")
                      )
