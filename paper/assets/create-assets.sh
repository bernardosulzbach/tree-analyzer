#!/usr/bin/env bash
cp ../../results/result.txt .
python3 ../../scripts/extract-data.py result.txt
Rscript ../../scripts/make-graphs.R
rm result.txt
rm *.csv
