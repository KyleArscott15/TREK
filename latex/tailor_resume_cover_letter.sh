#!/bin/bash

# TODO
#lower privelege of process so it cant delete your own files, after you copy over the resume and cover letter, mkdir and enter the dir, THEN lower privelege

# important script constants
USER="KYLE_ARSCOTT"
CURRENT_DIR=`pwd`
ext=".tex" # can be ".tex" (preferred) or ".docx"
MASTER_DOC_PATH="/home/`whoami`/career/master_documents/"
RESUME_PATH=$MASTER_DOC_PATH"resume/`whoami`/"
COVER_PATH=$MASTER_DOC_PATH"cover_letter/`whoami`/"
year_prefix="20"
year_suffix=`date +%y`
resume_regex="*Resume*$year_prefix$year_suffix*$ext"
cover_regex="*Cover*$year_prefix$year_suffix*$ext"
resume_format=$USER"_Resume"
cover_format=$USER"_Cover_Letter"
magicword_company="COMPANY"
magicword_location="LOCATION"
magicword_job="JOB"
dash="-----------------------------------------------------"

# arg checking
#if [ "$#" -ne 2 ]; then
#    echo $dash
#    echo "Illegal number of parameters, need:"
#    echo "1) company_name"
#    echo "2) job_title"
#    echo $dash
#    echo "Example: $0 intel clerk"
#    exit
#fi
#COMPANY="Intel Corp. Ltd."
#JOB="Worlds Greatest Jr."
#LOCATION="Marhkam ON"
#MKDIR="y"
declare -a arr=("COMPANY" "JOB" "LOCATION")
for i in "${arr[@]}"
do
   read -p "$i": reply
   declare $i="$reply"
done
echo $dash
echo "Using company name     --->" $COMPANY
echo "Using job title        --->" $JOB
echo "Using location         --->" $LOCATION
echo $dash
read -p "Continue? [yn]:" yn
echo $dash
case $yn in
     [Yy]* ) ;;
     [Nn]* ) exit;;
     * ) echo "Please answer yes or no." ;;
esac

declare -a arr=("MKDIR" "CP_RESUME" "CP_COVER" "COMPILE" "INDEED")
for i in "${arr[@]}"
do
   read -p "$i[Y/n]": reply
   declare $i="$reply"
done

if [ "$MKDIR" != "n" ]; then
	DIR=`echo ${COMPANY,,}`
	DIR=`echo $DIR | sed s/" "/"_"/g`
	echo $DIR
	mkdir $DIR
	cd $DIR # BE VERY CAREFUL YOU DONT WANT TO DELETE ANOTHER FOLDER
	CURRENT_DIR=`pwd`
fi

# copy the standard resume and cover letter from master into this folder
u="_"
CP_RESUME="n" # remove this line later when you've made a nice resume
if [ "$CP_RESUME" != "n" ]; then
	cp -v `find $RESUME_PATH -name $resume_regex` $CURRENT_DIR
	chmod a+w *Resume*$ext

	# replace resume and cover letter latex files to include company name
	resume_name=$resume_format$u$COMPANY$u$JOB$u$year_prefix$year_suffix
	resume_name=`echo $resume_name | sed s/" "/"_"/g`
	echo $resume_name$ext
	mv -v *Resume*$ext $resume_name$ext

	# replace all references to COMPANY to the one provided
	sed -i.bak s/$magicword_company/"$COMPANY"/g $resume_name$ext
	sed -i.bak s/$magicword_location/"$LOCATION"/g $resume_name$ext
	sed -i.bak s/$magicword_job/"$JOB"/g $resume_name$ext

	# remove the .bak files created by sed
	rm *$resume_name$ext.bak
fi
if [ "$CP_COVER" != "n" ]; then
	cp -v `find $COVER_PATH -name $cover_regex` $CURRENT_DIR
	chmod a+w *Cover*$ext

	# replace resume and cover letter latex files to include company name
	cover_name=$cover_format$u$COMPANY$u$JOB$u$year_prefix$year_suffix
	cover_name=`echo $cover_name | sed s/" "/"_"/g`
	echo $cover_name$ext
	mv -v *Cover*$ext $cover_name$ext

	# replace all references to COMPANY to the one provided
	sed -i.bak s/$magicword_company/"$COMPANY"/g $cover_name$ext
	sed -i.bak s/$magicword_location/"$LOCATION"/g $cover_name$ext
	sed -i.bak s/$magicword_job/"$JOB"/g $cover_name$ext

	# remove the .bak files created by sed
	rm *$cover_name$ext.bak	
fi

# create the pdfs
if [ "$COMPILE" != "n" ]; then

	TOKEN=0

	if [ "$CP_RESUME" != "n" ]; then
		pdflatex $resume_name$ext
		TOKEN=1
	fi

	if [ "$CP_COVER" != "n" ]; then
		pdflatex $cover_name$ext
		TOKEN=$(($TOKEN+1))
	fi

	# remove latex garbage created during making the pdf
	rm *.aux
	rm *.log
	rm *.out
	
	# hot off the press, open up the new PDFs
	if [ "$TOKEN" -ge 1 ]; then
		ext=".pdf"

		if [ "$CP_RESUME" != "n" ]; then
			xdg-open $resume_name$ext
			WID=`xdotool search "$resume_name$ext" | head -1`
			sleep 1
			echo $WID # blank if it could not find it
			xdotool windowactivate --sync $WID
			xdotool key ctrl+Super+Left
		fi

		if [ "$CP_COVER" != "n" ]; then
			xdg-open $cover_name$ext
			WID=`xdotool search "$cover_name$ext" | head -1`
			sleep 1
			echo $WID # blank if it could not find it
			xdotool windowactivate --sync $WID
			xdotool key ctrl+Super+Right
		fi
	fi

	if [ "$INDEED" != "n" ]; then
		find . -name "*Cover*.pdf" -exec pdftotext {} {}.txt \;
	fi
fi

echo "Done. Exiting."
echo $dash
