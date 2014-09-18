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

#ifndef _MFC_DECODER_H
#define _MFC_DECODER_H

/*
 * Decode JPEG images using the MFC.
 */

class MfcDecoder {
	public:
		MfcDecoder(const char *device);
		~MfcDecoder( );

		/* write a chunk of JPEG data */
		//void put_jpeg_frame(JPEGFrame *frame);

		/* grab next decoded frame (if available) */
		//NV12MTFrame *get_decoded_frame( );

	protected:
		int mfc_fd;

		void open_device(const char *device);
		void check_device_capabilities( );

		void xioctl(unsigned long request, void *arg);

		//Queue<JPEGFrame *> coded_frames;
		//Queue<NV12MTFrame *> decoded_frames;
};

#endif
