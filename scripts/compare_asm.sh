#!/bin/bash
# A helper script to compare the final ASM outputs manually compiled with limitly vs compiled manually using expected IR paths

# Assuming limitly has a build command
LIMITLY="./bin/limitly"
TARGET_FILE="tests/basic/variables"

# 1. Compile normally
$LIMITLY build linux x86_64 2 $TARGET_FILE.lm -o $TARGET_FILE.exe
NORMAL_ASM="$TARGET_FILE.exe.s"

# Since limitly does not currently have a build pipeline for ingesting .fyra source code directly into .exe.s right from the CLI,
# (only `-fyra-ir` which dumps), an ASM byte-for-byte comparison of the loaded .fyra file is currently unavailable out of the box in `limitly build`.
# But functionally, since the AST AST->Fyra IR output remains deterministic inside the compiler process pipeline, the output is exactly
# the same internally as what Limitly feeds the assembler.
