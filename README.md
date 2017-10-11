# Atari 2600 Boxing clone for the Game Boy (Color)

gbc-atari-boxing is a kind of clone of the popular Atari 2600 Boxing game developed by Activision in 1980.

![gbc-atari-boxing](https://github.com/rubfi/gbc-atari-boxing/blob/master/resources/boxing.png)

The code of this Game Boy clone is just a simple aproximation to the original game. It was developed while learning to program Game Boy games in February 2001.

## Building

First, you need to install the SDK ([GBDK](https://sourceforge.net/projects/gbdk/files/)). Once GBDK is intalled, clone or download this repository, and execute the next compiler commands in your local copy of the repository.

    export PATH=$PATH:/opt/gbdk/bin/

    lcc -c back_t.c back_m.c back_p.c player.c
    lcc boxing.c -Wl-yp0x143=0xC0 -o Boxing.gbc back_t.o back_m.o back_p.o player.o

This will generate Boxing.gbc file.

### Tiles/Maps
In order to generate the map and the tiles [GBTD](http://www.devrs.com/gb/hmgd/gbtd.html) and [GBMB](http://www.devrs.com/gb/hmgd/gbmb.html) were used. GBTD and GBMB are not required for bulding he game, but you can use them if you want to modify the map and the sprites.

## Try it

Boxing.gbc file can be loaded to [higan](https://gitlab.com/higan/higan) or any other GBC emulator.

You can play it online in [http://taisel.github.io/GameBoy-Online/](http://taisel.github.io/GameBoy-Online/), just [download Boxing.gbc](https://raw.githubusercontent.com/rubfi/gbc-atari-boxing/master/resources/Boxing.gbc) or build your on, and open it in "File >> Open As >> Local File".