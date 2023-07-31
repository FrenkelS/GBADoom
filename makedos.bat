call C:\Progs\djgpp\setenv.bat

set CFLAGS=-march=i386 
@rem set CFLAGS=%CFLAGS% -Ofast -flto -fwhole-program -fomit-frame-pointer -funroll-loops -fgcse-sm -fgcse-las -fipa-pta -mpreferred-stack-boundary=2 -Wno-attributes

@set GLOBOBJS=
@set GLOBOBJS=%GLOBOBJS% source\am_map.c
@set GLOBOBJS=%GLOBOBJS% source\d_client.c
@set GLOBOBJS=%GLOBOBJS% source\d_items.c
@set GLOBOBJS=%GLOBOBJS% source\d_main.c
@set GLOBOBJS=%GLOBOBJS% source\doom_iwad.c
@set GLOBOBJS=%GLOBOBJS% source\f_finale.c
@set GLOBOBJS=%GLOBOBJS% source\f_wipe.c
@set GLOBOBJS=%GLOBOBJS% source\g_game.c
@set GLOBOBJS=%GLOBOBJS% source\global_data.c
@set GLOBOBJS=%GLOBOBJS% source\hu_lib.c
@set GLOBOBJS=%GLOBOBJS% source\hu_stuff.c
@set GLOBOBJS=%GLOBOBJS% source\i_audio.c
@set GLOBOBJS=%GLOBOBJS% source\i_main.c
@set GLOBOBJS=%GLOBOBJS% source\i_system.c
@set GLOBOBJS=%GLOBOBJS% source\i_system_dos.c
@set GLOBOBJS=%GLOBOBJS% source\i_video.c
@set GLOBOBJS=%GLOBOBJS% source\info.c
@set GLOBOBJS=%GLOBOBJS% source\lprintf.c
@set GLOBOBJS=%GLOBOBJS% source\m_bbox.c
@set GLOBOBJS=%GLOBOBJS% source\m_cheat.c
@set GLOBOBJS=%GLOBOBJS% source\m_menu.c
@set GLOBOBJS=%GLOBOBJS% source\m_random.c
@set GLOBOBJS=%GLOBOBJS% source\m_recip.c
@set GLOBOBJS=%GLOBOBJS% source\misc_gfx.c
@set GLOBOBJS=%GLOBOBJS% source\p_ceilng.c
@set GLOBOBJS=%GLOBOBJS% source\p_doors.c
@set GLOBOBJS=%GLOBOBJS% source\p_enemy.c
@set GLOBOBJS=%GLOBOBJS% source\p_floor.c
@set GLOBOBJS=%GLOBOBJS% source\p_genlin.c
@set GLOBOBJS=%GLOBOBJS% source\p_inter.c
@set GLOBOBJS=%GLOBOBJS% source\p_lights.c
@set GLOBOBJS=%GLOBOBJS% source\p_map.c
@set GLOBOBJS=%GLOBOBJS% source\p_maputl.c
@set GLOBOBJS=%GLOBOBJS% source\p_mobj.c
@set GLOBOBJS=%GLOBOBJS% source\p_plats.c
@set GLOBOBJS=%GLOBOBJS% source\p_pspr.c
@set GLOBOBJS=%GLOBOBJS% source\p_setup.c
@set GLOBOBJS=%GLOBOBJS% source\p_sight.c
@set GLOBOBJS=%GLOBOBJS% source\p_spec.c
@set GLOBOBJS=%GLOBOBJS% source\p_switch.c
@set GLOBOBJS=%GLOBOBJS% source\p_telept.c
@set GLOBOBJS=%GLOBOBJS% source\p_tick.c
@set GLOBOBJS=%GLOBOBJS% source\p_user.c
@set GLOBOBJS=%GLOBOBJS% source\r_data.c
@set GLOBOBJS=%GLOBOBJS% source\r_draw.c
@set GLOBOBJS=%GLOBOBJS% source\r_hotpath.iwram.c
@set GLOBOBJS=%GLOBOBJS% source\r_main.c
@set GLOBOBJS=%GLOBOBJS% source\r_patch.c
@set GLOBOBJS=%GLOBOBJS% source\r_plane.c
@set GLOBOBJS=%GLOBOBJS% source\r_things.c
@set GLOBOBJS=%GLOBOBJS% source\s_sound.c
@set GLOBOBJS=%GLOBOBJS% source\sounds.c
@set GLOBOBJS=%GLOBOBJS% source\st_gfx.c
@set GLOBOBJS=%GLOBOBJS% source\st_lib.c
@set GLOBOBJS=%GLOBOBJS% source\st_stuff.c
@set GLOBOBJS=%GLOBOBJS% source\tables.c
@set GLOBOBJS=%GLOBOBJS% source\v_video.c
@set GLOBOBJS=%GLOBOBJS% source\version.c
@set GLOBOBJS=%GLOBOBJS% source\w_wad.c
@set GLOBOBJS=%GLOBOBJS% source\wi_stuff.c
@set GLOBOBJS=%GLOBOBJS% source\z_bmalloc.c
@set GLOBOBJS=%GLOBOBJS% source\z_zone.c

gcc %GLOBOBJS% %CFLAGS% -Iinclude -oGBADoom.exe
strip -s GBADoom.exe
stubedit GBADoom.exe dpmi=CWSDPR0.EXE
