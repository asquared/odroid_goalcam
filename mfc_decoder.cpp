/*
 * Copyright 2011, 2012, 2013 Exavideo LLC.
 * 
 * This file is part of openreplay.
 * 
 * openreplay is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openreplay is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openreplay.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mfc_decoder.h"

#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdexcept>

#include <stdio.h>
#include <string.h>

MfcDecoder::MfcDecoder(const char *device) : mfc_fd(-1) {
	open_device(device);
	check_device_capabilities( );
}

MfcDecoder::~MfcDecoder( ) {
	if (mfc_fd != -1) {
		close(mfc_fd);
	}
}
	
void MfcDecoder::open_device(const char *device) {
	/* try to open device */
	mfc_fd = open(device, O_RDWR);
	if (mfc_fd == -1) {
		perror("open v4l2 codec device");
		throw std::runtime_error("failed to open codec device");
	}
}

void MfcDecoder::check_device_capabilities( ) {
	/* check if device has the needed capabilities */
	struct v4l2_capability cap;
	memset(&cap, 0, sizeof(cap));
	xioctl(VIDIOC_QUERYCAP, &cap);
	
	if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE) == 0) {
		throw std::runtime_error("no V4L2_CAP_VIDEO_CAPTURE_MPLANE");
	}

	if ((cap.capabilities & V4L2_CAP_VIDEO_OUTPUT_MPLANE) == 0) {
		throw std::runtime_error("no V4L2_CAP_VIDEO_OUTPUT_MPLANE");
	}

	if ((cap.capabilities & V4L2_CAP_STREAMING) == 0) {
		throw std::runtime_error("no V4L2_CAP_STREAMING");
	}
}

void MfcDecoder::xioctl(unsigned long request, void *ptr) {
	if (ioctl(mfc_fd, request, ptr) == -1) {
		perror("ioctl");
		throw std::runtime_error("xioctl failed");
	}
}
