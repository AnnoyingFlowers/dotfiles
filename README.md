AnnoyingFlowers's dotfiles
==========================

The install script will:

1. Back up any existing dotfiles in your home directory to `~/gits/dotfiles/dotfiles_old/`
2. Create symlinks to the dotfiles in `~/gits/dotfiles/` in your home directory

Installation
------------
'''bash
git clone git://github.com/AnnoyingFlowers/dotfiles ~/gits/dotfiles
cd ~/gits/dotfiles
./makesymlinks.sh
'''

How to Add New Files
--------------------
'''bash
mv ~/.bashrc ~/gits/dotfiles/bashrc # remember to REMOVE '.'
cd ~/gits/dotfiles
./makesymlinks.sh
'''
