
--{{{  Tools for RAWTEXT (Iserver Output)
--
-- Takes a String (ending with #00)
-- Pads it to 32 Bit, take care
-- to add #00000000 at the end
-- and sends it as INTs (needed for VGA-Server RAWTEXT)
--
PROC sendstring(CHAN OF ANY Aus, VAL []BYTE in)
  INT strlen :
  [80]BYTE out :
  SEQ
    strlen := 0
    WHILE in[strlen]<>0(BYTE)
      SEQ
        out[strlen]:=in[strlen]
        strlen := strlen + 1
    [out FROM strlen FOR 8] := "*#00*#00*#00*#00*#00*#00*#00*#00"

    strlen :=((strlen+8)/\#FC)/4
    Aus ! RAWTEXT
    []INT ibuffer RETYPES out :
    SEQ i=0 FOR strlen
      Aus ! ibuffer[i]
:
--}}}

