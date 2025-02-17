-- Alle Befehle, deren Name auf ATTR endet sind GEMVDI-nah programmiert.
-- Sie beruecksichtigen die zum Befehlstyp gehoerenden Attribute in einer
-- Weise, die sehr am VDI orientiert ist!
-- Funktion : NOP (macht nix)
-- AUFRUF   : NOP
VAL NOP IS 0 :
-- Funktion : Graphik initialisieren
-- Aufruf   : INIT;modus;COLOR5
-- Aufruf   : INIT;modus;MEGAEVA
-- Aufruf   : INIT;modus;TO.THE.MAX
-- Aufruf   : INIT;modus;MESSUNG
-- Aufruf   : INIT;modus;VORDEF
-- Antwort  : MAXX;MAXY;MAXCOL;SEITEN
VAL INIT   IS 1 :
VAL COLOR5     IS 0 :
VAL MEGAEVA    IS 1 :
VAL TO.THE.MAX IS 2 :
VAL MESSUNG    IS 3 :
VAL VORDEF     IS 4 :
PROTOCOL INITP IS INT;INT :
PROTOCOL INITANTWP IS INT;INT;INT;INT :

-- Funktion : Information ueber die moeglichen Graphikmodi einholen
-- Aufruf   : SERVERINFO;modus
-- Antwort  : falls modus=BINGINFO : anzmodi;MAXX;MAXY;MAXCOL;SEITEN;
--                                   farbtiefe;maxpunkte(PFILL)
--                                   ...fuer alle Modi
--            falls modus=TEXTGINFO: anzmodi;Texterklaerung;Letzter String=#00
--                  Texterklaerung besteht aus strlaenge(INT)::text([]BYTE)
--                  Letzter String besteht aus #01(INT)::#00(BYTE)
--            falls modus=ANZGINFO : anzmodi
--            falls modus=BINTINFO(TEXTTINFO,ANZTINFO) wie oben fuer Textmodi
VAL SERVERINFO IS 2 :
PROTOCOL INFOP IS INT :
VAL ANZGINFO  IS 0:
VAL TEXTGINFO IS 1:
VAL BINGINFO  IS 2:
VAL ANZTINFO  IS 3:
VAL TEXTTINFO IS 4:
VAL BINTINFO  IS 5:

--Funktion: exit (Server beenden)
--Aufruf: EXIT
--Antwort: keine
VAL EXIT IS 3:

--Funktion: start timer
--Aufruf: TSTART
--Antwort: keine
VAL TSTART IS 4:

--Funktion: stop timer
--Aufruf: TSTOP
--Antwort: Dauer
VAL TSTOP IS 5:
PROTOCOL TSTOPANTWP IS REAL32 :

VAL RAWTEXT IS 6:
VAL GETVTGREG IS 7:
VAL GETVERREG IS 8:
VAL GETPALREG IS 9:
VAL GETBLTREG IS 10:
VAL SETVTGREG IS 11:
VAL GETKEY IS 20:
VAL POLKEY IS 21:
VAL SAVE IS 30:
VAL RESTORE IS 31:

-- Funktion : Angezeigte Bildschirmseite waehlen
-- Aufruf   : PHYSPAGE;seite
-- Antwort  : keine
VAL PHYSPAGE IS 100 :

-- Funktion : Seite, auf welche die Graphikbefehle wirken waehlen
-- Aufruf   : LOGPAGE;seite
-- Antwort  : keine
VAL LOGPAGE  IS 101 :
PROTOCOL PAGEP IS INT :

-- Funktion : Bildschirm invertieren
-- Aufruf   : INV
-- Antwort  : keine
VAL INV    IS 110 :

-- Funktion : Schattenbildschirm aktivieren (Graphikbef. wirken auf Schatten)
-- Aufruf   : SCHATTENON
-- Antwort  : keine
VAL SCHATTENON IS 120 :

-- Funktion : Schattenbildschirm abschalten (Graphikbef. wirken auf Bildschirm)
-- Aufruf   : SCHATTENOFF
-- Antwort  : keine
VAL SCHATTENOFF IS 121 :

-- Funktion : Schattenbildschirm mit Graphikschirm mischen
-- Aufruf   : COPYSCHATTEN;DECKEND;farbe
-- Aufruf   : COPYSCHATTEN;TRANSPARENT;farbe
-- Aufruf   : COPYSCHATTEN;INVERTIEREND;farbe
-- Antwort  : keine
VAL COPYSCHATTEN IS 122 :
PROTOCOL SCHATTENP IS INT;INT :
-- Funktion : Farbpaletteneintrag setzen
-- Aufruf   : SETPAL;nr;r;g;b
-- Antwort  : keine
VAL SETPAL    IS 200:
PROTOCOL PALP IS INT :

-- Funktion : Farpaletteneintrag lesen
-- Aufruf   : GETPAL;nr
-- Antwort  : r;g;b
VAL GETPAL    IS 201 :
PROTOCOL GPALP IS INT :
PROTOCOL GPALANTWP IS INT :

-- Funktion : Farbnummer einem Paletteneintrag zuordnen
-- Aufruf   : PALDACP;farbnummer;eintragnummer
-- Antwort  : keine
VAL PALDAC    IS 210 :
PROTOCOL PALDACP IS INT;INT :

-- Funktion : Farbpalette endlos Rotieren (Achtung Endlosschleife !!)
-- Aufruf   : DACROT
-- Antwort  : keine
VAL DACROT    IS 220 :

-- Funktion : Bildschirm loeschen
-- Aufruf   : CLS
-- Antwort  : keine
VAL CLS    IS 300 :

-- Funktion : Bildschirm mit Muster bzw. Farbe ueberschreiben
-- Aufruf   : MUSTER;muster
-- Antwort  : keine
VAL MUSTER IS 301 :
PROTOCOL MUSTERP IS INT :

-- Funktion : Clippingwindow loeschen
-- Aufruf   : CLSWIN
-- Antwort  : keine
VAL CLSWIN IS 310 :

-- Funktion : Bildschirm nach oben verschieben
-- Aufruf   : SCRUP
-- Antwort  : keine
VAL SCRUP IS 320 :
-- Funktion : Sprite definieren
-- Aufruf   : DEFSPRITE;nr;daten1;..daten32;maske1;..maske32;xhot;yhot
-- Antwort  : keine
VAL DEFSPRITE IS 400 :
PROTOCOL DEFSPRITEP IS INT;[32]INT;[32]INT;INT;INT :

-- Funktion : setzte Spritemodus
-- Aufruf   : SPRITEMODE;NICHT.SICHERN
-- Aufruf   : SPRITEMODE;SICHERN
-- Antwort  : keine
VAL SPRITEMODE IS 410 :
PROTOCOL SPRITEMODEP IS INT :
VAL NICHT.SICHERN IS 0 :
VAL SICHERN IS 1 :

-- Funktion : Sprite auf Bildschirm positionieren
-- Aufruf   : DRAWSPRITE;x;y;nr
-- Antwort  : keine
VAL DRAWSPRITE IS 420 :
PROTOCOL DRAWSPRITEP IS INT;INT;INT :

-- Funktion : Sprite vom Bildschirm loeschen
-- Aufruf   : UNDRAWSPRITE;nr
-- Antwort  : keine
VAL UNDRAWSPRITE IS 421 :
PROTOCOL UNDRAWSPRITEP IS INT :
-- Funktion : Punkt setzen
-- Aufruf   : POINT;xkoor;ykoor;farbe
-- Antwort  : keine
VAL POINT  IS 500 :
PROTOCOL POINTP IS INT;INT;INT :

-- Funktion : Punkt - Farbe auslesen
-- Aufruf   : GETPOINT;xkoor;ykoor
-- Antwort  : farbe
VAL GETPOINT  IS 501 :
PROTOCOL GPOINTP IS INT;INT :
PROTOCOL GPOINTANTWP IS INT :
-- Funktion : Linie ziehen (LINENC ohne Clipping)
-- Aufruf   : LINE;xkoor1;ykoor1;xkoor2;ykoor2;farbe
-- Antwort  : keine
VAL LINE   IS 600 :
VAL LINENC IS 601 :
PROTOCOL LINEP IS INT;INT;INT;INT;INT :

-- Funktion : Horizontale Linie ziehen
-- Aufruf   : HLINE;xkoor1;xkoor2;ykoor;farbe
-- Antwort  : keine
VAL HLINE  IS 610 :
PROTOCOL HLINEP IS INT;INT;INT;INT :

-- Funktion : Polyline ziehen  (mit und ohne Fuellung)
-- Aufruf :   PLINE;anzpkt;farbe;xkoor1;ykoor1;xkoor2;ykoor2;...f. alle Pkte
-- Aufruf :   PLINEVOLL;anzpkt;.... wie oben
-- Aufruf :   PLINEATTR;anzpkt;.... wie oben (Beachtet VDI-nahe Attribute)
-- Antwort:   keine
VAL PLINE IS 620 :
VAL PLINEVOLL IS 621 :
VAL PLINEATTR IS 630 :

-- Funktion : Zeichnet Kreis
-- Aufruf   : CIRCLE;xmittel;ymittel;radius;color
-- Antwort  : keine
VAL CIRCLE IS 640 :
VAL CIRCLEATTR IS 641 :
PROTOCOL CIRCLEP IS INT;INT;INT;INT :

-- Funktion : Zeichnet Ellipse
-- Aufruf   : ELIPSE;xmittel;ymittel;radiusx;radiusy;color
-- Antwort  : keine
VAL ELIPSE IS 645 :
VAL ELIPSEATTR IS 646 :
PROTOCOL ELIP IS INT;INT;INT;INT;INT :

-- Funktion : Kreisbogen zeichnen
-- Aufruf   : ARC;xmittel;ymittel;radius;startw (0..3600);endw (0..3600);farbe
-- Aufruf   : ARCATTR;xmittel;ymittel;radius;startw(*10);endw(*10);farbe
-- Antwort  : keine
VAL ARC IS  650 :
VAL ARCATTR IS 651 :
PROTOCOL ARCP IS INT;INT;INT;INT;INT;INT :

-- Funktion : Ellipsenbogen zeichnen
-- Aufruf   : ELARC;xmit;ymit;radx;rady;startw (0..3600);endw (0..3600);farbe
-- Aufruf   : ELARCATTR;xmit;ymit;radx;rady;startw(*10);endw(*10);farbe
-- Antwort  : keine
VAL ELARC IS 655 :
VAL ELARCATTR IS 656 :
PROTOCOL ELARCP IS INT;INT;INT;INT;INT;INT;INT :

-- Funktion : Rechteck mit Abrundung zeichnen
-- Aufruf   : RBOX;xlinks;yunten;xrechts;yoben;col
-- Antwort  : keine
VAL RBOX IS 660 :
PROTOCOL BOXP IS INT;INT;INT;INT;INT :
-- Funktion : gefuellte, polygonbegrenzte Flaechen
-- Aufruf :   PFILL;anzpkt;farbe;xkoor1;ykoor1;xkoor2;ykoor2
-- Aufruf :   PFILLVOLL;anzpkt;.... wie oben
-- Aufruf :   PFILLATTR;anzpkt;.... wie oben
-- Antwort:   keine
VAL PFILL IS 700 :
VAL PFILLVOLL IS 701 :
VAL PFILLATTR IS 702 :

-- Funktion : Zeichnet gefuellten Kreis
-- Aufruf   : DISC;xmittel;ymittel;radius;color
-- Aufruf   : DISCVOLL;xmittel;ymittel;radius;color
-- Antwort  : keine
-- Protokoll: CIRCLEP
VAL DISC IS 710 :
VAL DISCVOLL IS 711 :
VAL DISCATTR IS 712 :

-- Funktion : Zeichnet gefuellte Ellipse
-- Aufruf   : ELDISC;xmittel;ymittel;radiusx;radiusy;color
-- Antwort  : keine
-- Protokoll: ELIP
VAL ELDISC IS 720 :
VAL ELDISCATTR IS 722 :

-- Funktion : Kreissegment zeichnen
-- Aufruf   : PIE;xmittel;ymittel;radius;startw (0..3600);endw (0..3600);farbe
-- Antwort  : keine
-- Protokoll: ARCP
VAL PIE IS 730 :
VAL PIEATTR IS 732 :

-- Funktion : Ellipsensegment zeichnen
-- Aufruf   : ELPIE;xmit;ymit;radx;rady;startw (0..3600);endw (0..3600);farbe
-- Antwort  : keine
-- Protokoll: ELARCP
VAL ELPIE IS 740 :
VAL ELPIEATTR IS 742 :

-- Funktion : Gefuelltes Rechteck zeichnen
-- Aufruf   : BOX;xmin;ymin;xmax;ymax;farbe
-- Antwort  : keine
VAL BOX IS 750 :
VAL RECFL IS 751 :
VAL BAR IS 752 :
VAL RFBOX IS 753 :

-- Funktion : Umrandung fuellen
-- Aufruf   : FILL;xkoor;ykoor
-- Antwort  : keine
VAL FILL IS 760 :
-- Funktion : Font laden
-- Aufruf   : LOADFONT;startasc;endasc;stdzellhoehe;stdzellbreite
--                    ;topskip;halfskip;baseskip;underskip
--                    ;kursivheit;kursivoffsetlinks;kursivoffsetrechts
--                    ;lightheit;fettheit;unterstrichdicke
--                    ;zellbreiteN;zeichenhoeheN;zeichenbreiteN
--                    ;celltopskipN;cellleftskipN;bitimageN
-- Antwort  : keine !
VAL LOADFONT IS 1100 :

-- Funktion : Einzelzeichen ausgeben
-- Aufruf   : CHAROUT;asc;x;y;color
-- Antwort  : keine !
VAL CHAROUT IS 1101 :
PROTOCOL CHAROUTP IS INT;INT;INT;INT :

-- Funktion : Textstring mit Attributen (alle) ausgeben
-- Aufruf   : TEXTOUT;x;y;color;strlen;intstream...
-- Antwort  : keine !
VAL TEXTOUT IS 1110 :

-- Funktion : Textstring ohne Attribute ausgeben  (Udos Quick-Text)
-- Aufruf   : QTEXTOUT;x;y;color;strlen;intstream...
-- Antwort  : keine !
VAL QTEXTOUT IS 1120 :


-- Funktion : Clipping-Window festlegen
-- Aufruf   : SETCLIPWIN;winminx;winminy;winmaxx;winmaxy
-- Antwort  : keine
VAL SETCLIPWIN IS 800 :
PROTOCOL CLIPWINP IS INT;INT;INT;INT :

-- Funktion : setzte Linienmaske
-- Aufruf   : SETLINMASK;maske
-- Antwort  : keine
VAL SETLINMASK IS 810 :
PROTOCOL LINMASKP IS INT :

-- Funktion : setzte Linienmodus
-- Aufruf   : SETLINMODE;DECKEND
--            SETLINMODE;TRANSPARENT
--            SETLINMODE;INVERTIEREND
-- Antwort  : keine
VAL SETLINMODE IS 811 :
PROTOCOL LINMODEP IS INT :
VAL DECKEND      IS 0:
VAL TRANSPARENT  IS 1:
VAL INVERTIEREND IS 2:
VAL SCHATTEN     IS 4:

-- Funktion : setzte Linienbreite
-- Aufruf   : SETLINBREIT;breite
-- Antwort  : keine
VAL SETLINBREIT IS 812 :
PROTOCOL LINBREITP IS INT :

-- Funktion : setzte Endenstile
-- Aufruf   : SETLINENDS;startstil;endstil
-- Antwort  : keine
VAL SETLINENDS IS 813 :
PROTOCOL LINENDSP IS INT;INT :
VAL KANTE IS 0 :
VAL PFEIL IS 1 :
VAL RUNDUNG IS 2 :

-- Funktion : Fuellmodus setzen
-- Aufruf   : SETFILLMODE;fuellstil
-- Antwort  : keine
VAL SETFILLMODE IS 820 :
PROTOCOL FILLMODEP IS INT :
VAL SOLID.HINTERGRUND IS 0 :
VAL SOLID.VORDERGRUND IS 1 :
VAL MUSTER.EINFARBIG IS 2 :
VAL MUSTER.MONOFARBIG IS 3 :  -- wg. VDI-Naehe effektiv gleich MUSTER.EINFARBIG
VAL MUSTER.MEHRFARBIG IS 4 :

-- Funktion : Fuellmuster setzen
-- Aufruf   : SETMUSMASK;zeile1;zeile2;..zeile32
-- Antwort  : keine
VAL SETMUSMASK IS 821 :
PROTOCOL MUSMASKP IS [32]INT :

-- Funktion : einfarbiges Fuellmuster setzen (VDI-gemaess allerdings 16*16-Bit)
-- Aufruf   : SETMONOPATTERN;zeile1;..;zeile16
-- Antwort  : keine
VAL SETMONOPATTERN IS 822 :
PROTOCOL MONOPATTERNP IS [16]INT :

-- Funktion : (bis zu 32bittiges) Fuellmuster setzen (auch 16*16-Bit)
-- Aufruf   : SETCOLORPATTERN;planeanzahl;zeile1;..;zeile16;zeile16;...
-- Antwort  : keine
VAL SETCOLORPATTERN IS 823 :
PROTOCOL COLORPATTERNP IS INT;[16][16]INT :

-- Funktion : Ein bzw. Ausschalten der Umrandung beim Polygonfuellen
-- Aufruf   : SETPFILLMODE;MIT.RAND
-- Aufruf   : SETPFILLMODE;OHNE.RAND
-- Antwort  : keine
VAL SETPFILLMODE IS 825 :
VAL SETPERIMETER IS 826 :
VAL OHNE.RAND IS 0 :
VAL MIT.RAND  IS 1 :
PROTOCOL FILLMODEP IS INT :
PROTOCOL PERIMETERP IS INT :

-- Funktion : Texteffekte waehlen
-- Aufruf   : SETTEXTEFFECTS;EFFECTS
-- Antwort  : keine
VAL SETTEXTEFFECTS IS 830 :
PROTOCOL TEXTEFFECTSP IS INT :
VAL EFF.NORMAL IS 0 :
VAL EFF.FETT IS 1 :
VAL EFF.HELL IS 2 :
VAL EFF.KURSIV IS 4 :
VAL EFF.UNTERSTRICHEN IS 8 :
VAL EFF.OUTLINE IS 16 :

-- Funktion : Zellengroesse vorgeben (ermoeglicht Vergroesserung/-kleinerung)
-- Aufruf   : SETCELLSIZE;CELLSTDHEIGHT;CELLSTDWIDTH
-- Antwort  : keine
VAL SETCELLSIZE IS 831 :
PROTOCOL CELLSIZEP IS INT;INT :

-- Funktion : Rotationswinkel in 10-tel Grad
-- Aufruf   : SETTEXTROT;ROTATION
-- Antwort  : keine
VAL SETTEXTROT IS 832 :
PROTOCOL TEXTROTP IS INT :

-- Funktion : Horizontale und vertikale Ausrichtung der Textausgabe festlegen
-- Aufruf   : SETTEXTALIGN;HORIZONTAL;VERTIKAL
-- Antwort  : keine
VAL SETTEXTALIGN IS 840 :
PROTOCOL TEXTALIGNP IS INT;INT :
VAL HOR.LINKSBUENDIG IS 0 :
VAL HOR.ZENTRIERT IS 1 :
VAL HOR.RECHTSBUENDIG IS 2 :
VAL VER.BASISLINIE IS 0 :
VAL VER.HALBLINIE IS 1 :
VAL VER.ZEICHENOBERKANTE IS 2 :
VAL VER.ZELLENUNTERKANTE IS 3 :
VAL VER.ZEICHENUNTERKANTE IS 4 :
VAL VER.ZELLENOBERKANTE IS 5:

-- Funktion : Art des Blocksatzes fuer die Textausgabe festlegen
-- Aufruf   : SETTEXTJUSTIF;BLOCKSATZCODE;TEXTPIXELLAENGE
-- Antwort  : keine
VAL SETTEXTJUSTIF IS 841 :
PROTOCOL TEXTJUSTIFP IS INT;INT :
VAL BLOCKSATZ.AUS IS 0 :
VAL BLOCKSATZ.ZEICHEN.SPACED IS 1 :
VAL BLOCKSATZ.WORT.SPACED IS 2 :
VAL BLOCKSATZ.KOMBI.SPACED IS 3 :

-- Funktion : Text initialisieren
-- Aufruf   : TINIT;modus
-- Antwort  : SPALTEN;ZEILEN;MAXCOL;SEITEN
VAL TINIT   IS 900 :
PROTOCOL TINITP IS INT :
PROTOCOL TINITANTWP IS INT;INT;INT;INT :

-- Funktion : Test des Textmodus  (Achtung Endlosschleife)
-- Aufruf   : TTEST
-- Antwort  : keine
VAL TTEST IS 901 :

-- Funktion : Ueberschreibt Bildschirminhalt mit Daten vom Link
-- Aufruf   : DUMMSERV;32000 Byte - Daten
-- Antwort  : keine
VAL DUMMSERV IS 910 :

-- Funktion : Bildschirm ausdrucken (Centronics Karte noetig z.B. Herkules
--                                   oder Multi I/O)
-- Aufruf   : HARDCOPY;DITHER
-- Aufruf   : HARDCOPY;MONOCHROM
-- Antwort  : keine
VAL HARDCOPY IS 920 :
PROTOCOL HARDCOPYP IS INT :
VAL DITHER    IS 0 :
VAL MONOCHROM IS 1:

-- Funktion : Beschreibt PC-IO Register
-- Aufruf   : PCIOOUT;ADRMODE;Adresse;Wert
-- Aufruf   : PCIOOUT;SEQUENZER;Index;Wert
-- Aufruf   : PCIOOUT;CRT;Index;Wert
-- Aufruf   : PCIOOUT;ATTRIBUT;Index;Wert
-- Aufruf   : PCIOOUT;GRAPHIK;Index;Wert
-- Aufruf   : PCIOOUT;DAC;Index;Wert
-- Antwort  : keine
VAL PCIOOUT IS #FFFFFF01 :
PROTOCOL PCIOOUTP IS INT;INT;INT :
VAL ADRMODE   IS 0 :
VAL SEQUENZER IS 1 :
VAL CRT       IS 2 :
VAL ATTRIBUT  IS 3 :
VAL GRAPHIK   IS 4 :
VAL DAC       IS 5 :

-- Funktion : Beschreibt PC-IO Register
-- Aufruf   : PCIOIN;ADRMODE;Adresse
-- Aufruf   : PCIOIN;SEQUENZER;Index
-- Aufruf   : PCIOIN;CRT;Index
-- Aufruf   : PCIOIN;ATTRIBUT;Index
-- Aufruf   : PCIOIN;GRAPHIK;Index
-- Aufruf   : PCIOIN;DAC;Index
-- Antwort  : Der Wert des Registers
VAL PCIOIN IS #FFFFFF02 :
PROTOCOL PCIOINP IS INT;INT :

-- Funktion : Ermittelt die Bildwiederholrate
-- Aufruf   : GETRATE
-- Antwort  : Bildwiederholrate in Hz
VAL GETRATE IS #FFFFFF03 :
PROTOCOL GETRATEP IS INT :

-- Funktion : Gibt die verfuegbaren Pixelraten aus
-- Aufruf   : FREQINFO
-- Antwort  : Pixelrate1 , ... , Pixelrate8
VAL FREQINFO IS #FFFFFF04 :
PROTOCOL FREQINFOP IS [24]INT :
--PROTOCOL FREQINFOP IS INT;INT;INT;INT;INT;INT;INT;INT :
-- Funktion : Wartet bis zum naechsten Bildaufbau (vertikal Blank)
-- Aufruf   : SEITENEU
-- Antwort  : keine
VAL SEITENEU IS 1000 :

-- Funktion : Melde wenn letzter Befehl im Puffer abgearbeitet ist
-- Aufruf   : SYNC
-- Antwort  : 1 , wenn Puffer leer
VAL SYNC IS 1010 :
PROTOCOL SYNCP IS INT :

-- Funktion : Fuell-Befehl (darf beliebig zwischen den Befehlen stehen)
--            wird einfach ueberlesen
-- Aufruf   : FUELL
-- Antwort  : keine
VAL FUELL   IS #FFFFFFFF :
