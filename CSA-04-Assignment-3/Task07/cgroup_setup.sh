#!/usr/bin/env bash
# Example cgroup v2 limits for ML and logger (run as root on a Linux target; adjust paths).
set -e
CG=/sys/fs/cgroup
echo +memory > $CG/cgroup.subtree_control 2>/dev/null || true
mkdir -p $CG/ml $CG/logger
echo 1300M > $CG/ml/memory.max
echo 1200M > $CG/ml/memory.high
echo 64M   > $CG/logger/memory.max
echo "Move a PID in with: echo <PID> > $CG/ml/cgroup.procs"
