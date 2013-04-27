# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/FecSoftwareV3_0
# export LD_LIBRARY_PATH
export FEC_TYPE=vme
# export FEC_TYPE=pci
if [ "$FEC_TYPE" == "pci" ]; then
  export FEC_ADDRESS=0
  export RING_ADDRESS=0
  export FEC_FLAGS=-pci
elif [ "$FEC_TYPE" == "vme" ]; then
  #
  # CCS_6 board in vme slot #6
  export FEC_ADDRESS=6
  export FEC_FLAGS0="-vmecaenpci -fec $FEC_ADDRESS -ring 0"
  export FEC_FLAGS1="-vmecaenpci -fec $FEC_ADDRESS -ring 1"
  export FEC_FLAGS2="-vmecaenpci -fec $FEC_ADDRESS -ring 2"
  export FEC_FLAGS3="-vmecaenpci -fec $FEC_ADDRESS -ring 3"
  export FEC_FLAGS4="-vmecaenpci -fec $FEC_ADDRESS -ring 4"
  export FEC_FLAGS5="-vmecaenpci -fec $FEC_ADDRESS -ring 5"
  # aliases
  export FEC_FLAGS=$FEC_FLAGS0
  export FEC_FLAGS_RBp1near=$FEC_FLAGS0
  export FEC_FLAGS_RBp1far=$FEC_FLAGS3
  export FEC_FLAGS_RBp2near=$FEC_FLAGS1
  export FEC_FLAGS_RBp2far=$FEC_FLAGS2
  export FEC_FLAGS_RB0near=$FEC_FLAGS4
  export FEC_FLAGS_RB0far=$FEC_FLAGS5
  # 
  # CCS_5 board in vme slot #5
  export FEC2_ADDRESS=5
  export FEC2_FLAGS0="-vmecaenpci -fec $FEC2_ADDRESS -ring 0"
  export FEC2_FLAGS1="-vmecaenpci -fec $FEC2_ADDRESS -ring 1"
  export FEC2_FLAGS2="-vmecaenpci -fec $FEC2_ADDRESS -ring 2"
  export FEC2_FLAGS3="-vmecaenpci -fec $FEC2_ADDRESS -ring 3"
  export FEC2_FLAGS4="-vmecaenpci -fec $FEC2_ADDRESS -ring 4"
  export FEC2_FLAGS5="-vmecaenpci -fec $FEC2_ADDRESS -ring 5"
  # aliases
  export FEC_FLAGS_RBn1near=$FEC2_FLAGS0
  export FEC_FLAGS_RBn1far=$FEC2_FLAGS1
  export FEC_FLAGS_RBn2near=$FEC2_FLAGS2
  export FEC_FLAGS_RBn2far=$FEC2_FLAGS3
  export FEC_FLAGS_REp1near=$FEC2_FLAGS4
  export FEC_FLAGS_REp1far=$FEC2_FLAGS5
  # 
  # CCS_4 board in vme slot #4
  export FEC3_ADDRESS=4
  export FEC3_FLAGS0="-vmecaenpci -fec $FEC3_ADDRESS -ring 0"
  export FEC3_FLAGS1="-vmecaenpci -fec $FEC3_ADDRESS -ring 1"
  export FEC3_FLAGS2="-vmecaenpci -fec $FEC3_ADDRESS -ring 2"
  export FEC3_FLAGS3="-vmecaenpci -fec $FEC3_ADDRESS -ring 3"
  export FEC3_FLAGS4="-vmecaenpci -fec $FEC3_ADDRESS -ring 4"
  export FEC3_FLAGS5="-vmecaenpci -fec $FEC3_ADDRESS -ring 5"
  # aliases
  export FEC_FLAGS_REp3near=$FEC3_FLAGS0
  export FEC_FLAGS_REp3far=$FEC3_FLAGS1
  export FEC_FLAGS_REn1near=$FEC3_FLAGS2
  export FEC_FLAGS_REn1far=$FEC3_FLAGS3
  export FEC_FLAGS_REn3near=$FEC3_FLAGS4
  export FEC_FLAGS_REn3far=$FEC3_FLAGS5
fi

export CCU_ADDRESS=0x50
#export FECSOFTWARE_ROOT=$HOME/FecSoftwareV3_0
source $FECSOFTWARE_ROOT/cvs_profile
  
