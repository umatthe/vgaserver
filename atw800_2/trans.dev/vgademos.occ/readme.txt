
Udos OCCAM Demos
----------------

Those are some demo programs I created 1991/92 as part of my
diploma thesis using the TDS2 and TDS3.

I pulled the files from the TDS format using Origami and
converted my old VGA-Server to the ATW800/2. Still the source
is best viewed using Origami. In case You want to try it,
just open TOPLEVEL.TOP in Origami.

Currently I only converted the very basic stuff, so the
VGA.INC contains a lot of things that wont work - I will
clean this up when all I want to carry over is done.

There are mupfel makefiles provided for all demos.

The makefiles with "_A" are to be used in case You only
have the ATW800/2 Card without any extra Transputer.

The other makefiles create code that only runs if You have
an additional TRAM with T800/2MB in Slot 1 of the ATW800/2
installed. Those versions load the VGA-Server to the
ATW800/2 and run the Demo Application on the T800.

In case You have a different setup, have a look at the
*.PGM Files. There is done all the placement of the Code
in the Tranputer network.

To start the demos use "FPGABIOS.TOS" to communicate with the
Transputers. All demos currently need the ATW800/2 to be
set to 1024x768x256.

Udo Matthe, 28.1.2025

