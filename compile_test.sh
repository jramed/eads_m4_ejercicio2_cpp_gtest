#!/bin/bash

cd Testing
make
cd ..
./Testing/AnalizarNoticiasLinux_test --gtest_output=xml:gtestresults.xml
