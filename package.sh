#!/usr/bin/env bash
mkdir deploy
cd paper
bash compile.sh
cd ..
cp -r src/ deploy/src/
cp -r inputs/ deploy/inputs/
cp results/result.txt deploy/results.txt
cp paper/paper.pdf deploy/report.pdf
cp CMakeLists.txt LICENSE.txt README.md deploy/
cd deploy
zip -r tree-comparison *
cd ..
mv deploy/tree-comparison.zip .
rm -rf deploy
