#!/bin/bash
cd /home/louis/gits/ysyx
git switch master
git merge pa2
git push origin master pa2
git switch pa2
cd ./ysyx-workbench
git switch master
git merge pa2
git push backup master pa2
git switch pa2
cd ./am-kernels
git switch master
git merge pa2
git push backup master pa2
git switch pa2
