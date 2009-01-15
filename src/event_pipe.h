/* the Music Player Daemon (MPD)
 * Copyright (C) 2003-2007 Warren Dukes <warren.dukes@gmail.com>
 * Copyright (C) 2008 Eric Wong <normalperson@yhbt.net>
 *
 * This project's homepage is: http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef EVENT_PIPE_H
#define EVENT_PIPE_H

#include <glib.h>

enum pipe_event {
	/** database update was finished */
	PIPE_EVENT_UPDATE,

	/** during database update, a song was deleted */
	PIPE_EVENT_DELETE,

	/** an idle event was emitted */
	PIPE_EVENT_IDLE,

	/** must call syncPlayerAndPlaylist() */
	PIPE_EVENT_PLAYLIST,

	/** SIGHUP received: reload configuration, roll log file */
	PIPE_EVENT_RELOAD,

	PIPE_EVENT_MAX
};

typedef void (*event_pipe_callback_t)(void);

void event_pipe_init(void);

void event_pipe_deinit(void);

void
event_pipe_register(enum pipe_event event, event_pipe_callback_t callback);

void event_pipe_emit(enum pipe_event event);

/**
 * Similar to event_pipe_emit(), but aimed for use in signal handlers:
 * it doesn't lock the mutex, and doesn't log on error.  That makes it
 * potentially lossy, but for its intended use, that does not matter.
 */
void event_pipe_emit_fast(enum pipe_event event);

#endif /* MAIN_NOTIFY_H */