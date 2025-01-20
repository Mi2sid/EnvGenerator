#!/bin/bash

# Nom de l'exécutable
EXE="EnvGenerator"

echo "Launching Application..."

if ! cd build; then
    echo "Error: 'build' directory not found. Please run CMake first."
    exit 1
fi

make -j$(nproc) || { echo "Compilation failed"; exit 1; }

cd ..

./build/$EXE
echo "Application launched successfully"
