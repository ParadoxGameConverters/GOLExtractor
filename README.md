# GOLExtractor
Garment Of Limbs Extractor

This tool does its *darndest* to craft flags using CK3's garment of limbs definitions from Crusader Kings III\game\common\coat_of_arms\coat_of_arms\01_landed_titles.txt, (barring PDX errors in those definitions).
It will use realated named_colors (barring more PDX errors) and emblems (barring even more PDX errors) to craft .tga files of the same name (eg. b_avignon.tga).

It will **not**, at this stage, delve into PDXMath inside garment definitions (such as `@[1/3]`), but it will substitute regular hardcoded macros (eg. `@smCastleX = 0.27`) within loaded defs.

Input folder is wherever steam put CK3, and if it detects none, then running directory (where you unpacked it).
Export folder is `export` folder.
