#!/usr/bin/env bash
# Read-only inspection commands. Nothing here writes to disks.
echo "== lsblk -f =="; lsblk -f
echo; echo "== swapon --show =="; swapon --show || true
echo; echo "== fdisk -l (needs sudo) =="; sudo fdisk -l 2>/dev/null || echo "run with sudo for partition tables"
echo; echo "== df -h =="; df -h
