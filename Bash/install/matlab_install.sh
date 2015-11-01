#!/bin/bash

# Concrete MATLAB version with crack installing script
# Image was taken from nnm-club.me
#

if [ $# -eq 0 ]
  then
    echo "Please specify absolute path to folder with matlab and its crack"
fi

cd $1

sudo mkdir /media/iso
sudo mount -o loop $1/R2015a-glnxa64.iso /media/iso/
cd /media/iso
sudo ./install -inputFile installer_input.txt

cd $1
sudo mkdir /usr/local/MATLAB/MATLAB_Production_Server/licenses
sudo cp Standalone\ License.lic /usr/local/MATLAB/MATLAB_Production_Server/licenses/
sudo cp libmwservices.so /usr/local/MATLAB/MATLAB_Production_Server/R2015a/bin/glnxa64/
cd /usr/local/MATLAB/MATLAB_Production_Server/R2015a/bin
sudo ./matlab
