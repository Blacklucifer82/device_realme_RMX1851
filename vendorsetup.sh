#!/bin/bash

banner(){
clear
echo "================================"
echo "|                              |"
echo "|   Realme 3 Pro Setup Script  |"
echo "|     Branch: Infinity-15      |"
echo "|    Maintained By: Rishi      |"
echo "|                              |"
echo "================================"
}

banner 2>1

# Kernel
banner 2>1
echo "Cloning Kernel..."
git clone --depth=1 https://github.com/kdrag0n/proton-clang.git prebuilts/clang/host/linux-x86/clang-proton
git clone --depth=1 https://github.com/Cykeek-Labs/kernel_realme_sdm710-RUI2 kernel/realme/sdm710

# vendor
banner 2>1
echo "Cloning vendor and RUI2 firmware..."
git clone https://github.com/Blacklucifer82/android_vendor_RMX1851.git -b 15 vendor/realme/RMX1851
if [ ! -d "vendor/realme/RMX1851-fw" ]; then
    pushd vendor/realme
    mkdir RMX1851-fw
    cd RMX1851-fw
    wget https://github.com/R15Hi/Dump/releases/download/Rui2fw/Rui2fw.zip
    unzip Rui2fw.zip
    rm -rf Rui2fw.zip
    popd
fi
