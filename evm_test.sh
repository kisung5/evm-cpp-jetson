#!/bin/sh

rm -rf ./Results

echo "Testing results!"

# Color Magnification
./evm-cpp-linux ./vid/baby2.mp4 0 150 6 140/60 160/60 30 1
./evm-cpp-linux ./vid/face.mp4 0 50 4 50/60 60/60 30 1
./evm-cpp-linux ./vid/face2.mp4 0 50 6 50/60 60/60 30 1

# Motion Magnification
# Butter
./evm-cpp-linux ./vid/baby.mp4 1 30 16 0.4 3 30 0.1
./evm-cpp-linux ./vid/camera.mp4 1 150 20 45 100 300 0
./evm-cpp-linux ./vid/subway.mp4 1 60 90 3.6 6.2 30 0.3
./evm-cpp-linux ./vid/wrist.mp4 1 30 16 0.4 3.0 30 0.1
./evm-cpp-linux ./vid/shadow.mp4 1 5 48 0.5 10 30 0
./evm-cpp-linux ./vid/face2.mp4 1 20 80 0.5 10 30 0
# Ideal
./evm-cpp-linux ./vid/guitar.mp4 2 50 10 72 92 600 0
./evm-cpp-linux ./vid/guitar.mp4 2 100 10 100 120 600 0