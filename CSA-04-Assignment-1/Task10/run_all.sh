#!/usr/bin/env bash
# Collect the evidence the report asks for. Run from the repo root on your own Linux/WSL machine.
set -e
OUT=evidence/task10_results.txt
{
echo "== environment =="; gcc --version | head -1; uname -a; nproc; free -h | head -2
echo; echo "== file_copy =="; ( cd Task06 && ./file_copy )
echo; echo "== strace -c file_copy =="; ( cd Task06 && strace -c ./file_copy 2>&1 | tail -15 ) || echo "install strace"
echo; echo "== time -v file_copy =="; ( cd Task06 && /usr/bin/time -v ./file_copy 2>&1 | grep -E "Elapsed|User time|System time|Maximum resident" ) || true
echo; echo "== process vs thread benchmark (run 3 times) =="; for i in 1 2 3; do ./Task10/process_thread_bench; done
} 2>&1 | tee "$OUT"
