#!/bin/bash

TREK_DIR=~/projects/expert_systems/

cd $TREK_DIR

# prepare to backup on remote MOORE server at mcmaster
MOORE_MOUNTPOINT=~/projects/moore
#sshfs $MOORE: $MOORE_MOUNTPOINT
#sleep 2

BACKUP_DIR_NAME=~/backup/trek/`date +"%b-%d-%H_%M"`
BACKUP_DIR_NAME_REMOTE_SERVER=$MOORE_MOUNTPOINT/backups/trek
echo $BACKUP_DIR_NAME
mkdir $BACKUP_DIR_NAME
cp -vr trek/* $BACKUP_DIR_NAME
cp -vr trek/* $BACKUP_DIR_NAME_REMOTE_SERVER 
