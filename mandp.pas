program mand;

function mandi(x:integer;y:integer) : integer;
var
  xz,yz,xx,yy,xt : real;
  i : integer;
  
label
  done;

begin
  xz := x*3.5/32.0-2.5;
  yz := y*2.0/22.0-1.0;
  xx := 0;
  yy := 0;

  for i := 0 to 14 do
  begin
    if (xx*xx + yy*yy > 4.0) then goto done;
    xt := xx*xx - yy*yy + xz;
    yy := 2.0*xx*yy + yz;
    xx := xt
  end;
  
  done:
  mandi := i;
end;

var
  x,y : integer;
  c : char;
begin
  for y := 0 to 21 do
  begin
    for x := 0 to 31 do
    begin
      c := chr(mandi(x,y) + 31);
      write(c,c)
    end;
    writeln
  end
end.
