#!/usr/bin/env bash
cd inputs
bash create-inputs.sh
cd ..
rubber --pdf paper.tex
