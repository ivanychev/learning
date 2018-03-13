#!/usr/bin/env bash
cd ~
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y dist-upgrade
sudo apt-get -y  install htop gcc g++ vim libxrender1 libxrender-dev gfortran build-essential libatlas-dev libatlas3gf-base libsm6 git \
pkg-config libblas3gf libblas-doc libblas-dev liblapack3gf liblapack-doc liblapack-dev libpng-dev libjpeg8-dev libfreetype6-dev
sudo apt-get -y  install python-pip python-dev python-setuptools
sudo apt-get -y  install python3-pip python3-dev python3-setuptools

sudo pip install --upgrade pip
sudo pip3 install --upgrade pip

# wget -c http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
# bash Miniconda3-latest-Linux-x86_64.sh -b -p ~/miniconda
# export PATH=~/miniconda/bin:$PATH
# echo "export PATH=~/miniconda/bin:$PATH" >> ~/.bashrc
# conda install -y numpy scipy pandas scikit-learn jupyter seaborn
# sudo pip3 install xgboost
sudo pip3 install xgboost numpy scipy matplotlib pandas jupyter sklearn seaborn

ipython profile create nbserver
echo "Please, specify password for iPython notebook"
python ~/set_ipy_passwd.py
source hash.txt
mkdir certificates
cd certificates

openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout jupyter.pem -out jupyter.pem

printf "\n# Configuration file for ipython-notebook.\n
c = get_config()\n
# Notebook config\n
c.NotebookApp.ip = '*'\n
c.NotebookApp.password = u'$hash'\n
c.NotebookApp.open_browser = False\n
c.NotebookApp.port = 8888\n" >> ~/.ipython/profile_nbserver/ipython_notebook_config.py

# ipython notebook --config="~/.ipython/profile_nbserver/ipython_notebook_config.py" --certfile=certificates/jupyter.pem
# ipython notebook inline --profile=nbserver
cd ~
rm hash.txt
# export PATH=~/miniconda/bin:$PATH
# echo "export PATH=~/miniconda/bin:$PATH" >> ~/.bashrc
