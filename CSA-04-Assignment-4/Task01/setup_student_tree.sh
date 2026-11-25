#!/usr/bin/env bash
# Builds the /srv/student-data/<cohort>/<register>/{home,assignments,projects} layout
# inside a local demo directory (no root needed). Change BASE to /srv/student-data on a real server.
set -euo pipefail
BASE="${1:-./demo_student_data}"
COHORT="${2:-2024}"
REGS=(192524301 192524302 192524303)
for r in "${REGS[@]}"; do
  d="$BASE/$COHORT/$r"
  mkdir -p "$d"/{home,assignments,projects}
  chmod 0700 "$d" "$d/home"            # private owner-controlled
  chmod 0750 "$d/assignments"          # staff group may read
done
mkdir -p "$BASE/$COHORT/_shared_projects"
chmod 2770 "$BASE/$COHORT/_shared_projects"   # setgid: group collaboration
echo "Layout created under $BASE:"; find "$BASE" -maxdepth 3 -type d | sort
echo; echo "Permissions:"; ls -ld "$BASE/$COHORT"/* "$BASE/$COHORT/${REGS[0]}"/*
cat <<'NOTE'

On a real server also configure (examples, run as root, adjust names):
  setfacl -m g:staff:rx  <dir>                # explicit staff read access
  setquota -u <user> 5G 6G 0 0 /srv           # per-student quota
  sha256sum <file> > <file>.sha256            # integrity checksum
  # snapshots + off-host backups + restore tests are required
NOTE
