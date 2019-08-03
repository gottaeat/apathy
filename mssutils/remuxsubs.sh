#!/bin/env bash
for file in *.mkv
do
 meme=$(echo $file | sed 's/.mkv//g')
 mkvmerge -o "${meme}-subs.mkv" "${meme}.mkv" --language 0:eng --track-name 0:English "E${meme}".ass	\
  --attachment-mime-type font/sfnt --attach-file '.ttf'							\
  --attachment-mime-type application/vnd.ms-opentype --attach-file '.otf'				&&
 printf "\n\n done with episode $meme.\n\n\n"
done 
