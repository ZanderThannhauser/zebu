set -ev
ffmpeg \
	-y \
	-r 1 \
	-s 1920x1080 \
	-i 'dot/%d.png' \
	-vf "pad='max(ih*16/9,iw):max(iw*9/16,ih):(ow-iw)/2:(oh-ih)/2':color=white,scale=1920:1080,format=yuv420p'" \
	-vcodec libx264 /tmp/zebu.mp4
