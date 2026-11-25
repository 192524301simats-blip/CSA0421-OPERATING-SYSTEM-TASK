#!/usr/bin/env bash
# Read-only filesystem metadata collection. Saves nothing destructive.
T="${1:-.}"
echo "== stat =="; stat "$T"
echo; echo "== df -i (inodes) =="; df -i "$T"
echo; echo "== df -h =="; df -h "$T"
echo; echo "== ls -i =="; ls -i "$T" | head -10
echo; echo "== findmnt -T =="; findmnt -T "$T"
echo; echo "== lsblk -f =="; lsblk -f
DEV="$(findmnt -n -o SOURCE -T "$T")"
echo; echo "== block size =="; stat -f -c 'block size: %S bytes, total blocks: %b, free blocks: %f' "$T"
echo; echo "== tune2fs -l (only if ext*, needs sudo) =="
if [ "$(findmnt -n -o FSTYPE -T "$T")" = "ext4" ] || [ "$(findmnt -n -o FSTYPE -T "$T")" = "ext3" ]; then
  sudo tune2fs -l "$DEV" 2>/dev/null | grep -E 'Inode count|Block size|Free blocks|Filesystem features' || echo "need sudo/ext device"
else echo "not ext on $DEV - skipped"; fi
